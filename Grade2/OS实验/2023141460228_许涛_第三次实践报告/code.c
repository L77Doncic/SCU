#include <stdio.h>
#include <stdlib.h>

// 进程状态枚举
typedef enum {
    READY,
    RUNNING,
    TERMINATED
} ProcessState;

// 进程控制块（PCB）
typedef struct PCB {
    int pid;            // 进程ID
    int arrival_time;   // 到达时间
    int burst_time;     // 执行时间
    int priority;       // 优先级（仅用于优先级调度）
    int start_time;     // 开始时间
    int finish_time;    // 结束时间
    ProcessState state; // 进程状态
    struct PCB *next;   // 链表指针
} PCB;

// 全局变量：就绪队列头指针
PCB *ready_queue = NULL;

// 函数声明
void add_to_ready_queue(PCB *proc);
void schedule_fcfs();
void schedule_priority();
void print_schedule_result();

// 添加进程到就绪队列（按到达时间排序，FCFS用）
void add_to_ready_queue(PCB *proc) {
    if (ready_queue == NULL || proc->arrival_time < ready_queue->arrival_time) {
        proc->next = ready_queue;
        ready_queue = proc;
    } else {
        PCB *current = ready_queue;
        while (current->next != NULL && current->next->arrival_time <= proc->arrival_time) {
            current = current->next;
        }
        proc->next = current->next;
        current->next = proc;
    }
}

// FCFS调度算法
void schedule_fcfs() {
    int current_time = 0;
    PCB *current_proc = ready_queue;
    while (current_proc != NULL) {
        if (current_time < current_proc->arrival_time) {
            current_time = current_proc->arrival_time;
        }
        current_proc->start_time = current_time;
        current_proc->finish_time = current_time + current_proc->burst_time;
        current_proc->state = RUNNING;
        printf("Time %d: Process %d starts (FCFS)\n", current_time, current_proc->pid);
        current_time = current_proc->finish_time;
        current_proc->state = TERMINATED;
        current_proc = current_proc->next;
    }
}

// 优先级调度算法（非抢占式）
void schedule_priority() {
    int current_time = 0;
    PCB *temp_queue = NULL;  // 临时队列用于保存已调度进程
    
    while (ready_queue != NULL) {
        // 找到当前就绪队列中优先级最高的进程
        PCB *prev = NULL, *highest_prev = NULL, *highest = ready_queue;
        PCB *current = ready_queue, *prev_current = NULL;
        while (current != NULL) {
            if (current->arrival_time <= current_time && current->priority < highest->priority) {
                highest = current;
                highest_prev = prev_current;
            }
            prev_current = current;
            current = current->next;
        }
        
        // 如果当前没有进程到达，时间推进到下一个到达时间
        if (highest->arrival_time > current_time) {
            current_time = highest->arrival_time;
        }
        
        // 执行进程
        highest->start_time = current_time;
        highest->finish_time = current_time + highest->burst_time;
        highest->state = RUNNING;
        printf("Time %d: Process %d starts (Priority)\n", current_time, highest->pid);
        current_time = highest->finish_time;
        highest->state = TERMINATED;
        
        // 从就绪队列中移除该进程（但不释放内存）
        if (highest_prev == NULL) {
            ready_queue = highest->next;
        } else {
            highest_prev->next = highest->next;
        }
        
        // 将已调度的进程添加到临时队列以便后续打印
        highest->next = temp_queue;
        temp_queue = highest;
    }
    
    // 恢复就绪队列以便打印结果
    ready_queue = temp_queue;
}

// 打印调度结果
void print_schedule_result() {
    printf("\nScheduling Result:\n");
    printf("PID\tArrival\tBurst\tStart\tFinish\n");
    PCB *proc = ready_queue;
    while (proc != NULL) {
        printf("%d\t%d\t%d\t%d\t%d\n",
               proc->pid,
               proc->arrival_time,
               proc->burst_time,
               proc->start_time,
               proc->finish_time);
        proc = proc->next;
    }
}

int main() {
    int n, algorithm;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Choose algorithm (1-FCFS, 2-Priority): ");
    scanf("%d", &algorithm);

    // 输入进程信息
    for (int i = 0; i < n; i++) {
        PCB *proc = (PCB *)malloc(sizeof(PCB));
        printf("Process %d: Arrival Time, Burst Time, Priority: ", i + 1);
        scanf("%d %d %d", &proc->arrival_time, &proc->burst_time, &proc->priority);
        proc->pid = i + 1;
        proc->state = READY;
        proc->next = NULL;
        add_to_ready_queue(proc);
    }

    // 执行调度算法
    if (algorithm == 1) {
        schedule_fcfs();
    } else {
        schedule_priority();
    }

    // 输出结果
    print_schedule_result();

    // 释放内存
    PCB *current = ready_queue;
    while (current != NULL) {
        PCB *temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}