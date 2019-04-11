#include <stdio.h>


typedef unsigned int uint32_t;

int
calc(uint32_t val)
{
    int ret = 0;
LOOP:

    ret += 1;

    if(val == 1){
        return ret;
    }

    if(val & 1){
        val = val * 3 + 1;
    }else{
        val = val >> 1;
    }

    goto LOOP;
}

int
main(void)
{
    int i, j, k, beg, end, result, tmp;
    while(scanf("%d %d", &beg, &end) != EOF){
        result = 0;

        if(beg > end){
            j = end;
            k = beg;
        }else{
            j = beg;
            k = end;
        }

        for(i = j; i < k+1; i++){
            tmp = calc(i);
            if(tmp > result){
                result = tmp;
            }
        }

        printf("%d %d %d\n", beg, end, result);
    }

    return 0;
}
