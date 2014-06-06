#include<stdio.h>
#include<string.h>
#define MAXD 1010
#define INF 1000000000
int N, T, t[MAXD], d[MAXD][20], U[MAXD], D[MAXD], st[MAXD];
int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}
void init()
{
	int i, j, k;
	scanf("%d", &N);
	for(i = 1; i <= N; i ++)
	{
		scanf("%d", &t[i]);
		for(j = 0; j < t[i]; j ++)
			scanf("%d", &d[i][j]);
	}
	for(i = 0; i <= N; i ++)
	{
		D[i] = i + 1;
		U[i + 1] = i;
	}
	D[N] = 0;
	memset(st, 0, sizeof(st));
	T = 1;
	for(i = 1; i <= N; i ++)
	{
		if(T < t[i])
			k = gcd(t[i], T);
		else
			k = gcd(T, t[i]);
		T = T * t[i] / k;
	}
}
void solve()
{
	int i, j, k, cur, min, num, flag, a, p, sum;
	num = min = 0;
	for(p = 0;; p ++)
	{
		flag = 0;
		for(cur = 1; cur <= T; cur ++)
		{
			a = INF;
			for(i = D[0]; i != 0; i = D[i])
			{
				if(d[i][st[i]] < a)
				{
					a = d[i][st[i]];
					k = i;
					sum = 1;
				}
				else if(d[i][st[i]] == a)
					sum ++;
				st[i] = (st[i] + 1) % t[i];
			}
			if(sum == 1)
			{
				flag = 1;
				U[D[k]] = U[k];
				D[U[k]] = D[k];
				min = p * T + cur;
				num ++;
			}
		}
		if(!flag)
			break;
	}
	printf("%d %d\n", N - num, min);
}
int main()
{
	int test;
	scanf("%d", &test);
	while(test --)
	{
		init();
		solve();
	}
	return 0;
}
