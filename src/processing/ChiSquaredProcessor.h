/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChiSquaredProcessor.h
 * Author: ernstv
 *
 * Created on August 10, 2019, 10:48 PM
 */

#ifndef CHISQUAREDPROCESSOR_H
#define CHISQUAREDPROCESSOR_H

#include "../application/Images.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>

namespace LightCurveAnalysis{
    class ChiSquaredProcessor {
    public:
        ChiSquaredProcessor();
        ChiSquaredProcessor(const ChiSquaredProcessor& orig);
        virtual ~ChiSquaredProcessor();
        void process(std::string templateCurvePath, std::string curvePath);
    };
}

#endif /* CHISQUAREDPROCESSOR_H */

