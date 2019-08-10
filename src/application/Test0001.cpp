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

int main(int argc, char **argv) {
    typedef std::chrono::high_resolution_clock Clock;
    auto start = Clock::now();
    std::vector<WorkerThreading::WaitForCompletionFuture<void>> v;
    DIR* dirp = opendir("images/lc");
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(Workforce::enqueue([&dp]() {
            ChiSquaredProcessor processor;
            processor.process("images/template.jpg", dp->d_name);
        }));
    }
    closedir(dirp);
    for (auto& item : v) {
        item.get();
    }
    auto end = Clock::now();
    cout << "Time elapsed: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << '\n';

    return 0;
}
