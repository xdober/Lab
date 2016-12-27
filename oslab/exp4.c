#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

struct passwd *pw;
struct group *gp;
struct tm *tm;
void printdir(char *dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(dir)) == NULL){
        perror("opendir()");
        return;
    }
    chdir(dir);//将dir设置为当前目录;
    while((entry = readdir(dp)) != NULL){
        lstat(entry->d_name,&statbuf);//以该目录项的名字为参数,调用lstat得到该目录项的相关信息;
        if(S_ISDIR(statbuf.st_mode)){//是目录
            int flag = 0;
            if(!strcmp(".",entry->d_name)||!strcmp("..",entry->d_name))
               	 continue;
            else {

                for (size_t i = 0; i < depth; i++) {
                    printf(" ");
                }
                if(depth>=4 && flag==0){
                    printf("|___");
                    flag = 1;
                }
                switch (statbuf.st_mode & S_IFMT) {
                    case S_IFREG: printf("-"); break;
                    case S_IFDIR: printf("d"); break;
                    case S_IFLNK: printf("l"); break;
                    case S_IFBLK: printf("b"); break;
                    case S_IFCHR: printf("c"); break;
                    case S_IFIFO: printf("p"); break;
                    case S_IFSOCK: printf("s"); break;
                }
                for (size_t i = 0; i <= 8; i++) {
                  if(statbuf.st_mode&(0400 >> i)){
                    switch (i%3) {
                      case 0 : printf("r"); break;
                      case 1 : printf("w"); break;
                      case 2 : printf("x"); break;
                    }
                  }
                  else {
                    printf("-");
                  }
                }
                pw = getpwuid(statbuf.st_uid);
                gp = getgrgid(statbuf.st_gid);
                printf(" %s %s %8ld ", pw->pw_name, gp->gr_name, statbuf.st_size);
                tm = localtime(&statbuf.st_ctime);
                printf("%4d-%2d-%2d %2d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min);
        printf("  %s\n", entry->d_name); //打印目录项的深度、目录名等信息
            printdir(entry->d_name,depth+4); //递归调用printdir,打印子目录的信息,其中的depth+4;
            }
        }
	 else {//打印文件的深度、文件名等信息
         for (size_t i = 0; i < depth; i++) {
             printf(" ");
         }
         if(depth>=4){
             printf("|___");
         }
         switch (statbuf.st_mode & S_IFMT) {
             case S_IFREG: printf("-"); break;
             case S_IFDIR: printf("d"); break;
             case S_IFLNK: printf("l"); break;
             case S_IFBLK: printf("b"); break;
             case S_IFCHR: printf("c"); break;
             case S_IFIFO: printf("p"); break;
             case S_IFSOCK: printf("s"); break;
         }
         for (size_t i = 0; i <= 8; i++) {
           if(statbuf.st_mode&(0400 >> i)){
             switch (i%3) {
               case 0 : printf("r"); break;
               case 1 : printf("w"); break;
               case 2 : printf("x"); break;
             }
           }
           else {
             printf("-");
           }
         }
         pw = getpwuid(statbuf.st_uid);
         gp = getgrgid(statbuf.st_gid);
         printf(" %s %s %8ld ", pw->pw_name, gp->gr_name, statbuf.st_size);
         tm = localtime(&statbuf.st_ctime);
         printf("%4d-%2d-%2d %2d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min);
         printf("  %s\n", entry->d_name);
     }
    }
    chdir("..");//返回父目录;
    closedir(dp);//关闭目录项;
}

int main(){
    char *dirname = (char*)malloc(sizeof(char)*256);
    strcpy(dirname,"/home/xrr/Desktop");
    printdir(dirname,0);
    return 0;
}
