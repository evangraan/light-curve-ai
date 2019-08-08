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

using namespace std;
using namespace cv;

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

private:
	Mat color;
    Mat gray;
};

#endif /* IMAGES_H_ */
