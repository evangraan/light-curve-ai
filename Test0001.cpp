#include <utility>
#include <chrono>
#include "Images.h"
#include "src/workforce/WorkQueue.h"
#include "src/workforce/WorkerPool.h"
using namespace WorkerThreading;
using namespace Workforce;

int main(int argc, char **argv) {
    Images images;
    if (!images.Load()) {
        return 1;
    }
    if (!images.ExportGrayscale()) {
        return 2;
    }
    images.OutputColorPixels();
    images.Show();
    cout << "Press a key while focused on an image window to proceed.\n";
    waitKey(0);

    typedef std::chrono::high_resolution_clock Clock;
    auto start = Clock::now();
    std::vector<WorkerThreading::WaitForCompletionFuture<void>> v;
    for (std::uint32_t i = 0u; i < 21u; ++i) {
        v.push_back(Workforce::enqueue([]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }));
    }
    for (auto& item : v) {
        item.get();
    }
    auto end = Clock::now();
    cout << "Time elapsed: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << '\n';

    return 0;
}
