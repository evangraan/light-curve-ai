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

double ChiSquaredProcessor::calculateFit(std::string templateCurvePath, std::string curvePath){
    Mat templateImage = cv::imread(templateCurvePath, cv::IMREAD_COLOR);
    Mat curveImage = cv::imread(curvePath, cv::IMREAD_COLOR);
    Images images;
    return images.compare(templateImage, curveImage, 1);    
}

void ChiSquaredProcessor::outputResult(double fit, std::string curvePath){
    ofstream outfile;
    std::string outputPath = curvePath + "-comparison";
    outfile.open(outputPath, ios::out | ios::trunc );
    outfile << fit << endl;
    outfile.close();  
}

void ChiSquaredProcessor::process(std::string templateCurvePath, std::string curvePath)
{
    outputResult(calculateFit(templateCurvePath, curvePath), curvePath);
}

