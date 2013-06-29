#ifndef LINUX_SYSCALL_SUPPORT_H
#define LINUX_SYSCALL_SUPPORT_H

// A "test double" of sorts. This implementation defeats the 
// whole point--of not requiring the overhead of fopen, fread, etc...
// but it was the easiest way to get the code working under Windows.
// The focus of the linereader example is on the tests, anyway.

#include <stdio.h>
#include <io.h>

#define ssize_t size_t

// TODO add to vcxproj file

static const char templ[] = "c:\\temp\\line-reader-unittest-XXXXXX";
static char templ_copy[sizeof(templ)];
static int gfd;

int closed = false;
FILE* f;

size_t sys_read(unsigned int fd, char * buf, size_t count) {
   if (!closed) {
      _close(gfd);
      closed = true;
      fopen_s(&f, templ_copy, "r");
   }

   return fread(buf, sizeof(char), count, f);
}

#endif

