#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTITIONS 100
#define MEMORY_SIZE 640 // 总内存大小（单位：KB）

// 分区结构体
typedef struct Partition {
    int start;       // 分区起始地址
    int size;        // 分区大小
    int isFree;      // 是否为空闲分区（1表示空闲，0表示已分配）
    char name[10];   // 分区名称（用于区分作业）
} Partition;

// 全局分区表
Partition partitions[MAX_PARTITIONS];
int partitionCount = 0; // 当前分区数量

// 初始化内存
void initMemory() {
    partitions[0].start = 0;
    partitions[0].size = MEMORY_SIZE;
    partitions[0].isFree = 1;
    strcpy(partitions[0].name, "Free");
    partitionCount = 1;
}

// 打印分区表
void printPartitions() {
    printf("分区表情况：\n");
    printf("分区名称\t起始地址\t大小\t状态\n");
    for (int i = 0; i < partitionCount; i++) {
        printf("%s\t\t%d\t\t%d\t%s\n", partitions[i].name,
               partitions[i].start, partitions[i].size,
               partitions[i].isFree ? "空闲" : "已分配");
    }
    printf("\n");
}

// 合并相邻的空闲分区
void coalesceFreePartitions() {
    for (int i = 0; i < partitionCount - 1; i++) {
        if (partitions[i].isFree && partitions[i + 1].isFree) {
            partitions[i].size += partitions[i + 1].size;
            partitions[i].isFree = 1;
            strcpy(partitions[i].name, "Free");
            memmove(&partitions[i + 1], &partitions[i + 2], sizeof(Partition) * (partitionCount - i - 2));
            partitionCount--;
            i--; // 重新检查当前位置，因为数组已经改变
        }
    }
}

// 首次适应算法
int firstFit(int size, char *name) {
    for (int i = 0; i < partitionCount; i++) {
        if (partitions[i].isFree && partitions[i].size >= size) {
            partitions[i].isFree = 0;
            strcpy(partitions[i].name, name);
            if (partitions[i].size > size) {
                Partition newPartition;
                newPartition.start = partitions[i].start + size;
                newPartition.size = partitions[i].size - size;
                newPartition.isFree = 1;
                strcpy(newPartition.name, "Free");
                partitions[i].size = size;
                for (int j = partitionCount; j > i + 1; j--) {
                    partitions[j] = partitions[j - 1];
                }
                partitions[i + 1] = newPartition;
                partitionCount++;
            }
            return 1; // 分配成功
        }
    }
    return 0; // 分配失败
}

// 最佳适应算法
int bestFit(int size, char *name) {
    int bestIndex = -1;
    int minSize = MEMORY_SIZE + 1;
    for (int i = 0; i < partitionCount; i++) {
        if (partitions[i].isFree && partitions[i].size >= size && partitions[i].size < minSize) {
            bestIndex = i;
            minSize = partitions[i].size;
        }
    }
    if (bestIndex != -1) {
        partitions[bestIndex].isFree = 0;
        strcpy(partitions[bestIndex].name, name);
        if (partitions[bestIndex].size > size) {
            Partition newPartition;
            newPartition.start = partitions[bestIndex].start + size;
            newPartition.size = partitions[bestIndex].size - size;
            newPartition.isFree = 1;
            strcpy(newPartition.name, "Free");
            partitions[bestIndex].size = size;
            for (int j = partitionCount; j > bestIndex + 1; j--) {
                partitions[j] = partitions[j - 1];
            }
            partitions[bestIndex + 1] = newPartition;
            partitionCount++;
        }
        return 1; // 分配成功
    }
    return 0; // 分配失败
}

// 最坏适应算法
int worstFit(int size, char *name) {
    int worstIndex = -1;
    int maxSize = 0;
    for (int i = 0; i < partitionCount; i++) {
        if (partitions[i].isFree && partitions[i].size >= size && partitions[i].size > maxSize) {
            worstIndex = i;
            maxSize = partitions[i].size;
        }
    }
    if (worstIndex != -1) {
        partitions[worstIndex].isFree = 0;
        strcpy(partitions[worstIndex].name, name);
        if (partitions[worstIndex].size > size) {
            Partition newPartition;
            newPartition.start = partitions[worstIndex].start + size;
            newPartition.size = partitions[worstIndex].size - size;
            newPartition.isFree = 1;
            strcpy(newPartition.name, "Free");
            partitions[worstIndex].size = size;
            for (int j = partitionCount; j > worstIndex + 1; j--) {
                partitions[j] = partitions[j - 1];
            }
            partitions[worstIndex + 1] = newPartition;
            partitionCount++;
        }
        return 1; // 分配成功
    }
    return 0; // 分配失败
}

// 回收分区
void freePartition(char *name) {
    for (int i = 0; i < partitionCount; i++) {
        if (!partitions[i].isFree && strcmp(partitions[i].name, name) == 0) {
            partitions[i].isFree = 1;
            strcpy(partitions[i].name, "Free");
            coalesceFreePartitions(); // 合并相邻的空闲分区
            break;
        }
    }
}

int main() {
    initMemory();
    printf("初始内存情况：\n");
    printPartitions();

    // 选择分配算法
    int algorithm = 0;
    printf("请选择分配算法：\n");
    printf("1. 首次适应算法 (First Fit)\n");
    printf("2. 最佳适应算法 (Best Fit)\n");
    printf("3. 最坏适应算法 (Worst Fit)\n");
    scanf("%d", &algorithm);

    int (*allocFunc)(int, char *) = NULL; // 分配函数指针
    switch (algorithm) {
        case 1:
            allocFunc = firstFit;
            printf("选择了首次适应算法 (First Fit)。\n");
            break;
        case 2:
            allocFunc = bestFit;
            printf("选择了最佳适应算法 (Best Fit)。\n");
            break;
        case 3:
            allocFunc = worstFit;
            printf("选择了最坏适应算法 (Worst Fit)。\n");
            break;
        default:
            printf("无效选择，退出程序。\n");
            return 1;
    }

    // 用户输入作业请求
    while (1) {
        printf("请输入作业请求（格式：申请(allocate)/释放(release) 作业名 空间大小，退出请输入exit）：\n");
        char command[20];
        char name[10];
        int size;
        if (scanf("%s", command) != 1 || strcmp(command, "exit") == 0) {
            break;
        }
        scanf("%s %d", name, &size);

        // 支持中英文命令
        if (strcmp(command, "申请") == 0 || strcmp(command, "allocate") == 0) {
            if (allocFunc(size, name)) {
                printf("分配成功：%s\n", name);
            } else {
                printf("分配失败，没有足够的空闲空间。\n");
            }
        } else if (strcmp(command, "释放") == 0 || strcmp(command, "release") == 0) {
            freePartition(name);
            printf("释放成功：%s\n", name);
        } else {
            printf("无效命令，请重新输入。\n");
        }
        printPartitions(); // 打印当前分区表
    }

    // 退出程序前清空所有数据
    initMemory(); // 重新初始化内存到初始状态
    printf("退出程序，内存恢复到初始状态\n");

    return 0;
}