#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include<iostream>
using namespace std;

#define sleep(n) Sleep(n*1000)
struct ThreadInfo
{
    int tid;        //线程ID
    char role;      //扮演角色R or W
    double delay;   //线程延迟
    double persist; //线程读写操作持续时间
};
HANDLE Empty;
HANDLE mutex;
HANDLE Full;
void ProducersThread(LPVOID lpParam)
{
    ThreadInfo* info = (ThreadInfo*)lpParam;
    sleep(info->delay);//模拟延时时间
    printf("Producer thread %d sents the producting require.\n",info->tid);
    printf("Producer thread %d begins to product item.\n", info->tid);
    sleep(info->persist); // 模拟持续时间
    printf("Producer thread %d finished  producting item.\n", info->tid);
    WaitForSingleObject(Empty, -1);
    WaitForSingleObject(mutex, -1);//对传送带互斥访问
    printf("Producer thread %d had set the item.\n", info->tid);
    ReleaseSemaphore(mutex, 1, NULL);
    ReleaseSemaphore(Full, 1, NULL);
}

void ConsumersThread(LPVOID lpParam) {
    ThreadInfo* info = (ThreadInfo*)lpParam;
    sleep(info->delay);
    printf("Consumer thread %d sents the consuming require.\n",info->tid);
    WaitForSingleObject(Full, -1);
    WaitForSingleObject(mutex, -1);
    ReleaseSemaphore(mutex, 1, NULL);//释放资源
    ReleaseSemaphore(Empty, 1, NULL);//释放资源
    printf("Consumer thread %d begins to consume the item.\n", info->tid);
    sleep(info->persist);  // 模拟持续时间
    printf("Consumer thread %d finished  consuming the file.\n", info->tid);
}

int main()
{
    DWORD n_thread=0;       //线程数目
    DWORD thread_ID;        //线程ID
    //线程对象数组
    HANDLE h_thread[20];
    ThreadInfo thread_info[20];
    //创建互斥量
    Empty=CreateSemaphore(NULL,10,10,LPCSTR("mutex_for_readcount"));
    Full = CreateSemaphore(NULL, 0, 10, "mutex_for_writercount");
    mutex = CreateSemaphore(NULL, 1, 1, NULL);//
    //读取输入文件
    cout<<"Producers and Consumers questions:"<<endl;
    cout<<endl;
    ifstream inFile;
    inFile.open("../data2.txt");
    if(!inFile) {
        printf("erroe in open file!\n");
        return -1;
    }
    while(inFile>>thread_info[n_thread].tid) {
        inFile>>thread_info[n_thread].role;
        inFile>>thread_info[n_thread].delay;
        inFile>>thread_info[n_thread].persist;
        inFile.get();
        n_thread++;
    }
    //创建线程
    for (int i = 0; i < n_thread; i++ )
    {
        if(thread_info[i].role=='P'||thread_info[i].role=='p')
        {
            h_thread[i]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)(ProducersThread),&thread_info[i],0,&thread_ID);
        }
        else
        {
            h_thread[i] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)(ConsumersThread),&thread_info[i],0,&thread_ID);
        }
    }
    //等待所有线程结束
    DWORD wait_for_all=WaitForMultipleObjects(n_thread,h_thread,true,-1);
    cout<<endl;
    printf("Allreader and eriter have finished operating !\n");
    _getch();
    return 0;

}