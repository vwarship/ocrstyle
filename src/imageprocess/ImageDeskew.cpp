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
#include "ImageDeskew.h"
#include <opencv2/opencv.hpp>

const double ImageDeskew::PI = 3.1415926;
const double ImageDeskew::m_alphaStart = -20;
const double ImageDeskew::m_alphaStep = 0.2;
const int ImageDeskew::m_steps = 40 * 5;
const double ImageDeskew::m_dStep = 1.0;

using namespace std;

ImageDeskew::ImageDeskew(cv::Mat *image)
    : m_image(image)
{
}

double ImageDeskew::getSkewAngle()
{
    double sum = 0.0;
    int count = 0;

    // perform Hough Transformation
    calc();

    // top 20 of the detected lines in the image
    const int topLineNum = 20;
    vector<HoughLine> houghLines(topLineNum);
    getTopHoughLines(houghLines);

    if (houghLines.size() >= 20)
    {
        // average angle of the lines
        for (int i = 0; i < 19; ++i)
        {
            sum += houghLines[i].alpha;
            ++count;
        }

        return (sum / count);
    }
    else
    {
        return 0.0;
    }
}

void ImageDeskew::calc()
{
    int hMin = (int) ((m_image->rows) / 4.0);
    int hMax = (int) ((m_image->rows) * 3.0 / 4.0);
    init();

    for (int y = hMin; y < hMax; ++y)
    {
        for (int x = 1; x < (m_image->cols - 2); ++x)
        {
            // only lower edges are considered
            if (isBlack(x, y) &&
                !isBlack(x, y + 1))
            {
                calc(x, y);
            }
        }
    }
}

void ImageDeskew::init()
{
    // pre-calculation of sin and cos
    const int n = m_steps - 1;
    m_sinA.clear();
    m_cosA.clear();
    m_sinA.resize(n);
    m_cosA.resize(n);

    for (int i = 0; i < n; ++i)
    {
        double angle = getAlpha(i) * PI / 180.0;
        m_sinA[i] = sin(angle);
        m_cosA[i] = cos(angle);
    }

    // range of d
    m_dMin = -m_image->cols;
    m_dCount = (int) (2.0 * ((m_image->cols + m_image->rows)) / m_dStep);

    m_hMatrix.clear();
    m_hMatrix.resize(m_dCount * m_steps);
}

void ImageDeskew::getTopHoughLines(vector<HoughLine> &houghLines)
{
    const int count = houghLines.size();

    HoughLine tmp;
    for (size_t i = 0; i < m_hMatrix.size()-1; ++i)
    {
        if (m_hMatrix[i] > houghLines[count - 1].count)
        {
            houghLines[count - 1].count = m_hMatrix[i];
            houghLines[count - 1].index = i;
            int j = count - 1;
            while ((j > 0) && (houghLines[j].count > houghLines[j - 1].count))
            {
                tmp = houghLines[j];
                houghLines[j] = houghLines[j - 1];
                houghLines[j - 1] = tmp;
                --j;
            }
        }
    }

    int alphaIndex;
    int dIndex;

    for (int i = 0; i < count; ++i)
    {
        dIndex = houghLines[i].index / m_steps; // integer division, no
        // remainder
        alphaIndex = houghLines[i].index - dIndex * m_steps;
        houghLines[i].alpha = getAlpha(alphaIndex);
        houghLines[i].d = dIndex + m_dMin;
    }
}

void ImageDeskew::calc(int x, int y)
{
    for (int alpha = 0; alpha < (m_steps - 1); ++alpha)
    {
        double d = y * m_cosA[alpha] - x * m_sinA[alpha];
        int dIndex = (int) (d - m_dMin);
        int index = dIndex * m_steps + alpha;
        m_hMatrix[index] += 1;
    }
}

bool ImageDeskew::isBlack(int x, int y)
{
    if (m_image->channels() == 1)
    {
        uchar value = m_image->at<uchar>(y, x);
        if (value == 0)
            return true;
        else
            return false;
    }

    int luminanceValue = 140;
    return isBlack(x, y, luminanceValue);
}

bool ImageDeskew::isBlack(int x, int y, int luminanceCutOff)
{
    if (m_image->channels() < 3)
        return false;

    // return white on areas outside of image boundaries
    if (x < 0 || y < 0 || x > m_image->cols || y > m_image->rows)
    {
        return false;
    }

    
    int red = m_image->at<cv::Vec3b>(y, x)[2];
    int green = m_image->at<cv::Vec3b>(y, x)[1];
    int blue = m_image->at<cv::Vec3b>(y, x)[0];
    double luminance = (red * 0.299) + (green * 0.587) + (blue * 0.114);

    return luminance < luminanceCutOff;
}
