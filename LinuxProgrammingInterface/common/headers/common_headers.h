#ifndef _COMMON_HEADERS_H_
#define _COMMON_HEADERS_H_

#include<sys/types.h>       /* Type definitions used by many programs */
#include<stdio.h>           /* standard input output functions */
#include<stdlib.h>          /* prototypes  of commonly used library functions including EXIT_SUCCESS and EXIT_FAILURE constants */
#include<unistd.h>          /* Prototypes for many system calls */
#include<errno.h>           /* Declares the error numbers and defines the error constants */
#include<string.h>          /* Commonly used string handling functions */
#include"get_num.h"         /* Declares our functions for handling numeric arguements (getInt(),getLong())*/
#include"error_handling.h"  /* Declares our error-handling functions */

/* Some unix implementations define TRUE and FALSE so we will first undefine it here */
#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif


typedef enum { FALSE , TRUE } Boolean;

#define min(m,n) ((m) < (n) ? m : n )
#define max(m,n) ((m) > (n) ? m : n )

/* some unix implementations do not define socklen_t */
#if defined(__sgi)
typedef int socklen_t ;
#endif

#if defined(__sun)
#include<sys/file.h> /* has definition of FASYNC*/
#endif

#if !defined(FASYNC) && defined(O_ASYNC)
/* some implementations define FASYNC instead of O_ASYNC */
#define O_ASYNC FASYNC
#endif

#if defined(MAP_ANON) && !defined(MAP_ANOYMOUS)
/* BSD derivatives generally have the definition of MAP_ANON and not MAP_ANONYMOUS */
#define MAP_ANAONYMOUS MAP_ANON
#endif

#if !defined(O_SYNC) && defined(O_FSYNC)
/* Some implementations have O_FSYNC instead of O_SYNC */
#define O_SYNC O_FSYNC
#endif

#if defined(__FreeBSD__)

/* FreeBSD uses these alternate names for fields in the sigval structure */
#define sival_int sigval_int
#define sival_ptr sigval_ptr
#endif

#endif