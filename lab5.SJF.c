#include <stdio.h>

int main() {
    int n, i, complete = 0, current_time = 0;
    int burst_time[10], arrival_time[10], remaining_time[10];
    int waiting_time[10] = {0}, turnaround_time[10] = {0}, completion_time[10] = {0};

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst times for each process
    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];  // Initialize remaining time
    }

    // Input arrival times for each process
    printf("Enter arrival times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }

    // Start SRTF scheduling
    while (complete < n) {
        int shortest_job = -1, min_time = 9999;

        // Find the process with the shortest remaining time that has arrived
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0 && remaining_time[i] < min_time) {
                shortest_job = i;
                min_time = remaining_time[i];
            }
        }

        // If no process is available, increment time
        if (shortest_job == -1) {
            current_time++;
        } else {
            // Execute the selected process for 1 time unit
            remaining_time[shortest_job]--;
            current_time++;

            // Check if the process is complete
            if (remaining_time[shortest_job] == 0) {
                complete++;  // Increment the count of completed processes
                
                // Calculate completion time for the finished process
                completion_time[shortest_job] = current_time;

                // Calculate TAT and WT using the formulas
                turnaround_time[shortest_job] = completion_time[shortest_job] - arrival_time[shortest_job]; // TAT = CT - AT
                waiting_time[shortest_job] = turnaround_time[shortest_job] - burst_time[shortest_job];     // WT = TAT - BT
            }
        }
    }

    // Display results in a formatted table
    double avg_waiting = 0, avg_turnaround = 0;
    printf("\nProcess\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%9d\t%12d\t%15d\t%15d\t%12d\n", i + 1, burst_time[i], arrival_time[i], completion_time[i], turnaround_time[i], waiting_time[i]);
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }

    // Calculate and display average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f", avg_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround / n);

    return 0;
}
/*

student@student:~$ gcc TIA30_OS_5.c
student@student:~$ ./a.out
Enter the number of processes: 5        
Enter the burst time for each process:
Burst time for process 1: 2
Burst time for process 2: 4
Burst time for process 3: 6
Burst time for process 4: 3
Burst time for process 5: 8
Enter arrival times for each process:
Arrival time for process 1: 0
Arrival time for process 2: 3
Arrival time for process 3: 2
Arrival time for process 4: 1
Arrival time for process 5: 4


Process	Burst Time	Arrival Time	Waiting Time	Turnaround Time
P1	2		0		0		2
P2	4		3		2		6
P3	6		2		7		13
P4	3		1		1		4
P5	8		4		11		19

Average Waiting Time: 4.200000


notes::Here's a simpler version of the code that performs the same task with minimal structure and comments to help understand the core steps. This program calculates the waiting and turnaround times for processes based on the Shortest Job First (SJF) algorithm with arrival times.

Inputs: Burst time and arrival time are entered for each process.
SJF Algorithm: At each time unit, the code finds the process with the shortest remaining burst time that has arrived.
Waiting and Turnaround Time Calculation: When a process finishes, it calculates waiting and turnaround times.
Averages: Finally, it calculates and displays the average waiting and turnaround times.

*/
