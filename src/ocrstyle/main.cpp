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

#include <QtGui>
#include <QTimer>
#include <QLocale>
#include <QTranslator>
#include <QTextCodec>
#include <QSplashScreen>
#include <QStyleFactory>
#include <QtGui/QApplication>
#include "MainWindow.h"
#include "Config.h"
#include "PageSegModes.h"

QString translatorLanguageFilename();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/Images/images/ocrstyle.png"));

    //QSplashScreen *splash = new QSplashScreen(QPixmap(":/Images"), Qt::WindowStaysOnTopHint);
    //splash->show();

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QTranslator translator;
    translator.load(translatorLanguageFilename(), ":/Languages/translations");
    app.installTranslator(&translator);

    MainWindow mainWindow;
    mainWindow.showMaximized();
    mainWindow.show();
    
    //QTimer::singleShot(2000, splash, SLOT(close()));

    return app.exec();
}

QString translatorLanguageFilename()
{
    Config config;
    config.read();

    QString language = config.language();
    if (language.isEmpty())
    {
        language = QLocale::system().name();
        config.setLanguage(language);
        config.setOcrLanguage("eng");
        config.setOcrPageSegMode(PSM_AUTO);
        config.write();
    }

    return QString("ocrstyle_") + language;
}
