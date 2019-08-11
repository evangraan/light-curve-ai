/*
 * Images.h
 *
 *  Created on: 08 Aug 2019
 *      Author: Ernst van Graan
 */

#include <iostream>
#include <string>
#include <sstream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"

using namespace std;
using namespace cv;

#ifndef IMAGES_H_
#define IMAGES_H_

#pragma once

namespace LightCurveAnalysis{
    class Images {

    public:
            Images();
            virtual ~Images();
            double compare(Mat src_base, Mat src_test1, int method);
    };
}
#endif /* IMAGES_H_ */
