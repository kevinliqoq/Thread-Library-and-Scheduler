#include <stdlib.h>
#include <ucontext.h>
#include <stdio.h>

// 64kB stack
#define FIBER_STACK 1024*64

ucontext_t child, parent, three, four;
volatile int i=0;
// The child thread will execute this function
void threadFunction()
{
        
        i++;
        printf("%d\n",i);
        swapcontext( &child, &parent );     //remembers where you are
        i++;
        printf("%d, Only child touches this\n",i);
        swapcontext( &child, &parent );
        i++;
        printf("%d, Only child touches this\n",i);
        setcontext(&parent);
}
void threadFunction2()
{
        
        i+=30;
        printf("%d\n",i);
        setcontext(&parent);    //does not remember
}

int main()
{
        getcontext( &child );
         // Get the current execution context
         // Modify the context to a new stack
         child.uc_link = 0;
         child.uc_stack.ss_sp = malloc( FIBER_STACK );
         child.uc_stack.ss_size = FIBER_STACK;
         child.uc_stack.ss_flags = 0;        
         if ( child.uc_stack.ss_sp == 0 )
         {
                 perror( "malloc: Could not allocate stack" );
                 exit( 1 );
         }
         getcontext( &three );
         // Modify the context to a new stack
         three.uc_link = 0;
         three.uc_stack.ss_sp = malloc( FIBER_STACK );
         three.uc_stack.ss_size = FIBER_STACK;
         three.uc_stack.ss_flags = 0;        
         if ( three.uc_stack.ss_sp == 0 )
         {
                 perror( "malloc: Could not allocate stack" );
                 exit( 1 );
         }
          getcontext( &four );
         // Modify the context to a new stack
         four.uc_link = 0;
         four.uc_stack.ss_sp = malloc( FIBER_STACK );
         four.uc_stack.ss_size = FIBER_STACK;
         four.uc_stack.ss_flags = 0;        
         if ( four.uc_stack.ss_sp == 0 )
         {
                 perror( "malloc: Could not allocate stack" );
                 exit( 1 );
         }

         // Create the new context
         printf( "Creating child fiber\n" );
         makecontext( &child, &threadFunction, 0 );   //makes a thread link to a function
         makecontext( &three, &threadFunction2, 0 );   //makes a thread link to a function
         makecontext( &four, &threadFunction2, 0 );   //makes a thread link to a function
        
         // Execute the child context
        swapcontext(&parent,&child);   //saved previous thread and go to new one
        swapcontext( &parent, &child );
        swapcontext( &parent, &child ); 
        swapcontext( &parent, &three );  
        swapcontext( &parent, &three );
        swapcontext( &parent, &three );
        swapcontext( &parent, &four);  
        swapcontext( &parent, &four);
        swapcontext( &parent, &four );
        
         // Free the stack
        free( child.uc_stack.ss_sp );
        free( three.uc_stack.ss_sp );
        free( four.uc_stack.ss_sp );

        printf( "Child fiber returned and stack freed\n" );
        
        return 0;
}