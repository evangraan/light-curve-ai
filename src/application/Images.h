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

#pragma once

#ifndef IMAGES_H_
#define IMAGES_H_

extern const std::string SHOES;
extern const std::string SHOES_GRAYSCALE;

class Images {

public:
	Images();
	virtual ~Images();
	bool Load();
	bool ExportGrayscale();
	void OutputColorPixels();
	void Show();
        Mat getColor();
        Mat getGray();
        int compare(Mat templateImage, Mat image);

private:
    Mat color;
    Mat gray;
};

#endif /* IMAGES_H_ */
