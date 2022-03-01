#include "worker.h" 

static void discardQ(Tqueue* q){
    threadNode* pt = q->top;
    while (pt != NULL) {
        threadNode* temp = pt;
        pt = pt->next;
        free(temp);
    }
    free(q);
}

static *Tqueue initQ(){
    *Tqueue temp = (*Tqueue) malloc(sizeof(Tqueue));
    temp->count = 0;
    temp->top = NULL;
    temp->back = NULL;
    return temp;
}

static int isEmpty (Tqueue* queue){
    if (queue == NULL) return 1;
    if (queue->count == 0) return 1;
    else return 0;
}

static void enqueue (Tqueue* queue, threadNode* x){
    if (queue == NULL) queue = initQ();
    if (count == 0){
        queue->top = x;
        queue->back = x;
    }
    else{
        (queue->back)->next = x;
        queue->back = x;
    }
    x->next = NULL;
    count++;
}

static *threadNode pop (Tqueue* queue){
    if (isEmpty(queue)) return NULL;
    threadNode* temp = queue->top;
    queue->top = (queue->top)->next;
    if (count == 1) queue->back = NULL;
    count--;
    return temp;
}


 