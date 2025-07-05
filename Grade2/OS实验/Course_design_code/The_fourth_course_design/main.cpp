#include<iostream>
using namespace std;
const int N = 20;
int n;
int a[N];

int odd=0;
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
bool ok=false;
int dfs(int st)
{
    //剪枝
    //成功边界
    if(st==n+1)
    {
        for(int i = 1; i <= n; i++ )
        {

            cout<<a[i]<<" ";
        }
        cout<<endl;
        return 0;
    }
    for(int i = 2;i<=n;i++)
    {
        if( a[i] == 0 && isPrime( i + a[st-1] ) )
        {
            a[st]=i;
            dfs(st+1);
            a[st]=0;
        }

    }



}
int main()
{
    a[1]=1;
    cin>>n;
    if(n%2!=0)
        return 0;
    dfs(2);
    return 0;
}