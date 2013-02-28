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

#include <algorithm>
#include <QtGui>
#include "MainWindow.h"
#include "ImageView.h"
#include "Languages.h"
#include "OCRLanguages.h"
#include "Config.h"
#include "OCRThread.h"
#include "OCREngineAgent.h"
#include "ImageDeskew.h"
#include "ImageProcessAgent.h"
#include "PageSegModes.h"
#include "DownloadLanguageData.h"

const QString MainWindow::m_screenshotFilename("screenshot.jpg");

MainWindow::MainWindow()
    : m_ocrEngineAgent(new OCREngineAgent())
{
    setCentralWidgetWithImageView();
    initProgressDialog();

    createActions();
    createMenus();
    createToolbars();
    createStatusBar();
    createDockWindows();

    setWindowTitle("OCR Style");
}

MainWindow::~MainWindow()
{
    delete m_ocrEngineAgent;
}

void MainWindow::setCentralWidgetWithImageView()
{
    imageView = new ImageView();

    setCentralWidget(imageView);
}

void MainWindow::initProgressDialog()
{
    progressDlg = new OCRProgressDialog(this, Qt::SplashScreen);

    progressDlg->setRange(0, 0);
    progressDlg->setWindowModality(Qt::WindowModal);
    progressDlg->setWindowTitle(tr("Please Wait"));
    progressDlg->setLabelText(tr("Optical Character Recognition......"));
    progressDlg->setCancelButton(0);
    progressDlg->setMinimumWidth(300);
    progressDlg->setCursor(Qt::WaitCursor);
}

void MainWindow::createActions()
{
    createFileActions();
    createViewActions();
    createAdjustmentActions();
    createOcrActions();
    createLangActions();
    createWindowActions();
    createHelpActions();
}

void MainWindow::createFileActions()
{
    //scanAction = new QAction(tr("Scan(&N)..."), this);
    //scanAction->setIcon(createIcon("scan"));
    //scanAction->setShortcut(QKeySequence::New);
    //scanAction->setEnabled(false);
    //connect(scanAction, SIGNAL(triggered()), this, SLOT(scan()));

    openAction = new QAction(tr("Open(&O)..."), this);
    openAction->setIcon(createIcon("open"));
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    screenshotAction = new QAction(tr("Screenshot(&X)..."), this);
    screenshotAction->setIcon(createIcon("screenshot"));
    screenshotAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_X);
    connect(screenshotAction, SIGNAL(triggered()), this, SLOT(screenshot()));

    saveAction = new QAction(tr("Save(&S)..."), this);
    saveAction->setIcon(createIcon("save"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setEnabled(false);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    printAction = new QAction(tr("Print(&P)..."), this);
    printAction->setIcon(createIcon("print"));
    printAction->setShortcut(QKeySequence::Print);
    printAction->setEnabled(false);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    exitAction = new QAction(tr("Exit(&Q)"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

QIcon MainWindow::createIcon(const QString &filename) const
{
    QIcon icon;
    icon.addFile(QString(":/Images/images/16/")+ filename + ".png", QSize(16, 16));
    icon.addFile(QString(":/Images/images/32/")+ filename + ".png", QSize(32, 32));

    return icon;
}

void MainWindow::createViewActions()
{
    zoomInAction = new QAction(tr("Zoom In"), this);
    zoomInAction->setIcon(createIcon("zoom_in"));
    zoomInAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Equal));
    zoomInAction->setEnabled(false);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAction = new QAction(tr("Zoom Out"), this);
    zoomOutAction->setIcon(createIcon("zoom_out"));
    zoomOutAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    zoomOutAction->setEnabled(false);
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

    zoomToWindowAction = new QAction(tr("Fit To Screen"), this);
    zoomToWindowAction->setIcon(createIcon("zoom_to_window"));
    zoomToWindowAction->setEnabled(false);
    zoomToWindowAction->setShortcut(Qt::CTRL | Qt::Key_0);
    connect(zoomToWindowAction, SIGNAL(triggered()), this, SLOT(zoomToWindow()));

    resetZoomAction = new QAction(tr("Actual Size"), this);
    resetZoomAction->setIcon(createIcon("reset_zoom"));
    resetZoomAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_0);
    resetZoomAction->setEnabled(false);
    connect(resetZoomAction, SIGNAL(triggered()), this, SLOT(resetZoom()));
}

void MainWindow::createAdjustmentActions()
{
    deskewAction = new QAction(tr("Deskew"), this);
    //deskewAction->setIcon(createIcon("deskew"));
    connect(deskewAction, SIGNAL(triggered()), this, SLOT(deskew()));

    grayscaleAction = new QAction(tr("Grayscale"), this);
    //grayscaleAction->setIcon(createIcon("grayscale"));
    connect(grayscaleAction, SIGNAL(triggered()), this, SLOT(grayscale()));
}

void MainWindow::deskew()
{
    imageView->setCursor(Qt::WaitCursor);
    imageDeskew();
    loadImage();
    imageView->unsetCursor();
}

void MainWindow::grayscale()
{
    imageView->setCursor(Qt::WaitCursor);
    imageGrayscale();
    loadImage();
    imageView->unsetCursor();
}

void MainWindow::createOcrActions()
{
    ocrAction = new QAction(tr("Character Recognition"), this);
    ocrAction->setIcon(createIcon("ocr"));
    ocrAction->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(ocrAction, SIGNAL(triggered()), this, SLOT(ocr()));

    downloadOCRLanguageDataAction = new QAction(tr("Download Language Data..."), this);
    connect(downloadOCRLanguageDataAction, SIGNAL(triggered()), this, SLOT(downloadOCRLanguageData()));
}

void MainWindow::createLangActions()
{
}

void MainWindow::createWindowActions()
{
}

void MainWindow::createHelpActions()
{
    aboutAction = new QAction(tr("About(&A)"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    createFileMenus();
    createViewMenus();
    createAdjustmentMenus();
    createOcrMenus();
    createLanguageMenus();
    createWindowMenus();
    createHelpMenus();
}

void MainWindow::createFileMenus()
{
    fileMenu = new QMenu(tr("File(&F)"), this);
    //fileMenu->addAction(scanAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(screenshotAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addMenu(fileMenu);
}

void MainWindow::createViewMenus()
{
    viewMenu = new QMenu(tr("View(&V)"), this);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(zoomToWindowAction);
    viewMenu->addAction(resetZoomAction);

    menuBar()->addMenu(viewMenu);
}

void MainWindow::createAdjustmentMenus()
{
    adjustmentMenu = new QMenu(tr("Adjustments(&A)"), this);
    adjustmentMenu->addAction(deskewAction);
    adjustmentMenu->addAction(grayscaleAction);

    menuBar()->addMenu(adjustmentMenu);
}

void MainWindow::createOcrMenus()
{
    ocrMenu = new QMenu(tr("OCR(&O)"), this);
    ocrMenu->addAction(ocrAction);
    ocrMenu->addAction(downloadOCRLanguageDataAction);

    createOcrLanguagesMenu();
    createOcrPageSegModesMenu();
}

void MainWindow::createOcrLanguagesMenu()
{
    ocrLanguagesMenu = new QMenu(tr("Languages(&L)"));
    ocrMenu->addMenu(ocrLanguagesMenu);

    menuBar()->addMenu(ocrMenu);

    ocrLanguagesActionGroup = new QActionGroup(this);
    connect(ocrLanguagesActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(selectedOcrLanguage(QAction*)));

    updateOCRLanguagesAction();
}

void MainWindow::updateOCRLanguagesAction()
{
    ocrLanguageActions.clear();
    ocrLanguagesMenu->clear();
    ocrLanguagesActionGroup->actions().clear();

    Config config;

    QStringList availableLanguages = availableOCRLanguages();
    OCRLanguages ocrLanguages;
    for (int i=0; i<availableLanguages.size(); ++i)
    {
        QString languageAlias = availableLanguages[i];
        QString languageName = ocrLanguages.name(languageAlias);
        if (languageName.isEmpty())
            continue;

        QAction *action = new QAction(tr("%1").arg(languageName), this);
        action->setCheckable(true);
        action->setData(languageAlias);

        ocrLanguageActions[i] = action;

        ocrLanguagesMenu->addAction(action);
        ocrLanguagesActionGroup->addAction(action);

        if (languageAlias == config.ocrLanguage())
        {
            action->setChecked(true);
        }
    }
}

QStringList MainWindow::availableOCRLanguages()
{
    const QString path("./tessdata");
    QStringList languages;

    QDir dir(path);
    dir.setFilter(QDir::Files);
    QFileInfoList fileInfoList = dir.entryInfoList();

    QRegExp regExp("(.*).traineddata");
    foreach (QFileInfo fileInfo, fileInfoList)
    {
        QString filename = fileInfo.fileName();
        if (filename.indexOf(regExp) >= 0)
        {
            languages.push_back(regExp.cap(1));
        }
    }

    return languages;
}

void MainWindow::selectedOcrLanguage(QAction* action)
{
    QString lang = action->data().toString();

    Config config;
    config.setOcrLanguage(lang);
    config.write();

    ocrLanguagesComboBox->setCurrentIndex( findSelectedOcrLanguageIndex(action) );

    m_ocrEngineAgent->init(lang.toLocal8Bit().data());
    m_ocrEngineAgent->setPageSegMode(config.ocrPageSegMode());
}

int MainWindow::findSelectedOcrLanguageIndex(QAction* action)
{
    foreach (QAction* ocrLanguageAction, ocrLanguageActions.values())
    {
        if (action == ocrLanguageAction)
            return ocrLanguageActions.key(ocrLanguageAction);
    }

    return 0;
}

void MainWindow::createOcrPageSegModesMenu()
{
    ocrPageSegModesMenu = new QMenu(tr("Page Layout Analysis"));
    ocrMenu->addMenu(ocrPageSegModesMenu);

    ocrPageSegModesActionGroup = new QActionGroup(this);
    connect(ocrPageSegModesActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(selectedOcrPageSegMode(QAction*)));

    Config config;

    PageSegModes pageSegModes;
    QMap<PageSegMode, QString> pageSegModeMap = pageSegModes.pageSegModes();
    foreach (PageSegMode pageSegMode, pageSegModeMap.keys())
    {
        QAction *action = new QAction(pageSegModeMap[pageSegMode], this);
        action->setCheckable(true);
        action->setData(pageSegMode);

        ocrPageSegModesMenu->addAction(action);
        ocrPageSegModesActionGroup->addAction(action);

        if (pageSegMode == config.ocrPageSegMode())
        {
            action->setChecked(true);
        }
    }
}

void MainWindow::selectedOcrPageSegMode(QAction* action)
{
    PageSegMode pageSegMode = static_cast<PageSegMode>(action->data().toInt());

    Config config;
    config.setOcrPageSegMode(pageSegMode);
    config.write();

    m_ocrEngineAgent->setPageSegMode(pageSegMode);
}

void MainWindow::createLanguageMenus()
{
    Config config;

    languagesMenu = new QMenu(tr("Languages(&L)"), this);
    languagesActionGroup = new QActionGroup(this);
    connect(languagesActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(selectedLanguage(QAction*)));

    Languages languages;
    int count = languages.size();
    for (int i=0; i<count; ++i)
    {
        Language language = languages.item(i);
        QAction *action = new QAction(tr("%1").arg(language.name()), this);
        action->setCheckable(true);
        action->setData(language.alias());

        languagesMenu->addAction(action);
        languagesActionGroup->addAction(action);

        if (language.alias() == "en" ||
            language.alias() == config.language())
        {
            action->setChecked(true);
        }
    }

    menuBar()->addMenu(languagesMenu);
}

void MainWindow::selectedLanguage(QAction* action)
{
    QString langLocalName = action->data().toString();

    Config config;
    config.setLanguage(langLocalName);
    config.write();

    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void MainWindow::createWindowMenus()
{
    windowMenu = new QMenu(tr("Window(&W)"), this);
    menuBar()->addMenu(windowMenu);
}

void MainWindow::createHelpMenus()
{
    helpMenu = new QMenu(tr("Help(&H)"), this);
    helpMenu->addAction(aboutAction);

    menuBar()->addMenu(helpMenu);
}

void MainWindow::createToolbars()
{
    moveImageToolButton = createToolButton(tr("Move Image"), "move_image");
    moveImageToolButton->setCheckable(true);
    moveImageToolButton->setChecked(true);
    rectSelectionToolButton = createToolButton(tr("Rectangular Selection"), "rect_selection");
    rectSelectionToolButton->setCheckable(true);

    pointerTypeButtonGroup = new QButtonGroup(this);
    pointerTypeButtonGroup->addButton(moveImageToolButton, int(ptMove));
    pointerTypeButtonGroup->addButton(rectSelectionToolButton, int(ptSelection));
    connect(pointerTypeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(pointerGroupClicked(int)));

    toolbar = addToolBar("OCR Style Toolbar");
    //toolbar->addAction(scanAction);
    toolbar->addAction(openAction);
    toolbar->addAction(screenshotAction);
    toolbar->addSeparator();
    toolbar->addAction(saveAction);
    toolbar->addAction(printAction);
    toolbar->addSeparator();
    toolbar->addWidget(moveImageToolButton);
    toolbar->addWidget(rectSelectionToolButton);
    toolbar->addSeparator();
    toolbar->addAction(zoomInAction);
    toolbar->addAction(zoomOutAction);
    toolbar->addAction(zoomToWindowAction);
    toolbar->addAction(resetZoomAction);
    toolbar->addSeparator();
    toolbar->addAction(ocrAction);
    toolbar->addWidget(new QLabel(tr(" OCR Languages ")));

    ocrLanguagesComboBox = new QComboBox(toolbar);
    connect(ocrLanguagesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedOcrLanguageWithIndex(int)));
    toolbar->addWidget(ocrLanguagesComboBox);

    updateOCRLanguagesComboBox();
}

void MainWindow::updateOCRLanguagesComboBox()
{
    ocrLanguagesComboBox->clear();

    if (ocrLanguageActions.size())
    {
        int currentSelectedOcrLanguageIndex = findCurrentSelectedOcrLanguageIndex();
        foreach (QAction* ocrLanguageAction, ocrLanguageActions.values())
        {
            ocrLanguagesComboBox->addItem(ocrLanguageAction->text());
        }

        ocrLanguagesComboBox->setCurrentIndex(currentSelectedOcrLanguageIndex);
    }
}

int MainWindow::findCurrentSelectedOcrLanguageIndex()
{
    foreach (QAction* ocrLanguageAction, ocrLanguageActions.values())
    {
        if (ocrLanguageAction->isChecked())
            return ocrLanguageActions.key(ocrLanguageAction);
    }

    return 0;
}

void MainWindow::selectedOcrLanguageWithIndex(int curIndex)
{
    if (ocrLanguageActions.contains(curIndex))
    {
        ocrLanguageActions[curIndex]->setChecked(true);
        selectedOcrLanguage(ocrLanguageActions[curIndex]);
    }
}

void MainWindow::pointerGroupClicked(int pointerType)
{
    if (pointerType == ptMove)
        imageView->setMoveImageWithCurrentState(true);
    else if (pointerType == ptSelection)
        imageView->setMoveImageWithCurrentState(false);
}

QToolButton* MainWindow::createToolButton(const QString &text, const QString &iconFilename)
{
    QToolButton *toolButton = new QToolButton(this);
    toolButton->setText(text);
    toolButton->setIcon(createIcon(iconFilename));
    toolButton->setCheckable(true);

    return toolButton;
}

void MainWindow::createStatusBar()
{
    statusBar()->addWidget(new QLabel(""));
}

void MainWindow::createDockWindows()
{
    createDockWindowWithOcrResult();
}

void MainWindow::createDockWindowWithOcrResult()
{
    QDockWidget *dock = new QDockWidget(tr("OCR Result"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    ocrResultWindow = new QTextEdit(dock);
    dock->setWidget(ocrResultWindow);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    windowMenu->addAction(dock->toggleViewAction());
}

void MainWindow::scan()
{
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),
        "All Files (*.jpg;*.jpeg;*.jpe;*.jfif;*.tif;*.tiff;*.png;*.gif);;JPEG (*.jpg;*.jpeg;*.jpe;*.jfif);;TIFF (*.tif;*.tiff);;PNG (*.png);;GIF (*.gif)");

    if (!filename.isEmpty())
    {
        m_filename = filename;
        loadImage();
    }
}

void MainWindow::loadImage()
{
    QImage image(m_filename);
    if (image.isNull())
    {
        QMessageBox::information(this, "OCR Style", tr("Can not be loaded %1.").arg(m_filename));
        return;
    }

    _pixmap = QPixmap::fromImage(image, 0);
    showImage(_pixmap);
}

void MainWindow::imageDeskew()
{
    ImageProcessAgent imageProcessAgent;
    if (imageProcessAgent.LoadImage(m_filename))
    {
        QString tmpFilename("tmp.jpg");

        imageProcessAgent.Deskew();
        imageProcessAgent.Save(tmpFilename);

        m_filename = tmpFilename;
    }
}

void MainWindow::imageGrayscale()
{
    ImageProcessAgent imageProcessAgent;
    if (imageProcessAgent.LoadImage(m_filename))
    {
        QString tmpFilename("tmp.jpg");

        imageProcessAgent.TransformToGrayscale();
        imageProcessAgent.Save(tmpFilename);

        m_filename = tmpFilename;
    }
}

void MainWindow::screenshot()
{
    hide();
    QTimer::singleShot(0, this, SLOT(onTimerScreenshot()));
}

class Sleep : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

void MainWindow::onTimerScreenshot()
{
    while(true)
    {
        if (isHidden())
        {
            qApp->beep();
            Sleep::msleep(500);

            _pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
            saveScreenshot(_pixmap);
            showImage(_pixmap);
            show();

            break;
        }

        Sleep::msleep(0);
    }
}

void MainWindow::saveScreenshot(QPixmap &pixmap)
{
    m_filename = m_screenshotFilename;
    pixmap.save(m_filename, "JPG");
}

void MainWindow::showImage(const QPixmap &pixmap)
{
    imageView->showImage(pixmap);

    printAction->setEnabled(true);
    zoomToWindowAction->setEnabled(true);
    updateActions();

    if (!zoomToWindowAction->isChecked())
    {
        zoomToWindow();
    }
}

void MainWindow::save()
{
    QFileDialog fileDlg(this);
    QString fileName = fileDlg.getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("Text (*.txt)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly))
        {
            QTextStream textStream(&file);
            textStream.setCodec("utf-8");
            textStream << ocrResultWindow->toPlainText();
            file.close();
        }
    }
}

void MainWindow::print()
{
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);
    if (dialog.exec())
    {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = _pixmap.rect().size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(_pixmap.rect());
        painter.drawPixmap(0, 0, _pixmap);
    }
#endif
}

void MainWindow::zoomIn()
{
    imageView->zoomIn();
}

void MainWindow::zoomOut()
{
    imageView->zoomOut();
}

void MainWindow::resetZoom()
{
    imageView->resetZoom();
}

void MainWindow::zoomToWindow()
{
    double viewWidth = imageView->width();
    double viewHeight = imageView->height();
    double imageWidth = _pixmap.width();
    double imageHeight = _pixmap.height();
    double widthScaleFactor = imageWidth / viewWidth;
    double heightScaleFactor = imageHeight / viewHeight;

    double maxScaleFactor = std::max(widthScaleFactor, heightScaleFactor);
    double minScaleFactor = std::min(widthScaleFactor, heightScaleFactor);
    double scaleFactor = maxScaleFactor/minScaleFactor;

    if (widthScaleFactor < heightScaleFactor)
        imageView->fitInView(0, 0, imageWidth*scaleFactor, imageHeight);
    else
        imageView->fitInView(0, 0, imageWidth, imageHeight*scaleFactor);
}

void MainWindow::setOcrResult(QString text)
{
    progressDlg->close();
    ocrResultWindow->setText(text);

    saveAction->setEnabled(!text.isEmpty());
}

void MainWindow::ocr()
{
    OCRThread *ocrThread = new OCRThread(m_ocrEngineAgent, selectedRectImageFilename());
    connect(ocrThread, SIGNAL(ocrResult(QString)), this, SLOT(setOcrResult(QString)));
    ocrThread->start(QThread::NormalPriority);

    progressDlg->show();
    progressDlg->exec();
}

QString MainWindow::selectedRectImageFilename()
{
    if (imageView->isSelectedRect())
        return ImageView::m_selectedRectImageFilename;

    return m_filename;
}

void MainWindow::downloadOCRLanguageData()
{
    DownloadLanguageData *downloadLanguageData = new DownloadLanguageData(this);
    downloadLanguageData->exec();

    updateOCRLanguagesAction();
    updateOCRLanguagesComboBox();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About %1").arg("OCR Style"),
            tr("%1"
               "<p>Copyright @ 2013 Junjian Wang.</p>"
               "<p>All Rights Reserved.</p>").arg("<p><b>OCR Style 1.0</b></p><p><a href='https://github.com/vwarship/ocrstyle/'>https://github.com/vwarship/ocrstyle/</a></p><p>Email: <a href='mailto:vwarship@163.com'>vwarship@163.com</a></p>"));
}

void MainWindow::updateActions()
{
    zoomInAction->setEnabled(!zoomToWindowAction->isChecked());
    zoomOutAction->setEnabled(!zoomToWindowAction->isChecked());
    resetZoomAction->setEnabled(!zoomToWindowAction->isChecked());
}
