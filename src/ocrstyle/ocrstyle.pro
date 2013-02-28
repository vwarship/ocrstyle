# Copyright 2013, Zaoqibu Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Zaoqibu Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Author: vwarship@163.com (Junjian Wang)
#
# The Optical Character Recognition (OCR Style)

QT       += core gui network

TARGET = ../../../bin/ocrstyle
TEMPLATE = app

DEFINES += ZLIB_WINAPI

INCLUDEPATH += ../../include \
    ../../third-party/tesseract/include \
    ../../third-party/zlib \
    ../../third-party/zlib/contrib/minizip

SOURCES += main.cpp\
    RubberBand.cpp \
    MainWindow.cpp \
    ImageView.cpp \
    Language.cpp \
    Languages.cpp \
    Config.cpp \
    OCREngineAgent.cpp \
    ImageDeskew.cpp \
    ImageProcessAgent.cpp \
    PageSegModes.cpp \
    DownloadLanguageData.cpp \
    ZlibWrapper.cpp \
    OCRLanguages.cpp \
    OCRThread.cpp

HEADERS  += \
    RubberBand.h \
    MainWindow.h \
    ImageView.h \
    Language.h \
    Languages.h \
    Config.h \
    OCREngineAgent.h \
    StringUtil.h \
    ImageDeskew.h \
    ImageProcessAgent.h \
    PageSegModes.h \
    DownloadLanguageData.h \
    ZlibWrapper.h \
    OCRThread.h \
    OCRLanguages.h

FORMS    +=

RESOURCES += \
    ocrstyle.qrc

win32 {
    RC_FILE = ocrstyle.rc
    LIBS += ../../lib/ocrengine.lib \
        ../../lib/imageprocess.lib \
        ../../lib/zlibwapi.lib
}

CODECFORTR  = UTF-8
CODECFORSRC = UTF-8
TRANSLATIONS = translations/ocrstyle_en.ts \
        translations/ocrstyle_zh_CN.ts
#        translations/ocrstyle_zh_TW.ts\
#        translations/ocrstyle_es.ts\
#        translations/ocrstyle_fr.ts\
#        translations/ocrstyle_de.ts\
#        translations/ocrstyle_it.ts\
#        translations/ocrstyle_ja.ts\
#        translations/ocrstyle_ko.ts\
#        translations/ocrstyle_ru.ts\
#        translations/ocrstyle_nl.ts\
#        translations/ocrstyle_pt.ts

