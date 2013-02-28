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

#include "OCREngineAgent.h"
#include "OCREngineAPI.h"
#include <QImage>

OCREngineAgent::OCREngineAgent()
{
    m_initState = false;
    m_ocrEngine = NewOCREngine();
}

OCREngineAgent::~OCREngineAgent()
{
    DeleteOCREngine(m_ocrEngine);
}

bool OCREngineAgent::init(const char* language)
{
    bool ret = m_ocrEngine->Init(".", language);
    m_initState = ret;
    return m_initState;
}

void OCREngineAgent::setPageSegMode(int pageSegMode)
{
    if (m_initState)
        m_ocrEngine->SetPageSegMode(pageSegMode);
}

QStringList OCREngineAgent::availableLanguages()
{
    QStringList languages;

    if (!m_initState)
        return languages;

    char *availableLanguages = m_ocrEngine->GetAvailableLanguages();
    QString strAvailableLanguages(availableLanguages);
    FreeMemory(availableLanguages);

    QStringList langs = strAvailableLanguages.split(";");
    foreach (QString lang, langs)
    {
        if (!lang.isEmpty())
            languages << lang;
    }

    return languages;
}

QString convertGrayImage(QString filename)
{
     QImage image(filename);

     int w,h;
     w = image.width();
     h = image.height();
     QImage iGray(w,h,QImage::Format_RGB32);

     for(int i=0; i<w; i++){
         for(int j=0;j<h; j++){
             QRgb pixel = image.pixel(i,j);
             int gray = qGray(pixel);
             QRgb grayPixel = qRgb(gray,gray,gray);
             iGray.setPixel(i,j,grayPixel);
         }
     }

     QString imageFilename("grap_image.jpg");
     iGray.save(imageFilename, "JPG");

     return imageFilename;
}

QString OCREngineAgent::text(QString filename)
{
    QString strText;

    if (!m_initState)
        return strText;

    QImage image(filename);
    if (image.byteCount())
    {
        m_ocrEngine->SetImage(image.bits(), image.width(), image.height(), image.bytesPerLine()/image.width(), image.bytesPerLine());
        char *text = m_ocrEngine->GetText();
        strText = QString::fromUtf8(text);

        FreeMemory(text);
        m_ocrEngine->Clear();
    }

    return strText;
}
