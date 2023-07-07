#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

void executeFCFS(const vector<Process>& processes) {
    int currentTime = 0;
    int totalWaitingTime = 0;
    
    cout << "FCFS Scheduling:\n";
    
    for (const Process& process : processes) {
        currentTime = max(currentTime, process.arrivalTime);
        int waitingTime = currentTime - process.arrivalTime;
        totalWaitingTime += waitingTime;
        
        cout << "Process " << process.id << ": ";
        cout << "Arrival Time = " << process.arrivalTime << ", ";
        cout << "Burst Time = " << process.burstTime << ", ";
        cout << "Waiting Time = " << waitingTime << endl;
        
        currentTime += process.burstTime;
    }
    
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
    cout << "Average Waiting Time = " << averageWaitingTime << endl << endl;
}

void executeSJN(const vector<Process>& processes) {
    int n = processes.size();
    vector<bool> completed(n, false);
    vector<int> waitingTime(n, 0);
    
    cout << "SJN Scheduling:\n";
    
    for (int i = 0; i < n; i++) {
        int shortestTime = INT_MAX;
        int shortestIndex = -1;
        
        for (int j = 0; j < n; j++) {
            if (!completed[j] && processes[j].arrivalTime <= i && processes[j].burstTime < shortestTime) {
                shortestTime = processes[j].burstTime;
                shortestIndex = j;
            }
            if (shortestIndex != -1) {
            completed[shortestIndex] = true;
            waitingTime[shortestIndex] = i - processes[shortestIndex].arrivalTime;
            
            cout << "Process " << processes[shortestIndex].id << ": ";
            cout << "Arrival Time = " << processes[shortestIndex].arrivalTime << ", ";
            cout << "Burst Time = " << processes[shortestIndex].burstTime << ", ";
            cout << "Waiting Time = " << waitingTime[shortestIndex] << endl;
            
            i += processes[shortestIndex].burstTime - 1;
            }
        }
    }
    
    int totalWaitingTime = 0;
    for (int time : waitingTime) {
        totalWaitingTime += time;
    }
    
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / n;
    cout << "Average Waiting Time = " << averageWaitingTime << endl << endl;
}

void executeRR(const vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    vector<int> remainingTime(n);
    vector<int> waitingTime(n, 0);
    
    queue<int> readyQueue;
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
        readyQueue.push(i);
    }
    
    cout << "Round Robin Scheduling (Time Quantum = " << timeQuantum << "):\n";
    
    int currentTime = 0;
    while (!readyQueue.empty()) {
        int currentProcess = readyQueue.front();
        readyQueue.pop();

        if (remainingTime[currentProcess] <= timeQuantum) {
            waitingTime[currentProcess] += currentTime - processes[currentProcess].arrivalTime;
            currentTime += remainingTime[currentProcess];
            remainingTime[currentProcess] = 0;

            cout << "Process " << processes[currentProcess].id << ": ";
            cout << "Arrival Time = " << processes[currentProcess].arrivalTime << ", ";
            cout << "Burst Time = " << processes[currentProcess].burstTime << ", ";
            cout << "Waiting Time = " << waitingTime[currentProcess] << endl;
        } else {
            remainingTime[currentProcess] -= timeQuantum;
            currentTime += timeQuantum;

            cout << "Process " << processes[currentProcess].id << ": ";
            cout << "Arrival Time = " << processes[currentProcess].arrivalTime << ", ";
            cout << "Burst Time = " << processes[currentProcess].burstTime << ", ";
            cout << "Waiting Time = " << waitingTime[currentProcess] << endl;

            readyQueue.push(currentProcess);
        }
    }

    int totalWaitingTime = 0;
    for (int time : waitingTime) {
        totalWaitingTime += time;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / n;
    cout << "Average Waiting Time = " << averageWaitingTime << endl << endl;
}

int main() {
    vector<Process> processes = {
        {1, 0, 8, 0},
        {2, 1, 4, 0},
        {3, 2, 9, 0},
        {4, 3, 5, 0},
        {5, 4, 2, 0}
    };

    executeFCFS(processes);
    executeSJN(processes);
    executeRR(processes, 3);

    return 0;
}
