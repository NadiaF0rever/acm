/*
 * UVA 536
 *
 */
#include <stdio.h>
#include <string.h>

typedef unsigned char u_char;

#define TREENOBE_SIZE 32

u_char g_out[TREENOBE_SIZE];
u_char *g_tmp;

#define PUSH(c) do{	\
	*(g_tmp++) = (c);	\
}while(0)

#define FIND_CHAR(beg, val) do{	\
	while(*beg != (val)) beg++;	\
}while(0)

void
rebuild(u_char *p_str_beg, u_char *p_str_end, u_char *i_str_beg, u_char *i_str_end){
	u_char root = p_str_beg[0], *i_root = i_str_beg;
	size_t left_child_num, right_child_num;
	
	PUSH(root);	
	FIND_CHAR(i_root, root);
	left_child_num = i_root - i_str_beg;
	right_child_num = i_str_end - i_root - 1;
	
	#ifdef DEBUG
		printf("root=%c left_child_num=%lu right_child_num=%lu\n",\
			   	*i_root, left_child_num, right_child_num);
	#endif
	
	if(right_child_num > 1) rebuild(p_str_beg + left_child_num + 1, p_str_end, i_root + 1, i_str_end);
	else if(right_child_num == 1) PUSH(*(i_root + 1));
	else ;
	
	if(left_child_num > 1) rebuild(p_str_beg + 1, p_str_beg + left_child_num + 1, i_str_beg, i_root);
	else if(left_child_num == 1) PUSH(*(i_root - 1));
	else ;
	
}


int
main(void){
	u_char data[TREENOBE_SIZE << 1];
	u_char *tmp;
	while(fgets(data, TREENOBE_SIZE << 1, stdin) != NULL){
		tmp = data;
		FIND_CHAR(tmp, ' ');
		g_tmp = g_out;
		
		rebuild(data, tmp, tmp + 1, tmp + (tmp - data ) + 1);
		
		while(g_tmp != g_out){
			putchar(*(--g_tmp));
		}
		putchar('\n');
	}
	
	return 0;
}
