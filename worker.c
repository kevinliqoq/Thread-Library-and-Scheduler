// File:	worker.c

// List all group member's name:
// username of iLab:
// iLab Server:

#include "worker.h"
// INITAILIZE ALL YOUR VARIABLES HERE
// YOUR CODE HERE

threadNode *front = NULL;
threadNode *tail = NULL;
ucontext* scheduler;

/* create a new thread */
int worker_create(worker_t * thread, pthread_attr_t * attr, 
                      void *(*function)(void*), void * arg) {

       // - create Thread Control Block (TCB)
       // - create and initialize the context of this worker thread   
       // - allocate space of stack for this thread to run
	   
		struct TCB* temp = (struct TCB*)malloc(sizeof(struct TCB));
		temp->status = 1;
		temp->threadID = thread;
		getcontext(&thread->context);
		&thread->context.uc_link = 0;
		&thread->context.uc_stack.ss_sp = malloc(STACK_SIZE);
		temp->priority = 0;  
		temp->stack = &thread->context.uc_stack.ss_sp;
		&thread->context.uc_stack.ss_size = STACK_SIZE;   
		&thread->context.uc_stack.ss_flags = 0;        
		if ( &thread->context.uc_stack.ss_sp == 0 )
		{
				perror( "malloc: Could not allocate stack" );
				exit( 1 );
		}
		makecontext( &thread->context, function, 0);

		if (front == NULL) {
			front = (struct threadNode*)malloc(sizeof(threadNode));
			front->next = NULL;
			front->tcb = temp;
			tail = front;
		}
		else{
			threadNode* tnode = (struct threadNode*)malloc(sizeof(threadNode));
			tnode->tcb = temp;
			tnode->next = front;
			front = tnode;
		}
       // after everything is set, push this thread into run queue and 
       // - make it ready for the execution.

       // YOUR CODE HERE
	
    return 0;
};

/* give CPU possession to other user-level worker threads voluntarily */
int worker_yield() {
	
	// - change worker thread's state from Running to Ready
	// - save context of this thread to its thread control block
	// - switch from thread context to scheduler context

	// YOUR CODE HERE
	front->tcb->status=1;
	getcontext(&front->tcb->context)
	//setcontext(scheduler);
	
	return 0;
};

/* terminate a thread */
void worker_exit(void *value_ptr) {
	// - de-allocate any dynamic memory created when starting this thread
	front->tcb->status=3;
	free(front->tcb->context.uc_stack.ss_sp);
	threadNode* tnode = front;     //where do we put exited nodes?
	front=front->next;
	// YOUR CODE HERE
};


/* Wait for thread termination */
int worker_join(worker_t thread, void **value_ptr) {
	
	// - wait for a specific thread to terminate
	// - de-allocate any dynamic memory created by the joining thread
	threadNode* prev=NULL;
	threadNode* tnode=front;
	while (tnode!=NULL && tnode->thread==thread){
		prev=tnode;
		tnode=tnode->next;
	}
	prev->next=tnode->next;
	free(tnode);
	// YOUR CODE HERE
	return 0;
};

/* initialize the mutex lock */
int worker_mutex_init(worker_mutex_t *mutex, 
                          const pthread_mutexattr_t *mutexattr) {
	//- initialize data structures for this mutex

	// YOUR CODE HERE
	return 0;
};

/* aquire the mutex lock */
int worker_mutex_lock(worker_mutex_t *mutex) {

        // - use the built-in test-and-set atomic function to test the mutex
        // - if the mutex is acquired successfully, enter the critical section
        // - if acquiring mutex fails, push current thread into block list and
        // context switch to the scheduler thread

        // YOUR CODE HERE
        return 0;
};

/* release the mutex lock */
int worker_mutex_unlock(worker_mutex_t *mutex) {
	// - release mutex and make it available again. 
	// - put threads in block list to run queue 
	// so that they could compete for mutex later.

	// YOUR CODE HERE
	return 0;
};


/* destroy the mutex */
int worker_mutex_destroy(worker_mutex_t *mutex) {
	// - de-allocate dynamic memory created in worker_mutex_init

	return 0;
};

/* scheduler */
static void schedule() {
	// - every time a timer interrupt occurs, your worker thread library 
	// should be contexted switched from a thread context to this 
	// schedule() function

	// - invoke scheduling algorithms according to the policy (RR or MLFQ)

	// if (sched == RR)
	//		sched_rr();
	// else if (sched == MLFQ)
	// 		sched_mlfq();

	// YOUR CODE HERE

// - schedule policy
#ifndef MLFQ
	// Choose RR
#else 
	// Choose MLFQ
#endif

}

/* Round-robin (RR) scheduling algorithm */
static void sched_rr() {
	// - your own implementation of RR
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE
}

/* Preemptive MLFQ scheduling algorithm */
static void sched_mlfq() {
	// - your own implementation of MLFQ
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE
}

// Feel free to add any other functions you need

// YOUR CODE HERE

