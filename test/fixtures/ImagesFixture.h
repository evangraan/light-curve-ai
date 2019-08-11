/* 
 * File:   ImagesFixture.h
 * Author: ernstv
 *
 * Created on August 11, 2019, 8:49 PM
 */

#ifndef FIXTURE_H
#define FIXTURE_H

#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"

using namespace cv;
using namespace std;

class ImagesFixture {
public:    
    ImagesFixture();
    ImagesFixture(const ImagesFixture& orig);
    virtual ~ImagesFixture();
    void SetUp();
    void TearDown();
    string getTemplatePath();
    Mat getTemplateImage();
    
private:
    string m_templatePath;
    Mat m_templateImage;
};

#endif /* FIXTURE_H */

