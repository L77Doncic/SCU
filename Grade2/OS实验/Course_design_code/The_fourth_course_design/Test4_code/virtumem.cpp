//内存管理
//代码2-6-1  virtumem.cpp
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <process.h>

unsigned __stdcall simulator(void *);
unsigned __stdcall inspector(void *);
LPVOID BASE_PTR;
int Actnum=0;
int main(int argc,  char* argv[])
{
	unsigned ThreadID[2];
	_beginthreadex(NULL, 0, simulator, NULL, 0, &ThreadID[0]);
	_beginthreadex(NULL, 0, inspector, NULL, 0, &ThreadID[1]);
	getchar();
	
	
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	printf("处理器分页大小%u\n",systemInfo.dwPageSize);
	
	return 0;
}
unsigned __stdcall simulator(void *)
{
	DWORD OldProtect;
	int randnum;
	printf("Now the simulator procedure has been started.\n");
	srand((unsigned)time(NULL));
	randnum=-1;
	while(1) {
		Sleep(500);
		while(Actnum!=0) {
			Sleep(500);
		}

		randnum=rand()%6;
		printf("*************** randnum=%d ******************\n", randnum);
		switch(randnum) {
		case 0:
			if (BASE_PTR=VirtualAlloc(NULL, 1024*32, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE)) {
				sprintf((char*)BASE_PTR, "memory has been malloced\n");
							/*分配了内存就相当于malloc或者new操作一样了，可以写了，这里将这条字符串写进BASE_PTR指向的页面*/
				Actnum=1;      
//				目前执行动作：虚存的保留与提交 
			}
			break;
		case 1:
			if (VirtualFree(BASE_PTR, 1024*32, MEM_DECOMMIT)) {
				Actnum=2;
//				目前执行动作：虚存的除配
			}
			break;
		case 2:
			if (VirtualFree(BASE_PTR, 0, MEM_RELEASE)) {
				Actnum=3;
//				目前执行动作：虚存的除配并释放虚存空间
			}
			break;
		case 3:
			if (VirtualProtect(BASE_PTR, 1024*32, PAGE_READONLY, &OldProtect)) {
				Actnum=4;
//				目前执行动作：改变虚存内存页的保护
			}
			break;
		case 4:
			if (VirtualLock(BASE_PTR, 1024*32)) {
				Actnum=5;
//				目前执行动作：锁定虚存内存页
			}
			break;
		case 5:
			if (BASE_PTR=VirtualAlloc(NULL, 1024*32, MEM_RESERVE, PAGE_READWRITE)) { //仅仅是保留地址，没有分配
				Actnum=6;
//				目前执行动作：虚存的保留
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
unsigned __stdcall inspector(void *)
{
	char para1[3000];
	char tempstr[100];
	MEMORYSTATUSEX Vmeminfo;
	Vmeminfo.dwLength = sizeof(Vmeminfo);
	MEMORY_BASIC_INFORMATION inspectorinfo1;
	int structsize = sizeof(MEMORY_BASIC_INFORMATION);
	printf("Hi,  now inspector begin to work\n");
	SIZE_T before_ullAvailPhys= 0;
	SIZE_T before_ullAvailVirtual=0;
	while(1) {
		Sleep(1000);
		if(Actnum!=0) {
			switch(Actnum) {
			case 1:
				printf((char*)BASE_PTR);//把写在BASE_PTR指向的页面的信息输出出来				
				memset(&inspectorinfo1, 0, structsize);		
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "目前执行动作：虚存的保留与提交\n");
				break;
			case 2:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "目前执行动作：虚存的除配\n");
				break;
			case 3:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "目前执行动作：虚存的除配并释放虚存空间\n");
				break;
			case 4:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "目前执行动作：改变虚存内存页的保护\n");
				break;
			case 5:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "目前执行动作：锁定虚存内存页\n");
				break;
			case 6:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "目前执行动作：虚存的保留\n");
				break;
			default:
				break;
			}
			sprintf(tempstr, "开始地址:0X%x\n", inspectorinfo1.BaseAddress);
			strcat(para1, tempstr);
			sprintf(tempstr, "区块大小:0X%x\n", inspectorinfo1.RegionSize);
			strcat(para1, tempstr);
			sprintf(tempstr, "目前状态:0X%x\n", inspectorinfo1.State);
			strcat(para1, tempstr);
			sprintf(tempstr, "分配时访问保护:0X%x\n", inspectorinfo1.AllocationProtect);
			strcat(para1, tempstr);
			sprintf(tempstr, "当前访问保护:0X%x\n", inspectorinfo1.Protect);
			strcat(para1, tempstr);
			strcat(para1, "(状态:10000代表未分配；1000代表提交；2000代表保留；)\n");
			strcat(para1, "(保护方式：0代表其它；1代表禁止访问；2代表只读；4代表读写;\n10代表可执");
			strcat(para1, "行;20代表可读和执行;40代表可读写和执行);\n********************************\n");

			
			GlobalMemoryStatusEx(&Vmeminfo);			
			strcat(para1, "当前整体存储统计如下\n");
			sprintf(tempstr, "物理内存总数：%zu(KBYTES)\n",  Vmeminfo.ullTotalPhys/1024);
			strcat(para1, tempstr);
			sprintf(tempstr, "可用物理内存：%zu(KBYTES)\n",  Vmeminfo.ullAvailPhys/1024);
//			sprintf(tempstr, "物理内存变化：0x%x\n",  abs(Vmeminfo.ullAvailPhys-before_ullAvailPhys));
			strcat(para1, tempstr);
			sprintf(tempstr, "页面文件总数：%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
			strcat(para1, tempstr);
			sprintf(tempstr, "可用页面文件数：%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
			strcat(para1, tempstr);
			sprintf(tempstr, "虚存空间总数：%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
			strcat(para1, tempstr);
			sprintf(tempstr, "可用虚存空间数：%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
			strcat(para1, tempstr);
			sprintf(tempstr, "物理存储使用负荷：%%%lu\n\n\n\n",  Vmeminfo.dwMemoryLoad);
			before_ullAvailPhys=Vmeminfo.dwMemoryLoad;
			strcat(para1, tempstr);
			printf("%s", para1);
		
			Actnum=0;
			Sleep(500);
		}
	}
	return 0;
}
