///////////////////////////////////////////////////////////////////////////////
////                   ALL STUDENTS COMPLETE THESE SECTIONS
//// Title:            intdate.c
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
//// Course Section:   01
////
////////////////////// STUDENTS WHO GET HELP FROM OTHER THAN THEIR PARTNER //////

//Qing Yu		section 1
//Zhang Cai		section 1
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int numtoalarm = 3;//a specified number of seconds for activating the SIGALRM interrupt . 
int count = 5;//number of ^c need to count

/*This handler function is to print out the current time,
 re-arm the alarm to go off three seconds later,
 and then return back to the main function */
void  ALARMhandler(int sig){

time_t mytime;
mytime = time(NULL);
printf("current time is %s" , ctime(&mytime));
alarm(numtoalarm );//set a new alarm

}


/*The SIGINT handler either prints how many more times Control-c must be typed before exiting,
  or it prints that it caught the 5th one and it calls exit()
 */
void  CONTROLChandler(int sig){
	
	count--;
	if(count>0){
		printf("\nControl-c caught. %d more before program is ended.\n", count);
	}else{
		printf("\nFinal Control-c caught. Exiting.\n");
	exit(0);
}
	
}


int main(void){

	printf("Date will be printed every %d seconds.\nEnter ^C %d times to end the program:\n",numtoalarm,count);

//set up handler for SIGALRM and SIGINT
	struct sigaction alarmaction,ctrlaction;
	memset (&alarmaction, '\0', sizeof(alarmaction));  
	alarmaction.sa_handler = ALARMhandler;

	if(sigaction(SIGALRM,&alarmaction, NULL)<0){
		printf("cannot set up signal handler\n");
		return 1;
	}

	memset (&ctrlaction, '\0', sizeof(ctrlaction));  
	ctrlaction.sa_handler = CONTROLChandler;

	if(sigaction(SIGINT,&ctrlaction, NULL)<0){
		printf("cannot set up signal handler\n");
		return 1;
	}
	
	alarm(numtoalarm);//schedule first alarm
	while(1){

	}
	
	return 0;
}
