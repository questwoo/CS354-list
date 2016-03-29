/* Title: Assignment 1 list.c
 * Description: (Brief summary of program)
 *
 * Author: You Wu
 * Email: wu278@wisc.edu
 * CS Login: ywu
 * Section: Lec-002
 *
 * Pair Partner: Xibing Chen
 * Email:
 * CS Login:
 * Section: Lec-002
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_INTS 1000

/* A node in the linked list */
struct node {
    int data;
    struct node *next;
};

struct node* create_list(int intarray[], int len);

struct node* add_item_at_start(struct node *head, int data);

int search_array(int integers[], int numints, int element);

int search_list(struct node *head, int element);

struct node* create_sorted_list(struct node *head);

struct node* add_item_sorted(struct node *head, int data);

int copy_list_to_array(struct node *head, int *array);

void print_list(struct node *head);

void print_array(int integers[], int len);


int main(int argc, char *argv[])
{
    /* Open a file for reading */
    int len = 0;
    int num;
    int array[MAX_INTS];
    int sortedarray[MAX_INTS];
    
    if(argc != 2){
        printf( "usage: %s filename", argv[0] );
    }
    else{
        FILE *fp = fopen( argv[1], "r" );
        if(fp == 0){
            printf("Could not open file\n");
        }
        else{
            
            /* Read the numbers from the file, into an array */
            printf("Reading integers from a file to an array...\n");
            printf("\n");
            /* Print the array */
            while(fscanf(fp,"%d",&num)>0){
                array[len]=num;
                len++;
            }
            fclose(fp);
            printf("ARRAY: ");
            print_array(&array[0],len);
            printf("\n");
        }
    }
    /* Create a linked list with the integers from the array */
    struct node *tmpnode = NULL;
    tmpnode = create_list(&array[0],len);
    /* Print the linked list */
    printf("LINKED LIST: ");
    print_list(tmpnode);
    printf("\n");
    
    /* Repeatedly prompt the user for a number to be searched.
     *  Search the array for the number and print out the result as shown in the specs.
     *  Search the linked list for the number and print out the result as shown in the specs.
     *  Stop prompting when the user enters 'q' (just the character q without the single quotes).
     */
    char q = '\0';
    const char END = 'q';
    int input;
    printf("Enter an element to be searched in the list and array: ");
    scanf("%d", &input);
    scanf("%c", &q);
    printf("\n");
    while(q != END ){
        int resultarray = search_array(&array[0],len,input);
        if(resultarray == -1){
            printf("Element %d not found in the array\n", input);
            printf("\n");
        }
        else{
            printf("Element %d found in the array at index %d\n", input, resultarray);
            printf("\n");
        }
        int resultlist = search_list(tmpnode,input);
        if(resultlist == -1){
            printf("Element %d not found in the linked list\n", input);
            printf("\n");
        }
        else{
            printf("Element %d found in the linked list at position %d\n", input, resultlist);
            printf("\n");
        }
        printf("Enter an element to be searched in the list and array: ");
        scanf("%d", &input);
        scanf("%c", &q);
        printf("\n");
    }
    
    /* Create a sorted list(in ascending order) from the unsorted list */
    struct node *tmpnode2 = NULL;
    tmpnode2 = create_sorted_list(tmpnode);
    /* Print the sorted list */
    printf("SORTED LINKED LIST: ");
    print_list(tmpnode2);
    printf("\n");
    /* Copy the sorted list to an array with the same sorted order */
    int num_ints = copy_list_to_array(tmpnode2,&sortedarray[0]);
    /* Print out the sorted array */
    printf("SORTED ARRAY: ");
    print_array(&sortedarray[0],num_ints);
    printf("\n");
    /* Print the original linked list again */
    printf("ORIGINAL LINKED LIST: ");
    print_list(tmpnode);
    printf("\n");
    /* Print the original array again */
    printf("ORIGINAL ARRAY: ");
    print_array(&array[0],len);
    printf("\n");
    
    printf("Writing integers from a sorted array to a file...");
    printf("\n");
    /* Open a file for writing */
    /* Write the sorted array to a file named "sorted_numbers.txt" */
    FILE *fp2;
    fp2 = fopen("sorted_numbers.txt", "w");
    int i;
    for(i=0; i<num_ints; i++){
        fprintf(fp2, "%d\n", sortedarray[i]);
    }
    fclose(fp2);
    /* Print out the number of integers written to the file */
    printf("Number of integers written to the file = %d", num_ints);
    
    return 0;
}

/**
 * This method create a list by calling the add_item_at_start method
 *
 * @param int intarray[] (the start of an array)
 * @param int len (the length of the array)
 * @return head
 */
struct node* create_list(int intarray[], int len)
{
    if(len == 0){
        return NULL;
    }
    struct node *head = NULL;
    int i;
    for(i=0; i<len; i++){
        head = add_item_at_start(head,intarray[i]);
    }
    return head;
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
struct node* add_item_at_start(struct node *head, int data)
{
    struct node *newnode = malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = head;
    return newnode;
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
int search_list(struct node *head, int element)
{
    int index = -1;
    int i = 1;
    while(head != NULL){
        if(head->data == element){
            index = i;
        }
        head = head->next;
        i++;
    }
    return index;
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
int search_array(int integers[], int numints, int element)
{
    int index = -1;
    int i;
    for(i=0; i < numints; i++){
        if(integers[i] == element){
            index = i;
        }
    }
    return index;
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
int copy_list_to_array(struct node *head, int *array)
{
    int i = 0;
    for(; head != NULL; head = head->next){
        *array = head->data;
        array = array+1;
        i++;
    }
    return i;
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
struct node* create_sorted_list(struct node *head)
{
    struct node *sorted_head = NULL;
    if(head == NULL){
        return NULL;
    }
    for(;head != NULL; head = head->next){
        sorted_head = add_item_sorted(sorted_head, head->data);
    }
    return sorted_head;
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
struct node* add_item_sorted(struct node *sorted_head, int data)
{
    
    struct node **current = &sorted_head;
    while(*current != NULL && data > (*current)->data){
        current = &((*current)->next);
    }
    struct node *newnode = NULL;
    newnode = malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = *current;
    *current = newnode;
    
    return sorted_head;
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
void print_list(struct node *head)
{
    if (head == NULL) {
        printf("Linked List is Empty.\n");
    } else {
        struct node *temp = head;
        printf("head->");
        while (temp != NULL) {
            printf("|%d|->", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/**
 * (Write a succinct description of this method here)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
void print_array(int integers[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("| %d ", integers[i]);
    }
    printf("|\n");
}


