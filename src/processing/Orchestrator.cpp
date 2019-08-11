/* 
 * File:   Orchestrator.cpp
 * Author: ernstv
 * 
 * Created on August 11, 2019, 1:56 PM
 */

#include "Orchestrator.h"

using namespace LightCurveAnalysis;
using namespace WorkerThreading;
using namespace Workforce;

extern const std::string DATA_DIR = "/home/ernstv/build/opencv/projects/Test0001/images";
extern const std::string IMAGES_DIR = DATA_DIR + "/lc";
extern const std::string TEMPLATE = DATA_DIR + "/template.jpg";

Orchestrator::Orchestrator() {
}

Orchestrator::Orchestrator(const Orchestrator& orig) {
}

Orchestrator::~Orchestrator() {
}

void Orchestrator::queueForWork(dirent * dp){
    m_futures.push_back(Workforce::enqueue([dp]() {
                std::string path = IMAGES_DIR + "/" + dp->d_name; 
                std::cout << PROCESSING << path << std::endl;
                ChiSquaredProcessor processor;
                processor.process(IMAGES_DIR, path);
            }));
}

void Orchestrator::queueFile(dirent * dp){
    if ((strcmp(".", dp->d_name) != 0) && (strcmp("..", dp->d_name) != 0)){
        queueForWork(dp);
    }    
}

void Orchestrator::scanAndQueue(){
    DIR* dirp = opendir(IMAGES_DIR.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        queueFile(dp);
    }
    closedir(dirp);
}

void Orchestrator::completeWork(){
    for (auto& item : m_futures) {
        item.get();
    }   
}

void Orchestrator::processDataDirectory(){
    scanAndQueue();
    completeWork();
}

