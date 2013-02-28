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

#ifndef IMAGEDESKEW_H
#define IMAGEDESKEW_H

#include <cmath>
#include <vector>

class QImage;

class ImageDeskew
{
    //Representation of a line in the image.
    struct HoughLine
    {
        HoughLine()
            : count(0), index(0), alpha(0.0), d(0.0)
        {
        }

        // count of points in the line
        int count;
        // index in matrix.
        int index;
        // the line is represented as all x, y that solve y * cos(alpha) - x *
        // sin(alpha) = d
        double alpha;
        double d;
    };

public:
    ImageDeskew(QImage *image);

    // calculate the skew angle of the image m_image
    double getSkewAngle();

private:
    // Hough Transformation
    void calc();

    void init();

    double getAlpha(int index)
    {
        return m_alphaStart + (index * m_alphaStep);
    }

    // calculate the count lines in the image with most points
    void getTopHoughLines(std::vector<HoughLine> &houghLines);

    // calculate all lines through the point (x,y)
    void calc(int x, int y);

    bool isBlack(int x, int y);
    bool isBlack(int x, int y, int luminanceCutOff);


private:
    static const double PI;

    // the range of angles to search for lines
    static const double m_alphaStart;
    static const double m_alphaStep;
    static const int m_steps;
    // pre-calculation of sin and cos
    std::vector<double> m_sinA;
    std::vector<double> m_cosA;
    // range of d
    double m_dMin;
    static const double m_dStep;
    int m_dCount;
    // count of points that fit in a line
    std::vector<int> m_hMatrix;


    // the source image
    QImage *m_image;

};

#endif // IMAGEDESKEW_H
