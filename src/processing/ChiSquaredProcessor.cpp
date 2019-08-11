/* 
 * File:   ChiSquaredProcessor.cpp
 * Author: ernstv
 * 
 * Created on August 10, 2019, 10:48 PM
 */

#include "ChiSquaredProcessor.h"

using namespace LightCurveAnalysis;
using namespace cv;
using namespace std;

ChiSquaredProcessor::ChiSquaredProcessor() {
}

ChiSquaredProcessor::ChiSquaredProcessor(const ChiSquaredProcessor& orig) {
}

ChiSquaredProcessor::~ChiSquaredProcessor() {
}

double ChiSquaredProcessor::calculateFit(string templateCurvePath, string curvePath){
    Mat templateImage = imread(templateCurvePath, IMREAD_COLOR);
    Mat curveImage = imread(curvePath, IMREAD_COLOR);
    Images images;
    return images.compare(templateImage, curveImage, 1);    
}

void ChiSquaredProcessor::outputResult(double fit, string curvePath){
    ofstream outfile;
    string outputPath = curvePath + "-comparison";
    outfile.open(outputPath, ios::out | ios::trunc );
    outfile << fit << endl;
    outfile.close();  
}

void ChiSquaredProcessor::process(string templateCurvePath, string curvePath)
{
    outputResult(calculateFit(templateCurvePath, curvePath), curvePath);
}

