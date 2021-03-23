#include <cstdio>
#include <ctime>

using namespace std;

const char * swday(int yd, int wd_start){
  static const char *wday[7]={"شنبه","یک‌شنبه","دوشنبه","سه‌شنبه","چهارشنبه","پنج‌شنبه","آدینه"};
  return wday[(yd+wd_start)%7];
}

const char * smday(int yd){
  static const char * mday[31]={"۱","۲","۳","۴","۵","۶","۷","۸","۹","۱۰","۱۱","۱۲","۱۳","۱۴","۱۵","۱۶","۱۷","۱۸","۱۹","۲۰","۲۱","۲۲","۲۳","۲۴","۲۵","۲۶","۲۷","۲۸","۲۹","۳۰","۳۱"};
  int i = yd%365;
  if(i<186) return mday[i%31];
  return mday[(i-186)%30];
}

const char * smonth(int yd){
  static const char * month[12]={"فروردین","اردی‌بهشت","خرداد","تیر","مرداد","شهریور","مهر","آبان","آذر","دی","بهمن","اسپند"};
  int i = yd%365;
  if(i<186) return month[i/31];
  return month[(i-186)/30+6];
}

const char * syear(int yd, int y_start){
  static const char * year[6]={"۱۳۹۹","۱۴۰۰","۱۴۰۱","۱۴۰۲","۱۴۰۳","۱۴۰۴"};
  if(yd>0 && (y_start == 1399 || y_start == 1404) )
    yd = yd - 1;
  int i = yd/365 + y_start;
  if(1399<=i && i<=1404) return year[i-1399];
  return "";
}


int main(){
  int y_start=1400;
  struct tm cal = {.tm_year=2021-1900, .tm_mon=3-1, .tm_mday=21};

  mktime(&cal);
  int wd_start=(cal.tm_wday+1)%7; 
  int dtstart = 10000*(cal.tm_year+1900) + 100*(cal.tm_mon+1) + cal.tm_mday;
  printf("BEGIN:VCALENDAR\nVERSION:2.0\nCALSCALE:GREGORIAN\nMETHOD:PUBLISH\n");
  for(int yd=0;yd<366;yd++){
    cal.tm_mday++;
    mktime(&cal);
    int dtend = 10000*(cal.tm_year+1900) + 100*(cal.tm_mon+1) + cal.tm_mday;
    printf("BEGIN:VEVENT\nUID:j%d\nSUMMARY:%s %s %s %s\nDTSTART;VALUE=DATE:%d\nDTEND;VALUE=DATE:%d\nEND:VEVENT\n",dtstart,swday(yd,wd_start),smday(yd),smonth(yd),syear(yd,y_start),dtstart,dtend);
    dtstart = dtend;
  }  
  printf("END:VCALENDAR\n");
  return 0;
}
