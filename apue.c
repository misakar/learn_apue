#include"apue.h"
#include<stdarg.h>
#include<errno.h>
#include<fcntl.h>
/*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

*/

static void err_doit(int,int,const char *,va_list);

void 
err_quit(const char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,0,fmt,ap);
	va_end(ap);
	exit(1);
}

void
err_msg(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
}

void 
err_exit(int error,const char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,error,fmt,ap);
	va_end(ap);
	exit(1);
}


void 
err_dump(const char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);
	abort();
	exit(1);
}

void 
err_sys(const char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);
	exit(1);
}

void 
err_ret(const char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);
}

void 
err_doit(int errnoflag,int error,const char *fmt,va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",strerror(error));
	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}

void 
set_fl(int fd,int flags)
{
	int val;
	
	if((val = fcntl(fd,F_GETFL,0)) < 0)
		err_sys("fcntl F_GETFL error");
	
	val |= flags;
	
	if((fcntl(fd,F_SETFL,val)) < 0)
		err_sys("fcntl F_SETFL error");
}

void 
clr_fl(int fd,int flags)
{
	int val;
	
	if((val = fcntl(fd,F_GETFL,0)) < 0)
		err_sys("fcntl F_GETFL error");

	val &= ~flags;
	
	if((fcntl(fd,F_SETFL,val)) < 0)
		err_sys("fcntl F_SETFL error");
}

int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;
	
	return(fcntl(fd, cmd, &lock));
}

pid_t
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	if (fcntl(fd, F_GETLK, &lock) < 0)
		err_sys("fcntl error");

	if (lock.l_type == F_UNLCK)
		return(0);
	return(lock.l_pid); 
}

int
lockfile(int fd)
{
	struct flock fl;
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return(fcntl(fd, F_SETLK, &fl));
}
