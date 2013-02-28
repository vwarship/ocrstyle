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

#include "ImageView.h"

#include <QtGui>

const QString ImageView::m_selectedRectImageFilename("selected_rect_image.jpg");

ImageView::ImageView(QWidget* parent)
    : QGraphicsView(parent), isMoveImageWithCurrentState(true), isMousePress(false)
{
    setBackgroundRole(QPalette::Light);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setScene(new QGraphicsScene(this));
    setSceneRect(0, 0, rect().width(), rect().height());
    setCenterPoint(QPointF(rect().width()/2, rect().height()/2));
    setCursor(Qt::OpenHandCursor);

    setMouseTracking(true);

    rubberBand = 0;
}

void ImageView::showImage(const QPixmap &pixmap)
{
    scene()->clear();
    scene()->addPixmap(pixmap);
    setSceneRect(pixmap.rect());
}

bool ImageView::isSelectedRect()
{
    if (rubberBand)
    {
        const int limitSize = 4;
        QSize size = rubberBand->rect().size();
        if (size.width() > limitSize && size.height() > limitSize)
            return true;
    }

    return false;
}

void ImageView::setMoveImageWithCurrentState(bool state)
{
    isMoveImageWithCurrentState = state;

    if (isMoveImageWithCurrentState)
        setCursor(Qt::OpenHandCursor);
    else
        setCursor(Qt::CrossCursor);
}


/**
  * Sets the current centerpoint.  Also updates the scene's center point.
  * Unlike centerOn, which has no way of getting the floating point center
  * back, setCenterPoint() stores the center point.  It also handles the special
  * sidebar case.  This function will claim the centerPoint to sceneRec ie.
  * the centerPoint must be within the sceneRec.
  */
//Set the current centerpoint in the
void ImageView::setCenterPoint(const QPointF& centerPoint) {
    //Get the rectangle of the visible area in scene coords
    QRectF visibleArea = mapToScene(rect()).boundingRect();

    //Get the scene area
    QRectF sceneBounds = sceneRect();

    double boundX = visibleArea.width() / 2.0;
    double boundY = visibleArea.height() / 2.0;
    double boundWidth = sceneBounds.width() - 2.0 * boundX;
    double boundHeight = sceneBounds.height() - 2.0 * boundY;

    //The max boundary that the centerPoint can be to
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);

    if(bounds.contains(centerPoint)) {
        //We are within the bounds
        currentCenterPoint = centerPoint;
    } else {
        //We need to clamp or use the center of the screen
        if(visibleArea.contains(sceneBounds)) {
            //Use the center of scene ie. we can see the whole scene
            currentCenterPoint = sceneBounds.center();
        } else {

            currentCenterPoint = centerPoint;

            //We need to clamp the center. The centerPoint is too large
            if(centerPoint.x() > bounds.x() + bounds.width()) {
                currentCenterPoint.setX(bounds.x() + bounds.width());
            } else if(centerPoint.x() < bounds.x()) {
                currentCenterPoint.setX(bounds.x());
            }

            if(centerPoint.y() > bounds.y() + bounds.height()) {
                currentCenterPoint.setY(bounds.y() + bounds.height());
            } else if(centerPoint.y() < bounds.y()) {
                currentCenterPoint.setY(bounds.y());
            }

        }
    }

    //Update the scrollbars
    centerOn(currentCenterPoint);
}

/**
  * Handles when the mouse button is pressed
  */
void ImageView::mousePressEvent(QMouseEvent* event)
{
    isMousePress = true;

    if (isMoveImageWithCurrentState)
    {
        lastPoint = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    else
    {
        origin = event->pos();
        if (!rubberBand)
            rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();
    }
}

/**
  * Handles when the mouse button is released
  */
void ImageView::mouseReleaseEvent(QMouseEvent* event)
{
    isMousePress = false;


    if (isMoveImageWithCurrentState)
    {
        setCursor(Qt::OpenHandCursor);
        lastPoint = QPoint();
    }
    else
    {
        if (rubberBand)
        {
            //rubberBand->hide();

            QRect selectedRect = QRect(origin, event->pos()).normalized();
            //QPointF ptTopLeft = mapToScene(selectedRect.topLeft());
            //QPointF ptBottomRight = mapToScene(selectedRect.bottomRight());
            //QRectF selectedRectF = QRectF(ptTopLeft, ptBottomRight).normalized();
            QRectF selectedRectF = mapToScene(QRect(selectedRect.topLeft(), selectedRect.bottomRight())).boundingRect();

            int selectedRectWidth = selectedRectF.width();
            int selectedRectHeight = selectedRectF.height();
            QPixmap outputImage(selectedRectWidth, selectedRectHeight);
            QPainter outputPainter(&outputImage);
            outputPainter.fillRect(outputImage.rect(), Qt::white);

            QRectF targetRect(0, 0, selectedRectWidth, selectedRectHeight);
            render(&outputPainter, targetRect, selectedRect);
            outputImage.save(m_selectedRectImageFilename, "JPG");

            outputPainter.end();
        }
    }
}

/**
*Handles the mouse move event
*/
void ImageView::mouseMoveEvent(QMouseEvent* event)
{
    if (isMoveImageWithCurrentState)
    {
        if(!lastPoint.isNull())
        {
            //Get how much we panned
            QPointF delta = mapToScene(lastPoint) - mapToScene(event->pos());
            lastPoint = event->pos();

            //Update the center ie. do the pan
            setCenterPoint(centerPoint() + delta);
        }
    }
    else
    {
        if (isMousePress && rubberBand)
            rubberBand->setGeometry(QRect(origin, event->pos()).normalized());

        /*
        if (isMousePress && rubberBand)
        {
            rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
            rubberBand->setRect(QRect(origin, event->pos()).normalized());
        }

        if ((!isMousePress) && rubberBand)
        {
            QPoint curPt = event->pos();

            if (rubberBand->topLeftRect().contains(curPt) ||
                rubberBand->bottomRightRect().contains(curPt))
            {
                setCursor(Qt::SizeFDiagCursor);
                //rubberBand->setGeometry(rectTopLeft);
            }
            else if (rubberBand->topRightRect().contains(curPt) ||
                     rubberBand->bottomLeftRect().contains(curPt))
            {
                setCursor(Qt::SizeBDiagCursor);
                //rubberBand->setGeometry(rectTopLeft);
            }
        }*/
    }
}

/**
  * Zoom the view in and out.
  */
void ImageView::wheelEvent(QWheelEvent* event)
{
    //Get the position of the mouse before scaling, in scene coords
    QPointF pointBeforeScale(mapToScene(event->pos()));

    //Get the original screen centerpoint
    QPointF screenCenter = centerPoint(); //CurrentCenterPoint; //(visRect.center());

    //Scale the view ie. do the zoom
    if(event->delta() > 0) {
        //Zoom in
        zoomIn();
    } else {
        //Zooming out
        zoomOut();
    }

    //Get the position after scaling, in scene coords
    QPointF pointAfterScale(mapToScene(event->pos()));

    //Get the offset of how the screen moved
    QPointF offset = pointBeforeScale - pointAfterScale;

    //Adjust to the new center for correct zooming
    QPointF newCenter = screenCenter + offset;
    setCenterPoint(newCenter);
}

/**
  * Need to update the center so there is no jolt in the
  * interaction after resizing the widget.
  */
void ImageView::resizeEvent(QResizeEvent* event)
{
    //Get the rectangle of the visible area in scene coords
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    setCenterPoint(visibleArea.center());

    //Call the subclass resize so the scrollbars are updated correctly
    QGraphicsView::resizeEvent(event);
}

void ImageView::zoomIn()
{
    double scaleFactor = 1.15;
    scale(scaleFactor, scaleFactor);
}

void ImageView::zoomOut()
{
    double scaleFactor = 1.15;
    scale(1.0 / scaleFactor, 1.0 / scaleFactor);
}

void ImageView::resetZoom()
{
    resetCachedContent();
    resetMatrix();
    resetTransform();
}

void ImageView::fitToView()
{
    fitInView(0, 0, scene()->width(), scene()->height());
}
