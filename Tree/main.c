/*
 * UVA 548
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long uint64_t;
typedef struct __result{
	uint64_t	sum;
	int		nobe_val;
}result_t;

#define FIND(beg, val) do{	\
	while(*(beg) != (val)) (beg)++;	\
}while(0)
 
/*#define DEBUG*/
#define NOBEMAX_VAL	-1
#define NOBENUM_MAX 10001
void
process(int *i_beg, int *i_end, int *p_beg, int *p_end, result_t *result){
	int root_val = *(p_end - 1), *i_root = i_beg, left_child_num, right_child_num;
	FIND(i_root, root_val);
	left_child_num = i_root - i_beg;
	right_child_num = i_end - i_root - 1;

#ifdef DEBUG
	printf("root: %d\n", root_val);
#endif

	if(left_child_num == 0 && right_child_num == 0 ){
		result->sum = root_val;
		result->nobe_val = root_val;
		return;
	}

	result_t left_result = {NOBEMAX_VAL, 0}, right_result = {NOBEMAX_VAL, 0};

	if(left_child_num > 1){
		process(i_beg, i_root, p_beg, p_beg + left_child_num, &left_result);
	}else if(left_child_num == 1){
		left_result.sum = *i_beg;
		left_result.nobe_val = *i_beg;
	}else ;

	if(right_child_num > 1){
		process(i_root + 1, i_end, p_beg + left_child_num, p_end - 1, &right_result);
	}else if(right_child_num == 1){
		right_result.sum = *(p_end - 2);
		right_result.nobe_val = *(p_end - 2);
	}else ;

#ifdef DEBUG
	printf("root: %d left: %lu %d right: %lu %d\n", root_val, left_result.sum, left_result.nobe_val, \
			right_result.sum, right_result.nobe_val);
#endif
	result_t * ret;
	if(left_result.sum < right_result.sum){
		ret = &left_result;
	}else if(left_result.sum > right_result.sum){
		ret = &right_result;
	}else{
		ret = left_result.nobe_val < right_result.nobe_val ? \
			  &left_result: &right_result;
	}

	result->sum = root_val + ret->sum;
	result->nobe_val = ret->nobe_val;
	return;
}


int
main(void){
	int input[NOBENUM_MAX << 1], *ptr = input, i_tmp, len, line_count = 0;
	char c_tmp;
	result_t r;
	while(scanf("%d%c", ptr++, &c_tmp) != EOF){
		if(c_tmp == '\n'){
			line_count++;
		}
		if(line_count == 2){
			len = (ptr - input) / 2;
			process(input, input + len, input + len, ptr, &r);

			printf("%d\n", r.nobe_val);
			ptr = input;
			line_count = 0;
		}
	}
	return 0;
}
