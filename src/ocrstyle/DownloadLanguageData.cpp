// Copyright 2013, Zaoqibu Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Zaoqibu Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: vwarship@163.com (Junjian Wang)
//
// The Optical Character Recognition (OCR Style)

#include "DownloadLanguageData.h"
#include <QtGui>
#include <QtNetwork>
#include "OCRLanguages.h"
#include "MainWindow.h"
#include "ZlibWrapper.h"

DownloadLanguageData::DownloadLanguageData(QWidget *parent)
    : QDialog(parent), reply(0), file(0)
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(createOCRLanguages());
    topLayout->addLayout(createControlButtons());

    progressBar = new QProgressBar(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(progressBar);
    setLayout(mainLayout);

    setWindowTitle(tr("Download OCR Language Data"));
}

QWidget* DownloadLanguageData::createOCRLanguages()
{
    ocrLanguagesItemModel = new QStandardItemModel(this);
    createOCRLanguagesItemModel();

    ocrLanguagesListView = new QListView(this);
    ocrLanguagesListView->setModel(ocrLanguagesItemModel);
    ocrLanguagesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ocrLanguagesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(enableDownloadButton(QModelIndex)));

    QGroupBox *groupBox = new QGroupBox(tr("OCR Languages"), this);
    QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBox);
    groupBoxLayout->addWidget(ocrLanguagesListView);
    groupBox->setLayout(groupBoxLayout);

    return groupBox;
}

void DownloadLanguageData::createOCRLanguagesItemModel()
{
    ocrLanguagesItemModel->clear();
    OCRLanguages ocrLanguages;

    QSettings settings("tessdata/tessdata.ini", QSettings::IniFormat);
    settings.beginGroup("tessdata");
    QStringList languageAliases = settings.allKeys();
    printf("%d\n", languageAliases.count());
    foreach (QString languageAlias, languageAliases)
    {
        QString url = settings.value(languageAlias).toString();
        QString languageName = ocrLanguages.name(languageAlias);
        if (languageName.isEmpty())
            continue;

        QStandardItem *item = new QStandardItem(languageName);
        item->setData(url);

        if (isExistOCRLanguages(languageAlias))
        {
            item->setData("");
            item->setBackground(Qt::green);
            item->setEnabled(false);
        }

        ocrLanguagesItemModel->appendRow(item);
    }
    settings.endGroup();
}

bool DownloadLanguageData::isExistOCRLanguages(QString languageAlias)
{
    QStringList availableOCRLanguages = MainWindow::availableOCRLanguages();
    foreach (QString language, availableOCRLanguages)
    {
        if (language == languageAlias)
            return true;
    }

    return false;
}

QLayout* DownloadLanguageData::createControlButtons()
{
    downloadButton = new QPushButton(tr("Download"));
    downloadButton->setDefault(true);
    downloadButton->setEnabled(false);
    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(false);
    cancelButton->setEnabled(false);
    quitButton = new QPushButton(tr("Close"));
    quitButton->setAutoDefault(false);

    connect(downloadButton, SIGNAL(clicked()), this, SLOT(downloadFile()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelDownload()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(closeWindow()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(downloadButton);
    layout->addWidget(cancelButton);
    layout->addStretch(1);
    layout->addWidget(quitButton);

    return layout;
}

void DownloadLanguageData::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void DownloadLanguageData::downloadFile()
{
    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    if (QFile::exists(fileName))
        QFile::remove(fileName);

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }

    ocrLanguagesListView->setEnabled(false);
    downloadButton->setEnabled(false);
    cancelButton->setEnabled(true);

    // schedule the request
    httpRequestAborted = false;
    startRequest(url);
}

void DownloadLanguageData::cancelDownload()
{
    //statusLabel->setText(tr("Download canceled."));
    httpRequestAborted = true;
    reply->abort();
    ocrLanguagesListView->setEnabled(true);
    downloadButton->setEnabled(true);
    cancelButton->setEnabled(false);
}

void DownloadLanguageData::closeWindow()
{
    if (reply)
        cancelDownload();
    close();
}

void DownloadLanguageData::httpFinished()
{
    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        reply = 0;
        progressBar->setValue(0);
        return;
    }

    file->flush();
    file->close();

    ZlibWrapper zw;
    zw.uncompress(file->fileName().toLocal8Bit().data());
    createOCRLanguagesItemModel();

    ocrLanguagesListView->setEnabled(true);
    cancelButton->setEnabled(false);

    //QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file->remove();
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(reply->errorString()));
        downloadButton->setEnabled(true);
    } else {
        //QString fileName = QFileInfo(QUrl(url).path()).fileName();
        //statusLabel->setText(tr("Downloaded %1 to %2.").arg(fileName).arg(QDir::currentPath()));
        downloadButton->setEnabled(false);
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void DownloadLanguageData::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());
}

void DownloadLanguageData::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        return;

    progressBar->setMaximum(totalBytes);
    progressBar->setValue(bytesRead);
}

void DownloadLanguageData::enableDownloadButton(QModelIndex modelIndex)
{
    QString url = ocrLanguagesItemModel->itemFromIndex(modelIndex)->data().toString();
    downloadButton->setEnabled(!url.isEmpty());
    this->url = url;
}
