#include "Worker.h"

Worker::Worker(double pay, double companyPay)
{
    tasksDone = 0;
    earnings = 0.0;
    companyEarnings = 0.0;
    payPerTask = pay;
    companyPerTask = companyPay;
}

void Worker::completeTask()
{
    tasksDone++;
    earnings = earnings + payPerTask;
    companyEarnings = companyEarnings + companyPerTask;
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
