#include <iostream>

using namespace std;

int main() {
    // 页面访问序列
    int page_sequence[] = {3, 4, 2, 6, 4, 3, 7, 4, 3, 6, 3, 4, 8, 4, 6};
    int sequence_length = sizeof(page_sequence) / sizeof(page_sequence[0]);
    int num_pages = 3; // 内存中可以存放的页面数
    int num_faults = 0; // 缺页次数
    int hits = 0; // 命中次数

    int memory[3] = {-1, -1, -1}; // 用于存放当前内存中的页面
    int last_used[3] = {0, 0, 0}; // 记录每个页面上次使用的时间

    for (int time = 0; time < sequence_length; ++time) {
        int page = page_sequence[time];
        bool hit = false;

        // 检查页面是否在内存中
        for (int i = 0; i < num_pages; ++i) {
            if (memory[i] == page) {
                hits++;
                last_used[i] = time; // 更新该页面的上次使用时间
                hit = true;
                break;
            }
        }

        if (!hit) {
            // 页面未命中，缺页
            num_faults++;

            // 找到最近最少使用的页面进行替换
            int lru_index = 0;
            for (int i = 1; i < num_pages; ++i) {
                if (memory[i] == -1) { // 找到空闲位置
                    lru_index = i;
                    break;
                }
                if (last_used[i] < last_used[lru_index]) {
                    lru_index = i;
                }
            }

            memory[lru_index] = page; // 替换页面
            last_used[lru_index] = time; // 更新使用时间
        }

        // 输出当前内存状态
        cout << "Time " << time << ": Page " << page << " => Memory: ";
        for (int i = 0; i < num_pages; ++i) {
            if (memory[i] == -1) {
                cout << "[] ";
            } else {
                cout << "[" << memory[i] << "] ";
            }
        }
        cout << endl;
    }

    double hit_rate = static_cast<double>(hits) / sequence_length;
    double fault_rate = static_cast<double>(num_faults) / sequence_length;

    cout << "缺页次数: " << num_faults << endl;
    cout << "命中率: " << hit_rate << endl;

    return 0;
}
