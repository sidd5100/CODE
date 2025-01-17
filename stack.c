//Title: C program that demonstrates the functionality of Stack DSA. 

//Libraries included
#include<stdio.h>
#include<stdlib.h>

// Defines
#define TRUE 1
#define FALSE 0
#define SIZE 10

// Structures

/* 1. Stack Structure
    a.  array[SIZE]; 
        It is the data container of size SIZE. This array represents the collection of data in stack form.
    b.  int top;
        It is the reference to the top most element in the stack. As the element is added to the stack the top is updated by one*/  
typedef struct { 
    int array[SIZE]; 
    int top;
}stack_t;

typedef int bool_t;

// Enums for menu lables. Improves redability
enum menulist{
    EXIT,PUSH,POP,PEEK 
};

//function declarations
int display_menu(void);
void int_stack(stack_t *sptr);
bool_t is_stack_empty (stack_t *sptr);
bool_t is_stack_full (stack_t *sptr);
void push_element(stack_t *sptr, int data);
void pop_element(stack_t *sptr);
int peek_element(stack_t *sptr);

//Entry point Function
int main (void){
    stack_t s1;
    int_stack(&s1);
    
    
    while(TRUE){
        int choice =0; int data=0;
        choice = display_menu();
        switch(choice){
            case EXIT:
                {
                    printf("Exiting.....\n");
                    exit (0);
                }
                break;

            // Adding element on to the stack
            case PUSH:
                {
                    if(! is_stack_full(&s1)){
                        printf("Enter the data to be pushed on stack => ");
                        scanf("%d",&data);
                        push_element(&s1,data); // Addition function call
                    }

                    else{
                        printf("Stack Overflow\n");
                    }
                }
                break;

            // Deleting element from the stack
            case POP:
                {
                    if(!is_stack_empty(&s1)){
                        data = peek_element(&s1); // Reading function call
                        pop_element(&s1); // Deletion function call
                        printf("Deleted element is => %d\n",data);
                    }

                    else{
                        printf("Stack Underflow\n");
                    }
                }
                break;

            // Reading element from the stack (topmost)
            case PEEK:
                {
                    if(!is_stack_empty(&s1)){
                        data = peek_element(&s1); // Reading function call
                        printf("Peeked element is => %d\n",data);
                    }

                    else{
                        printf("Stack Underflow\n");
                    }
                }
                break;
            default:
                break;    
        }
    }
    return 0;
}

//function definitions

//Initialize memebers of the stack
void int_stack(stack_t *sptr){
    sptr->top = -1;
}

// display_menu()::
int display_menu(void){
    int choice =0;
    printf("***********Stack Demo***********\n");
    printf("Choose from below options\n");
    printf("0. Exit\n");
    printf("1. Add an element to the stack\n");
    printf("2. Delete an element from the stack\n");
    printf("3. Read an element from the stack\n");
    printf("Enter choice ==>");
    scanf("%d", &choice);
    return choice;
}

// is_stack_empty()::
bool_t is_stack_empty (stack_t *sptr){
    
    //if top remains unchanged then no element is added. Return true if so.
    if(sptr->top==-1){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

//is_stack_full()::
bool_t is_stack_full (stack_t *sptr){
    
    //Return true if top is at the last element of the array bound.
    if(sptr->top==SIZE-1){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

// push_element()::
void push_element(stack_t *sptr, int data){
    //Increement top and load data in the array at the index array[sptr->top].
    sptr->top++;
    sptr->array[sptr->top] = data;    
}

//pop_element()::
void pop_element(stack_t *sptr){
    //Decreement top to delete an element from the array
    sptr->top--;
}

int peek_element(stack_t *sptr){
    //Return the value of top from the array array[sptr->top]
    return(sptr->array[sptr->top]);
}


