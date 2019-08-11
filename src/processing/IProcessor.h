/* 
 * File:   IProcessor.h
 * Author: ernstv
 *
 * Created on August 11, 2019, 3:12 PM
 */

#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include "Images.h"

namespace LightCurveAnalysis{
    class IProcessor {
    public:
        IProcessor() = default;
        IProcessor(const IProcessor& orig) = delete;
        virtual ~IProcessor() = default;
        virtual void process(std::string templateCurvePath, std::string curvePath) = 0;

    private:
        virtual double calculateFit(std::string templateCurvePath, std::string curvePath) = 0;
        virtual void outputResult(double fit, std::string curvePath) = 0;
    };
}

#endif /* IPROCESSOR_H */

