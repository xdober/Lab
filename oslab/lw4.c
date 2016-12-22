#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <grp.h>
#include <pwd.h>

int fstat(int fildes,struct stat *buf);		//返回文件描述符相关的文件的状态信息
int stat(const char *path, struct stat *buf);	//通过文件名获取文件信息，并保存在buf所指的结构体stat中
int lstat(const char *path, struct stat *buf);	//如读取到了符号连接，lstat读取符号连接本身的状态信息，而stat读取的是符号连接指向文件的信息。
/*
struct stat {
	unsigned long  st_dev;		// 文件所属的设备
	unsigned long  st_ino;		// 文件相关的inode
	unsigned short st_mode;		// 文件的权限信息和类型信息: S_IFDIR, S_IFBLK, S_IFIFO, S_IFLINK
	unsigned short st_nlink;	//硬连接的数目
	unsigned short st_uid;		// 文件所有者的ID
	unsigned short st_gid;		//文件所有者的组ID
	unsigned long  st_rdev;		//设备类型
	unsigned long  st_size;		//文件大小
	unsigned long  st_blksize;	//块大小
	unsigned long  st_blocks;	//块数
	unsigned long  st_atime;	// 文件最后访问时间
	unsigned long  st_atime_nsec;
	unsigned long  st_mtime;	// 最后修改内容的时间
	unsigned long  st_mtime_nsec;entry
	unsigned long  st_ctime;	// 文件最后修改属性的时间
	unsigned long  st_ctime_nsec;
	unsigned long  __unused4;
	unsigned long  __unused5;
};
*/
/*
struct dirent {  
        #ifndef __USE_FILE_OFFSET64
    __ino_t  d_ino; //索引节点号  
    __off_t  d_off; //在目录文件中的偏移
        #else
           __ino64_t  d_ino;
          __off64_t   d_off;
       #endif
    unsigned   short   int   d_reclent;     //文件名的长度
    unsigned   char   d_type;     //d_name所指的文件类型  
        char   d_name[256];     //文件名  
  }
*/

void printdir(char *dir, int depth){
	int i;
	DIR *dp;
	struct passwd * pw;
	struct tm * tm;
	struct group * gr;
    	struct dirent *entry;
    	struct stat statbuf;
    	if  ((dp = opendir(dir))==NULL){
    	    printf("Error while opening directory:/%s.\n",dir);
    	    return ;
    	}
    	chdir(dir);
	while((entry = readdir(dp)) != NULL){
        	lstat(entry -> d_name, &statbuf);
        	if(S_ISDIR(statbuf.st_mode)){
			if(!strcmp("..",entry->d_name)||!strcmp(".",entry->d_name) )
   	   	         	 continue;
			switch(statbuf.st_mode & S_IFMT)
    			{
    				case S_IFREG:  printf("-");    break;
					case S_IFDIR:  printf("d");    break;
					case S_IFLNK:  printf("l");    break;
    				case S_IFBLK:  printf("b");    break;
    				case S_IFCHR:  printf("c");    break;
    				case S_IFIFO:  printf("p");    break;
    				case S_IFSOCK: printf("s");    break;
    			}
			for(i = 8; i >= 0; i--)
    			{
        			if(statbuf.st_mode & (1 << i))
        			{
            				switch(i%3)
            				{
           				 		case 2: printf("r"); break;
            					case 1: printf("w"); break;
            					case 0: printf("x"); break;
            				}
        			}
        			else
            				printf("-");
    			}
			pw = getpwuid(statbuf.st_uid);
			gr = getgrgid(statbuf.st_gid);
   	        	printf("%2d %s %s %8ld", depth, pw->pw_name, gr->gr_name, statbuf.st_size);
			tm = localtime(&statbuf.st_ctime);
			printf(" %04d-%02d-%02d %02d:%02d",tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
			printf(" %s\n", entry->d_name);
			printdir(entry->d_name,depth+4);
        	}
		else 	{
			switch(statbuf.st_mode & S_IFMT)
    			{
    				case S_IFREG:  printf("-");    break;
					case S_IFDIR:  printf("d");    break;
					case S_IFLNK:  printf("l");    break;
    				case S_IFBLK:  printf("b");    break;
    				case S_IFCHR:  printf("c");    break;
    				case S_IFIFO:  printf("p");    break;
    				case S_IFSOCK: printf("s");    break;
    			}
			for(i = 8; i >= 0; i--)
    			{
        			if(statbuf.st_mode & (1 << i))
        			{
            				switch(i%3)
            				{
           				 		case 2: printf("r"); break;
            					case 1: printf("w"); break;
            					case 0: printf("x"); break;
            				}
        			}
        			else
            				printf("-");
    			}
			pw = getpwuid(statbuf.st_uid);
			gr = getgrgid(statbuf.st_gid);
   	        	printf("%2d %s %s %8ld", depth, pw->pw_name, gr->gr_name, statbuf.st_size);
			tm = localtime(&statbuf.st_ctime);
			printf(" %04d-%02d-%02d %02d:%02d",tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
			printf(" %s\n",entry->d_name);
		}
	}
    	chdir("..");
   	i = closedir(dp);
	if(i == -1)
		printf("Error while closing Directory:/%s\n",dir);
}

int main(){
	char temp[100];
	printf("Please input a directory\n");
	scanf("%s",temp);
	printf("Directory scan of %s\n",temp);
	printdir(temp,0);
	printf("Done\n");
	return 0;
}
