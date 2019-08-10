/* 
 * File:   SimpleWorker.h
 * Author: ernstv
 *
 * Created on August 10, 2019, 3:08 PM
 */

#ifndef SIMPLEWORKER_H
#define SIMPLEWORKER_H

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>
#include "IWorker.h"

namespace WorkerThreading
{
    template <typename Func>
    class SimpleWorker : public IWorker {
    public:
        SimpleWorker(Func&& func)
        : m_func{std::move(func)}
        {
        }

        ~SimpleWorker(void) override = default;
        SimpleWorker(const SimpleWorker& rhs) = delete;
        SimpleWorker& operator=(const SimpleWorker& rhs) = delete;
        SimpleWorker(SimpleWorker&& other) = default;
        SimpleWorker& operator=(SimpleWorker&& other) = default;

        void execute() override {
            m_func();
        }

    private:
        Func m_func;
    };
}

#endif /* SIMPLEWORKER_H */

