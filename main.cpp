#include<bits/stdc++.h>
#include "Data.h"
using namespace std;
typedef long long int ll;
typedef long double ld;
#define M 1000000007
#define mp make_pair
#define pb push_back
#define vll vector<ll>
#define pll vector< pair <ll,ll> >
#define F first
#define S second
#define PII pair <ll,ll>
#define PI pair<int,int>

map<string, pll > m; // mapping sections to coordinates
map<string, int > g; //mapping sections to groups 
char a[31][31];
vector <product> prod;
int visited[31][31];
map < pair< pair<int,int> , pair<int,int> >, string> finalPath;
// string finalPath[31][31][31][31];

void display()
{
    ll i,j;
    for (i=1;i<=30;i++)
    {
        for (j=1;j<=30;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}

int check(int x, int y)
{
    if (x>0 and x<=30 and y>0 and y<=30)
    {
        if (a[x][y]==' ' and visited[x][y]==-1) return 1;
        else return 0;
    }
    else return 0;
}

void bfs(PI source)
{
    queue< PI > q; 
    string path[31][31];
    q.push(source);
    int i,j;
    memset(visited,-1,sizeof(visited));
    path[source.F][source.S] = "";
    visited[source.F][source.S] = 1;

    while(!q.empty()) {
        int x = q.front().F, y = q.front().S;
        q.pop();
        if (check(x, y + 1))
            path[x][y+1] = path[x][y], path[x][y+1].pb('R'), q.push({x,y+1}), visited[x][y+1]=1;
        if (check(x, y - 1))
            path[x][y-1] = path[x][y], path[x][y-1].pb('L'), q.push({x,y-1}), visited[x][y-1]=1;
        if (check(x - 1, y))
            path[x-1][y] = path[x][y], path[x-1][y].pb('U'), q.push({x-1,y}), visited[x-1][y]=1;
        if (check(x + 1, y))
            path[x+1][y] = path[x][y], path[x+1][y].pb('D'), q.push({x+1,y}), visited[x+1][y]=1;
    }
    // cout<<source.F<<" "<<source.S<<endl;
    for (i=1;i<=30;i++)
    {
        for (j=1;j<=30;j++)
        {
            if (a[i][j]==' ')
            {
                PI dest = {i,j};
                finalPath[{source,dest}] = path[i][j];
                // finalPath[source.F][source.S][i][j] = path[i][j];
            }
        }
    }
}

void calculateShortestPath()
{
    int i,j;
    for (i=1;i<=30;i++)
    {
        for (j=1;j<=30;j++)
        {
            if (a[i][j]==' ')
                bfs({i,j});
        }
    }
}

void pathFromXtoY(PI x, PI y)
{
    string s = finalPath[{x,y}];
    int x1 = x.F, y1 = x.S, x2 = y.F, y2 = y.S;
    int i=0;

    while (!(x1==x2 and y1==y2))
    {
        if (s[i]=='L')  a[x1][y1-1] = s[i], y1-=1;
        else if (s[i]=='R') a[x1][y1+1] = s[i], y1+=1;
        else if (s[i]=='U') a[x1-1][y1] = s[i], x1-=1;
        else a[x1+1][y1] = s[i], x1+=1;
        i++;
    }
    a[x.F][x.S] = '1'; a[y.F][y.S] = '2';
    display();
    // cout<<s<<endl;
    // cout<<s.length()<<endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	#endif
	Data ob;
    m = ob.m; 
    g = ob.g;   
    prod = ob.prod;
    ll i,j;
    for (i=0;i<=30;i++)
        for (j=0;j<=30;j++)
            a[i][j] = ob.a[i][j];
    calculateShortestPath();
    pathFromXtoY({23,9},{3,20});
}