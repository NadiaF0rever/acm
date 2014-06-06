#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=10010;
struct node
{
	int col,data;
	node(int c,int d):col(c),data(d){}
};
vector<node> matrix[maxn];
int n,m,col[maxn],cnt,x;
void init()
{
	for(int i=0;i<=max(n,m);i++)
		matrix[i].clear();
}
int main()
{
	while(cin>>n>>m)
	{
		init();
		for(int i=1;i<=n;i++)
		{
			cin>>cnt;
			if(!cnt)continue;
			for(int j=1;j<=cnt;j++)
				cin>>col[j];
			for(int j=1;j<=cnt;j++)
			{
				cin>>x;
				matrix[col[j]].push_back(node(i,x));
			}
		}
		cout<<m<<" "<<n<<endl;
		for(int i=1;i<=m;i++)
		{
			int len=matrix[i].size();
			cout<<len;
			for(int j=0;j<len;j++)
				cout<<" "<<matrix[i][j].col;
			cout<<endl;
			bool first=true;
			for(int j=0;j<len;j++)
			{
				if(first)first=false;
				else cout<<" ";
				cout<<matrix[i][j].data;

			}
			cout<<endl;
		}
	}
	return 0;
}

