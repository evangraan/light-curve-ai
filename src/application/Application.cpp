#include <utility>
#include <chrono>
#include <sys/types.h>
#include <dirent.h>
#include "Images.h"
#include "../processing/ChiSquaredProcessor.h"
#include "../workforce/WorkQueue.h"
#include "../workforce/WorkerPool.h"

using namespace WorkerThreading;
using namespace Workforce;
using namespace LightCurveAnalysis;

extern const std::string DATA_DIR = "/home/ernstv/build/opencv/projects/Test0001/images";
extern const std::string IMAGES_DIR = DATA_DIR + "/lc";
extern const std::string TEMPLATE = DATA_DIR + "/template.jpg";

int main(int argc, char **argv) {
    typedef std::chrono::high_resolution_clock Clock;
    auto start = Clock::now();
    std::vector<WorkerThreading::WaitForCompletionFuture<void>> v;
    DIR* dirp = opendir(IMAGES_DIR.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        if ((strcmp(".", dp->d_name) != 0) && (strcmp("..", dp->d_name) != 0)){
            v.push_back(Workforce::enqueue([dp]() {
                std::string path = IMAGES_DIR + "/" + dp->d_name; 
                std::cout << "Processing: " << path << std::endl;
                ChiSquaredProcessor processor;
                processor.process(IMAGES_DIR, path);
            }));
        }
    }
    closedir(dirp);
    for (auto& item : v) {
        item.get();
    }
    auto end = Clock::now();
    cout << "Time elapsed: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << '\n';

    return 0;
}
