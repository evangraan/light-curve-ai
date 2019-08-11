#ifndef WORKQUEUE_H
#define WORKQUEUE_H

#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

using namespace std;

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
            lock_guard<mutex> lock{m_mutex};
            if(m_stack.empty() || !m_valid)
            {
                return false;
            }
            out = move(m_stack.front());
            m_stack.pop();
            return true;
        }
        
        bool dequeueBlocking(T& out)
        {
            unique_lock<mutex> lock{m_mutex};
            
            m_observers.wait(lock, [this]()
            {
                return !m_stack.empty() || !m_valid;
            });
            if (m_valid){
                out = move(m_stack.front());
                m_stack.pop();
            }
            return m_valid;
        }

        void enqueue(T value)
        {
            lock_guard<mutex> lock{m_mutex};
            m_stack.push(move(value));
            m_observers.notify_one();
        }

        bool isEmpty(void) const
        {
            lock_guard<mutex> lock{m_mutex};
            return m_stack.empty();
        }

        void flush(void)
        {
            lock_guard<mutex> lock{m_mutex};
            emptyStack();
            m_observers.notify_all();
        }

        void invalidate(void)
        {
            lock_guard<mutex> lock{m_mutex};
            m_valid = false;
            m_observers.notify_all();
        }

        bool isValid(void) const
        {
            lock_guard<mutex> lock{m_mutex};
            return m_valid;
        }

    private:
        atomic_bool m_valid{true};
        mutable mutex m_mutex;
        queue<T> m_stack;
        condition_variable m_observers;
        
        void emptyStack(){
            while(!m_stack.empty())
            {
                m_stack.pop();
            }
        }
    };
}

#endif /* WORKQUEUE_H */