//�ڴ����
//����2-6-2 memoryAlloc.cpp
#include <windows.h>
#include <stdio.h>

int main(int argc,  char* argv[])
{
	FILE* fp = fopen("../Test4_code/memoryAlloc.txt","w+");//������ļ�
	//if(!fp.is_open())
	MEMORYSTATUSEX Vmeminfo;//���Բ�ѯȫ���ڴ�״̬
	Vmeminfo.dwLength = sizeof(Vmeminfo);
	MEMORY_BASIC_INFORMATION inspectorinfo1;//���Բ�ѯ����ҳ���״̬
	int structsize = sizeof(MEMORY_BASIC_INFORMATION);
	LPVOID BASE_PTR = NULL;
	
	
	GlobalMemoryStatusEx(&Vmeminfo);//��ѯû�з���֮ǰ������״̬

	fprintf(fp,"********************��ѯû�з���֮ǰ������״̬**********************\n\n");

	//�����Ϣ
	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"���������ڴ棺%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"ҳ���ļ�������%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"���ռ�������%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"�������ռ�����%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	
	
	
	BASE_PTR = VirtualAlloc(NULL, 1024*32, MEM_COMMIT, PAGE_READWRITE);/*�������ڴ�*/
	VirtualQuery(BASE_PTR, &inspectorinfo1, structsize);/*��ѯVirtualAlloc֮��ĵ�ǰ����״̬״̬*/
	//�����Ϣ
	fprintf(fp,"*******************��ѯVirtualAlloc֮��ĵ�ǰ����״̬*********\n\n");
	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//��ѯVirtualAlloc֮�������״̬
	//�����Ϣ
	fprintf(fp,"*******************��ѯVirtualAlloc֮����������״̬*********\n\n");

	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"���������ڴ棺%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"ҳ���ļ�������%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"���ռ�������%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"�������ռ�����%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	
	
	
	VirtualFree(BASE_PTR, 0, MEM_RELEASE);//�ͷ��ڴ�
	DWORD lerr = GetLastError();
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);//��ѯVirtualFree֮��ĵ�ǰ����״̬״̬
	fprintf(fp,"*******************��ѯVirtualFree֮��ĵ�ǰ����״̬*********\n\n");

	//�����Ϣ
	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//��ѯVirtualFree֮�������״̬
	//�����Ϣ
	fprintf(fp,"*******************��ѯVirtualFree֮�������״̬*********\n\n");

	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"���������ڴ棺%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"ҳ���ļ�������%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"���ռ�������%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"�������ռ�����%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	
	
	
	BASE_PTR = malloc(1024*32*sizeof(char));//������new
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);/*��ѯmalloc֮��ĵ�ǰ����״̬״̬*/

	//�����Ϣ
	fprintf(fp,"*******************��ѯmalloc֮��ĵ�ǰ����״̬*********\n\n");

	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//��ѯmalloc֮�������״̬
	//�����Ϣ
	fprintf(fp,"*******************��ѯmalloc֮����������״̬*********\n\n");

	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"���������ڴ棺%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"ҳ���ļ�������%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"���ռ�������%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"�������ռ�����%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	
	
	
	free(BASE_PTR);//�����new������delete
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);/*��ѯfree֮��ĵ�ǰ����״̬״̬*/
	//�����Ϣ
	fprintf(fp,"*******************��ѯfree֮��ĵ�ǰ����״̬*********\n\n");

	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n");
	GlobalMemoryStatusEx(&Vmeminfo);//��ѯfree֮�������״̬
	//�����Ϣ
	fprintf(fp,"*******************��ѯfree֮����������״̬*********\n\n");

	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%zu(BYTES)\n",  Vmeminfo.ullTotalPhys);
	fprintf(fp,"���������ڴ棺%zu(BYTES)\n",  Vmeminfo.ullAvailPhys);
	fprintf(fp,"ҳ���ļ�������%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
	fprintf(fp,"���ռ�������%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
	fprintf(fp,"�������ռ�����%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	fclose(fp);
	return 0;
}
