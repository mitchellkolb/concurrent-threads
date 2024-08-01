/** C4.1.c file: compute matrix sum by threads */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 8//#1 change to 8x8
int A[N][N], sum[N];

//-------------------------
//#2 "Define a global int total = 0"
int total = 0;
//-------------------------

//-----------------------------
//#3 mutex
pthread_mutex_t *m; //mutex pointer
//-----------------------------


void func(void *arg) // threads function
{
    int j, row, sum = 0;
    pthread_t tid = pthread_self(); // get thread ID number
    row = (int)arg; // get row number from arg
    printf("Thread %d [%lu] computes sum of row %d\n", row, tid, row);
    for (j=0; j<N; j++) // compute sum of A[row]in global sum[row]
    {
        sum += A[row][j];
    }

    /*//-------------------------
    //#2 "Modify the func() code to let each thread add its row sum to total"
    int tmp = total;   // tmp = current total
    tmp += sum;        // update tmp locally 
    sleep(1);          // simulate interrupts, which may switch process/threads 
    total = tmp;       // write tmp to total
    //-------------------------*/

    //-------------------------
    //#3 mutex
    pthread_mutex_lock(m);
        total += sum;
    //pthread_t mutex unlock(m);
    pthread_mutex_unlock(m);
    //printf("total = %d\n", total);
    //-------------------------

    //printf("Thread %d [%lu] done: sum[%d] = %d\n",row, tid, row, sum[row]);
    //pthread_exit((void*)0); // thread exit: 0=normal termination
}

int main (int argc, char *argv[])
{
    pthread_t thread[N]; // thread IDs
    int i, j, r;
    void *status;
    printf("Main: initialize A matrix\n");
    for (i=0; i<N; i++)
    {
        sum[i] = 0;
        for (j=0; j<N; j++)
        {
            A[i][j] = i*N + j + 1;
            printf("%4d ", A[i][j]);
        }
        printf("\n");
    }
    //-------------------------
    //#3 create a mutex m
    m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(m, NULL); //initialize mutex m
    //-------------------------

    printf("Main: create %d threads\n", N);
    for(i=0; i<N; i++) 
    {
        pthread_create(&thread[i], NULL, func, (void *)i);
    }
    printf("Main: try to join with threads\n");
    for(i=0; i<N; i++) 
    {
        pthread_join(thread[i], &status);
        printf("Main: joined with %d [%lu]: status=%d\n",i, thread[i], (int)status);
    }

    //-------------------------
    //#2 "Modify main() to join with all threads; then print total value" This is after the try to join all threads for loop so I put my print statement here.
    printf("Global Total: %d\n", total);
    //-------------------------

    //-------------------------
    //#3 destory mutex m
    pthread_mutex_destroy(m);
    //-------------------------

    printf("Main: compute and print total sum: ");
    for (i=0; i<N; i++)
    {
        total += sum[i];
    }
    printf("total = %d\n", total);
    pthread_exit(NULL);
}

/*
1. Copy the example program C4.1.c in the book as t.c
   Modify  N   to let A be an 8x8 matrix.
   Compile and run the program. Record the total output value ___total = 2080___.

2. Define a global   int total = 0;
   Modify the func() code to let each thread add its row sum to total, as in

   //-------------------------------------
   int tmp = total;   // tmp = current total
   tmp += sum;        // update tmp locally 

   sleep(1);          // simulate interrupts, which may switch process/threads 

   total = tmp;       // write tmp to total
   //-------------------------------------
              
   Modify main() to join with all threads; then print total value

   Run the modified program. What's the total output value? ___Global Total: 0___
        
        That number was gotten because of the code from #2 above taken literally. This number is incorrect because the total is still the same value as when it was initalized. There are a couple of reasons for this. I think it could be because all the threads are all trying to access the same global variable and that makes 'total' a race condition which stops the value from being changed. Or the other reason is that total is redfined in main() and that the line of code "tmp += sum;" is not correct because "sum" is defined as an array of [N] and not an int. When I look into the example for #3 of this prelab with example program C4.3 "sum" is an global int and not a global array. It seems to be that I need to add in the concepts of Mutex locking and unlocking for each thread. I think the process will work only the idea that "Each working thread computes the partial sum of a row. Instead of depositing the partial sums in a global sum[ ] array, each working thread tries to update a global variable, total, by adding its partial sum to it. Since all the working threads try to update the same global variable, they must be synchronized to prevent race conditions. This can be achieved by a mutex lock, which ensures that only one working thread can update the total variable at a time in a Critical Region." as stated by KC in his lecture and in the textbook.

3. Devise a way to make the modified code work CORRECTLY.
   HINT: read example program C4.3
        
        Looking at the general idea I think the I have to make it so a thread computes the sum of the row then prints the sum of that row on the next line. This will show that the thread locked and unlocked the sum variable for that single thread then after the execution process terminated the next thread takes the variable that is in waiting queue to then repeat the process. I think this because comparing the ./mk output I'm getting right now and the ./output sample that is given to me the print states are in the wrong order.
*/
