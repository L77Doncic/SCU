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
    cout<<"总内存量："<<TotalPage<<"，已使用内存量："<<UsedPage<<"，剩余内存量："<<TotalPage - UsedPage<<"，进程数："<<TotalProcess<<endl;
    cout<<"已使用的内存块为：";
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
        cout<<"进程号被占用，请重试"<<endl;
        return 0;
    }
    if (need > (TotalPage - UsedPage)){
        if (need > 100)
        {
            cout<<"剩余内存不足，无法进行"<<endl;
            return -1;
        }
        
        cout<<"剩余内存不足，无法进行"<<endl;
        return 0;
    }
    for (int i = 0; i < 100; i++) {
        if (processtotal[i].name == name)
        {
            cout<<"名称重复，请重试"<<endl;
            return 0;
        }
    }
    return 1;
    
}

bool CreateProcess(){
    cout<<"请输入进程号(0-99)，进程别名和所需内存大小，用空格隔开：";
    int num ,need;
    string name ;
    cin>>num>>name>>need;
    int help = CreateProcessCheck(num ,name , need);
    while (help == 0)
    {
        cout<<"请输入进程号(0-99)，进程别名，用空格隔开，输入-1取消：";
        cin>>num;
        if (num == -1)
        {
            help = -1;
            cout<<"已取消"<<endl;
            return false;
        }
        cin>>name>>need;
        help = CreateProcessCheck(num , name , need);
    }
    if (help == -1 )     return false;
    UsedPage += need;
    processtotal[num].name = name ;
    processtotal[num].NeedPage = need;
    cout<<"创建成功"<<endl;
    TotalProcess++;
    show();
    return true;
}

void DeleteProcess(){
    cout<<"1.通过程序号删除"<<endl;
    cout<<"2.通过名称删除"<<endl;
    int num;
    cin>>num;
    switch (num)
    {
    case 1:{
        cout<<"请输入程序号"<<endl;
        int num1;
        cin>>num1;
        if (processtotal[num1].NeedPage != -1)
        {
            cout<<"已删除"<<num1<<"号程序"<<endl;
            TotalProcess--;
            UsedPage -= processtotal[num1].NeedPage;
            processtotal[num1].NeedPage = -1;
            processtotal[num1].name = "";
            show();
        }
        else{
            cout<<"无此程序号程序"<<endl;
        }
        break;
    }
    case 2:{
        cout<<"请输入程序名"<<endl;
        string name;
        cin>>name;
        bool flag = false;
        for (int i = 0; i < 100; i++)
        {
            if (processtotal[i].name == name)
            {
                cout<<"已删除"<<name<<"程序"<<endl;
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
            cout<<"未找到该名称的程序"<<endl;
        }
        break;
    }
    default:{
        cout<<"你输入了错误的选项"<<endl;
        break;
    }
    }
}

bool table(){
    cout<<"1.创建进程"<<endl;
    cout<<"2.结束进程"<<endl;
    cout<<"3.查看内存"<<endl;
    cout<<"4.退出程序"<<endl;
    cout<<"请输入你要进行的操作";
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
        cout<<"你输入了错误选项"<<endl;
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
