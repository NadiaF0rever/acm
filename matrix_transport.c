/*
 *UVA 10895
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOBE_MAX_NUM	10001
#define HEAD_MAX_NUM	10001

int tmp[NOBE_MAX_NUM];
typedef int nobe_ptr_t;

typedef struct{
	int	row;
	int col;
	int val;
	nobe_ptr_t next;	
}nobe_t;

typedef struct{
	nobe_ptr_t	beg;
	nobe_ptr_t	end;
	size_t		len;
}head_t;


nobe_t g_nobe_pool[NOBE_MAX_NUM];
head_t g_head_pool[HEAD_MAX_NUM];
int		g_nobe_index = 1;


#define NOBE_PTR_NULL 0
#define NOBE_NEW(ROW, COL, VAL) \
	(g_nobe_pool[g_nobe_index].row = ROW, \
	 g_nobe_pool[g_nobe_index].col = COL, \
	 g_nobe_pool[g_nobe_index].val = VAL, \
	 g_nobe_pool[g_nobe_index].next = NOBE_PTR_NULL, \
	 g_nobe_index++)

#define PUSH_BACK(index, nobe_ptr) do{	\
	if(g_head_pool[index].len == 0){ \
		g_head_pool[index].beg = g_head_pool[index].end \
		= nobe_ptr;}	\
	else{ \
		g_nobe_pool[g_head_pool[index].end].next = nobe_ptr; \
		g_head_pool[index].end = nobe_ptr;	\
	} \
	g_head_pool[index].len++;	\
}while(0)

int
main(void){
	int row, col, val, index, t, i, j, n, k;

	g_nobe_pool[0].row = -1;
	g_nobe_pool[0].col = -1;
	g_nobe_pool[0].val = -1;
	g_nobe_pool[0].next = -1;
	while(scanf("%d", &row) != EOF){
		scanf("%d", &col);
	
		for(i = 0; i < row; i++){
			scanf("%d", &n);
			if(n == 0) continue;
			for(j = 0; j < n; j++){
				scanf("%d", (tmp + j));
			}

			for(j = 0; j < n; j++){
				scanf("%d", &val);
				index = *(tmp + j);
				t = NOBE_NEW(index, i + 1, val);
				PUSH_BACK(index, t);
			}
		}

		printf("%d %d\n", col, row);
		for(j = 1; j <= col; j++){
			if(t = g_head_pool[j].len){
				printf("%d", t);
				t = g_head_pool[j].beg;
				while(t != 0){
					printf(" %d", g_nobe_pool[t].col);
					t = g_nobe_pool[t].next;
				}
				printf("\n");
				t = g_head_pool[j].beg;
				while(t != 0){
					k = t;
					t = g_nobe_pool[t].next;
					printf("%d%c", g_nobe_pool[k].val, (t == 0) ? '\n': ' ');
				}
			}else{
				printf("0\n\n");
			}
		}

		g_nobe_index = 1;
		memset(g_head_pool, 0, HEAD_MAX_NUM * sizeof(head_t));
	}

	return 0;
}
