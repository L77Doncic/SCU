#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;
int WorkNumber;//统计作业数 

typedef struct node {
	int number;          //作业号
	int reach_time;     //作业抵达时间
	int need_time;      //作业的执行时间
	int privilege;	  //作业优先权
	float excellent;     //响应比
	//int start_time; 	  //作业开始时间
	int wait_time;      //等待时间
	int tr_time;        //周转时间
	double wtr_time;   //带权周转时间
	//int run_time;       //作业累计已执行时间
	int visited;		  //作业是否完成
	//bool isreached;	  //作业是否已抵达
} job;

void per_output(job a) {
	cout<<"执行完的作业是："<<a.number<<"号作业，等待时间为"<<a.wait_time<<" 周转时间为"<<a.tr_time<<" 带权周转时间为";
	cout<<fixed<<setprecision(2);//保留两位小数
	cout<<a.wtr_time<<endl;
}

bool cmp(job a,job b) { //sort比较
	return a.reach_time<=b.reach_time;
}

void read_Jobdata(string file) { //读取数据文件；
	ifstream ifs;
	ifs.open(file,ios::in);
	if (!ifs.is_open()) {					//判断文件是否打开
		cout << "打开文件失败！！！";
		return ;
	}	//打开文件
	char c;
	int lineCnt=0;
	while(ifs.get(c)) {
		if(c=='\n')
			lineCnt++;
	}
	WorkNumber=lineCnt;
	cout<<"作业个数为："<<lineCnt<<endl;
	ifs.close();

	ifs.open(file,ios::in);
	if (!ifs.is_open()) {					//判断文件是否打开
		cout << "打开文件失败！！！";
		return ;
	}	//打开文件
	string data;
	while( getline(ifs,data) )
		cout<<data<<endl;//按行查看文件信息

	ifs.close();
}
void initial_jobs(job jobs[],string file) { //初始化所有作业信息;
	ifstream ifs;
	ifs.open(file,ios::in);
	if (!ifs.is_open()) {					//判断文件是否打开
		cout << "打开文件失败！！！";
		return ;
	}	//打开文件
	//输入到对应位置
	int u;
	int i=0,j=0;
	string data;
	getline(ifs,data);//先把标签行处理了
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
	sort(jobs,jobs+7,cmp);//根据到达时间对作业进行排序，
}
//int findEarlyJob(job jobs[],int count);//找到执行时间最短的作业;
void averagedata(job v[]) //输出平均等待时间，平均周转时间，平均带权周转时间 
{
	double wait=0,tr=0,wtr=0;
	for(int i = 0; i < WorkNumber; i++) {
		wait+=v[i].wait_time;
		tr+=v[i].tr_time;
		wtr+=v[i].wtr_time;
	}
	cout<<"平均等待时间："<<wait/(double)WorkNumber<<endl;
	cout<<"平均周转时间:"<<tr/(double)WorkNumber<<endl;
	cout<<"平均带权周转时间:"<<wtr/(double)WorkNumber<<endl;
}

void SJF( job v[],int count) { //短作业优先算法，count表示目前时刻
	int st=1e8;//用于后面和作业运行时间比较，找出最小
	int j=-1;//记录取哪个 并且作为退出递归标志
	for(int i=0 ; i < WorkNumber; i++)//在已经抵达里的作业找最短作业
		if(count>=v[i].reach_time&&v[i].visited==0)
			if(st>v[i].need_time) {
				st=v[i].need_time;
				j=i;//最终j即为最短作业的数组索引
			}
	if(j==-1)//说明还没有作业到达，得新找count
		for(int i=0 ; i < WorkNumber; i++)
			if(v[i].visited==0) {
				count=v[i].reach_time;
				j=i;
				break;//前面以及排过序，所以找到的第一个即使第一个到达的
			}

	if(j==-1)   return;       //说明所有的作业都已经访问了 ,退出递归

	v[j].wait_time=count-v[j].reach_time;
	v[j].tr_time=v[j].need_time+v[j].wait_time;//周转时间
	v[j].wtr_time=(double)v[j].tr_time/(double)v[j].need_time;//带权周转时间
	per_output(v[j]);//输出函数
	v[j].visited=1;//作业已经完成

	SJF(v,count+v[j].need_time);//刷新时刻，递归调用SJF

}
void HRRF(job v[],int count) { //高响应比优先算法
	double st=0;//用于后面和响应比比较，找出最大
	int j=-1;//记录取哪个 并且作为退出递归标志
	for(int i=0 ; i < WorkNumber; i++)//在已经抵达里的作业找响应比最高的作业
		if(count>=v[i].reach_time&&v[i].visited==0) {
			v[i].wait_time=count-v[i].reach_time;
			v[i].excellent=1+(float)v[i].wait_time/(float)v[i].need_time;
			if(st<v[i].excellent) {
				st=v[i].excellent;
				j=i;//最终j即为最短作业的数组索引
			}
		}
	if(j==-1)//说明还没有作业到达，得新找count
		for(int i=0 ; i < WorkNumber; i++)
			if(v[i].visited==0) {
				count=v[i].reach_time;
				j=i;
				break;//前面以及排过序，所以找到的第一个即使第一个到达的
			}

	if(j==-1)   return;       //说明所有的作业都已经访问了 ,退出递归

	v[j].wait_time=count-v[j].reach_time;
	v[j].tr_time=v[j].need_time+v[j].wait_time;//周转时间
	v[j].wtr_time=(double)v[j].tr_time/(double)v[j].need_time;//带权周转时间
	per_output(v[j]);//输出函数
	v[j].visited=1;//作业已经完成

	HRRF(v,count+v[j].need_time);//刷新时刻，递归调用SJF
}
void HPF(job v[],int count) {
	int st=1e8;//用于后面和作业的优先权值比较，找出最小
	int j=-1;//记录取哪个 并且作为退出递归标志
	for(int i=0 ; i < WorkNumber; i++)//在已经抵达里的作业找优先权最大(即优先权值最小)的作业
		if(count>=v[i].reach_time&&v[i].visited==0)
			if(st>v[i].privilege)
			{
				st=v[i].privilege;
				j=i;//最终j即为最短作业的数组索引
			}
	if(j==-1)//说明还没有作业到达，得新找count
		for(int i=0 ; i < WorkNumber; i++)
			if(v[i].visited==0) {
				count=v[i].reach_time;
				j=i;
				break;//前面以及排过序，所以找到的第一个即使第一个到达的
			}

	if(j==-1)   return;       //说明所有的作业都已经访问了 ,退出递归

	v[j].wait_time=count-v[j].reach_time;
	v[j].tr_time=v[j].need_time+v[j].wait_time;//周转时间
	v[j].wtr_time=(double)v[j].tr_time/(double)v[j].need_time;//带权周转时间
	per_output(v[j]);//输出函数
	v[j].visited=1;//作业已经完成

	HPF(v,count+v[j].need_time);//刷新时刻，递归调用SJF

}

int main() {
	//system("chcp 65001");
	string path="../data.txt";
	read_Jobdata(path);//读数据文件
	job jobs[WorkNumber];
	initial_jobs(jobs,path);//初始化作业信息
	cout<<"短作业优先(SJF):"<<endl;
	SJF(jobs,0);
	averagedata(jobs);//输出平均等待时间，平均周转时间，平均带权周转时间 

	initial_jobs(jobs,path);
	cout<<"高相应比优先(HRRF):"<<endl;
	HRRF(jobs,0);
	averagedata(jobs);

	initial_jobs(jobs,path);
	cout<<"优先权高者优先(HPF):"<<endl;
	HPF(jobs,0);
	averagedata(jobs);

	// cout<<jobs[2].wtr_time;

	return 0;
}
