#include"stdio.h"
#include"string.h"
#include"vector"
#include"algorithm"
using namespace std;
#define INF 1000000
int Graph[501][501];
int N,M;
int MARK=1;
int sum=0;
int MMM=1;
vector<int>Q[501];
int used[501][501]={0};
int path[501][501];
int Find(int f[],int x)
{
    if(f[x]==x)
        return x;
    return f[x]=Find(f,f[x]);
}
void Creat(int Graph[][501])
{
    int weight[501];
    int vis[501];
    int p[501];
    int i,j,k;
    for(int i=1; i<=N; i++)
    {
        weight[i]=Graph[1][i];
        vis[i]=0;
        p[i]=1;
    }
    vis[1]=1;
    for(i=1; i<N; i++)
    {
        k=-1;
        j=1;
        int minx=INF;
        while(j<=N)
        {
            if(vis[j]==0&&minx>weight[j])
            {
                k=j;
                minx=weight[j];
            }
            j++;
        }
        if(k==-1)
        {
            MMM=0;
            sum=INF;
            break;
        }
        sum+=weight[k];
        vis[k]=1;
        used[p[k]][k]=1;//如果是最小生成树上的边则标记一下
        used[k][p[k]]=1;
        for(j=1; j<=N; j++)
        {
            if(j!=k&&vis[j])//求出j到k这个环路上值最大的边
            {
                path[j][k]=path[k][j]=max(path[j][k],weight[k]);
            }
            if(vis[j]==0&&weight[j]>Graph[k][j])
            {
                weight[j]=Graph[k][j];
                p[j]=k;
            }
        }
    }
}
int ans=INF;
void SecondTree(int Graph[][501])//求次小生成树的函数
{
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(i!=j&&used[i][j]==0)//将不是最小生成树上的边加入进去，并删除环路上最大的边
            {
                ans=min(ans,sum+Graph[i][j]-path[i][j]);
            }
        }
    }
}
int main()
{
    int f[501];
    for(int i=1; i<501; i++)
        f[i]=i;
    scanf("%d%d",&N,&M);
    for(int i=0; i<=N; i++)
        for(int j=0; j<=N; j++)
            if(i==j)
                Graph[i][j]=0;
            else
                Graph[i][j]=INF;
    for(int i=0; i<M; i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        int n=Find(f,a);
        int m=Find(f,b);
        if(n!=m)
            f[n]=m;
        if(Graph[a][b]>c)
        {
            Graph[a][b]=c;
            Graph[b][a]=c;
        }
    }
    Creat(Graph);
    int mmm=MMM;
    int cnt=0;
    int minx=sum;
    SecondTree(Graph);
    if(ans==sum)
        cnt=1;
    if(mmm==1)
    {
        printf("%d\n",minx);
        if(cnt==0)
            printf("Yes\n");
        else
            printf("No\n");
    }
    else
    {
        printf("No MST\n");
        int cnt=0;
        for(int i=1; i<=N; i++)
            if(f[i]==i)
                cnt++;
        printf("%d\n",cnt);
    }
}
