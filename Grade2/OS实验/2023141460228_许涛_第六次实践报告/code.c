#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义指令序列的长度为 320
#define INSTRUCTION_COUNT 320
// 定义页面大小为 1KB
#define PAGE_SIZE 1024
// 定义用户虚拟内存大小为 32KB
#define USER_VIRTUAL_MEMORY 32768
// 定义用户内存最小页面数为 4
#define USER_MEMORY_MIN_PAGES 4
// 定义用户内存最大页面数为 32
#define USER_MEMORY_MAX_PAGES 32

// 函数：生成指令序列
// 参数：instruction_sequence - 存储生成的指令序列的数组
// 说明：使用随机数生成器生成一个包含 320 条指令的序列
void generate_instruction_sequence(int *instruction_sequence) {
    // 初始化随机数生成器，使用当前时间作为种子
    srand(time(NULL));
    // 循环生成 320 个随机指令
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        // 每个指令对应一个页面号，页面号范围为 0 到 (USER_VIRTUAL_MEMORY / PAGE_SIZE - 1)
        instruction_sequence[i] = rand() % (USER_VIRTUAL_MEMORY / PAGE_SIZE);
    }
}

// 函数：FIFO 页面置换算法
// 参数：page_sequence - 页面序列，memory_size - 内存页面数
// 返回值：命中率
// 说明：模拟 FIFO 页面置换算法，计算页面失效次数并返回命中率
double fifo_algorithm(int *page_sequence, int memory_size) {
    // 定义内存数组，用于存储当前内存中的页面
    int memory[memory_size];
    // 定义队列数组，用于维护页面进入内存的顺序
    int queue[memory_size];
    // 初始化页面失效次数为 0
    int page_faults = 0;
    // 初始化队列前端指针
    int front = 0;

    // 初始化内存和队列，初始时内存和队列为空（用 -1 表示）
    for (int i = 0; i < memory_size; i++) {
        memory[i] = -1;
        queue[i] = -1;
    }

    // 遍历页面序列中的每个页面
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        int page = page_sequence[i];
        // 标志位，表示页面是否命中（存在于内存中）
        int hit = 0;

        // 检查页面是否存在于内存中
        for (int j = 0; j < memory_size; j++) {
            if (memory[j] == page) {
                hit = 1;
                break;
            }
        }

        // 如果页面未命中
        if (!hit) {
            page_faults++; // 增加页面失效次数
            // 如果内存未满
            if (front < memory_size) {
                memory[front] = page; // 将新页面放入内存
                queue[front] = page; // 将新页面加入队列
                front++; // 移动队列前端指针
            } else {
                // 如果内存已满，移除队列前端的页面并加入新页面
                for (int j = 0; j < memory_size - 1; j++) {
                    queue[j] = queue[j + 1]; // 移动队列中的页面
                    memory[j] = memory[j + 1]; // 移动内存中的页面
                }
                memory[memory_size - 1] = page; // 将新页面放入内存末尾
                queue[memory_size - 1] = page; // 将新页面加入队列末尾
            }
        }
    }

    // 计算并返回命中率
    return 1.0 - (double)page_faults / INSTRUCTION_COUNT;
}

// 函数：LRU 页面置换算法
// 参数：page_sequence - 页面序列，memory_size - 内存页面数
// 返回值：命中率
// 说明：模拟 LRU 页面置换算法，计算页面失效次数并返回命中率
double lru_algorithm(int *page_sequence, int memory_size) {
    // 定义内存数组，用于存储当前内存中的页面
    int memory[memory_size];
    // 初始化页面失效次数为 0
    int page_faults = 0;

    // 初始化内存，初始时内存为空（用 -1 表示）
    for (int i = 0; i < memory_size; i++) {
        memory[i] = -1;
    }

    // 遍历页面序列中的每个页面
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        int page = page_sequence[i];
        // 标志位，表示页面是否命中（存在于内存中）
        int hit = 0;

        // 检查页面是否存在于内存中
        for (int j = 0; j < memory_size; j++) {
            if (memory[j] == page) {
                hit = 1;
                // 将最近访问的页面移到内存末尾（表示最近使用）
                for (int k = j; k > 0; k--) {
                    memory[k] = memory[k - 1];
                }
                memory[0] = page;
                break;
            }
        }

        // 如果页面未命中
        if (!hit) {
            page_faults++; // 增加页面失效次数
            // 如果内存未满
            if (memory_size > 0) {
                // 将新页面放入内存末尾
                for (int j = memory_size - 1; j > 0; j--) {
                    memory[j] = memory[j - 1];
                }
                memory[0] = page;
            }
        }
    }

    // 计算并返回命中率
    return 1.0 - (double)page_faults / INSTRUCTION_COUNT;
}

// 函数：OPT 页面置换算法
// 参数：page_sequence - 页面序列，memory_size - 内存页面数
// 返回值：命中率
// 说明：模拟 OPT 页面置换算法，计算页面失效次数并返回命中率
double opt_algorithm(int *page_sequence, int memory_size) {
    // 定义内存数组，用于存储当前内存中的页面
    int memory[memory_size];
    // 初始化页面失效次数为 0
    int page_faults = 0;

    // 初始化内存，初始时内存为空（用 -1 表示）
    for (int i = 0; i < memory_size; i++) {
        memory[i] = -1;
    }

    // 遍历页面序列中的每个页面
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        int page = page_sequence[i];
        // 标志位，表示页面是否命中（存在于内存中）
        int hit = 0;

        // 检查页面是否存在于内存中
        for (int j = 0; j < memory_size; j++) {
            if (memory[j] == page) {
                hit = 1;
                break;
            }
        }

        // 如果页面未命中
        if (!hit) {
            page_faults++; // 增加页面失效次数

            // 如果内存已满
            if (memory_size > 0 && memory[memory_size - 1] != -1) {
                // 查找要替换的页面（以后最长时间不被访问的页面）
                int replace_index = 0;
                int max_distance = -1;

                // 遍历内存中的每个页面
                for (int j = 0; j < memory_size; j++) {
                    int distance = -1;
                    // 查找页面在后续页面序列中出现的位置，计算距离
                    for (int k = i + 1; k < INSTRUCTION_COUNT; k++) {
                        if (page_sequence[k] == memory[j]) {
                            distance = k - i;
                            break;
                        }
                    }

                    // 如果页面在后续序列中不再出现或距离更远，则更新要替换的页面索引
                    if (distance == -1 || distance > max_distance) {
                        max_distance = distance;
                        replace_index = j;
                    }
                }

                // 将新页面放入内存中要替换的位置
                for (int j = replace_index; j > 0; j--) {
                    memory[j] = memory[j - 1];
                }
                memory[0] = page;
            } else {
                // 如果内存未满，将新页面放入内存末尾
                for (int j = memory_size - 1; j > 0; j--) {
                    memory[j] = memory[j - 1];
                }
                memory[0] = page;
            }
        }
    }

    // 计算并返回命中率
    return 1.0 - (double)page_faults / INSTRUCTION_COUNT;
}

// 主函数
int main() {
    // 定义指令序列数组，长度为 320
    int instruction_sequence[INSTRUCTION_COUNT];
    // 定义页面序列数组，用于存储转换后的页面序列
    int page_sequence[INSTRUCTION_COUNT];

    // 生成指令序列
    generate_instruction_sequence(instruction_sequence);

    // 将指令序列转换为页面序列（这里直接复制，因为每个指令对应一个页面）
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        page_sequence[i] = instruction_sequence[i];
    }

    // 输出表格标题
    printf("\n页面置换算法命中率对比\n");
    printf("内存容量(页) | FIFO命中率 | LRU命中率 | OPT命中率\n");
    printf("--------------------------------------------\n");

    // 遍历不同的内存页面数
    for (int memory_size = USER_MEMORY_MIN_PAGES; memory_size <= USER_MEMORY_MAX_PAGES; memory_size++) {
        // 调用 FIFO 算法，计算命中率
        double fifo_hit_rate = fifo_algorithm(page_sequence, memory_size);
        // 调用 LRU 算法，计算命中率
        double lru_hit_rate = lru_algorithm(page_sequence, memory_size);
        // 调用 OPT 算法，计算命中率
        double opt_hit_rate = opt_algorithm(page_sequence, memory_size);

        // 输出结果
        printf("%d | %.4f | %.4f | %.4f\n", memory_size, fifo_hit_rate, lru_hit_rate, opt_hit_rate);
    }

    return 0;
}