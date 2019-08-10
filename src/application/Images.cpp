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

int Images::compare(Mat templateImage, Mat compareImage) {
    if (!templateImage.data || !compareImage.data) {
        printf(" --(!) Error reading images \n");
        return -1;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    SurfFeatureDetector detector(minHessian);

    std::vector<KeyPoint> keypoints_1, keypoints_2;

    detector.detect(templateImage, keypoints_1);
    detector.detect(compareImage, keypoints_2);

    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;

    Mat descriptors_1, descriptors_2;

    extractor.compute(templateImage, keypoints_1, descriptors_1);
    extractor.compute(compareImage, keypoints_2, descriptors_2);

    //-- Step 3: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);

    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for (int i = 0; i < descriptors_1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist);
    printf("-- Min dist : %f \n", min_dist);

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
    //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
    //-- small)
    //-- PS.- radiusMatch can also be used here.
    std::vector< DMatch > good_matches;

    for (int i = 0; i < descriptors_1.rows; i++) {
        if (matches[i].distance <= max(2 * min_dist, 0.02)) {
            good_matches.push_back(matches[i]);
        }
    }

    //-- Draw only "good" matches
    Mat img_matches;
    drawMatches(templateImage, keypoints_1, compareImage, keypoints_2,
            good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    //-- Show detected matches
    imshow("Good Matches", img_matches);

    for (int i = 0; i < (int) good_matches.size(); i++) {
        printf("-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);
    }

    waitKey(0);
    
    return good_matches.size();
}
