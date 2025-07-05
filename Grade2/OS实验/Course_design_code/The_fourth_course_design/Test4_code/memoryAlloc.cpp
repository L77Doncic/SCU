//内存分配
//代码2-6-2 memoryAlloc.cpp
#include <windows.h>
#include <stdio.h>

int main(int argc,  char* argv[])
{
	FILE* fp = fopen("../Test4_code/memoryAlloc.txt","w+");//输出到文件
	//if(!fp.is_open())
	MEMORYSTATUSEX Vmeminfo;//用以查询全局内存状态
	Vmeminfo.dwLength = sizeof(Vmeminfo);
	MEMORY_BASIC_INFORMATION inspectorinfo1;//用以查询单个页面的状态
	int structsize = sizeof(MEMORY_BASIC_INFORMATION);
	LPVOID BASE_PTR = NULL;
	
	
	GlobalMemoryStatusEx(&Vmeminfo);//查询没有分配之前的整体状态

	fprintf(fp,"********************查询没有分配之前的整体状态**********************\n\n");

	//输出信息
	fprintf(fp,"当前整体存储统计如下\n");
	fprintf(fp,"物理内存总数：%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"可用物理内存：%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"页面文件总数：%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"可用页面文件数：%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"虚存空间总数：%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"可用虚存空间数：%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"物理存储使用负荷：%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//结构体置0
	
	
	
	BASE_PTR = VirtualAlloc(NULL, 1024*32, MEM_COMMIT, PAGE_READWRITE);/*分配虚内存*/
	VirtualQuery(BASE_PTR, &inspectorinfo1, structsize);/*查询VirtualAlloc之后的当前分配状态状态*/
	//输出信息
	fprintf(fp,"*******************查询VirtualAlloc之后的当前分配状态*********\n\n");
	fprintf(fp,"开始地址:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"区块大小:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"目前状态:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"分配时访问保护:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"当前访问保护:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(状态:10000代表未分配；1000代表提交；2000代表保留；)\n");
	fprintf(fp,"(保护方式：0代表其它；1代表禁止访问；2代表只读；4代表读写;\n10代表可执");
	fprintf(fp,"行;20代表可读和执行;40代表可读写和执行);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//查询VirtualAlloc之后的整体状态
	//输出信息
	fprintf(fp,"*******************查询VirtualAlloc之后的整体分配状态*********\n\n");

	fprintf(fp,"当前整体存储统计如下\n");
	fprintf(fp,"物理内存总数：%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"可用物理内存：%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"页面文件总数：%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"可用页面文件数：%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"虚存空间总数：%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"可用虚存空间数：%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"物理存储使用负荷：%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//结构体置0
	
	
	
	VirtualFree(BASE_PTR, 0, MEM_RELEASE);//释放内存
	DWORD lerr = GetLastError();
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);//查询VirtualFree之后的当前分配状态状态
	fprintf(fp,"*******************查询VirtualFree之后的当前分配状态*********\n\n");

	//输出信息
	fprintf(fp,"开始地址:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"区块大小:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"目前状态:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"分配时访问保护:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"当前访问保护:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(状态:10000代表未分配；1000代表提交；2000代表保留；)\n");
	fprintf(fp,"(保护方式：0代表其它；1代表禁止访问；2代表只读；4代表读写;\n10代表可执");
	fprintf(fp,"行;20代表可读和执行;40代表可读写和执行);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//查询VirtualFree之后的整体状态
	//输出信息
	fprintf(fp,"*******************查询VirtualFree之后的整体状态*********\n\n");

	fprintf(fp,"当前整体存储统计如下\n");
	fprintf(fp,"物理内存总数：%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"可用物理内存：%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"页面文件总数：%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"可用页面文件数：%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"虚存空间总数：%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"可用虚存空间数：%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"物理存储使用负荷：%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//结构体置0
	
	
	
	BASE_PTR = malloc(1024*32*sizeof(char));//或者用new
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);/*查询malloc之后的当前分配状态状态*/

	//输出信息
	fprintf(fp,"*******************查询malloc之后的当前分配状态*********\n\n");

	fprintf(fp,"开始地址:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"区块大小:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"目前状态:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"分配时访问保护:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"当前访问保护:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(状态:10000代表未分配；1000代表提交；2000代表保留；)\n");
	fprintf(fp,"(保护方式：0代表其它；1代表禁止访问；2代表只读；4代表读写;\n10代表可执");
	fprintf(fp,"行;20代表可读和执行;40代表可读写和执行);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//查询malloc之后的整体状态
	//输出信息
	fprintf(fp,"*******************查询malloc之后的整体分配状态*********\n\n");

	fprintf(fp,"当前整体存储统计如下\n");
	fprintf(fp,"物理内存总数：%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"可用物理内存：%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"页面文件总数：%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"可用页面文件数：%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"虚存空间总数：%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"可用虚存空间数：%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"物理存储使用负荷：%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//结构体置0
	
	
	
	free(BASE_PTR);//如果用new，则用delete
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);/*查询free之后的当前分配状态状态*/
	//输出信息
	fprintf(fp,"*******************查询free之后的当前分配状态*********\n\n");

	fprintf(fp,"开始地址:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"区块大小:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"目前状态:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"分配时访问保护:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"当前访问保护:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(状态:10000代表未分配；1000代表提交；2000代表保留；)\n");
	fprintf(fp,"(保护方式：0代表其它；1代表禁止访问；2代表只读；4代表读写;\n10代表可执");
	fprintf(fp,"行;20代表可读和执行;40代表可读写和执行);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//查询free之后的整体状态
	//输出信息
	fprintf(fp,"*******************查询free之后的整体分配状态*********\n\n");

	fprintf(fp,"当前整体存储统计如下\n");
	fprintf(fp,"物理内存总数：%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"可用物理内存：%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"页面文件总数：%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"可用页面文件数：%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"虚存空间总数：%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"可用虚存空间数：%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"物理存储使用负荷：%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	fclose(fp);
	return 0;
}
