///////////////////////////////////////////////////////////////////////////////
////                   ALL STUDENTS COMPLETE THESE SECTIONS
//// Title:            division.c
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
//Qing Yu section 1
//Zhang Cai section 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

/*Error handler when divisor is 0 and print the error message. 
*/
int count = 0;
void  sig_handler(int sig){
	printf("a divide by 0 operation was attempted\n");
	printf("%d successfully completed division operations\n", count);
	exit(0);

}


int main(int argc, char *argv[]){
	int a;
	int b;
	char bufferUser[80];
/*set up sigaction handler for user input.
*/
	struct sigaction act;
	memset (&act, '\0', sizeof(act));  
	act.sa_handler = sig_handler;
	
	if(sigaction( SIGFPE, &act, NULL)<0){
		perror("sigaction failed");
		return 1;
	}
/*Repeatedly read user input and compute the quotient and remainder. Count the number of successfully completed division operations.*/

	while(1){
		printf("Enter first integer: ");
		fgets ( bufferUser, 80, stdin );
		a = atoi(bufferUser);
		printf("Enter second integer: ");
		fgets ( bufferUser, 80, stdin );
		b = atoi(bufferUser);
		printf("%d / %d is %d with a remainder of %d \n", a, b, a/b, a%b);
		count++;
	}
	

	return 0;
}
