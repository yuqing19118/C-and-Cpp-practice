///////////////////////////////////////////////////////////////////////////////
////                   ALL STUDENTS COMPLETE THESE SECTIONS
//// Title:            game.c
//// Semester:         CS 354  Fall 2015
////
//// Author:           Zhang Cai
//// Email:            zcai28@wisc.edu
//// CS Login:         zcai
//// Lecturer's Name:  Jason Lowe-Power
//// Course Section:   01
////
////////////////////// PAIR PROGRAMMERS COMPLETE THIS SECTION ////////////////////
////
////                   CHECK ASSIGNMENT PAGE TO see IF PAIR-PROGRAMMING IS ALLOWED
////                   If pair programming is allowed:
////                   1. Read PAIR-PROGRAMMING policy (in cs302 policy)
////                   2. choose a partner wisely
////                   3. REGISTER THE TEAM BEFORE YOU WORK TOGETHER
////                      a. one partner creates the team
////                      b. the other partner must join the team
////                   4. complete this section for each program file.
////
//// Pair Partner:     Qing Yu (Sabrina)
//// Email:            qyu37@wisc.edu
//// CS Login:         sabrina
//// Lecturer's Name:  Jason Lowe Power
//// Course Section:      01
////
////////////////////// STUDENTS WHO GET HELP FROM OTHER THAN THEIR PARTNER //////

///**
//// * We made a structure which contains some parameters that the node we created. We made a
//// linked list and add new node to the list at each time and finally, it prints out the new list.
//// (val) the value contained in the node
//// (next) a pointer to the next position
//// (curr) the pointer to the node
//// (node_item) the name of the node
//// (intforlist) the value stored in the node
////
////        **/
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdbool.h>

struct node{
    int val;
    struct node * next;
};
typedef struct node node_item;
 
/*This function creates a new Node structure and
 *  hooks it into the list This function
 *   returns the (new) head of the linked list.
 *   */
struct node * listadd(struct node *head, int intforlist){
    node_item *curr;
    curr = (node_item *)malloc(sizeof(node_item));
    curr->val = intforlist;
    curr->next = head;
    return curr;
}

/*This function gets the value from the input file and store each integer to one position in an array.
 *  *Error checking if we cannot read the file statistics orr if the
 * list is empty, it returns the value NULL.
 * (fileStat) the same of the input file location
 * (head) the pointer of node_item
  (curr) the value stored in node_item
 * (storeInt) the address of the file that is read
 * */
struct node * createlist(int fd){
    struct stat fileStat;
    
    if(fstat(fd,&fileStat) < 0){
        printf("Could not read file statistics!\n");
        return NULL;
    }//exit if could not read file Statistics
    
    
    node_item *head, *curr;
    head = NULL;
    int storeInt;
    curr = head;
    while(read(fd,&storeInt,sizeof(int))>0){
        head = listadd(head, storeInt);
    }
    
    return head;
}

/*    This method  prints out each
 value on its own line.*/
void printlist(struct node *head){
    
    while(head){
        printf("%d-->", head->val);
        head = head->next ;
    }
    printf("NULL\n");
}
char bufferUser[80];

/*This function is aimed to test whether one integer belongs to the file.
* It has a pointer to search each value in the node and if intvalue has not been found,
 the function returns the value 0.*/

int inlist(struct node *head, int intvalue){
    node_item *curr;
    curr = head;
    while (curr!= NULL){
        if((curr-> val)== intvalue){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}


/* This function helps user play a guess.It allows users to keep guessing until they get it right. 
 * It compares users input with all integers inside the array and return true if users get it right. 
 * Otherwise return false.
 * */
void playgame(struct node * listhead){
    bool keepPlay = true;
    printf("This game has you guess which integers are in the list.\nEnter an integer\nor q\nto quit.\n");
    while(keepPlay){
        printf("Integer guess:");
        fgets ( bufferUser, 80, stdin );
        if(bufferUser[0] == 'q'){
            printf("Quitting\n");
            keepPlay = false;
        }else{
            int temp;
            
            temp = atoi(bufferUser);
            
            int checkAvail;
            checkAvail = inlist(listhead,temp);
            if(checkAvail==1){
                printf("%d is in the list.\n", temp);
            }else{
                printf("%d is not in the list.\n", temp);
            }
        }
    }
}

/**
 *   We made a structure which contains some parameters that describe the file we read.
 *   We store each character after reading it and print out the average of all integers.
 *  (numInt) represents the number of integers in the file we read.
 *   (fd) file descriptor of the binary file
 *   (outfile) a pointer to the address of outfile in memory
*/

int main(int argc, char *argv[]){
    node_item *head;
    
    head = NULL;
    if (argc != 2) {
        printf ("Error: cannot open file");
        exit(1);
    }
    char *outfile;
    outfile = argv[1];
    int fd;
    if((fd = open(outfile, O_RDONLY)) < 0){
        printf("could not open file!\n");
       exit(1);
    }
    head = createlist(fd);
    /*close the file and error checking if the file is successfully closed.
     */    
    if ( close(fd) != 0 ) {
        fprintf(stderr, "error closing file -- quitting\n");
        exit(1);
    }
    if(head ==NULL){
        printf("file is empty!\n");
        exit(1);
    }
    //printlist(head);
    playgame(head);
    
    return 0;
}
