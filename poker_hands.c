/*
 * UVA 10315
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TYPE_ONE	1
#define TYPE_TWO	2
#define TYPE_THREE	3
#define TYPE_FOUR	4
#define TYPE_STRAIGHT	5
#define TYPE_FLUSH		6
#define TYPE_SFLUSH		7


#define SIZE 5
#define COLOR(x) ((u_char *)&x)[1]
#define VALUE(x) (u_char)val[x]
#define ADD_VAL(ptr, val) ((ptr)->type++;(ptr)->value=val;)

#define LEVEL_S 9
#define LEVEL_C 6
#define LEVEL_D 5

/* return 1 if (slot_t)a < (slot_t)b*/
#define FUN_PTR(a, b) ((a)->type == (b)->type ? (a)->val < (b)->val: \
		(a)->type < (b)->type ? 1: 0)

#define EQUAL_PTR(a, b)((a)->type == (b)->type && (a)->val == (b)->val)
#define SWAP(a, b) do{\
	slot_t __hehe = (a);	\
	(a) = (b);	\
	(b) = __hehe;	\
}while(0)

typedef unsigned short	uint16_t;
typedef unsigned char	u_char;
int level[5][3] = {
	{0, 0, 0},
	{0, 1, 0},
	{0, 2, 3},
	{0, 4, 6},
	{0, 7, 0}
};

int val[35] = {2, 3, 4, 5, 6, 7, 8, 9};
typedef struct{
	u_char	type;
	u_char 	val;
}slot_t;

typedef struct{
	slot_t	beg[SIZE];
	slot_t	*tmp, *end;
	u_char	level;
}bucket_t;

void
init_bucket(bucket_t *p){
	memset(p->beg, 0, sizeof(bucket_t));
	p->tmp = p->beg;
	p->end = p->beg + SIZE;
}

void
print_bucket(bucket_t *p){
	slot_t *t = p->beg;
	printf("level=%d ", p->level);
	while(t != p->tmp){
		printf(" beg[%ld].type=%d beg[%ld].val=%d", t - p->beg, t->type, \
				t - p->beg, t->val);
		t++;
	}
	printf("\n");
}

void
build_bucket(uint16_t *input, bucket_t *buck){
	int i;
	uint16_t tmp;
	slot_t *p, *p_p;
	u_char last_color = 0xFF, tmp_val, tmp_color, is_straight = 0;
	for(i = 0; i < SIZE; i++){
		tmp = *input++;

		tmp_color = COLOR(tmp);
		if(i == 0) last_color = tmp_color;
		else{
			if(last_color != tmp_color) last_color = 0xFF;
		}

		tmp_val = VALUE((u_char)tmp - '2');
		p = buck->beg;
		while(p != buck->tmp){
			if(p->val == tmp_val) break;
			p++;
		}

		if(p == buck->tmp){
			p->val = tmp_val;
			p->type = TYPE_ONE;
			buck->tmp++;
		}else{
			p->type += 1;
		}

		p_p = p - 1;
		while(p_p != buck->beg - 1){
			if(FUN_PTR(p_p, p)){ 
				SWAP(*p_p, *p);
				p = p_p;
				p_p--;
			}else break;
		}
	}

#define X(i) (buck->beg[i].val - buck->beg[i + 1].val)
	if(buck->tmp == buck->end && X(0)== 1 && X(1) == 1 && X(2) == 1 && X(3) == 1){
		is_straight = 1;
	}

	if(is_straight && last_color != 0xFF) buck->level = LEVEL_S;
	else if(last_color != 0xFF) buck->level = LEVEL_C;
	else if(is_straight) buck->level = LEVEL_D;
	else buck->level = level[buck->beg->type][(buck->beg + 1)->type];
}

int
compare_buck_ptr(bucket_t *a, bucket_t *b){
	slot_t *a_t = a->beg, *b_t = b->beg;
	if(a->level != b->level) return a->level < b->level ? -1: 1;
	for(; a_t != a->tmp && b_t != b->tmp; a_t++, b_t++){
		if(EQUAL_PTR(a_t, b_t)) continue;
		else return FUN_PTR(a_t, b_t) == 1 ? -1: 1;
	}

	if(a_t == a->tmp && b_t == b->tmp) return 0;
	return 0;
}

void 
process(char *input){
	int i = 1;
	char *p, *s = input + 2;
	for(i = 1; i < 10; i++){
		p = input + 3 * i;
		*s++ = *p++;
		*s++ = *p++;
	}
}
int
main(void){
	char ___in[64];
	int i, compare_ret;
	bucket_t a, b;
	val[15] = 14;
	val[24] = 11;
	val[25] = 13;
	val[31] = 12;
	val[34] = 10; 


	while(fgets(___in, sizeof(___in), stdin) != NULL){
		process(___in);
		init_bucket(&a);
		init_bucket(&b);

		build_bucket((uint16_t *)___in, &a);
		build_bucket((uint16_t *)(___in + 10), &b);

		/*print_bucket(&a);
		print_bucket(&b);*/
		printf("%s\n", (compare_ret = compare_buck_ptr(&a, &b)) == 0 ? "Tie." : \
				compare_ret == -1 ? "White wins.": "Black wins.");
	}
	return 0;
}
