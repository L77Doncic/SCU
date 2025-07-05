#include <iostream>

using namespace std;

int main() {
    // ҳ���������
    int page_sequence[] = {3, 4, 2, 6, 4, 3, 7, 4, 3, 6, 3, 4, 8, 4, 6};
    int sequence_length = sizeof(page_sequence) / sizeof(page_sequence[0]);
    int num_pages = 3; // �ڴ��п��Դ�ŵ�ҳ����
    int num_faults = 0; // ȱҳ����
    int hits = 0; // ���д���

    int memory[3] = {-1, -1, -1}; // ���ڴ�ŵ�ǰ�ڴ��е�ҳ��
    int last_used[3] = {0, 0, 0}; // ��¼ÿ��ҳ���ϴ�ʹ�õ�ʱ��

    for (int time = 0; time < sequence_length; ++time) {
        int page = page_sequence[time];
        bool hit = false;

        // ���ҳ���Ƿ����ڴ���
        for (int i = 0; i < num_pages; ++i) {
            if (memory[i] == page) {
                hits++;
                last_used[i] = time; // ���¸�ҳ����ϴ�ʹ��ʱ��
                hit = true;
                break;
            }
        }

        if (!hit) {
            // ҳ��δ���У�ȱҳ
            num_faults++;

            // �ҵ��������ʹ�õ�ҳ������滻
            int lru_index = 0;
            for (int i = 1; i < num_pages; ++i) {
                if (memory[i] == -1) { // �ҵ�����λ��
                    lru_index = i;
                    break;
                }
                if (last_used[i] < last_used[lru_index]) {
                    lru_index = i;
                }
            }

            memory[lru_index] = page; // �滻ҳ��
            last_used[lru_index] = time; // ����ʹ��ʱ��
        }

        // �����ǰ�ڴ�״̬
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

    cout << "ȱҳ����: " << num_faults << endl;
    cout << "������: " << hit_rate << endl;

    return 0;
}
