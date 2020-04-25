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

map<string, pll > m; // mapping sections to coordinates
map<string, int > g; //mapping sections to groups 
char a[31][31];
vector <product> prod;

void display()
{
    ll i,j;
    for (i=0;i<=30;i++)
    {
        for (j=0;j<=30;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
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
    display();
}