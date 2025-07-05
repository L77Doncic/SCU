#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;
int WorkNumber;//ͳ����ҵ�� 

typedef struct node {
	int number;          //��ҵ��
	int reach_time;     //��ҵ�ִ�ʱ��
	int need_time;      //��ҵ��ִ��ʱ��
	int privilege;	  //��ҵ����Ȩ
	float excellent;     //��Ӧ��
	//int start_time; 	  //��ҵ��ʼʱ��
	int wait_time;      //�ȴ�ʱ��
	int tr_time;        //��תʱ��
	double wtr_time;   //��Ȩ��תʱ��
	//int run_time;       //��ҵ�ۼ���ִ��ʱ��
	int visited;		  //��ҵ�Ƿ����
	//bool isreached;	  //��ҵ�Ƿ��ѵִ�
} job;

void per_output(job a) {
	cout<<"ִ�������ҵ�ǣ�"<<a.number<<"����ҵ���ȴ�ʱ��Ϊ"<<a.wait_time<<" ��תʱ��Ϊ"<<a.tr_time<<" ��Ȩ��תʱ��Ϊ";
	cout<<fixed<<setprecision(2);//������λС��
	cout<<a.wtr_time<<endl;
}

bool cmp(job a,job b) { //sort�Ƚ�
	return a.reach_time<=b.reach_time;
}

void read_Jobdata(string file) { //��ȡ�����ļ���
	ifstream ifs;
	ifs.open(file,ios::in);
	if (!ifs.is_open()) {					//�ж��ļ��Ƿ��
		cout << "���ļ�ʧ�ܣ�����";
		return ;
	}	//���ļ�
	char c;
	int lineCnt=0;
	while(ifs.get(c)) {
		if(c=='\n')
			lineCnt++;
	}
	WorkNumber=lineCnt;
	cout<<"��ҵ����Ϊ��"<<lineCnt<<endl;
	ifs.close();

	ifs.open(file,ios::in);
	if (!ifs.is_open()) {					//�ж��ļ��Ƿ��
		cout << "���ļ�ʧ�ܣ�����";
		return ;
	}	//���ļ�
	string data;
	while( getline(ifs,data) )
		cout<<data<<endl;//���в鿴�ļ���Ϣ

	ifs.close();
}
void initial_jobs(job jobs[],string file) { //��ʼ��������ҵ��Ϣ;
	ifstream ifs;
	ifs.open(file,ios::in);
	if (!ifs.is_open()) {					//�ж��ļ��Ƿ��
		cout << "���ļ�ʧ�ܣ�����";
		return ;
	}	//���ļ�
	//���뵽��Ӧλ��
	int u;
	int i=0,j=0;
	string data;
	getline(ifs,data);//�Ȱѱ�ǩ�д�����
	while(ifs>>u) {
		if(j==0)
			jobs[i].number=u;
		if(j==1)
			jobs[i].reach_time=u;
		if(j==2)
			jobs[i].need_time=u;
		if(j==3)
			jobs[i].privilege=u;
		j++;
		if(j>3)
			i++,j=0;
	}
	ifs.close();
	for(int i = 0; i < WorkNumber; i++) {
		jobs[i].tr_time=0;
		jobs[i].wait_time=0;
		jobs[i].excellent=0;
		jobs[i].wtr_time=0;
		jobs[i].visited=0;
	}
	sort(jobs,jobs+7,cmp);//���ݵ���ʱ�����ҵ��������
}
//int findEarlyJob(job jobs[],int count);//�ҵ�ִ��ʱ����̵���ҵ;
void averagedata(job v[]) //���ƽ���ȴ�ʱ�䣬ƽ����תʱ�䣬ƽ����Ȩ��תʱ�� 
{
	double wait=0,tr=0,wtr=0;
	for(int i = 0; i < WorkNumber; i++) {
		wait+=v[i].wait_time;
		tr+=v[i].tr_time;
		wtr+=v[i].wtr_time;
	}
	cout<<"ƽ���ȴ�ʱ�䣺"<<wait/(double)WorkNumber<<endl;
	cout<<"ƽ����תʱ��:"<<tr/(double)WorkNumber<<endl;
	cout<<"ƽ����Ȩ��תʱ��:"<<wtr/(double)WorkNumber<<endl;
}

void SJF( job v[],int count) { //����ҵ�����㷨��count��ʾĿǰʱ��
	int st=1e8;//���ں������ҵ����ʱ��Ƚϣ��ҳ���С
	int j=-1;//��¼ȡ�ĸ� ������Ϊ�˳��ݹ��־
	for(int i=0 ; i < WorkNumber; i++)//���Ѿ��ִ������ҵ�������ҵ
		if(count>=v[i].reach_time&&v[i].visited==0)
			if(st>v[i].need_time) {
				st=v[i].need_time;
				j=i;//����j��Ϊ�����ҵ����������
			}
	if(j==-1)//˵����û����ҵ���������count
		for(int i=0 ; i < WorkNumber; i++)
			if(v[i].visited==0) {
				count=v[i].reach_time;
				j=i;
				break;//ǰ���Լ��Ź��������ҵ��ĵ�һ����ʹ��һ�������
			}

	if(j==-1)   return;       //˵�����е���ҵ���Ѿ������� ,�˳��ݹ�

	v[j].wait_time=count-v[j].reach_time;
	v[j].tr_time=v[j].need_time+v[j].wait_time;//��תʱ��
	v[j].wtr_time=(double)v[j].tr_time/(double)v[j].need_time;//��Ȩ��תʱ��
	per_output(v[j]);//�������
	v[j].visited=1;//��ҵ�Ѿ����

	SJF(v,count+v[j].need_time);//ˢ��ʱ�̣��ݹ����SJF

}
void HRRF(job v[],int count) { //����Ӧ�������㷨
	double st=0;//���ں������Ӧ�ȱȽϣ��ҳ����
	int j=-1;//��¼ȡ�ĸ� ������Ϊ�˳��ݹ��־
	for(int i=0 ; i < WorkNumber; i++)//���Ѿ��ִ������ҵ����Ӧ����ߵ���ҵ
		if(count>=v[i].reach_time&&v[i].visited==0) {
			v[i].wait_time=count-v[i].reach_time;
			v[i].excellent=1+(float)v[i].wait_time/(float)v[i].need_time;
			if(st<v[i].excellent) {
				st=v[i].excellent;
				j=i;//����j��Ϊ�����ҵ����������
			}
		}
	if(j==-1)//˵����û����ҵ���������count
		for(int i=0 ; i < WorkNumber; i++)
			if(v[i].visited==0) {
				count=v[i].reach_time;
				j=i;
				break;//ǰ���Լ��Ź��������ҵ��ĵ�һ����ʹ��һ�������
			}

	if(j==-1)   return;       //˵�����е���ҵ���Ѿ������� ,�˳��ݹ�

	v[j].wait_time=count-v[j].reach_time;
	v[j].tr_time=v[j].need_time+v[j].wait_time;//��תʱ��
	v[j].wtr_time=(double)v[j].tr_time/(double)v[j].need_time;//��Ȩ��תʱ��
	per_output(v[j]);//�������
	v[j].visited=1;//��ҵ�Ѿ����

	HRRF(v,count+v[j].need_time);//ˢ��ʱ�̣��ݹ����SJF
}
void HPF(job v[],int count) {
	int st=1e8;//���ں������ҵ������Ȩֵ�Ƚϣ��ҳ���С
	int j=-1;//��¼ȡ�ĸ� ������Ϊ�˳��ݹ��־
	for(int i=0 ; i < WorkNumber; i++)//���Ѿ��ִ������ҵ������Ȩ���(������Ȩֵ��С)����ҵ
		if(count>=v[i].reach_time&&v[i].visited==0)
			if(st>v[i].privilege)
			{
				st=v[i].privilege;
				j=i;//����j��Ϊ�����ҵ����������
			}
	if(j==-1)//˵����û����ҵ���������count
		for(int i=0 ; i < WorkNumber; i++)
			if(v[i].visited==0) {
				count=v[i].reach_time;
				j=i;
				break;//ǰ���Լ��Ź��������ҵ��ĵ�һ����ʹ��һ�������
			}

	if(j==-1)   return;       //˵�����е���ҵ���Ѿ������� ,�˳��ݹ�

	v[j].wait_time=count-v[j].reach_time;
	v[j].tr_time=v[j].need_time+v[j].wait_time;//��תʱ��
	v[j].wtr_time=(double)v[j].tr_time/(double)v[j].need_time;//��Ȩ��תʱ��
	per_output(v[j]);//�������
	v[j].visited=1;//��ҵ�Ѿ����

	HPF(v,count+v[j].need_time);//ˢ��ʱ�̣��ݹ����SJF

}

int main() {
	//system("chcp 65001");
	string path="../data.txt";
	read_Jobdata(path);//�������ļ�
	job jobs[WorkNumber];
	initial_jobs(jobs,path);//��ʼ����ҵ��Ϣ
	cout<<"����ҵ����(SJF):"<<endl;
	SJF(jobs,0);
	averagedata(jobs);//���ƽ���ȴ�ʱ�䣬ƽ����תʱ�䣬ƽ����Ȩ��תʱ�� 

	initial_jobs(jobs,path);
	cout<<"����Ӧ������(HRRF):"<<endl;
	HRRF(jobs,0);
	averagedata(jobs);

	initial_jobs(jobs,path);
	cout<<"����Ȩ��������(HPF):"<<endl;
	HPF(jobs,0);
	averagedata(jobs);

	// cout<<jobs[2].wtr_time;

	return 0;
}
