#ifndef ACM_LIBRARY_LIST_H
#define ACM_LIBRARY_LIST_H
/*
 *A list support follow features
 *1.support arbitrary runtime data types
 *
 *2.support sort method (user must support compare method)
 *
 *
 *
 *
 */


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

static inline void
list_foreach(struct list_head *head, IterFun fun, void *arg){
	struct list_nobe *nobe;
	LIST_FOREACH(nobe, head){
		fun(nobe, arg);
	}	
}

static inline void
list_foreach_reverse(struct list_head *head, IterFun fun, void *arg){
	struct list_nobe *nobe;
	LIST_FOREACH_REVERSE(nobe, head){
		fun(nobe, arg);
	}
}

static inline struct list_nobe *
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
			//if(LIST_EMPTY(dest)){
			//	dest->head = arg_tmp;
			//	arg_tmp->prev = (void *)dest;
			//}else{
			//	dest->tail->next = arg_tmp;
			//	arg_tmp->prev = dest->tail;
			//}
			//dest->tail = arg->tail;
			//arg->tail->next = (void *)dest;
			//arg->head = arg->tail = (void *)arg;
			//break;
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

//@beg the first element of the list
//@end the last element of the list
static void
list_quick_sort(struct list_nobe *beg, struct list_nobe *end, CmpFun cmp){
}
#endif
