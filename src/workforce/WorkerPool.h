/* 
 * File:   WorkerPool.h
 * Author: ernstv
 *
 * Created on 09 August 2019, 8:15 PM
 */

#ifndef WORKERPOOL_H
#define WORKERPOOL_H

#pragma once

#include "IWorker.h"
#include "SimpleWorker.h"
#include "WorkQueue.h"
#include "WaitForCompletionFuture.h"

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
    class WorkerPool
    {
    private:
        unsigned int allocateCoresAndReserveOneForTheWorkerPool(){
            return max(thread::hardware_concurrency(), 2u) - 1u;
        }
    public:
        WorkerPool(void)
            :WorkerPool{allocateCoresAndReserveOneForTheWorkerPool()}
        { }

        explicit WorkerPool(const uint32_t numThreads)
            :m_done{false},
            m_workQueue{},
            m_workers{}
        {
            try
            {
                for(uint32_t i = 0u; i < numThreads; ++i)
                {
                    m_workers.emplace_back(&WorkerPool::doWorkOrWaitUntilWorkIsAvailable, this);
                }
            }
            catch(...)
            {
                destroy();
                throw;
            }
        }

        WorkerPool(const WorkerPool& rhs) = delete;

        WorkerPool& operator=(const WorkerPool& rhs) = delete;

        ~WorkerPool(void)
        {
            destroy();
        }

        template <typename Func, typename... Args>
        auto enqueue(Func&& func, Args&&... args)
        {
            auto boundTask = bind(forward<Func>(func), forward<Args>(args)...);
            using ResultType = result_of_t<decltype(boundTask)()>;
            using PackagedTask = packaged_task<ResultType()>;
            using TaskType = SimpleWorker<PackagedTask>;
            
            PackagedTask task{move(boundTask)};
            WaitForCompletionFuture<ResultType> result{task.get_future()};
            m_workQueue.enqueue(make_unique<TaskType>(move(task)));
            return result;
        }

    private:
        void doWorkOrWaitUntilWorkIsAvailable(void)
        {
            while(!m_done)
            {
                unique_ptr<IWorker> pTask{nullptr};
                if(m_workQueue.dequeueBlocking(pTask))
                {
                    pTask->execute();
                }
            }
        }

        void destroy(void)
        {
            m_done = true;
            m_workQueue.invalidate();
            for(auto& thread : m_workers)
            {
                if(thread.joinable())
                {
                    thread.join();
                }
            }
        }

    private:
        atomic_bool m_done;
        WorkQueue<unique_ptr<IWorker>> m_workQueue;
        vector<thread> m_workers;
    };

    namespace Workforce
    {
        inline WorkerPool& getWorkerPool(void)
        {
            static WorkerPool defaultPool;
            return defaultPool;
        }

        template <typename Func, typename... Args>
        inline auto enqueue(Func&& func, Args&&... args)
        {
            return getWorkerPool().enqueue(forward<Func>(func), forward<Args>(args)...);
        }
    }
}

#endif /* WORKERPOOL_H */

