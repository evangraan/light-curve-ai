#ifndef WORKQUEUE_H
#define WORKQUEUE_H

#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

namespace WorkerThreading
{
    template <typename T>
    class WorkQueue
    {
    public:
        ~WorkQueue(void)
        {
            invalidate();
        }

        bool dequeue(T& out)
        {
            std::lock_guard<std::mutex> lock{m_mutex};
            if(m_stack.empty() || !m_valid)
            {
                return false;
            }
            out = std::move(m_stack.front());
            m_stack.pop();
            return true;
        }
        
        bool dequeueBlocking(T& out)
        {
            std::unique_lock<std::mutex> lock{m_mutex};
            
            m_observers.wait(lock, [this]()
            {
                return !m_stack.empty() || !m_valid;
            });
            if (m_valid){
                out = std::move(m_stack.front());
                m_stack.pop();
            }
            return m_valid;
        }

        void enqueue(T value)
        {
            std::lock_guard<std::mutex> lock{m_mutex};
            m_stack.push(std::move(value));
            m_observers.notify_one();
        }

        bool isEmpty(void) const
        {
            std::lock_guard<std::mutex> lock{m_mutex};
            return m_stack.empty();
        }

        void flush(void)
        {
            std::lock_guard<std::mutex> lock{m_mutex};
            emptyStack();
            m_observers.notify_all();
        }

        void invalidate(void)
        {
            std::lock_guard<std::mutex> lock{m_mutex};
            m_valid = false;
            m_observers.notify_all();
        }

        bool isValid(void) const
        {
            std::lock_guard<std::mutex> lock{m_mutex};
            return m_valid;
        }

    private:
        std::atomic_bool m_valid{true};
        mutable std::mutex m_mutex;
        std::queue<T> m_stack;
        std::condition_variable m_observers;
        
        void emptyStack(){
            while(!m_stack.empty())
            {
                m_stack.pop();
            }
        }
    };
}

#endif /* WORKQUEUE_H */