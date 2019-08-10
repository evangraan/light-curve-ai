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

    if (!color.data) {
        cout << FILE_NOT_FOUND << SHOES << std::endl;
        return false;
    }

    return true;
}

bool Images::ExportGrayscale() {
    imwrite(SHOES_GRAYSCALE, gray);
    return true;
}

void Images::OutputColorPixels() {
    int myRow = color.cols - 1;
    int myCol = color.rows - 1;
    Vec3b pixel = color.at<Vec3b>(myRow, myCol);
    cout << PIXELS_LABEL << "(" << (int) pixel[0] << "," << (int) pixel[1] << "," << (int) pixel[2] << ")" << endl;
}

void Images::Show() {
    imshow(SHOW_COLOR_LABEL, color);
    imshow(SHOW_GRAYSCALE_LABEL, gray);
}

Mat Images::getColor() {
    return color;
}

Mat Images::getGray() {
    return gray;
}

int Images::compare(Mat src_base, Mat src_test1) {
    Mat hsv_base, hsv_test1;
    cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
    cvtColor(src_test1, hsv_test1, COLOR_BGR2HSV);
    Mat hsv_half_down = hsv_base(Range(hsv_base.rows / 2, hsv_base.rows), Range(0, hsv_base.cols));
    int h_bins = 50, s_bins = 60;
    int histSize[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};
    Mat hist_base, hist_half_down, hist_test1, hist_test2;
    calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false);
    normalize(hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
    normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());
    for (int compare_method = 0; compare_method < 4; compare_method++) {
        double base_base = compareHist(hist_base, hist_base, compare_method);
        double base_half = compareHist(hist_base, hist_half_down, compare_method);
        double base_test1 = compareHist(hist_base, hist_test1, compare_method);
        cout << "Method " << compare_method << " : "
                << base_base << " / " << base_half << " / " << base_test1 << endl;
    }
    cout << "Done \n";
    return 0;
}
