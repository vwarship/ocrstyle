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

#include "StdAfx.h"
#include "TesseractOCREngine.h"
#include "baseapi.h"

using namespace std;
using namespace tesseract;

TesseractOCREngine::TesseractOCREngine()
{
    m_tessBaseAPI = new TessBaseAPI;
}

TesseractOCREngine::~TesseractOCREngine()
{
    m_tessBaseAPI->Clear();
    m_tessBaseAPI->End();
}

bool TesseractOCREngine::Init(const char* datapath, const char* language)
{
    int ret = m_tessBaseAPI->Init(datapath, language);
	return !ret;
}

void TesseractOCREngine::SetPageSegMode(int pageSegMode)
{
	m_tessBaseAPI->SetPageSegMode(static_cast<tesseract::PageSegMode>(pageSegMode));
}

char* TesseractOCREngine::GetAvailableLanguages()
{
    GenericVector<STRING> languages;
    m_tessBaseAPI->GetAvailableLanguagesAsVector(&languages);

    string langs;
    for (int i=0; i<languages.size(); ++i)
    {
		langs += languages[i].string();
		langs += ";";
    }

	if (!langs.length())
		return '\0';

	const int size = langs.length()+1;
	char *str = new char[size];
	memset(str, 0, size);
	memcpy(str, langs.data(), size);

    return str;
}

void TesseractOCREngine::SetImage(const unsigned char* imagedata, int width, int height, int bytes_per_pixel, int bytes_per_line)
{
    if (imagedata)
    {
        m_tessBaseAPI->SetImage(imagedata, width, height, bytes_per_pixel, bytes_per_line);
    }
}

char* TesseractOCREngine::GetText()
{
    return m_tessBaseAPI->GetUTF8Text();
}

void TesseractOCREngine::Clear()
{
	m_tessBaseAPI->Clear();
}