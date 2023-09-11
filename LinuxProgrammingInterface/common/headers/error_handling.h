/*
File name   : error_handling.h
Description : This file contains the declarations of the error handling functions that are used across the 
              programs   
*/

#ifndef _ERROR_HANDLING_H_
#define _ERROR_HANDLING_H_

//variable arguement method to print the error message text corresponding to the error number to std error
void errMsg(const char *format,...);

/* This macro stops the 'gcc -Wall' complaining that the control has reahed the end of a non-void function if we
attempt to terminate a process using the following functions ( could be main or some other non void function)*/

#ifdef __GNUC__
#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif

/* 
Name: errExit
Description: This function also behaves like errMsg but also terminates the program calling exit()
*/
void errExit(const char *format,...) NORETURN;  

/*
Name: err_exit
Description : This is similar to errExit() but differs in two aspects 
                1. Does not flush the standard output before printing the error message 
                2. calls _exit instead of exit() 
*/
void err_exit(const char *format,...) NORETURN;

/*
Name: errExitEN
Description: Same as errExit but instead of printing the error text corresponding to the current value of error number it prints the text
             corresponding to the error number ( see ename.h )
*/
void errExitEN(const char *format,...) NORETURN;

//to diagnose other errors we use the following functions

//the fatal error is used to diagnose the general errors and the errors that do not set an error number
void fatal(const char *format,...) NORETURN;

//the usageErr function is used to diagnose the errors in command line arguement usage
void usageErr(const char *format,...) NORETURN;

//the cmdLineErr is similar to usage error but is used to diagnosing errors in the command line arguements speified in the program
void cmdLineErr(const char *format,...) NORETURN;

#endif