 /*
    error_handling.c 
    Some standard error handling routines used by all the example programs
 
 */
 
 
 #include<stdarg.h>
 #include"error_handling.h"
 #include"common_headers.h"
 #include"ename.h"

 NORETURN
 static void 
 terminate(Boolean bUseExit3)
 {
    char * s;
    /* check if the EF_DUMPCORE environment is set*/
    s = getenv("EF_DUMPCORE");
    if( s!=NULL && *s!="\0")
        abort();
    /* otherwise call exit(3) or _exit(2),
       depending on the value of 'useExit3'. */
    if(bUseExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
 }


 /*
 Function name : outputError
 Description   : diagnose the errnum by the following
                 1. Printing the errNum string  from the ename array corresponding to the errnum
                 2. Along with the above Print the corresponding error text related to the errnum from the stderror()
                 3. Print the user provided messages from the format and ap parameters
 */


static
void outputError(Boolean useError, int errNum , Boolean flushStdout , const char * format,va_list ap)
{
#define BUFFER_SIZE 500
    char buf[BUFFER_SIZE],userMsg[BUFFER_SIZE],errText[BUFFER_SIZE];

    vsnprintf(userMsg,BUFFER_SIZE,format,ap);

    if(useError)
        snprintf(errText,BUFFER_SIZE," [%s %s]", 
        (errNum > 0 && errNum <= MAX_ENAME) ? 
        ename[errNum] : "?UNKNOWN?", strerror(errNum));
    else
        snprintf(errText,BUFFER_SIZE,":");

    
    #if __GNUC__ >= 7
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored  "-Wformat-truncation"
    #endif
        snprintf(buf,"Error:%s %s",errText,userMsg);
    #if __GNUC__ >= 7
    #pragma GCC diagnostic pop
    #endif

    if(flushStdout)
        fflush(stdout);  /* flush any pending stdoutput */
    fputs(buf,stderr);
    fflush(stderr);
}

/* Display error message including 'errNo' diagnostic, 
   and return to the caller */

void 
errMsg(const char *format, ...)
{
    va_list argList;
    int savedErrno = errno;   /* the current error number in case we change it here */

    va_start(argList,format);
    outputError(TRUE,errno,TRUE,format,argList);
    va_end(argList);

    errno = savedErrno;
}

/* Display the error message including errNo diagnostic and terminate the process */
void 
errExit(const char *format,...)
{
    va_list argList;

    va_start(argList,format);
    outputError(TRUE,errno,TRUE,format,argList);
    va_end(argList);

    terminate(TRUE);
}



/* Display error message including errNo diagnostic and terminate the process by calling _exit() 

   The relationship between this function and errExit is analogous to _exit(2) and exit(3)
   In case of _exit(2) the error handlers are not callled and exit(3) error handlers are called.
   Unlike exit(3) this function does not flush stdout and file handlers but calls _exit(2) to
   terminate the process

   This is specially useful in library functions that invoke a child process and the child process 
   must terminate due to an error. In this case the termination of the child process does not cause
   the callers stdio buffers to be flushed and also avoiding the exit handlers of the caller from
   being called.

   The child must terminate without flushing the stdio buffers that were partially filled by the 
   caller and without invoking exit handlers that were established by the caller. */

void 
err_exit(const char * format,...)
{
    va_list argList;

    va_start(argList,format);
    outputError(TRUE,errno,FALSE,format,argList);
    va_end(argList);

    terminate(FALSE);
}

/*


*/