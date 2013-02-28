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

#include "PageSegModes.h"
#include <QObject>

PageSegModes::PageSegModes()
{
    init();
}

void PageSegModes::init()
{
    m_pageSegModes[PSM_OSD_ONLY] = QObject::tr("Orientation and script detection (OSD) only.");
    m_pageSegModes[PSM_AUTO_OSD] = QObject::tr("Automatic page segmentation with OSD.");
    m_pageSegModes[PSM_AUTO_ONLY] = QObject::tr("Automatic page segmentation, but no OSD, or OCR");
    m_pageSegModes[PSM_AUTO] = QObject::tr("Fully automatic page segmentation, but no OSD. (Default)");
    m_pageSegModes[PSM_SINGLE_COLUMN] = QObject::tr("Assume a single column of text of variable sizes.");
    m_pageSegModes[PSM_SINGLE_BLOCK_VERT_TEXT] = QObject::tr("Assume a single uniform block of vertically aligned text.");
    m_pageSegModes[PSM_SINGLE_BLOCK] = QObject::tr("Assume a single uniform block of text.");
    m_pageSegModes[PSM_SINGLE_LINE] = QObject::tr("Treat the image as a single text line.");
    m_pageSegModes[PSM_SINGLE_WORD] = QObject::tr("Treat the image as a single word.");
    m_pageSegModes[PSM_CIRCLE_WORD] = QObject::tr("Treat the image as a single word in a circle.");
    m_pageSegModes[PSM_SINGLE_CHAR] = QObject::tr("Treat the image as a single character.");
}
