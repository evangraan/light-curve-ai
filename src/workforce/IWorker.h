/* 
 * File:   IWorker.h
 * Author: ernstv
 *
 * Created on August 10, 2019, 3:06 PM
 */

#ifndef IWORKER_H
#define IWORKER_H

namespace WorkerThreading
{
    class IWorker
    {
    public:
        IWorker(void) = default;
        virtual ~IWorker(void) = default;
        IWorker(const IWorker& rhs) = delete;
        IWorker& operator=(const IWorker& rhs) = delete;
        IWorker(IWorker&& other) = default;
        IWorker& operator=(IWorker&& other) = default;
        virtual void execute() = 0;
    };
}
#endif /* IWORKER_H */

