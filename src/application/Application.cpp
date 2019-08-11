#include <utility>
#include <chrono>
#include <sys/types.h>
#include "Messages.h"
#include "../processing/Orchestrator.h"

using namespace LightCurveAnalysis;

int main(int argc, char **argv) {
    typedef std::chrono::high_resolution_clock Clock;
    auto start = Clock::now();
    
    Orchestrator orchestrator;
    orchestrator.processDataDirectory();

    auto end = Clock::now();
    cout << TIME_ELAPSED << chrono::duration_cast<chrono::milliseconds>(end - start).count() << '\n';

    return 0;
}
