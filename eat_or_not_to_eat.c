/*
 * UVA 10273
 *
 */
#include <stdio.h>
#include <string.h>

/*#define DEBUG*/
#define COWNUM_MAX 1001
#define DAY_MAX 10

typedef struct{
	int data[COWNUM_MAX];
	int ind[COWNUM_MAX];
	int map[COWNUM_MAX];
	int nums;
}cows_heap_t;

void
cows_heap_init(cows_heap_t *self){
	memset(self->data, 0, DAY_MAX);
	self->nums = 0;
}

int 
caonima(i){
	return (i -= (0x1 & ~ i)) >> 1;
}

void
cows_heap_insert(cows_heap_t *self, int index, int elem){
	int *t = self->data, *map = self->map, *ind = self->ind, i = self->nums, j, tmp;
	for(i = self->nums++, j = caonima(i); i > 0 && elem < t[j]; i = j, j = caonima(j)){
		t[map[ind[i] = ind[j]] = i] = t[j];
	}
	t[map[ind[i] = index] = i] = elem;
}

void
cows_heap_delmin(cows_heap_t *self, int *index, int *elem){
	int *t = self->data, *map = self->map, *ind = self->ind, n = --self->nums, p = 0, i;
	*index = ind[0];
	*elem = t[0];

	for(i = 1; i < n + 1 && t[i += (i < n && t[i + 1] < t[i])] < t[n]; \
			t[map[ind[p] = ind[i]] = p] = t[i], p = i, i = (i<<1) + 1) ;
	t[map[ind[p] = ind[n]] = p] = t[n];
}

void
cows_heap_del(cows_heap_t *self, int index, int *elem){
	int *t = self->data, *map = self->map, *ind = self->ind, p = map[index], i, e;	
	*elem = t[p];
	for(i = caonima(p); p > 0; t[map[ind[p] = ind[i]] = p] = t[i], p = i, i = caonima(i)) ;
	/*for(i = 1; i < n + 1 && t[i += (i < n && t[i + 1] < t[i])] < t[n]; \
			t[map[ind[p] = ind[i]] = p] = t[i], p = i, i = (i << 1) + 1) ;
	t[map[ind[p] = ind[n]] = p] = t[n];*/
	cows_heap_delmin(self, &i, &e);
}

void
cows_heap_print(cows_heap_t *self){
	int i, j = 1;
	printf("****************\n");
	for(i = 0; i < self->nums; i++){
		printf("%d ", self->data[i]);
		if(i + 1 == j){
			printf("\n");
			j = (j << 1) + 1;
		}
	}
	printf("\n");
}

int
get_gcd(int a, int b){
	int t;
	while(b){
		t = a;
		a = b;
		b = t % a;
	}
	return a;
}

int g_cow_num = 0;
int g_T = 1;
cows_heap_t g_heaps[DAY_MAX][DAY_MAX];

void
init(){
	int cow_num, i, j, milk, day;
	g_T = 1;
	g_cow_num = 0;
	memset(g_heaps, 0, sizeof(cows_heap_t) * DAY_MAX * DAY_MAX);

	scanf("%d", &cow_num);
	g_cow_num = cow_num;
	while(cow_num--){
		scanf("%d", &day);
		for(i = 0; i< day; i++){
			scanf("%d", &milk);
			cows_heap_insert(&g_heaps[day - 1][i], cow_num, milk);
		}
	}

	for(i = 1; i < DAY_MAX + 1; i++){
		if(g_heaps[i - 1][0].nums != 0){
			g_T = i * g_T / get_gcd(i, g_T);
		}
	}
}

void
solve(){
	int times, days, i, t, n,  milk_min, min_heap_i, cow_i, milk, if_over, last_day = -1, if_kill; 
	int original_cow_num = 0;
	for(days = 0; ; days++){
		if_kill = 0;
		milk_min = 100000;
		if(g_cow_num == 0) break;
		if(days % g_T == 0){
			if(original_cow_num == g_cow_num) break;
			else original_cow_num = g_cow_num;
		}
		for(i = 0; i < DAY_MAX; i++){
			if(g_heaps[i][0].nums == 0) continue;
			n = days % (i + 1);
			t = g_heaps[i][n].data[0];
#ifdef DEBUG
			printf("HOLE %d %d\n", t, n);
#endif
			if(t < milk_min){
				milk_min = t;
				if(g_heaps[i][n].nums > 2 && (t == g_heaps[i][n].data[1] || t == g_heaps[i][n].data[2])){
					if_kill = 0;
				}else if(g_heaps[i][n].nums > 1 && t == g_heaps[i][n].data[1]){
					if_kill = 0;
				}else{
					if_kill = 1;
				}
				min_heap_i = i;
			}else if(t == milk_min){
				if_kill = 0;
			}
		}
#ifdef DEBUG
		printf("SHABI %d %d\n", milk_min, if_kill);
#endif
		if(if_kill == 1){
			cows_heap_delmin(&g_heaps[min_heap_i][days % (min_heap_i + 1)], &cow_i, &milk);
			last_day = days;
#ifdef DEBUG
			printf("CAONIMA %d %d %d\n", min_heap_i, days % (min_heap_i + 1), last_day);
			printf("DEL %d\n",  milk);
#endif

			for(i = 0; i < min_heap_i + 1; i++){
				if(i == days % (min_heap_i + 1)) continue;
				cows_heap_del(&g_heaps[min_heap_i][i], cow_i, &milk);
#ifdef DEBUG
				printf("DEL_OTHER %d\n", milk);
#endif
			}
			if_over = 0;
			g_cow_num--;
		}
	}
	printf("%d %d\n", g_cow_num, 1 + last_day);
}


int
main(void){
	int n;
	scanf("%d", &n);
	while(n--){
		init();
		solve();
	}

	return 0;
}
