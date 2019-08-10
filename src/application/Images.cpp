/*
 * Images.cpp
 *
 *  Created on: 08 Aug 2019
 *      Author: Ernst van Graan
 */

#include "Images.h"
#include "Messages.h"

Images::Images() {
}

Images::~Images() {
}

double Images::compare(Mat src_base, Mat src_test1, int method) {
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
    Mat hist_base, hist_half_down, hist_test1;
    calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false);
    normalize(hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
    normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());
    double base_base = compareHist(hist_base, hist_base, method);
    double base_half = compareHist(hist_base, hist_half_down, method);
    double base_test1 = compareHist(hist_base, hist_test1, method);
    return base_test1;
}
