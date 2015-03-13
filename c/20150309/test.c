#include <stdio.h>
#include <time.h>

typedef enum{
	TRUE=1,
	FALSE=0
}BOOL;

main(){
	BOOL flag = TRUE;
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    printf("sec = %d\n", timep);
    p = localtime(&timep); //取得当地时间
    printf ("%d%d%d ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    printf("%s%d:%d:%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
}
