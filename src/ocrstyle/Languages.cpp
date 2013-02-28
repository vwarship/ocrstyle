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

#include "Languages.h"
#include <QObject>

Languages::Languages()
{
    initLanguages();
}

void Languages::initLanguages()
{
    addLanguage(Language(QObject::tr("English"), "en"));
    addLanguage(Language(QObject::tr("Chinese (Simplified)"), "zh_CN"));
    /*addLanguage(Language(QObject::tr("Chinese (Traditional)"), "zh_TW"));
    addLanguage(Language(QObject::tr("Spanish"), "es"));
    addLanguage(Language(QObject::tr("French"), "fr"));
    addLanguage(Language(QObject::tr("German"), "de"));
    addLanguage(Language(QObject::tr("Italian"), "it"));
    addLanguage(Language(QObject::tr("Japanese"), "ja"));
    addLanguage(Language(QObject::tr("Korean"), "ko"));
    addLanguage(Language(QObject::tr("Russian"), "ru"));
    addLanguage(Language(QObject::tr("Dutch"), "nl"));
    addLanguage(Language(QObject::tr("Portuguese"), "pt"));
    addLanguage(Language(QObject::tr("Tamil"), "ta"));
    addLanguage(Language(QObject::tr("Arabic"), "ar"));
    addLanguage(Language(QObject::tr("Bengali"), "bn"));*/
}

void Languages::addLanguage(const Language &language)
{
    m_languages.append(language);
}

Language Languages::item(int index)
{
    return m_languages[index];
}

int Languages::size()
{
    return m_languages.size();
}
