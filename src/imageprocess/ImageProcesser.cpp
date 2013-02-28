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
#include "ImageProcesser.h"
#include <string>
#include "ImageDeskew.h"

using namespace std;
using namespace cv;

ImageProcesser::ImageProcesser()
{
}

ImageProcesser::~ImageProcesser()
{
}

bool ImageProcesser::LoadImage(const char *filename)
{
    m_filename = filename;
    m_mat = imread(m_filename);
    return !m_mat.empty();
}

void ImageProcesser::Deskew()
{
    double angle = SkewAngle();
    Rotate(angle);
}

double ImageProcesser::SkewAngle()
{
    if (m_mat.empty())
        return 0.0;

    cv::Mat image = imread(m_filename);
    ImageDeskew imageDeskew(&m_mat);
    return imageDeskew.getSkewAngle();
}

void ImageProcesser::Rotate(double angle)
{
    if (m_mat.empty())
        return;

    IplImage img(m_mat);
    angle = angle  * CV_PI / 180.0;
    double a = sin(angle), b = cos(angle); 
    int width=img.width, height=img.height;
    //旋转后的新图尺寸
    int width_rotate= int(height * fabs(a) + width * fabs(b));  
    int height_rotate=int(width * fabs(a) + height * fabs(b));  
    IplImage* img_rotate = cvCreateImage(cvSize(width_rotate, height_rotate), img.depth, img.nChannels);  
    cvZero(img_rotate);  
    //保证原图可以任意角度旋转的最小尺寸
    int tempLength = sqrt((double)width * width + (double)height *height) + 10;  
    int tempX = (tempLength + 1) / 2 - width / 2;  
    int tempY = (tempLength + 1) / 2 - height / 2;  
    IplImage* temp = cvCreateImage(cvSize(tempLength, tempLength), img.depth, img.nChannels);  
    cvZero(temp);  
    //将原图复制到临时图像tmp中心
    cvSetImageROI(temp, cvRect(tempX, tempY, width, height));  
    cvCopy(&img, temp, NULL);  
    cvResetImageROI(temp);  
    //旋转数组map
    // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
    // [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
    float m[6];  
    int w = temp->width;  
    int h = temp->height;  
    m[0] = b;  
    m[1] = a;  
    m[3] = -m[1];  
    m[4] = m[0];  
    // 将旋转中心移至图像中间  
    m[2] = w * 0.5f;  
    m[5] = h * 0.5f;  
    CvMat M = cvMat(2, 3, CV_32F, m);  
    cvGetQuadrangleSubPix(temp, img_rotate, &M);  
    cvReleaseImage(&temp);  

    m_mat = img_rotate;
}

/*
static IplImage* QImageToIplImage(const ImageData& imageData)
{
    // Creates a iplImage with 3 channels
    const int channels = 3;
    IplImage *image = cvCreateImage(cvSize(imageData.width, imageData.height), IPL_DEPTH_8U, channels);
    char * imgBuffer = image->imageData;
    //Remove alpha channel
    //int jump = (qImage.hasAlphaChannel()) ? 4 : 3;
    for (int h=0; h<image->height; ++h)
    {
        for (int w=0; w<image->width; w+=channels)
        {
            //Swap from RGB to BGR 
            imgBuffer[2] = imageData.data[h*channels + w*channels];
            imgBuffer[1] = imageData.data[h*channels + w*channels + 1];
            imgBuffer[0] = imageData.data[h*channels + w*channels + 2];
            imgBuffer+=3;
        }
    }

    return image;
}
*/

void ImageProcesser::TransformToGrayscale()
{
	if (m_mat.empty())
		return;

	cvtColor(m_mat, m_mat, COLOR_RGB2GRAY);
}

//这种方法只适用于灰度图
void ImageProcesser::RotateWithGrayscale(double angle)
{
    if (m_mat.empty())
        return;

    TransformToGrayscale();

	std::vector<cv::Point> points;
	cv::Mat_<uchar>::iterator iter = m_mat.begin<uchar>();
	cv::Mat_<uchar>::iterator end = m_mat.end<uchar>();
	for (; iter != end; ++iter)
	{
		if (*iter)
			points.push_back(iter.pos());
	}

	cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));
	cv::Mat rotateMat = cv::getRotationMatrix2D(box.center, angle, 1);
	cv::warpAffine(m_mat, m_mat, rotateMat, m_mat.size(), cv::INTER_CUBIC);

	//cv::Size boxSize = box.size;
	//if (box.angle < -45.)
	//	std::swap(boxSize.width, boxSize.height);
	//cv::getRectSubPix(m_mat, boxSize, box.center, m_mat);
}

/*cv::Mat ImageProcesser::ROI(cv::Rect rect)
{
	return roi(m_mat, rect);
}*/

void ImageProcesser::Save(const char *filename)
{
    if (m_mat.empty())
        return;

	imwrite(filename, m_mat);
}