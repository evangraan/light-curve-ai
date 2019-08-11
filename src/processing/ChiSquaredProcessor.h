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

#pragma once

#include "IProcessor.h"
#include "Images.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>

using namespace std;

namespace LightCurveAnalysis{
    class ChiSquaredProcessor : IProcessor{
    public:
        ChiSquaredProcessor();
        ChiSquaredProcessor(const ChiSquaredProcessor& orig);
        virtual ~ChiSquaredProcessor();
        void process(string templateCurvePath, string curvePath) override;
        
    private:
        double calculateFit(string templateCurvePath, string curvePath) override;
        void outputResult(double fit, string curvePath) override;
    };
}

#endif /* CHISQUAREDPROCESSOR_H */

