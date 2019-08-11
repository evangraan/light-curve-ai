/* 
 * File:   WaitForCompletionFuture.h
 * Author: ernstv
 *
 * Created on August 10, 2019, 3:12 PM
 */

#ifndef WAITFORCOMPLETIONFUTURE_H
#define WAITFORCOMPLETIONFUTURE_H

#pragma once

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

using namespace std;

namespace WorkerThreading
{
    template <typename T>
    class WaitForCompletionFuture {
    public:
        WaitForCompletionFuture(future<T>&& future)
        : m_future{move(future)}
        {
        }

        WaitForCompletionFuture(const WaitForCompletionFuture& rhs) = delete;
        WaitForCompletionFuture& operator=(const WaitForCompletionFuture& rhs) = delete;
        WaitForCompletionFuture(WaitForCompletionFuture&& other) = default;
        WaitForCompletionFuture& operator=(WaitForCompletionFuture&& other) = default;

        ~WaitForCompletionFuture(void) {
            if (m_future.valid()) {
                m_future.get();
            }
        }

        auto get(void) {
            return m_future.get();
        }

    private:
        future<T> m_future;
    };
}
#endif /* WAITFORCOMPLETIONFUTURE_H */

