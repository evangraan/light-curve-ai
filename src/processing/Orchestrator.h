/* 
 * File:   Orchestrator.h
 * Author: ernstv
 *
 * Created on August 11, 2019, 1:56 PM
 */

#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#pragma once

#include <utility>
#include <chrono>
#include <sys/types.h>
#include <dirent.h>
#include "Images.h"
#include "ChiSquaredProcessor.h"
#include "../workforce/WorkQueue.h"
#include "../workforce/WorkerPool.h"
#include "../application/Messages.h"

extern const std::string DATA_DIR;
extern const std::string IMAGES_DIR;
extern const std::string TEMPLATE;

namespace LightCurveAnalysis {
    class Orchestrator {
    public:
        Orchestrator();
        Orchestrator(const Orchestrator& orig);
        virtual ~Orchestrator();
        void processDataDirectory();
    
    private:
        void queueFile(dirent * dp);
        void scanAndQueue();
        void completeWork();
        void queueForWork(dirent * dp);
        
        std::vector<WorkerThreading::WaitForCompletionFuture<void>> m_futures;
    };
}
#endif /* ORCHESTRATOR_H */

