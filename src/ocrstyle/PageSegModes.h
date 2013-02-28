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

#ifndef PAGESEGMODES_H
#define PAGESEGMODES_H

#include <QMap>

enum PageSegMode {
  PSM_OSD_ONLY,       ///< Orientation and script detection only.
  PSM_AUTO_OSD,       ///< Automatic page segmentation with orientation and
                      ///< script detection. (OSD)
  PSM_AUTO_ONLY,      ///< Automatic page segmentation, but no OSD, or OCR.
  PSM_AUTO,           ///< Fully automatic page segmentation, but no OSD.
  PSM_SINGLE_COLUMN,  ///< Assume a single column of text of variable sizes.
  PSM_SINGLE_BLOCK_VERT_TEXT,  ///< Assume a single uniform block of vertically
                               ///< aligned text.
  PSM_SINGLE_BLOCK,   ///< Assume a single uniform block of text. (Default.)
  PSM_SINGLE_LINE,    ///< Treat the image as a single text line.
  PSM_SINGLE_WORD,    ///< Treat the image as a single word.
  PSM_CIRCLE_WORD,    ///< Treat the image as a single word in a circle.
  PSM_SINGLE_CHAR,    ///< Treat the image as a single character.

  PSM_COUNT           ///< Number of enum entries.
};

class PageSegModes
{
public:
    PageSegModes();

    QMap<PageSegMode, QString> pageSegModes()
    {
        return m_pageSegModes;
    }

private:
    void init();

private:
    QMap<PageSegMode, QString> m_pageSegModes;

};

#endif // PAGESEGMODES_H
