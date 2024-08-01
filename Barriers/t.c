
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define N 8 //As requested by the lab n should be set to 8 instead of 4

//-----------------------------------------------------------
//Global Variable for input of threads from the user
int num_threads = 0;
//-----------------------------------------------------------


double A[N][N+1];
pthread_barrier_t barrier;

int print_matrix()
{
    int i, j;

    printf("------------------------------------\n");
    for(i=0; i<N; i++)
    {
        for(j=0;j<N+1;j++)
        {
            printf("%6.2f ", A[i][j]);
        }
        printf("\n");
    }
}

void *ge(void *arg) // threads function: Gauss elimination
{
    int i, j, k, prow;
    int myid = (int)arg;
    double temp, factor;

    int start_row = myid * (N / num_threads);
    int end_row = (myid + 1) * (N / num_threads);
    printf("\nMy id: %d, N: %d, num_threads: %d, start_row: %d, end_row: %d\n", myid, N, num_threads, start_row, end_row);
    

    for(i=0; i<N-1; i++)
    {
        if (i == myid)
        {
            printf("partial pivoting by thread %d on row %d: ", myid, i);
            temp = 0.0; prow = i;

            for (j=start_row; j<=end_row; j++)
            {
                if (fabs(A[j][i]) > temp)
                {
                    temp = fabs(A[j][i]);
                    prow = j;
                }
            }

            printf("pivot_row=%d pivot=%6.2f\n", prow, A[prow][i]);
            if (prow != i)
            { // swap rows
                for (j=i; j<N+1; j++)
                {
                    temp = A[i][j];
                    A[i][j] = A[prow][j];
                    A[prow][j] = temp;
                }
            }
        }


        //printf("\n1\n");

        // wait for partial pivoting done
        pthread_barrier_wait(&barrier);

        for(j=i+1; j<N; j++)
        {
            if (j == myid)
            {
                printf("thread %d do row %d\n", myid, j);
                factor = A[j][i]/A[i][i];
                for (k=i+1; k<=N; k++)
                {
                    A[j][k] -= A[i][k] * factor;
                }
                A[j][i] = 0.0;
            }
        }
        
        //printf("\n2\n");

        // wait for current row reductions to finish
        pthread_barrier_wait(&barrier);

        if (i == myid)
        {
            print_matrix();
        }
        //printf("\n3\n");

    }
}

int main(int argc, char *argv[])
{
    int i, j;
    double sum;
    pthread_t threads[num_threads];


    printf("main: initialize matrix A[N][N+1] as [A|B]\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            A[i][j] = 1.0;
        }
    }

    for (i=0; i<N; i++)
    {
        A[i][N-i-1] = 1.0 * N;
    }
    for (i=0; i<N; i++)
    {
        A[i][N] = 2.0*N - 1;
    }

    print_matrix(); // show initial matrix [A|B]


    //-----------------------------------------------------------
    //Asking the user for number of threads
    do {
        printf("Enter the number of threads to use: ");
        scanf("%d", &num_threads);
        if (num_threads < 1 || num_threads > 4) {
            printf("Invalid input. Please try again.\n");
        }
    } while (num_threads < 1 || num_threads > 4);
    //printf("You entered %d.\n", num_threads);
    //-----------------------------------------------------------


    pthread_barrier_init(&barrier, NULL, num_threads); // set up barrier
    printf("main: create N=%d working threads\n",num_threads);
    for (i=0; i<num_threads; i++)
    {
        //pthread_create(&threads[i], NULL, ge, (void *)i);
        if (pthread_create(&threads[i], NULL, ge, (void *)i) != 0) {
            perror("\nFailed to create thread\n");
            return 1;
        }
    }

    printf("main: wait for all %d working threads to join\n",num_threads);
    for (i=0; i<num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    printf("main: back substitution : ");
    for (i=N-1; i>=0; i--)
    {
        sum = 0.0;
        for (j=i+1; j<N; j++) 
        {
            sum += A[i][j] * A[j][N];
        }

        A[i][N] = (A[i][N]- sum) / A[i][i];
    }

    // print solution
    printf("The solution is :\n");
    for(i=0; i<N; i++)
    {
        printf("%6.2f ", A[i][N]);
    }
    printf("\n");

    return 0;
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define N 8


double A[N][N+1];
pthread_barrier_t barrier;

int print_matrix()
{
    int i, j;

    printf("------------------------------------\n");
    for(i=0; i<N; i++)
    {
        for(j=0;j<N+1;j++)
        {
            printf("%6.2f ", A[i][j]);
        }
        printf("\n");
    }
}

void *ge(void *arg) // threads function: Gauss elimination
{
    int i, j, k, prow;
    int myid = (int)arg;
    double temp, factor;

    for(i=0; i<N-1; i++)
    {
        if (i == myid)
        {
            printf("partial pivoting by thread %d on row %d: ", myid, i);
            temp = 0.0; prow = i;

            for (j=i; j<=N; j++)
            {
                if (fabs(A[j][i]) > temp)
                {
                    temp = fabs(A[j][i]);
                    prow = j;
                }
            }

            printf("pivot_row=%d pivot=%6.2f\n", prow, A[prow][i]);
            if (prow != i)
            { // swap rows
                for (j=i; j<N+1; j++)
                {
                    temp = A[i][j];
                    A[i][j] = A[prow][j];
                    A[prow][j] = temp;
                }
            }
        }

        // wait for partial pivoting done
        pthread_barrier_wait(&barrier);

        for(j=i+1; j<N; j++)
        {
            if (j == myid)
            {
                printf("thread %d do row %d\n", myid, j);
                factor = A[j][i]/A[i][i];
                for (k=i+1; k<=N; k++)
                {
                    A[j][k] -= A[i][k] * factor;
                }
                A[j][i] = 0.0;
            }
        }

        // wait for current row reductions to finish
        pthread_barrier_wait(&barrier);

        if (i == myid)
        {
            print_matrix();
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j;
    double sum;
    pthread_t threads[N];

    printf("main: initialize matrix A[N][N+1] as [A|B]\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            A[i][j] = 1.0;
        }
    }

    for (i=0; i<N; i++)
    {
        A[i][N-i-1] = 1.0 * N;
    }
    for (i=0; i<N; i++)
    {
        A[i][N] = 2.0*N - 1;
    }

    print_matrix(); // show initial matrix [A|B]

    pthread_barrier_init(&barrier, NULL, N); // set up barrier
    printf("main: create N=%d working threads\n", N);
    for (i=0; i<N; i++)
    {
        pthread_create(&threads[i], NULL, ge, (void *)i);
    }

    printf("main: wait for all %d working threads to join\n", N);
    for (i=0; i<N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("main: back substitution : ");
    for (i=N-1; i>=0; i--)
    {
        sum = 0.0;
        for (j=i+1; j<N; j++) 
        {
            sum += A[i][j] * A[j][N];
        }

        A[i][N] = (A[i][N]- sum) / A[i][i];
    }

    // print solution
    printf("The solution is :\n");
    for(i=0; i<N; i++)
    {
        printf("%6.2f ", A[i][N]);
    }
    printf("\n");
}
*/
