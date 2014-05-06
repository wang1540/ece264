#include <stdio.h>
#include <stdlib.h>

int *genRandomArray (int number)
{
    int *array = malloc(sizeof(int) * number);
    int ind;
    for (ind = 0; ind < number; ind++)    {
        array[ind] = rand();
    }
    return array;
}

int intcmp (const void *a, const void *b)
{
    return *((int *)a) - *((int*) b);
}


typedef struct {//
    int *array;//
    int length;//
} Task;//

Task * Task_create (int *array, val)
{
    Task * task = malloc(sizeof(Task));
    task -> array = array;
    task -> length = val;
    return task;
}


void * thread_worker (void * arg)
{
    Task *task = (Task *) arg;
    qsort (task->array, task->length, sizeof(int), intcmp);
    free(task->array);
    free(task);
    printf("Done!\n");
}


int main (int argc, char ** argv)
{
    //feof 为检测stdin是否停止。停止便return非0，未停return 0
    
    while (!feof(stdin))   {
        int val;
        printf("> ");
        scanf("%d", &val);
        if (feof(stdin))    break;
        
        int *array = genRandomArray (val);
        
        pthread_t * th = malloc(sizeof(pthread_t));//
        Task * task = Task_create (array, val);//
        pthread_create (th, NULL, thread_worker, (void *) task);//
        
        //qsort (array, val, sizeof(int), intcmp);
        printf("done!\n");
        free(array);
    }
    
    return EXIT_SUCCESS;
}
