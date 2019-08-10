/* 
 * File:   ChiSquaredProcessor.cpp
 * Author: ernstv
 * 
 * Created on August 10, 2019, 10:48 PM
 */

#include "ChiSquaredProcessor.h"

using namespace LightCurveAnalysis;

ChiSquaredProcessor::ChiSquaredProcessor() {
}

ChiSquaredProcessor::ChiSquaredProcessor(const ChiSquaredProcessor& orig) {
}

ChiSquaredProcessor::~ChiSquaredProcessor() {
}

void ChiSquaredProcessor::process(std::string templateCurvePath, std::string curvePath)
{
    Mat templateImage = cv::imread(templateCurvePath, cv::IMREAD_COLOR);
    Mat curveImage = cv::imread(curvePath, cv::IMREAD_COLOR);
    Images images;
    double fit = images.compare(templateImage, curveImage, 1);
    ofstream outfile;
    std::string outputPath = curvePath + "-comparison";
    outfile.open(outputPath, ios::out | ios::trunc );
    outfile << fit << endl;
    outfile.close();
}

