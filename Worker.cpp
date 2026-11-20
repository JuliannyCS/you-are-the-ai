#include "Worker.h"

Worker::Worker(double payPerTask, double companyPerTask)
    : tasksDone(0), earnings(0.0), companyEarnings(0.0),
      payPerTask(payPerTask), companyPerTask(companyPerTask)
{
    
}

void Worker::completeTask()
{
    ++tasksDone;
    earnings += payPerTask;
    companyEarnings += companyPerTask;
}

int Worker::getTasksDone() const
{
    return tasksDone;
}

double Worker::getEarnings() const
{
    return earnings;
}

double Worker::getCompanyEarnings() const
{
    return companyEarnings;
}
