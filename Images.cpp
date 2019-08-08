/*
 * Images.cpp
 *
 *  Created on: 08 Aug 2019
 *      Author: Ernst van Graan
 */

#include "Images.h"
#include "Messages.h"

extern const std::string SHOES = "images/shoes.png";
extern const std::string SHOES_GRAYSCALE = "images/shoes_grayscale.png";

Images::Images() {
}

Images::~Images() {
}

bool Images::Load() {
	color = imread(SHOES);
	gray = imread(SHOES, cv::ImreadModes::IMREAD_GRAYSCALE);

	if (!color.data)
	{
		cout << FILE_NOT_FOUND << SHOES << std::endl;
		return false;
	}

	return true;
}

bool Images::ExportGrayscale() {
	imwrite(SHOES_GRAYSCALE, gray);
	return true;
}

void Images::OutputColorPixels(){
   int myRow=color.cols-1;
   int myCol=color.rows-1;
   Vec3b pixel= color.at<Vec3b>(myRow, myCol);
   cout << PIXELS_LABEL << "(" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;
}

void Images::Show(){
	imshow(SHOW_COLOR_LABEL, color);
	imshow(SHOW_GRAYSCALE_LABEL, gray);
}
