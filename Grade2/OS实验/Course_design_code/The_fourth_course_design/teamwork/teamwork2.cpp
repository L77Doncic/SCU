#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

using namespace std ;

int TotalPage;
int UsedPage;
int TotalProcess;

struct process
{
    string name ;
    int NeedPage;
};

process processtotal[100];
vector<int> pages(100);


void show(){
    cout<<"���ڴ�����"<<TotalPage<<"����ʹ���ڴ�����"<<UsedPage<<"��ʣ���ڴ�����"<<TotalPage - UsedPage<<"����������"<<TotalProcess<<endl;
    cout<<"��ʹ�õ��ڴ��Ϊ��";
    cout<<pages[0];
    for (int i = 1; i < UsedPage; i++)
    {
        cout<<","<<pages[i];
    }
    cout<<endl;
}

void init(){
    TotalPage = 100;
    UsedPage = 10;
    TotalProcess = 0;
    for (int i = 0; i < 100; i++)
    { 
        processtotal[i].name = "";
        processtotal[i].NeedPage = -1;
        pages[i] = i;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(pages.begin(),pages.end(),g);
    show();
}

int  CreateProcessCheck(int num,string name ,int need){
    if (processtotal[num].NeedPage != -1)
    {
        cout<<"���̺ű�ռ�ã�������"<<endl;
        return 0;
    }
    if (need > (TotalPage - UsedPage)){
        if (need > 100)
        {
            cout<<"ʣ���ڴ治�㣬�޷�����"<<endl;
            return -1;
        }
        
        cout<<"ʣ���ڴ治�㣬�޷�����"<<endl;
        return 0;
    }
    for (int i = 0; i < 100; i++) {
        if (processtotal[i].name == name)
        {
            cout<<"�����ظ���������"<<endl;
            return 0;
        }
    }
    return 1;
    
}

bool CreateProcess(){
    cout<<"��������̺�(0-99)�����̱����������ڴ��С���ÿո������";
    int num ,need;
    string name ;
    cin>>num>>name>>need;
    int help = CreateProcessCheck(num ,name , need);
    while (help == 0)
    {
        cout<<"��������̺�(0-99)�����̱������ÿո����������-1ȡ����";
        cin>>num;
        if (num == -1)
        {
            help = -1;
            cout<<"��ȡ��"<<endl;
            return false;
        }
        cin>>name>>need;
        help = CreateProcessCheck(num , name , need);
    }
    if (help == -1 )     return false;
    UsedPage += need;
    processtotal[num].name = name ;
    processtotal[num].NeedPage = need;
    cout<<"�����ɹ�"<<endl;
    TotalProcess++;
    show();
    return true;
}

void DeleteProcess(){
    cout<<"1.ͨ�������ɾ��"<<endl;
    cout<<"2.ͨ������ɾ��"<<endl;
    int num;
    cin>>num;
    switch (num)
    {
    case 1:{
        cout<<"����������"<<endl;
        int num1;
        cin>>num1;
        if (processtotal[num1].NeedPage != -1)
        {
            cout<<"��ɾ��"<<num1<<"�ų���"<<endl;
            TotalProcess--;
            UsedPage -= processtotal[num1].NeedPage;
            processtotal[num1].NeedPage = -1;
            processtotal[num1].name = "";
            show();
        }
        else{
            cout<<"�޴˳���ų���"<<endl;
        }
        break;
    }
    case 2:{
        cout<<"�����������"<<endl;
        string name;
        cin>>name;
        bool flag = false;
        for (int i = 0; i < 100; i++)
        {
            if (processtotal[i].name == name)
            {
                cout<<"��ɾ��"<<name<<"����"<<endl;
                TotalProcess--;
                processtotal[i].name = "";
                UsedPage -= processtotal[i].NeedPage;
                processtotal[i].NeedPage = -1;
                flag = true;
                show();
                break;
            }
        }
        if (!flag)
        {
            cout<<"δ�ҵ������Ƶĳ���"<<endl;
        }
        break;
    }
    default:{
        cout<<"�������˴����ѡ��"<<endl;
        break;
    }
    }
}

bool table(){
    cout<<"1.��������"<<endl;
    cout<<"2.��������"<<endl;
    cout<<"3.�鿴�ڴ�"<<endl;
    cout<<"4.�˳�����"<<endl;
    cout<<"��������Ҫ���еĲ���";
    int num;
    cin>>num;
    switch (num){
    case 1:{
        CreateProcess();
        break;
    }
    case 2:{
        DeleteProcess();
        break;
    }
    case 3:{
        show();
        break;
    }
    case 4:{
        return false;
    }
    default:{
        cout<<"�������˴���ѡ��"<<endl;
    }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    init();
    while (1){
        if (!table())
        {
            break;
        }
        
    }
    return 0;
}
