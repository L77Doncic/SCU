#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
   // system("chcp 65001");
    MEMORYSTATUSEX help1;
    help1.dwLength = sizeof(help1);
    GlobalMemoryStatusEx(&help1);
    cout<<"当前整体存储如下："<<endl;
    cout <<"物理内存总量："<<help1.ullTotalPhys/(1024 * 1024)<<"MB"<<endl;
    cout <<"可用物理内存："<<help1.ullAvailPhys/(1024 * 1024)<<"MB"<<endl;
    cout <<"页文件总量："<<help1.ullTotalPageFile/(1024 * 1024)<<"MB"<<endl;
    cout <<"可用页文件："<<help1.ullAvailPageFile/(1024 * 1024)<<"MB"<<endl;
    cout <<"虚拟内存总量："<<help1.ullTotalVirtual/(1024 * 1024)<<"MB"<<endl;
    cout <<"可用虚拟内存："<<help1.ullAvailVirtual/(1024 * 1024)<<"MB"<<endl;
    cout <<"额外虚拟内存："<<help1.ullAvailExtendedVirtual/(1024 * 1024)<<"MB"<<endl;
    cout <<"物理内存负载情况："<<help1.dwMemoryLoad<<"%"<<endl;
    return 0;
}
