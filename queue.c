// DSA implementation (Circular QUEUE)

//Libraries included
#include<stdio.h>
#include<stdlib.h>

// Defined Macros
#define TRUE 1
#define FALSE 0
#define SIZE 10

// Structures

/* 1. Queue Structure
    a.  int array[SIZE];
        It is the data container. The data is storeed in this array in the form of STACK. FILO or LIFO form   
    b.  int front;
        It points to the starting index of the array
    c.  int rear;
        It points to the last index of the array or the index upto which the array is occupied*/  
typedef struct { 
    int array[SIZE]; 
    int front;
    int rear;
}queue_t;

typedef int bool_t;

// Enums for  menu labels to improve redability
enum menulist{
    EXIT,ENQUEUE,DEQUEUE 
};

//Function declarations
int display_menu(void);
void init_queue(queue_t* qptr);
bool_t is_queue_empty(queue_t* qptr);
bool_t is_queue_full(queue_t* qptr);
void enque_element(queue_t* qptr, int data);
void deque_element(queue_t* qptr);

//Entry point function
int main(void)
{
    
    queue_t q1;
    init_queue(&q1);
    
    while(TRUE){
        int choice=0; int data=0;
        choice = display_menu();
        switch (choice){
            case EXIT:
                {
                    printf("Exiting.....");
                    exit(0);
                }
            break;

            //Adding element to the queue
            case ENQUEUE:
                {
                    if(!is_queue_full(&q1)){
                        printf("Enter the data to be queued => ");
                        scanf("%d", &data);
                        enque_element(&q1, data); //Adition function call
                        printf("Data element added to the queue => %d\n", data);
                    }

                    else{
                        printf("Queue already fulled....\n");
                    }
                }
                break;

            //Deleting element from the queue
            case DEQUEUE:
                {
                    if(!is_queue_empty(&q1)){
                        deque_element(&q1); //Deletion function call
                    }

                    else{
                        printf("Queue already empty....\n");
                    }
                }
                break;
        }
    }
    
    return 0;
}

//Function definitions

// display_menu()::
int display_menu(void){
    int choice=0;
    printf("*********Circular queue*********\n");
    printf("Choose from below options\n");
    printf("0. Exit\n");
    printf("1. Add an element to the queue\n");
    printf("2. Delete an element from the queue\n");
    printf("Enter choice ==>");
    scanf("%d",&choice);
    return choice;
}

// init_queue()::
void init_queue(queue_t* qptr){
    qptr->front=-1;
    qptr->rear=-1;
}

// is_queue_empty()::
bool_t is_queue_empty(queue_t* qptr){
    
    // Return true if front and rear are -1 OR front is equal to rear
    if(qptr->rear==-1 || qptr->front>qptr->rear){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

// is_queue_full()::
bool_t is_queue_full(queue_t* qptr){
    
    if(((qptr->rear+1)%SIZE)==qptr->front){ 
        return TRUE;
    }
    else{
        return FALSE;
    }
}

// enque_element()::
void enque_element(queue_t* qptr, int data){
    
    //Set front to the first index = 0
    if (qptr->front==-1){
        qptr->front = 0;
    }
    //Increement rear by one and this condition ensures the cyclic operation of the array bounds
    qptr->rear = (qptr->rear+1)%SIZE;
    //Load data at the index array[qptr->rear]
    qptr->array[qptr->rear] = data;
}

// deque_element()::
void deque_element(queue_t* qptr){
    int data = qptr->array[qptr->front];
    
    //printf("Element dequed is %d\n",data);
    //Initialize front and rear to -1 if the array is totally emptied
    if(qptr->front > qptr->rear){
        qptr->front = qptr->rear = -1; 
    }
    // If not empty, decreement the front by one 
    else{
        printf("Element dequed is %d\n",data);
        qptr->front = (qptr->front+1)%SIZE;
        
    }
}

