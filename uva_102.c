#include <stdio.h>

typedef struct chocie_s {
    char    *code;
    int     s1;
    int     s2;
    int     s3;
}choice_t;

/*
 * B G C
 * 0 1 2
 * 3 4 5
 * 6 7 8
 */
static choice_t choices[] = {
    {"BCG", 0, 5, 7},
    {"BGC", 0, 4, 8},
    {"CBG", 2, 3, 7},
    {"CGB", 2, 4, 6},
    {"GBC", 1, 3, 8},
    {"GCB", 1, 5, 6}
};

void
choice_make(
        int b1, int g1, int c1,
        int b2, int g2, int c2,
        int b3, int g3, int c3)
{
    choice_t    *ch;
    int         min_val = 0x7fffffff, tmp;
    int         sum = b1 + b2 + b3 + g1 + g2 + g3 + c1 + c2 + c3;
    int         arr[] = {b1, g1, c1, b2, g2, c2, b3, g3, c3};
    int         i, result = 0;

    for(i = 0; i < sizeof(choices) / sizeof(choices[0]); i++){
        ch = choices + i;
        tmp = sum - arr[ch->s1] - arr[ch->s2] - arr[ch->s3];

        if(tmp < min_val) {
            min_val = tmp;
            result = i;
        }
    }

    printf("%s %d\n", choices[result].code, min_val);
}


int
main(void)
{
    char        line[256];
    int         b1, b2, b3, g1, g2, g3, c1, c2, c3; 

    while(fgets(line, sizeof(line), stdin) != NULL){
        sscanf(line, "%d %d %d %d %d %d %d %d %d",
                &b1, &b2, &b3, &g1, &g2, &g3, &c1, &c2, &c3);

        choice_make(b1, b2, b3, g1, g2, g3, c1, c2, c3);
    }

    return 0;
}
