/*
 * UVA 10149
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 

#define VAL_MAX_LEN 13
#define N			8196
typedef unsigned short elem_t;

elem_t g_val[VAL_MAX_LEN][VAL_MAX_LEN];

elem_t g_data[N];
elem_t g_elems[N][VAL_MAX_LEN];

int
read_data(){
	int  i = 0, j, val, index, ret = 0, max_count, sum, z_count;
	char input[16], *tmp;
	int data[6];
	while(i < VAL_MAX_LEN && fgets(input, 16, stdin) != NULL){
		tmp = input;
		sum = 0;
		max_count = 0;
		j = 0;
		z_count = 0;
		ret = 1;

		memset(data, 0, sizeof(int) * 6);
		for(j = 0; j < 5; j++, tmp += 2){
			val = *tmp - '0';
			index = val - 1;
			sum += val;
			
			max_count = (++data[index] > max_count) ? data[index] : max_count;
		}
		for(j = 0; j < 6; j++){
			g_val[i][j] = data[j] *(j + 1);
		}
		g_val[i][6] = sum;
		g_val[i][7] = max_count > 2 ? sum: 0;
		g_val[i][8] = max_count > 3 ? sum: 0;
		g_val[i][9] = max_count == 5 ? 50: 0;	

		if(max_count > 3){
			g_val[i][10] = 0;
			g_val[i][11] = 0;
			g_val[i][12] = 0;
		}else if(max_count == 3){
			g_val[i][10] = 0;
			g_val[i][11] = 0;
			for(j = 0; j < 6; j++){
				z_count += (data[j] == 0);
			}
			g_val[i][12] = (z_count == 4) ? 40: 0;
		}else if(max_count == 2){
			for(j = 0; j < 6; j++){
				z_count += (data[j] == 0);
			}
			if(z_count == 2){
				if(data[0] == 0 && data[1] == 0 || data[0] == 0 && data[5] == 0 || \
						data[4] == 0 && data[5] == 0){
					g_val[i][10] = 25;
				}else g_val[i][10] = 0;

			}else{
				g_val[i][10] = 0;
			}
			g_val[i][11] = 0;
			g_val[i][12] = 0;
		}else{
			g_val[i][10] = (data[2] != 0 && data[3] != 0) ? 25: 0;
			g_val[i][11] = (data[0] == 0 || data[5] == 0) ? 35: 0;
			g_val[i][12] = 0;
		}
		i++;
	}

	return ret;
}

#define SET(val, n) (val) = (val | (1 << (n)))
#define UNSET(val, n) (val) = (val & ~(1 << (n)))

elem_t stack[VAL_MAX_LEN];
size_t tail = 0;
#define PUSH(i) stack[tail++] = (i)
#define POP() stack[--tail]
#define EMPTY() (tail == 0)

void
main_process(n){
	elem_t end[VAL_MAX_LEN + 1], val, index;
	unsigned short  i, j;
	unsigned short mask = 0, pmask = 0;
	for(i = 0; i < n - 1; i++){
		end[i] = VAL_MAX_LEN - n + i + 1;
		PUSH(i);
		SET(mask, i);
	}

	while(1){
		while(i != VAL_MAX_LEN){
			PUSH(i);
			SET(mask, i);
			for(j = 0; j != tail; j++){
				pmask = mask;
				index = stack[j];
				UNSET(pmask, index);
				val = g_data[pmask] + g_val[index][n - 1];

				if(n == 6 && val > 62){
					val += 35;
				}
				if(g_data[mask] < val){
					g_data[mask] = val;

					if(n == 1){
						g_elems[mask][0] = g_val[index][n - 1];
					}else{
						memcpy(g_elems[mask], g_elems[pmask], sizeof(elem_t) * (n - 1));
						g_elems[mask][n - 1] = g_val[index][n - 1];
					}
				}
			}
			UNSET(mask, i);
			POP();
			i++;
		}

		while(1){
			if(EMPTY()) goto done;
			i = POP();
			UNSET(mask, i);
			if(i != end[tail]){
				while(tail != n - 1){
					PUSH(++i);
					SET(mask, i);
				}
				i++; /*IT IS IMPORTANT*/
				break;
			}
		}

	}
done:
	return;
}

void
x_print(){
	int i;
	for(i = 0; i < N; i++){
		if(g_data[i] != 0){
			printf("%x %d %d\n", i, g_data[i], g_elems[i][0]);
		}
	}
}

int
main(int argc, char *argv[]){
	int i, p_6; /*the sum of first six categores*/
	int t;

	while(read_data() != 0){
		p_6 = 0;
		memset(g_data, 0, sizeof(elem_t) * N);
		for(i = 0; i < VAL_MAX_LEN; i++){
			main_process(i + 1);
		}

		for(i = 0; i < VAL_MAX_LEN; i++){
			t = g_elems[8191][i];
			p_6 += (i < 6) ? t: 0;
			printf("%d ", t);
		}
		printf("%d %d\n", p_6 > 62 ? 35: 0, g_data[8191]);
	}

	return 0;
}
