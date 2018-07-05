#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GL/glut.h> //linux 

/*
* GL Basic Error Check Function
* Original by Willem A. (Vlakkies) Schreuder
*/
void ErrCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Print message to stderr and exit
 * Original by Willem A. (Vlakkies) Schreuder
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}
