#include <stdio.h>

#define BLOCK_NUM   32

#include <stdlib.h>
#define assert(x)   (void *)0

typedef struct block_s block_t;

struct block_s{
    block_t **pprev;
    block_t *next;
    int     num;
    int     idx;
};

struct pile_s{
    block_t *beg;
    block_t *end;
};
typedef struct pile_s pile_t;

block_t *piles[BLOCK_NUM];
block_t blocks[BLOCK_NUM];

void
block_reset(block_t *b)
{
    b->idx = b->num;
    b->next = NULL;
    b->pprev = piles + b->num;

    piles[b->num] = b;
}

void
block_clear(block_t *a)
{
    block_t     *del = a->next, *tmp;
    while(del){
        tmp = del;
        del = del->next;

        block_reset(tmp);
    }

    a->next = NULL;
}

void
block_move(block_t *dst, block_t *src)
{
    block_t *p = src;
    while(p){
        p->idx = dst->idx;
        p = p->next;
    }

    *src->pprev = NULL;
    src->pprev = &dst->next;
    dst->next = src;
}

void
block_init()
{
    block_t *block;
    int     i;
    for(i = 0; i < BLOCK_NUM; i++){
        block = blocks + i;
        block->num = i;
        block_reset(block);
    }
}

block_t *
block_pile_top(block_t *b)
{
    while(b->next){
        b = b->next;
    }

    return b;
}

void
cmd_move_a_onto_b(int a, int b)
{
    block_t *ba = blocks + a;
    block_t *bb = blocks + b;

    block_clear(ba);
    block_clear(bb);
    block_move(bb, ba);
}

void
cmd_move_a_over_b(int a, int b)
{
    block_t *ba = blocks + a;
    block_t *bb = blocks + b;

    block_clear(ba);

    bb = block_pile_top(bb);
    block_move(bb, ba);
}

void
cmd_pile_a_onto_b(int a, int b)
{
    block_t *ba = blocks + a;
    block_t *bb = blocks + b;

    block_clear(bb);

    block_move(bb, ba);
}

void
cmd_pile_a_over_b(int a, int b)
{
    block_t *ba = blocks + a;
    block_t *bb = blocks + b;

    bb = block_pile_top(bb);
    block_move(bb, ba);
}

int
cmd_illegal(int a, int b)
{
    if(a == b){
        return 1;
    }
    block_t *ba = blocks + a;
    block_t *bb = blocks + b;

    if(ba->idx == bb->idx){
        return 1;
    }

    return 0;
}

void dump(int);

int
main(void)
{
    char    buf[32], type[8], op[8];
    int     a, b, n;
    block_init();

    a = scanf("%d\n", &n);

    while(fgets(buf, sizeof(buf), stdin) != NULL){
        if(buf[0] == 'q'){
            break;
        }

        sscanf(buf, "%s %d %s %d", type, &a, op, &b);

        if(cmd_illegal(a, b)){
            continue;
        }

        if(type[0] == 'm'){
            if(op[1] == 'v'){
                cmd_move_a_over_b(a, b);
            }else if(op[1] == 'n'){
                cmd_move_a_onto_b(a, b);
            }else{
                assert(0);
            }
        }else if(type[0] == 'p'){
            if(op[1] == 'v'){
                cmd_pile_a_over_b(a, b);
            }else if(op[1] == 'n'){
                cmd_pile_a_onto_b(a, b);
            }else{
                assert(0);
            }

        }else{
            assert(0);
        }
    }


    dump(n);
    return 0;
}

void
block_print(block_t *b){
    while(b){
        printf(" %d", b->num);
        b = b->next;
    }
}

void
dump(int n)
{
    int i;
    for(i = 0; i < n; i++){
        printf("%d:", i);
        block_print(piles[i]);
        printf("\n");
    }
}
