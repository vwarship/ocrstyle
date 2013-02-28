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

#include "RubberBand.h"
#include <QtGui>

RubberBand::RubberBand(Shape shape, QWidget *parent)
    : QRubberBand(shape, parent), m_pt(4, 4)
{
}

void RubberBand::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QApplication::processEvents();

    QPainter painter;
    QPen pen = QPen(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::DashLine);

    //QBrush brush = QBrush(Qt::yellow);

    painter.begin(this);
    painter.setPen(pen);
    painter.setOpacity(0.7);
    //painter.setBrush(brush);
    painter.drawRect(event->rect());
    painter.end();
}

void RubberBand::setRect(QRect rect)
{
    m_rect = rect;
}

QRect RubberBand::topLeftRect()
{
    QPoint ptTopLeft = m_rect.topLeft();
    return QRect(ptTopLeft-m_pt, ptTopLeft+m_pt);
}

QRect RubberBand::topRightRect()
{
    QPoint ptTopRight = m_rect.topRight();
    return QRect(ptTopRight-m_pt, ptTopRight+m_pt);
}

QRect RubberBand::bottomLeftRect()
{
    QPoint ptBottomLeft = m_rect.bottomLeft();
    return QRect(ptBottomLeft-m_pt, ptBottomLeft+m_pt);
}

QRect RubberBand::bottomRightRect()
{
    QPoint ptBottomRight = m_rect.bottomRight();
    return QRect(ptBottomRight-m_pt, ptBottomRight+m_pt);
}
