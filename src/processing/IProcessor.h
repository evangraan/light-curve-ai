/* 
 * File:   IProcessor.h
 * Author: ernstv
 *
 * Created on August 11, 2019, 3:12 PM
 */

#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include "Images.h"

using namespace std;

namespace LightCurveAnalysis{
    class IProcessor {
    public:
        IProcessor() = default;
        IProcessor(const IProcessor& orig) = delete;
        virtual ~IProcessor() = default;
        virtual void process(string templateCurvePath, string curvePath) = 0;

    private:
        virtual double calculateFit(string templateCurvePath, string curvePath) = 0;
        virtual void outputResult(double fit, string curvePath) = 0;
    };
}

#endif /* IPROCESSOR_H */

