#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
   // system("chcp 65001");
    MEMORYSTATUSEX help1;
    help1.dwLength = sizeof(help1);
    GlobalMemoryStatusEx(&help1);
    cout<<"��ǰ����洢���£�"<<endl;
    cout <<"�����ڴ�������"<<help1.ullTotalPhys/(1024 * 1024)<<"MB"<<endl;
    cout <<"���������ڴ棺"<<help1.ullAvailPhys/(1024 * 1024)<<"MB"<<endl;
    cout <<"ҳ�ļ�������"<<help1.ullTotalPageFile/(1024 * 1024)<<"MB"<<endl;
    cout <<"����ҳ�ļ���"<<help1.ullAvailPageFile/(1024 * 1024)<<"MB"<<endl;
    cout <<"�����ڴ�������"<<help1.ullTotalVirtual/(1024 * 1024)<<"MB"<<endl;
    cout <<"���������ڴ棺"<<help1.ullAvailVirtual/(1024 * 1024)<<"MB"<<endl;
    cout <<"���������ڴ棺"<<help1.ullAvailExtendedVirtual/(1024 * 1024)<<"MB"<<endl;
    cout <<"�����ڴ渺�������"<<help1.dwMemoryLoad<<"%"<<endl;
    return 0;
}
