#include "Worker.h"
/*I asked copilot on what the constructor parameters/functions should be*/
Worker::Worker(double pay, double companyPay) /*Sets everything to zero but saves the two pay numbers*/
{
    tasksDone = 0;
    earnings = 0.0;
    companyEarnings = 0.0;
    payPerTask = pay;
    companyPerTask = companyPay;
}

void Worker::completeTask() /*Adds 1 to taskdone and adds the pay to earnings*/
{
    tasksDone++;
    earnings = earnings + payPerTask;
    companyEarnings = companyEarnings + companyPerTask;
}

int Worker::getTasksDone() const /*Returns tasksDone value*/
{
    return tasksDone;
}

double Worker::getEarnings() const /*Returns earnings value*/
{
    return earnings;
}

double Worker::getCompanyEarnings() const /*Returns companyEarnings value*/
{
    return companyEarnings;
}
