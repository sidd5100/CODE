// Libraries required
#include<stdio.h>
#include<stdlib.h>

// Defined Macros
#define TRUE 1
#define FALSE 0

// Structures

/* 1. Node Structure
    a.  Has 3 members one for data and aother two for refernce to other node
    b.  Is a self refrential structure i.e. it contains pointer of its own type. Hence, the name node after struct*/
typedef struct node{ 
    struct node *prev; 
    int data;
    struct node *next;
}node_t;

/* 2. List structure
    a.  Has only one member to hold the address to a list
    b.  When multiple objects of this struct type are defined eg: list_t l1,l2,l3;. li, l1 and l3 will point to 3 different lists
        i.e. the starting (address) node of the list
    c.  No self refferential member so no need to name struct before */
typedef struct{
    node_t *head;
}list_t;

typedef int bool_t;

enum menulist{
    EXIT,ADDFIRST,ADDLAST,ADDSPEC,DELFIRST,DELLAST,DELSPEC,DISPFWD,DISPREV    
};

//function declarations
void init_list(list_t *lptr);
node_t* createnode(int data);
bool_t is_list_empty(list_t *lptr);
void display_list_fwd(list_t *lptr);
void display_list_rev(list_t *lptr);
void addnode_atfirst_posn(list_t *lptr,int data);
void addnode_atlast_posn(list_t *lptr, int data);
void deletenode_at_firstpostn(list_t *lptr,int data);
void deletenode_at_lastpostn(list_t *lptr, int data);
void deletenode_at_specfpostn(list_t *lptr, int key);
node_t* searchnode(list_t *lptr, int key);
void addnode_at_specfposn(list_t *lptr, int posn, int data);
int display_menu();

//Entry point Function
int main(void)
{
    int data=0; int key=0; int posn=0; int choice = 0;
    list_t l1;
    init_list(&l1);
    while(TRUE){
        choice = display_menu();
        switch (choice){

            //add node at first postition
            case ADDFIRST:
                {
                    printf("Enter data => ");
                    scanf("%d", &data);
                    addnode_atfirst_posn(&l1,data);
                }    
                break;
            //add node at last postition
            case ADDLAST:
                {    
                    printf("Enter data => ");
                    scanf("%d", &data);
                    addnode_atlast_posn(&l1,data);
                }
                break;
            //add node at specific postition, where location is taken from user
            case ADDSPEC:
                {
                    printf("Enter data => ");
                    scanf("%d", &data);
                    printf("Enter position => ");
                    scanf("%d", &posn);
                    addnode_at_specfposn(&l1,posn,data);
                }
                break;
            //delete node at first postition    
            case DELFIRST:
                {
                    deletenode_at_firstpostn(&l1,data);
                }
                break;
            //delete node at last postition
            case DELLAST:
                {
                    deletenode_at_lastpostn(&l1,data);
                }
                break;
            /*delete node at specific postition, where key data element is taken from user 
            it is searched through the list if found is deleted*/
            case DELSPEC:
                {
                    printf("Enter key data  => ");
                    scanf("%d", &key);
                    deletenode_at_specfpostn(&l1,key);
                    continue; //written so that while loop does not break and menu continues to be displayed to user if key not found  
                }
                break;
            //displays the list in forward direction
            case DISPFWD:
                {
                    printf("list L1 in forward: HEAD "); 
                    display_list_fwd(&l1); printf("\n");
                }
                break;
            //displays the list in reverse direction
            case DISPREV:
                {
                    printf("list L1 in forward: HEAD "); 
                    display_list_rev(&l1); printf("\n");
                }
                break;
            case EXIT:
                {
                    exit (0);
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }    
    return 0;
}

//function definitions
//init_list():
void init_list(list_t *lptr)
{
    lptr->head =NULL;
}

//addnode_atfirst_posn:
void addnode_atfirst_posn(list_t *lptr,int data)
{
    //createnode(); function creates the newnode with data passed to it and returns the address of node_t type hence, node_t* 
    node_t* newnode = createnode(data);

    //adds node and revise the connections if lis is not empty
    if(! is_list_empty(lptr)){
        //making new connections before breaking the old ones so refernce to the list nodes is not lost
        newnode->next = lptr-> head;
        newnode->prev = lptr->head->prev;
        lptr->head->prev->next = newnode;
        lptr->head->prev = newnode;
        lptr->head = newnode;
    }

    //if list is empty one node is added. Since its the only node in the list, its next and prev part contains address of its own
    else{ //error occured for not placing braces 
        lptr->head = newnode;
        lptr->head->prev = newnode;
        newnode->next = lptr-> head;
    }
}

//createnode():
node_t* createnode(int data)
{
    /*dynamic allocation of memory in the heap section of the memory 
        malloc returns the address of the type of memory allocated from the heap section of memory*/ 
    node_t *temp = (node_t*)malloc(sizeof(node_t));

    if(temp==NULL){
        printf("malloc function failed");
    }   

    //initializing the members of the node
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

//is_list_empty: checks whether list is empty or not
bool_t is_list_empty(list_t *lptr)
{
    if(lptr->head == NULL){
        return TRUE;
    }
    else
        return FALSE;
}

//display_list_fwd():
void display_list_fwd(list_t *lptr)
{
    if(!is_list_empty(lptr)){
        node_t *trav = lptr->head;

        /*List traversal
        printed using do while loop since condition when trav = head wont be printed using while loop*/
        do 
        {
            printf("==> %d ",trav->data);
            trav = trav->next;
        }while(trav!= lptr->head);
    }
    else{
        printf("list is empty");
    }  
}

//display_list_rev():
void display_list_rev(list_t *lptr)
{
    if(!is_list_empty(lptr)){
        node_t *trav = lptr->head->prev;
        //printed using do while loop since condition when trav = head->prev wont be printed using while loop
        do 
        {
            printf("==> %d ",trav->data);
            trav = trav->prev;
        }while(trav!= lptr->head->prev);//should be while(trav!= lptr->head->prev)
    }
    else{
        printf("list is empty");
    }  
}

//addnode_atlast_posn():
void addnode_atlast_posn(list_t *lptr, int data)   
{
    node_t *newnode = createnode(data);
    if(! is_list_empty(lptr)){
        newnode->next = lptr->head;
        newnode->prev = lptr->head->prev;
        lptr->head->prev->next = newnode;
        lptr->head->prev = newnode;
    }

    else{
        lptr->head = newnode;
        lptr->head->prev = newnode;
        newnode->next = lptr->head;
    }
}

//deletenode_at_lastpostn():
void deletenode_at_lastpostn(list_t *lptr, int data){
    if(! is_list_empty(lptr)){
        node_t *temp = lptr->head->prev;
        if(temp == lptr->head){
            lptr->head = NULL;
            free(temp);
        }
        else{
            lptr->head->prev->prev->next = lptr->head;
            lptr->head->prev = lptr->head->prev->prev;
            free(temp);
            temp = NULL;
        } 
    }

    else{
        
        printf("list is empty already");
    }
}

//deletenode_at_firstpostn():
void deletenode_at_firstpostn(list_t *lptr,int data){
    if(!is_list_empty(lptr)){
        
        node_t *temp = lptr->head;
        if (temp->next == temp){
            lptr->head = NULL;
            free(temp);
            temp = NULL;
        }
        else{    
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            lptr->head = temp->next;
            free(temp);
            temp = NULL; 
        }
    }

    else{
        
        printf("list is already emptied");
    }
}

//deletenode_at_firstpostn():
node_t* searchnode(list_t *lptr, int key){
    if(! is_list_empty(lptr)){
        //traverse the list from 1st node to last and search for the data requested by user
        node_t* trav = lptr->head;
        do{
            //if found return the address
            if(trav->data==key){
                printf("key found = %d\n", key);
                return trav;
            }
            else{
                trav = trav->next;
            }
        }while(trav!=lptr->head);//Condition to execute loop untill last node. Loop breaks when trav completes a cycle throught the list
            
        printf("key is not found\n");
        return NULL; // returns NULL when key not found
        }
    
    else{
        printf("list is empty");
    }
}

//deletenode_at_specfpostn():
void deletenode_at_specfpostn(list_t *lptr, int key){
    node_t *found = searchnode(lptr, key);

    //if searchnode returns NULL then print data not found
    if(found==NULL){
        printf("Data not found\n");
        return; //prints the message and returns to the calling function without executing next instructions
    }

    //make connections if found node is at 1st position and assign next node to head
    if (found == lptr->head){
        found->prev->next = found->next;
        found->next->prev = found->prev;
        lptr->head = found->next;
        printf("Node with data = %d deleted from the list\n",found->data);
        free(found);
    }
    //make connections if found node is in between position 
    else{
        found->prev->next = found->next;
        found->next->prev = found->prev;
        printf("Node with data = %d deleted from the list\n",found->data);
        free(found);
    }
    
}

//addnode_at_specfposn():
void addnode_at_specfposn(list_t *lptr, int posn,int data){
    if(!is_list_empty(lptr)){
        node_t *newnode = createnode(data);
        int index = 0;
        node_t *trav = lptr->head;
        while(index != posn-1){
            index++;
            trav = trav->next;
        }
        newnode->prev = trav->prev;
        newnode->next = trav;
        trav->prev->next = newnode;
        trav->prev = newnode;
    }

    else{
        printf("list is empty\n");
    }
}

//display_menu():
int display_menu(){
    int choice=0;
    printf("*********** Linked List (DCLL) demo ***********\n");
    printf("Choose from below options\n");
    printf("0. Exit\n");
    printf("1. Add node at first position\n");
    printf("2. Add node at last position\n");
    printf("3. Add node at specific position\n");
    printf("4. Del. node at first position\n");
    printf("5. Del. node at last position\n");
    printf("6. Del. node at speccific position\n");
    printf("7. Display LL forward\n");
    printf("8. Display LL reverse\n");
    printf("Enter the Choice ==> ");
    scanf("%d",&choice);
    return choice;
}


/*Errors detected
1. no \n should be added in scanf function as it allows an extra whitespace to be accepted from the user
2. proper indentation of the cases should be done 
    a. single case statements could be used with no {} required
    b. multiple statemnts in a case require {statements} to be enclosed within the {}
    c. case constants should be int const and case syntax should not include '' if ther are char const then they should be
        enclosed in '' eg: case 0: , case 'A': , case CONDITION : where CONDITION is defined macro or a enum cnst
3. Proper indentation should be done for decision control statements statemnts for execution under if and else block 
    should be enclosed in {}
4. Proper handling of the flow of the program should be done in deletenode_at_specfpostn(); if key not found the control should
    return to the calling function and from ther it should continue to prompt the user for input i.e. the while(TRUE) loop 
    should not break unexpectedly*/

/* Takeouts
1. Implementation of 
    a. Pointers and pointers to structure
    b. Double pointers and their handling
2. Self refrential structures and their implemntation
3. Dynamic allocation of memory
4. List traversals and its conditions for effective traversal*/        