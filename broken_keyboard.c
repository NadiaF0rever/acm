/*
 *http://uva.onlinejudge.org/external/119/11988.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct list_nobe{
	struct list_nobe *prev;
	struct list_nobe *next;
	void *data;
};

struct list_head{
	struct list_nobe  *head;
	struct list_nobe  *tail;
};

#define LIST_INIT_HEAD(head_nobe) do{	\
	(head_nobe)->head = (void *)(head_nobe);	\
	(head_nobe)->tail = (void *)(head_nobe);	\
}while(0)

#define LIST_INSERT_HEAD(head_nobe, new_nobe) do{	\
	(new_nobe)->next = (head_nobe)->head;	\
	(new_nobe)->prev = (void *)(head_nobe);	\
	if((head_nobe)->tail == (void *)(head_nobe))	\
		(head_nobe)->tail = (new_nobe);	\
	else	\
		(head_nobe)->head->prev = (new_nobe);	\
	(head_nobe)->head = (new_nobe);	\
}while(0)

#define LIST_INSERT_TAIL(head_nobe, new_nobe) do{	\
	(new_nobe)->next = (void *)(head_nobe);	\
	(new_nobe)->prev = (head_nobe)->tail;	\
	if((head_nobe)->head == (void *)(head_nobe))	\
		(head_nobe)->head = (new_nobe);	\
	else	\
		(head_nobe)->tail->next = (new_nobe);	\
	(head_nobe)->tail = (new_nobe);	\
}while(0)

#define LIST_INSERT_BEFORE(head_nobe, nobe, new_nobe) do{	\
	(new_nobe)->next = (nobe);	\
	(new_nobe)->prev = (nobe)->prev;	\
	if((nobe)->prev == (void *)(head_nobe))	\
		(head_nobe)->head = new_nobe;	\
	else	\
		(nobe)->prev->next = (new_nobe);	\
	(nobe)->prev = (new_nobe);	\
}while(0)

#define LIST_INSERT_AFTER(head_nobe, nobe, new_nobe) do{	\
	(new_nobe)->prev = (nobe);	\
	(new_nobe)->next = (nobe)->next;	\
	if((nobe)->next == (void *)(head_nobe))	\
		(head_nobe)->tail = (new_nobe);	\
	else	\
		(nobe)->next->prev = (new_nobe);	\
	(nobe)->next = (new_nobe);	\
}while(0)

#define LIST_DELETE(head_nobe, nobe) do{	\
	if((nobe)->prev == (void *)(head_nobe))	\
		(head_nobe)->head = (nobe)->next;	\
	else	\
		(nobe)->prev->next = (nobe)->next;	\
	if((nobe)->next == (void *)(head_nobe))	\
		(head_nobe)->tail = (nobe)->prev;	\
	else	\
		(nobe)->next->prev = (nobe)->prev;	\
}while(0)

#define LIST_FOREACH(var, head_nobe)	\
	for((var) = (head_nobe)->head;	\
		(var) != (const void *)(head_nobe);	\
		(var) = ((var)->next))

#define LIST_FOREACH_REVERSE(var, head_nobe)	\
	for((var) = (head_nobe)->tail;	\
		(var) != (const void *)(head);	\
		(var) = ((var)->prev))

#define LIST_EMPTY(head_nobe)	((head_nobe)->head == (void *)(head_nobe))
#define LIST_HEAD(head_nobe)	((head_nobe)->head)
#define LIST_TAIL(head_nobe)	((head_nobe)->tail)
typedef void(*IterFun)(struct list_nobe *nobe, void *arg);
typedef int(*CmpFun)(void *data1, void *data2);

static void
list_foreach(struct list_head *head, IterFun fun, void *arg){
	struct list_nobe *nobe;
	LIST_FOREACH(nobe, head){
		fun(nobe, arg);
	}	
}

static void
list_foreach_reverse(struct list_head *head, IterFun fun, void *arg){
	struct list_nobe *nobe;
	LIST_FOREACH_REVERSE(nobe, head){
		fun(nobe, arg);
	}
}

static struct list_nobe *
list_nobe_new(void *data){
	if(data == NULL){
		return NULL;
	}
	struct list_nobe *ret = malloc(sizeof(struct list_nobe));
	if(ret == NULL) return NULL;
	ret->data = data;
	return ret;
}

static void
list_merge(struct list_head *dest, struct list_head *arg, CmpFun cmp){
	struct list_nobe *dest_tmp = dest->head, *arg_tmp = arg->head;
	while(!LIST_EMPTY(arg)){
		arg_tmp = arg->head;
		LIST_DELETE(arg, arg_tmp);
		while(dest_tmp != (void *)dest && cmp(dest_tmp->data, arg_tmp->data)){
			dest_tmp = dest_tmp->next;
		}
		if(dest_tmp == (void *)dest){
			LIST_INSERT_TAIL(dest, arg_tmp);
		}else{
			LIST_INSERT_BEFORE(dest, dest_tmp, arg_tmp);
		}
	}
}

static void
list_bubble_sort(struct list_head *head_nobe, CmpFun cmp){
	struct list_nobe *tmp;
	int stop = 0;
	for(tmp = head_nobe->head; (const void *)head_nobe != tmp && stop != 1; tmp = tmp->next){
		stop = 1;
		struct list_nobe *j, *jp;
		for(j = head_nobe->tail, jp = j->prev; j != tmp; j = jp, jp = jp->prev){
			if(cmp(j->data, jp->data)){
				void *tmp = jp->data;
				jp->data = j->data;
				j->data = tmp;
				stop = 0;
			}
		}
	}
}


void
insert_nobe(struct list_head *head, struct list_nobe *nobe, struct list_nobe *new_nobe){
	if(LIST_HEAD(head) == nobe){
		LIST_INSERT_HEAD(head, new_nobe);
	}else if(LIST_TAIL(head) == nobe){
		LIST_INSERT_TAIL(head, new_nobe);
	}else{
		LIST_INSERT_AFTER(head, nobe, new_nobe);
	}
}
void print(struct list_nobe *nobe, void *arg){
	printf("%s", (char *)nobe->data);
}

#define LINE_MAX 1024
#define INSERT_HEAD (void *)0
#define INSERT_TAIL (void *)1
int 
main(int argc, char *argv[]){	
	char line[LINE_MAX];
	struct list_head head;
	LIST_INIT_HEAD(&head);
	struct list_nobe *insert_pos = INSERT_HEAD;

	while(fgets(line, LINE_MAX, stdin) != NULL){
		char *tmp = line, *end = line + strlen(line);	
		char c;
		while(tmp != end){
			char *dump_beg = tmp;
			while((c = *tmp) != '\0' && c != '[' && c != ']' && c != '\n'){
				tmp++;
			}
	
			if(c != '\0') *tmp++ = '\0';
			if(1 ){ /* insert new nobe*/
				struct list_nobe *new_nobe = list_nobe_new(strdup(dump_beg));
				if(insert_pos == INSERT_HEAD){
					LIST_INSERT_HEAD(&head, new_nobe);
				}else if(insert_pos == INSERT_TAIL){
					LIST_INSERT_TAIL(&head, new_nobe);
				}else{
					LIST_INSERT_AFTER(&head, insert_pos, new_nobe);
				}
				insert_pos = new_nobe;
			}

			if(c == '\n'){ /*need to process a new line. dump the list and clear variable */
				list_foreach(&head, print, NULL);
				printf("\n");
				struct list_nobe *tmp_nobe;
				while(!LIST_EMPTY(&head)){
					tmp_nobe = LIST_HEAD(&head);
					LIST_DELETE(&head, tmp_nobe);
					free(tmp_nobe->data);
					free(tmp_nobe);
				}
				insert_pos = INSERT_HEAD;
				break;
			}

			if(c == '[') insert_pos = INSERT_HEAD;
			else if(c == ']') insert_pos = INSERT_TAIL;
			else ;
		}
	}
	return 0;
}
