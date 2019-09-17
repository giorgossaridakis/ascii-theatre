#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct window_prototype {
   char ul;
   char dl;
   char ur;
   char dr;
   char hr;
   char vr;} ;

struct points {
   int x;
   int y; } ;

struct window_points {
   struct points ptul;
   struct points ptdl;
   struct points ptur;
   struct points ptdr; } ;


void draw_window(int type, int x, int y, int width, int height, char title[]);
void popup_window(int type, int x, int y, int width, int height, char title[]);
void paint_window(int x,int y, int width, int lenth, char c);
int print_in_window(int flag, int x, int y, int width, int height, char filename[]);
char window_keypress(int x, int y, int height);

/* draw the window */
void draw_window(int type, int x, int y, int width, int height, char title[])
{
  int i;

  struct window_prototype window_scheme[10];
   window_scheme[0].ul=32;
   window_scheme[0].dl=32;
   window_scheme[0].ur=32;
   window_scheme[0].dr=32;
   window_scheme[0].hr=32;
   window_scheme[0].vr=32;

   window_scheme[1].ul=201;
   window_scheme[1].dl=200;
   window_scheme[1].ur=187;
   window_scheme[1].dr=188;
   window_scheme[1].hr=205;
   window_scheme[1].vr=186;

   window_scheme[2].ul=219;
   window_scheme[2].dl=219;
   window_scheme[2].ur=219;
   window_scheme[2].dr=219;
   window_scheme[2].hr=219;
   window_scheme[2].vr=219;
   
   window_scheme[3].ul=42;
   window_scheme[3].dl=42;
   window_scheme[3].ur=42;
   window_scheme[3].dr=42;
   window_scheme[3].hr=42;
   window_scheme[3].vr=42;

  struct window_points current_window;
   current_window.ptul.x=x;
   current_window.ptul.y=y;
   current_window.ptdl.x=x;
   current_window.ptdl.y=y+height;
   current_window.ptur.x=x+width;
   current_window.ptur.y=y;
   current_window.ptdr.x=x+width;
   current_window.ptdr.y=y+height;

  gotoxy(current_window.ptul.x, current_window.ptul.y);
   putchar(window_scheme[type].ul);
  gotoxy(current_window.ptdl.x, current_window.ptdl.y);
   putchar(window_scheme[type].dl);
  gotoxy(current_window.ptur.x, current_window.ptur.y);
   putchar(window_scheme[type].ur);
  gotoxy(current_window.ptdr.x, current_window.ptdr.y);
   putchar(window_scheme[type].dr);

  for (i=1;i<width;i++) {
   gotoxy(current_window.ptul.x+i, current_window.ptul.y);
    putchar(window_scheme[type].hr);
   gotoxy(current_window.ptdl.x+i, current_window.ptdl.y);
    putchar(window_scheme[type].hr);  }

  for (i=1;i<height;i++) {
   gotoxy(current_window.ptul.x, current_window.ptul.y+i);
    putchar(window_scheme[type].vr);
   gotoxy(current_window.ptur.x, current_window.ptur.y+i);
    putchar(window_scheme[type].vr);  }

   gotoxy(current_window.ptul.x, current_window.ptul.y-1);
    printf("%s",title);

}

/* popup effect */
void popup_window(int type, int x, int y, int width, int height, char title[])
{
 int i=2;
 int flag=0;
 int middlex,middley;
 int tx,ty,ttype;                                      

  middlex=x+(width/2);
  middley=y+(height/2);

  ttype=type;

  do {

   tx=middlex-1;
   ty=middley;

   while (x<tx-1 || y<ty-1) {
    draw_window(ttype, tx, ty, i, i, " ");
     tx--;
     ty--;
     i+=2; }

      flag++;
      ttype=0;
      i=2;
    } while (flag<2);
   
   draw_window(type, x, y, width, height, title);

}

/* paint inside with char of choice */
void paint_window(int x,int y, int width, int height, char c)
{
 int dx,dy;
                                                    
  for (dx=1;dx<width;dx++) {

   for (dy=1;dy<height;dy++) {
    gotoxy(x+dx,y+dy);
    putchar(c); }
     }
}

/* open a file inside a window */
int print_in_window(int flag, int x, int y, int width, int height, char filename[])
{
  FILE *f;
  char c;
  int tx,ty;
  int res;

  int *pi;
  double *pd;
  char *tstr;
   
   if ((check_file(filename))==-1)
	 exit(-1);
   
   f=fopen(filename,"r");

   tx=x+1;
   ty=y+1;

    while (c!=EOF) {

    c=fgetc(f);

     if (tx==x+width || c=='\n') {
      ty++;
      tx=x+1; }

     if (ty==y+height) {
       tx=x+1;
       ty=y+1;
       if (flag==1)
        window_keypress(x,y,height);
	   if (flag==2)
		sleep(3);   
       paint_window(x,y, width, height, ' '); }

      gotoxy(tx,ty);
       putchar(c);
      tx++; }

     if (flag==1)
      window_keypress(x,y,height);

    fclose(f);
	
 return 0;
}

char window_keypress(int x, int y, int height)
{
  char c;

   gotoxy(x,y+height+1);
   printf("<<<keypress>>>");
   c=getch();

 return c;
}


