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

namespace Threading
{
    class WorkerPool
    {
    private:
        unsigned int allocateCoresAndReserveOneForTheWorkerPool(){
            return std::max(std::thread::hardware_concurrency(), 2u) - 1u;
        }
    public:
        WorkerPool(void)
            :WorkerPool{allocateCoresAndReserveOneForTheWorkerPool()}
        { }

        explicit WorkerPool(const std::uint32_t numThreads)
            :m_done{false},
            m_workQueue{},
            m_workers{}
        {
            try
            {
                for(std::uint32_t i = 0u; i < numThreads; ++i)
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
            auto boundTask = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
            using ResultType = std::result_of_t<decltype(boundTask)()>;
            using PackagedTask = std::packaged_task<ResultType()>;
            using TaskType = SimpleWorker<PackagedTask>;
            
            PackagedTask task{std::move(boundTask)};
            WaitForCompletionFuture<ResultType> result{task.get_future()};
            m_workQueue.enqueue(std::make_unique<TaskType>(std::move(task)));
            return result;
        }

    private:
        void doWorkOrWaitUntilWorkIsAvailable(void)
        {
            while(!m_done)
            {
                std::unique_ptr<IWorker> pTask{nullptr};
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
        std::atomic_bool m_done;
        WorkQueue<std::unique_ptr<IWorker>> m_workQueue;
        std::vector<std::thread> m_workers;
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
            return getWorkerPool().enqueue(std::forward<Func>(func), std::forward<Args>(args)...);
        }
    }
}

#endif /* WORKERPOOL_H */

