#include <stdio.h>
#include <math.h>
#include <string.h>
#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <constrea.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h> /* for atof() */

#define NUMLIMIT 32767 /* maximum limit in input */
#define MAXCHARS 9999

struct input_types {
 int integer;
 double decimal;
 char line[MAXCHARS];
 char ch; } ;

struct input_types read_input;

struct calendar {
 int day;
 int month;
 int year;
 int hour;
 int min;
 int sec; 
 int msec; } ;
 
int mod(double a, double b);
void randomizer(long int depth);
int add_digits(int number);
int read_kbrd(int instruction, double lima, double limb, char input_name[], int *integer, double *decimal, char *str);
int read_words(char str[], char *pstr[]);
char *salloc(char string[]);
void clear_string(char string[]);
void *xmalloc (size_t size);
double compare_strings(double length, char string1[], char string2[]);
int sort_array(int signal, char string[], char *pstr[]);
double *sort_double(int size, double *pd);
void sleep(int duration);
int freadline(FILE *source, char string[]);
int check_file(char filename[]);
struct calendar date_time();
int bin_to_dec(char string[]);
void dec_to_bin(int value, char string[]);
int find_integer_edge(int flag, int *table);
void *zmalloc();
int copy_file(char *source, char *dest);
long int hex_to_dec(char string[]);

/* read a string and copy data to structure */
int read_kbrd(int instruction, double lima, double limb, char input_name[], int *integer, double *decimal, char str[])  /* instruction 0: integer, 1:decimal, 2:string, lower limit, upper limit, quote line and 3 pointers */
{
 double result_local=-(NUMLIMIT);
 int result_integer;
 double result_decimal;
 int i=0;
 char c;
 char local_line[999];
 char local_char;

  clear_string(local_line);

  clear_string(read_input.line);
  read_input.integer=0;
  read_input.decimal=0.0;

  switch (instruction) {
   case 0:
    while (result_local<lima || result_local>limb) {
    printf("numerical %s [%d to %d]:",input_name,int(lima),int(limb));
     i=0;
	 c=NULL;
     result_local=-(NUMLIMIT);
      while (c!='\n') {
       c=getchar();
       local_line[i++]=c; }
      local_line[--i]='\0';
      result_local=atoi(local_line); }

     result_integer=atoi(local_line);
     read_input.integer=result_integer;
     *integer=read_input.integer;
    break;

   case 1:
    while (result_local<lima || result_local>limb) {
    printf("numerical %s [%f to %f]:",input_name, lima, limb);
     i=0;
	 c=NULL;
     result_local=-(NUMLIMIT);
      while (c!='\n') {
       c=getchar();                                                   
       local_line[i++]=c; }
      local_line[--i]='\0';
      result_local=atoi(local_line); }

     result_decimal=atof(local_line);
     read_input.decimal=result_decimal;
     *decimal=read_input.decimal;
    break;
    
    case 2:
    printf("alphanumerical %s [max %d chars]:",input_name, int(limb));
      i=0;
	  c=NULL;
      while (c!='\n' && i<limb+1) {
        c=getchar();
        local_line[i++]=c; } 
      local_line[--i]='\0';
      strcpy(read_input.line,local_line);
     read_input.ch=read_input.line[0];
     strcpy(str,read_input.line);
	break; }

   fflush(stdin);
   return sizeof(read_input.line);
}

/* separate words in a string and generate an array of pointers  */
int read_words(char str[], char *pstr[])
{
 int n;
 int strlength;
 int nwords=0;

 pstr[nwords]=str;

 strlength=strlen(str);

 for (n=0;n<(strlength-1);n++) {

  if ((int)(str[n])==32) {
   pstr[++nwords]=&str[n+1];
   str[n]='\0'; }

 }

 nwords++;
 return nwords;
}

double compare_strings(double length, char string1[], char string2[])
{
 int i;
 double equals;
 double percentage;

  if (strlen(string1)< length)
   length=strlen(string1);

  for (i=0;i<length;i++) {
   if (int(string1[i])==int(string2[i]))
    equals++; }

  percentage=(equals*100)/length;

 return percentage;
}

/* give me a new string in a free block of memory */
char *salloc(char string[], size_t size)                         
{
 char *ps;

  ps=(char *) xmalloc(size+1);
  memcpy(ps, string, size);

 return ps;
}

void *xmalloc (size_t size)
{
 void *value = malloc(size);
 
  if (!value)
  printf ("virtual memory exhausted\n");

return value;
}

/* return pointer to a new memory assigned string of 999 chars */
void *zmalloc()
{
  size_t size;
  char s[999];
  
    void *value=malloc(sizeof(s));
 
  return value;
}

/* empty a string */
void clear_string(char string[])
{
 memset(string, 0, sizeof(string));
}

/* copy source to destination file */
int copy_file(char *source, char *dest)
{
  FILE *f;
  FILE *w;
  char c;
  char buf[BUFSIZ];
  size_t size;
  
   f=fopen(source, "rb");
   w=fopen(dest, "wb");
   if (!f || !w)
	return -1;
   
    while (size = fread(buf, 1, BUFSIZ, f)) 
     fwrite(buf, 1, size, w);
	
	fclose(f);
	fclose(w);
	
  return 0;
}

int ctoi(char c);

int ctoi(char c)
{
 return c-'0';
}

int mod (double a, double b)
{
int tmp =a/b;

return a-(b*tmp);
}

/* randomize numbers better */
void randomizer(long int depth)
{
  time_t timer;
  int seed_number;
  int i,n,l;

  randomize();

  time(&timer);
  seed_number=mod(timer,10000);
 
   for (n=0;n<seed_number;n++) {

    for (i=0;i<depth;i++)
     l=(rand () % 1111);

  }
}
/* add digits of an integer */
int add_digits(int number)
{
  int result=0;
  
  if (number<10 && number>-1)
   return number;
  
  while (number) {
   result+=number % 10;
  number/=10; }

 return result;
} 

double *sort_double(int size, double *pd)
{
 int i,n;
 double temp;
 double table[999];

    for (i=0;i<size;i++)
     table[i]=*(pd+i);

     for (i=0;i<size;i++) {
      for (n=size;n>0;n--)  {
       if (table[n-1]>table[n]) {
        temp=table[n-1];
        table[n-1]=table[n];
        table[n]=temp; } } }
                                                        
 return &table[0];
}

/* sort separate words inside an array and arrange array of pointers. signal 1 to disregard upper/lower */
int sort_array(int signal, char string[], char *pstr[])
{
 int i, n, k;
 int flag=0;
 int nwords;                                                
 char str1[99], str2[99];
 char *tp;
 int l1,l2,l;

   nwords=read_words(string, pstr)-1;

   for (k=0;k<nwords;k++) {

    for (n=nwords;n>0;n--) {
     flag=0;
     clear_string(str1);
     clear_string(str2);
     strcpy(str1, pstr[n]);
     strcpy(str2, pstr[n-1]);
      l1=strlen(str1);
      l2=strlen(str2);

      l=(l1<l2) ? l1 : l2;
      if (signal==1) {
       for (i=0;i<l;i++) {
        str1[i]=tolower(str1[i]);
        str2[i]=tolower(str2[i]); } }

       for (i=0;i<l;i++) {
        if ((int(str1[i])<int(str2[i])) && flag==0) {
          flag=1;
          tp=pstr[n-1];
          pstr[n-1]=pstr[n];
          pstr[n]=tp; }
        if ((int(str1[i])>int(str2[i])))
          flag=1; }
       }
      }

 nwords++;
 return nwords;
}

/* sleep routine using timer */
void sleep(int duration)
{
  double seconds;
  time_t timer1;
  time_t timer2;
  
   time(&timer1);
   time(&timer2);
   
   while(duration>seconds) {
	time(&timer2);
	seconds=difftime(timer2, timer1); }
	
}

/* check if a file exists */
int check_file(char filename[])
{
  FILE *f;
  
   f=fopen(filename, "r");
   if (!(f))
    return -1;

   fclose(f);

 return 0;
}

/* copy a line from file to string, line by line */
int freadline(FILE *source, char string[])
{
  int i;
  char c;
  
     i=0;
	 c=0;
	 
	 while (c!='\n' && c!=EOF) {
	  string[i++]=c; }
	  string[--i]='\0'; 
	  
 return 0;
}

/* return time and date in calendar structure */
struct calendar date_time()
{
  time_t rawtime;
  struct tm *timeinfo;
  struct calendar cal;

  time (&rawtime);
  timeinfo = localtime (&rawtime);
    
   cal.day=timeinfo->tm_mday;
   cal.month=timeinfo->tm_mon+1;
   cal.year=timeinfo->tm_year+1900;
   cal.hour=timeinfo->tm_hour;
   cal.min=timeinfo->tm_min;
   cal.sec=timeinfo->tm_sec; 
   
  return cal;
}

/* set up string with binary value of int */
void dec_to_bin(int value, char string[])
{
 int i, n, l;
 int sum=0;
 int counter=7;
 int kept=0;
 int digit=7;
 int digits[8];
 
  for (i=0;i<8;i++)
   digits[i]=0;
  
    while (value!=sum) {
	
	 digits[7]++;
	 
	 for (i=7;i>-1;i--) {
	  digits[i]+=kept;
	  if (digits[i]==2) {
	   digits[i]=0;
	   kept=1; } 
	   else 
		kept=0;  }
	   	 
	   sum=0;
	   for(i=0;i<8;i++) { 
        if (digits[i])
   	     sum+=pow(2,7-i); }
	 
	 }
        
     for (i=0;i<8;i++)
	  string[i]=digits[i]+'0'; 
     string[i]='\0';

} 

/* convert binary string to decimal value */
int bin_to_dec(char string[])
{

 int i;
 int sum=0;
 
  for (i=7;i>-1;i--) {
   if (ctoi(string[i]))
    sum+=pow(2, (7-i)); }

 return sum;
}

/* set up a string with hexadecimals from decimal value */
void dec_to_hex(long int value, char string[])
{
  int i,n;
  long int sum=0;
  int digits[8];

  for (i=0;i<8;i++)
   digits[i]=0;
   strcpy(string, "00000000"); 
  
    while (sum!=value) {
    /* convert decimal value to hexadecimal char */  
    for (n=0;n<8;n++) {
	 if (digits[n]<10)
	  string[n]=digits[n]+'0';
  	 else 
 	 string[n]=55+digits[n]; }
	 /* calculate sum from string and exit if decimal value has been reached */
	 sum=hex_to_dec(string); 
	 if (sum==value)
	  break;
  
     ++digits[7];
	 /* let us rearrange the array now */
	 for (i=7;i>1;i--) {
	  if (digits[i]>15) {
	   ++digits[i-1];
	   for (n=i;n<8;n++)
	digits[n]=0; } } }
}

/* convert hexadecimal string to decimal value */
long int hex_to_dec(char string[])
{

 int i;
 int digit;
 int sum=0;

   for (i=strlen(string)-1;i>-1;i--)  {
	if (isdigit(string[i])) 
	  digit=ctoi(string[i]);
	if (isalpha(string[i])) {
	 digit=(int) (toupper(string[i]))-55;
	 if (digit<0 || digit>16)
  	digit=0;  }  	 
   sum+=digit*pow(16, strlen(string)-i-1); }

 return sum;
}

/* return smallest or biggest of integers */
int find_integer_edge(int flag, int *table)
{
   int i1,i2; /* i1 smallest, i2 biggest */
   int result;
   i1=NUMLIMIT;
   i2=-1*NUMLIMIT;
   
    while (*table) {
	 if (*table<i1)
	  i1=*table;
     if (*table>i2)
      i2=*table;
	++table; }
	
	result=!flag ? i1 : i2 ;

 return result;
} 