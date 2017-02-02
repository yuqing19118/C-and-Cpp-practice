///////////////////////////////////////////////////////////////////////////////
////                   ALL STUDENTS COMPLETE THESE SECTIONS
//// Title:            stats.c
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

/**
 * We made a structure which contains some parameters that describe the file we read.
 * We store each character after reading it and print out the average of all integers.
 * (numInt) represents the number of integers in the file we read. 
 * (fd) file descriptor of the binary file.
 * (outfile) a pointer to the address of outfile in memory.
 * (sum) the sum of integers from the file we read.
 *
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
typedef struct info{
    char *outfile;
    int numInts;
    int fd;
    int sum;
} fileInfo;

int main(int argc, char *argv[]){
    /* if a single command line argument is not specified, print usage
     * information and exit
     */
    struct stat fileStat;
    fileInfo file;
    /*Error checking about opening the file.
     */
	if (argc != 2) {
        printf ("Error: cannot open file");
        exit(1);
    }
    file.outfile = argv[1];
    /*Error checking about reading the file.
      */

    if((file.fd = open(file.outfile, O_RDONLY)) < 0){
        printf("could not open file!\n");
        exit(1);    }
    /*Initialize the value of sum and numInts
    */
    file.sum=0;
    file.numInts = 0;
    
    /*Error checking about the total size of the file we read
    */
        if(fstat(file.fd,&fileStat) < 0){
        printf("Could not read file statistics!\n");
        return 1;//exit if could not read file Statistics
    }
    file.numInts = fileStat.st_size/sizeof(int);
    /*Create an array to store all values we read
     */
    int *storeInt ;
        if((storeInt= (int *)malloc(fileStat.st_size))<0){
        printf("Could not allocate memory!\n");
        exit(1);
    }
     /*Initialize the array
      */ 
    

    int i;
    for (i =0; i<file.numInts; i++)
    {
        storeInt[i]=0;
    }
    /*Error checking about storing each value we read to the array.
     */ 
     int j; 
    for(j=0;j<file.numInts;j++){
        if(read(file.fd,&storeInt[j],sizeof(int)) < 0)
        {
            printf("Unable to read");
            exit(1);
        }
        file.sum += storeInt[j];
    }
    /*Close file
     */ 
    if ( close(file.fd) != 0 ) {
        fprintf(stderr, "error closing file -- quitting\n");
        exit(1);
    }
    /*print out the average we get
     */
    int average =file.sum/file.numInts;
    printf("averge of %d numbers is %d\n", file.numInts, average);
    free(storeInt);
    return 0;
    
    
}
