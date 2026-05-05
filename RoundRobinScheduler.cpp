#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

class Process {
public:
int id;
int arrivalTime;
int burstTime;
int remainingTime;
int completionTime;
int turnaroundTime;
int waitingTime;


Process(int id, int at, int bt) {
    this->id = id;
    arrivalTime = at;
    burstTime = bt;
    remainingTime = bt;
    completionTime = turnaroundTime = waitingTime = 0;
}


};

class RoundRobinScheduler {
private:
    vector<Process> processes;
    queue<int> readyQueue;
        int timeQuantum;
        int currentTime;
        int completed;
        int nextIndex;

public:
RoundRobinScheduler(int tq) {
    timeQuantum = tq;
    currentTime = 0;
    completed = 0;
    nextIndex = 0;
}


void addProcess(int id, int at, int bt) {
    processes.push_back(Process(id, at, bt));
}

void addArrivedProcesses() {
    while (nextIndex < processes.size() && processes[nextIndex].arrivalTime <= currentTime) {
        readyQueue.push(nextIndex);
        nextIndex++;
    }
}

void printQueue() {
    if (readyQueue.empty()) {
        cout << "[ Empty ]" << endl;
        return;
    }

    queue<int> temp = readyQueue;
    cout << "[ ";
    bool first = true;

    while (!temp.empty()) {
        if (!first) cout << ", ";
        cout << "P" << processes[temp.front()].id;
        temp.pop();
        first = false;
    }

    cout << " ]" << endl;
}

void run() {
    addArrivedProcesses();
    cout << "\nQueue updates:" << endl;
    printQueue();

    while (completed < processes.size()) {

        if (readyQueue.empty()) {
            currentTime = processes[nextIndex].arrivalTime;
            addArrivedProcesses();
            printQueue();
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        int execTime = min(timeQuantum, processes[idx].remainingTime);

        processes[idx].remainingTime -= execTime;
        currentTime += execTime;

        addArrivedProcesses();

        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = currentTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        } else {
            readyQueue.push(idx);
        }
        printQueue();
    }
}

void printResults() {
    cout << "\nProcess  Completion Time  Turnaround Time  Waiting Time\n";

    float totalWaiting = 0;

    for (auto &p : processes) {
        cout << "P" << p.id
             << "       " << p.completionTime
             << "               " << p.turnaroundTime
             << "               " << p.waitingTime << endl;

        totalWaiting += p.waitingTime;
    }

    cout << fixed << setprecision(1);
    cout << "\nAverage Waiting Time: " << totalWaiting / processes.size() << endl;
}


};

int main() {
int n, tq;


cout << "Time Quantum: ";
cin >> tq;

cout << "Number of Processes: ";
cin >> n;

RoundRobinScheduler scheduler(tq);

for (int i = 0; i < n; i++) {
    int at, bt;
    cout << "Arrival Time, Needed Time P" << i + 1 << ": ";
    cin >> at >> bt;

    scheduler.addProcess(i + 1, at, bt);
}

scheduler.run();
scheduler.printResults();

return 0;


}
