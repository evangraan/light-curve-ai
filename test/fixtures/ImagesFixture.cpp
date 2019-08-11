/* 
 * File:   ImagesFixture.cpp
 * Author: ernstv
 * 
 * Created on August 11, 2019, 8:49 PM
 */

#include "ImagesFixture.h"

using namespace cv;
using namespace std;

ImagesFixture::ImagesFixture() {
    SetUp();
}

ImagesFixture::ImagesFixture(const ImagesFixture& orig) {
}

ImagesFixture::~ImagesFixture() {
    TearDown();
}

void ImagesFixture::SetUp(){
    m_templatePath = "images/template.jpg";
    m_templateImage = imread(m_templatePath, IMREAD_COLOR);
}

void ImagesFixture::TearDown(){
}

string ImagesFixture::getTemplatePath(){
    return m_templatePath;
}

Mat ImagesFixture::getTemplateImage(){
    return m_templateImage;
}
