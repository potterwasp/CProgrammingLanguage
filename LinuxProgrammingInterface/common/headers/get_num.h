#ifndef _GET_NUM_H_
#define _GET_NUM_H_

#define GN_NONNEG   01  /*the value should be >=0*/
#define GN_GT_0     02  /*the value should be > 0*/


#define GN_ANY_BASE 0100 /*can use any base like strtol(3)*/
#define GN_BASE_8   0200 /*value is expressed in octal */
#define GN_BASE_16  0400 /*value is expressed in hexadecimal*/

long getLong(const char *arg,int flags,const char * name);
int  getInt(const char *arg, int flags,const char *name);

#endif