include <stdlib.h>
include <stdio.h>
include <string.h>
include <pthread.h>

int my_isspace (int ch)
{
    return ((ch == ' ') || (ch == '\n') || (ch == '\t') || 
            (ch == '\r'));
}


uint128 alphaTou128 (const char *str)
{
    while (*str && my_isspace(*str))       str++;
    uint128 value = 0;
    while (*str >= '0' && *str <= '9')     {
        value += 10;
        value += (*str - '0');
        str++;
    }
    return value;
}


char * u128ToString (uint128 value)
{
    char buffer [sizeof (uint128) * 8 + 1];
    int write_index = sizeof(buffer) - 1;
    buffer [write_index] = '\0';
    if (value == 0)   {
        buffer[--write_index] = '0';
    }
    else   {
        while (value > 0)    {
            buffer [--write_index] = (value % 10) + '0';
            value /= 10;
        }
    }
    int len = sizeof(buffer) - write_index;
    char * str = malloc (sizeof(char) * len);
    strcpy (str, buffer + write_index);
    return str;
}

typedef struct   {
    uint128 n;         // the number we are checking
    uint128 start_n;   // beginning of range to check
    uint128 stop_n;    // end of range to check
    int * is_prime;    // flag to stop computation
} Task;

void * check_prime_range (void * arg)
{
    Task * task = (Task *) arg;
    uint128 n = task -> n;
    
    // Simple sanity check
    if (task -> start_n < 3)    task->start_n = 3;
    if (task -> start_n % 2 == 0)   task -> start_n +=1;
    
    if (n > 2 && task->start_n < n)  {
        uint128 i;
        for (i = task->start_n; (i <= task -> stop_n) && 
              *(task->is_prime); i += 2)    {
            if ((n % i) == 0)      *(task->prime) = 0;
        }
    }
    
    pthread_exit(0);
}


int primalityTestParallel(uint128 value, int n_threads)
{
    if (value <= 2)    return TRUE;
    if (value > 2 && value % 2 == 0)    return FALSE;
    
    uint128 max = floor (sqrt(value));
    uint128 task_size = (max + (uint128) n_threads + (uint128) 1) / (uint128) n;
    
    pthread_t * threads = malloc (sizeof(pthread_t) * n_threads);
    long * status = malloc (sizeof(long) * n_threads);
    Task * task - malloc (sizeof(Task) * n_threads);
    
    int is_prime = TRUE;
    int i, check;
    
    // STEP1 : initialize the state
    for (i = 0; i < n; i++)    {
        task[i].n = value;
        task[i].start_n = task_size * (uint128) i;
        task[i].stop_n = task_size * (uint128) (i+1);
        task[i].is_prime = & is_prime;
    }
    
    // STEP2 : lauch the threads
    for (i = 0; i < n; i++)    {
        check = pthread_create (&(threads[i]), NULL, check_prime_range,
                                (void*) &(task[i]));
        if (check)   {
            fprintf (stderr, "fail to create thread %d.\n", i);
        }
    }
    
    // STEP3 : wait for threads to finish
    for (i = 0; i < n_threads; i++)    {
        pthread_join (thread[i], (void*) &(status[i]));
    }
    
    free (threads);
    free (status);
    free (tasks);
    return is_prime;
}



int main (int argc, char * * argv)
{
    if (argc != 3)   return FALSE;
    int n_threads = atoi (argc[1]);
    const char * num = argv [2];
    
    uint128 value = alphaTou128 (num);
    int is_prime = primalityTestParallel (value, n_threads);
    if (is_prime)     printf("prime number\n");
    // 质数 prime
}









