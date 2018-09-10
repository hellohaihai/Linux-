/************************************************************************* > File Name: log.c > Author: haihai > Mail:xiehonghui@estor.com.cn > Created Time: Thu 06 9月2018日 10:17:05 AM CST ************************************************************************/ #include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
int _gf_haihai_log(const char *domain,const char *file, const char *function, int line,const char *fmt, ...); #define gf_haihai_log(dom,fmt...) do { \ _gf_haihai_log (dom, __FILE__, __FUNCTION__, __LINE__, \ ##fmt); \ } while (0) int main(){ gf_haihai_log("haihai","%s-%s-%s","print","hello","haihai"); return 0;
}
int _gf_haihai_log(const char *domain,const char *file, const char *function, int line,const char *fmt, ...){ char *log_name = "/var/log/digioceanfs/haihai.log"; int fd = 0; char log_buff[2048]; char date[256]; time_t now; FILE *fp = NULL; va_list ap; struct tm *timenow; char *str = NULL; memset(date,'\0',sizeof(date)); memset(log_buff,'\0',sizeof(log_buff)); time(&now); timenow = localtime(&now); va_start (ap, fmt); vasprintf (&str, fmt, ap); va_end (ap); sprintf(date,"[%.4d-%.2d-%.2d %.2d:%.2d:%.2d]",(1900+timenow->tm_year),timenow->tm_mon+1,timenow->tm_mday,timenow->tm_hour,timenow->tm_min,timenow->tm_sec); sprintf(log_buff,"%s, %s, [%s:%s:%d], %s\n",date,domain,file,function,line,str); fd = open(log_name,O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR); if(fd < 0){ return -1; } close(fd); fp = fopen(log_name,"a"); fwrite(log_buff,strlen(log_buff),1,fp); fclose(fp); return 0;
}
