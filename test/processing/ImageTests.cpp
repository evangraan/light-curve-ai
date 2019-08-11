/* 
 * File:   ImageTests.cpp
 * Author: ernstv
 *
 * Created on August 11, 2019, 9:33 PM
 */

#include "ImageTests.h"

using namespace LightCurveAnalysis;

TEST(Processing, ImageComparison) {
    Images images;
    ImagesFixture fixture;
    double result = images.compare(fixture.getTemplateImage(), fixture.getTemplateImage(), 1);
    EXPECT_EQ(0, result);
}