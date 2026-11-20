#ifndef WORKER_H
#define WORKER_H

class Worker {
public:
    Worker(double payPerTask, double companyPerTask);

    void completeTask();
    int getTasksDone() const;
    double getEarnings() const;
    double getCompanyEarnings() const;

private:
    int tasksDone;
    double earnings;
    double companyEarnings;
    double payPerTask;
    double companyPerTask;
};

#endif