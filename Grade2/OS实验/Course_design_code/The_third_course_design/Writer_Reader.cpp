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
int ReadCount = 0;
int WriterCount = 0;
HANDLE Rmutex;              //用于读者只能一个访问ReadCount
HANDLE Wmutex;              //用于写者只能有一个访问Writercount
HANDLE RW_mutex;             //避免写者与多个读者竞争
HANDLE mutex;               //读写互斥
HANDLE OneWmutex;           //控制能否写（只能有一个写者同时写，同时避免读时写入）
void ReaderThread(LPVOID lpParam)
{
    ThreadInfo* info = (ThreadInfo*)lpParam;
    sleep(info->delay);//模拟延时时间
    printf("Reader thread %d sents the reading require.\n",info->tid);

    //WaitForSingleObject(RW_mutex, -1);
    WaitForSingleObject(mutex, -1);
    WaitForSingleObject(Rmutex, -1);//对readercount互斥访问
    if (ReadCount == 0)WaitForSingleObject(OneWmutex, -1);//第一位读者申请书,同时防止写者进行写操作
    ReadCount++;

    ReleaseSemaphore(Rmutex, 1, NULL);//释放互斥信号量
    ReleaseSemaphore(mutex, 1, NULL);//释放互斥信号量
   // ReleaseSemaphore(RW_mutex, 1, NULL);//释放互斥信号量

    printf("Reader thread %d begins to read file.\n", info->tid);
    sleep(info->persist); // 模拟持续时间
    printf("Reader thread %d finished  reading file.\n", info->tid);

    WaitForSingleObject(Rmutex, -1);//修改readercount
    ReadCount--;
    if (ReadCount == 0)     ReleaseSemaphore(OneWmutex, 1, NULL);//释放资源，写者可写
    ReleaseSemaphore(Rmutex, 1, NULL);//释放互斥信号量
}

void WriterThread(LPVOID lpParam) {
    ThreadInfo* info = (ThreadInfo*)lpParam;
    sleep(info->delay);
    printf("Writer thread %d sents the writing require.\n",info->tid);
    WaitForSingleObject(Wmutex, -1);//对writercount互斥访问
    if (WriterCount == 0)WaitForSingleObject(mutex, -1);//第一位写者申请资源
    WriterCount++;
    ReleaseSemaphore(Wmutex, 1, NULL);//释放资源

    WaitForSingleObject(OneWmutex, -1);
    printf("Writer thread %d begins to write to the file.\n", info->tid);
    sleep(info->persist);  // 模拟持续时间
    printf("Writer thread %d finished  writing to the file.\n", info->tid);
    ReleaseSemaphore(OneWmutex, 1, NULL);//释放资源

    WaitForSingleObject(Wmutex, -1);//对writercount互斥访问
    WriterCount--;
    if (WriterCount == 0)ReleaseSemaphore(mutex, 1, NULL);//释放资源
    ReleaseSemaphore(Wmutex, 1, NULL);
}

int main()
{
    DWORD n_thread=0;       //线程数目
    DWORD thread_ID;        //线程ID
    //线程对象数组
    HANDLE h_thread[20];
    ThreadInfo thread_info[20];
    //创建互斥量
    Rmutex=CreateMutex(NULL,FALSE,LPCSTR("mutex_for_readcount"));
    Wmutex = CreateSemaphore(NULL, 1, 1, "mutex_for_writercount");//写者对count修改互斥信号量，初值为1,最大为1
    OneWmutex = CreateSemaphore(NULL, 1, 1, NULL);//
    mutex = CreateSemaphore(NULL, 1, 1, NULL);//
    RW_mutex = CreateSemaphore(NULL, 1, 1, NULL);
    //读取输入文件
    cout<<"Writer Priority:"<<endl;
    cout<<endl;
    ifstream inFile;
    inFile.open("../data.txt");
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
        if(thread_info[i].role=='R'||thread_info[i].role=='r')
        {
            h_thread[i]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)(ReaderThread),&thread_info[i],0,&thread_ID);
        }
        else
        {
            h_thread[i] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)(WriterThread),&thread_info[i],0,&thread_ID);
        }
    }
    //等待所有线程结束
    DWORD wait_for_all=WaitForMultipleObjects(n_thread,h_thread,true,-1);
    cout<<endl;
    printf("Allreader and eriter have finished operating !\n");
    _getch();
    return 0;

}