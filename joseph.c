/*
 * UVA 305
 *
 */
#include <stdio.h>

#define INT_MAX 0x7fffffff
#define NEXT_POS(tmp_pos, gap, len) (((tmp_pos) + (gap) -1) % (len))
/*#define DEBUG*/

int
next_pos(int tmp_pos, int gap, int len){
	int ret = (tmp_pos + gap - 1) % len;
	return ret == 0 ? len: ret;
}
/*
 * ret % 2k = pos1
 * ret % 2k - 1 = pos2
 *
 */
int
judge(int val, int k){
	int i, tmp_pos=1, queue_len = k << 1;
	for(i = 0; i < k; i++){
		tmp_pos = next_pos(tmp_pos, val, queue_len--);
		if(tmp_pos > k){
			continue;
		}
		break;
	}

	return tmp_pos > k ? val: -1;
}


int
main(void){
	int k, i, j, ret, ans[32];
	for(k = 1; k < 15; k++){
		for(i = k + 1; i < INT_MAX; i += k){
			for(j = 0; j < k; j++){
				ret = judge(i, k);
				i++;

				if(ret != -1){
					goto next;
				}
			}
		}
next:
		ans[k] = ret;
	}
	while(scanf("%d", &k) != EOF){
		if(k == 0) break;
		printf("%d\n", ans[k]);
	}
	return 0;
}
