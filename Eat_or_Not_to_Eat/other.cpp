#include <stdio.h>
#define MAXN 1010
#define _cp(a,b) ((a)<(b))
typedef int elem_t;

struct heap{
	elem_t h[MAXN];
	int ind[MAXN],map[MAXN],n,p,c;
	void init(){n=0;}
	void ins(int i,elem_t e){
		for (p=++n;p>1&&_cp(e,h[p>>1]);h[map[ind[p]=ind[p>>1]]=p]=h[p>>1],p>>=1);
		h[map[ind[p]=i]=p]=e;
	}
	int del(int i,elem_t& e){
		i=map[i];if (i<1||i>n) return 0;
		for (e=h[p=i];p>1;h[map[ind[p]=ind[p>>1]]=p]=h[p>>1],p>>=1);
		int a, b;
		return delmin(a, b);
//		for (c=2;c<n&&_cp(h[c+=(c<n-1&&_cp(h[c+1],h[c]))],h[n]);h[map[ind[p]=ind[c]]=p]=h[c],p=c,c<<=1);
//		h[map[ind[p]=ind[n]]=p]=h[n];n--;return 1;
	}
	int delmin(int& i,elem_t& e){
		if (n<1) return 0;i=ind[1];
		for (e=h[p=1],c=2;c<n&&_cp(h[c+=(c<n-1&&_cp(h[c+1],h[c]))],h[n]);h[map[ind[p]=ind[c]]=p]=h[c],p=c,c<<=1);
		h[map[ind[p]=ind[n]]=p]=h[n];n--;return 1;
	}
	int getmin(elem_t& e) {
		e = h[1]; return ind[1];
	}
};

long long getGcd(long long a, long long b)
{
	long long t;
	while (b) {
		t = a;
		a = b;
		b = t % a;
	}
	return a;
}


int m[1010][20], ti[1010], indexs[10], l;
heap cow[15][15];

int main()
{
	int cases, n, count, mint, mini, c, e, temp, k, ln;
	scanf("%d", &cases);
	while (cases--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", ti + i);
			for (int j = 0; j < ti[i]; j++)
				scanf("%d", &m[i][j]);
		}
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				cow[i][j].init();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < ti[i]; j++) {
				cow[ti[i]][j].ins(i, m[i][j]);
			}
		}
		long long t = 1;
		for (int i = 0; i < 11; i++)
			if (cow[i][0].n)
				t = t * i / getGcd(t, i);

		l = -1;
		ln = 0;
		int sb;
		for (k = 0; k <= t * n; k++) {
			if (!n) break;
			if (k % t == 0) {
				if (ln == n) break;
				ln = n;
			}
			mint = 1000;
			for (int j = 1; j < 11; j++){
				if (cow[j][k%j].n == 0) continue;
				sb = cow[j][k%j].h[1];
				printf("HOLE %d %d\n", sb, k%j);
				if(sb < mint){
					mint = sb;
					mini = j;
				}
			}
			count = 0;
			for (int j = 1; j < 11; j++)
				if (cow[j][k%j].n && mint == cow[j][k%j].h[1])
					count++;
			printf("SHABI %d %d\n", mint, count);
			if (count > 1) continue;

			cow[mini][k%mini].delmin(c, e);
			if (e == cow[mini][k%mini].h[1] && cow[mini][k%mini].n)
				cow[mini][k%mini].ins(c, e);
			else {
				n--;
				l = k;
				printf("CAONIMA %d %d %d\n", mini - 1, k % mini, l);
				printf("DEL %d\n", e);
				for (int i = 0; i < mini; i++)
					if (i != k%mini){
						cow[mini][i].del(c, e);
						printf("DEL_OTHER %d\n",e);
					}
			}
		}
		printf("%d %d\n", n, l + 1);
	}

}
