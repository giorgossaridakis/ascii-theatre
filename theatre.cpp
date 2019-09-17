#include "mylibrary.cpp"
#include "windows.cpp"
#include <windows.h>
#include <constrea.h>

#define WINLIMIT_L 10
#define WINLIMIT_R 64
#define WINLIMIT_U 5
#define WINLIMIT_D 20
#define MAXACTORS 15
#define MAXNAME 10
#define VISIBLE 1
#define INVISIBLE 0

char *filenames[99];

struct object {
	char name[MAXNAME]; 
	char character; 
	int color;
	int x;
    int y; 	
	bool opacity; } ;	
	
int actors;
int scene;
char title[50];
struct object actor[MAXACTORS];
FILE *pl;
char filename[25];
int filemode=0;
int moves=0;

constream win1;	

void place_actors(int flag, struct object *actor);
void object_limits(struct object *tempobject);
int parse_command(char command[]);
int load_scene();
void clear_scene();
void curtain(int flag);
void showCursor(bool showFlag);

main()
{
  int i;
  char c;
  char command[50];
  int parse_result;
   
  int *pi;
  double *pd;
  char *pc;
  
   randomizer(9);
   
   win1.window(1, 1, 150, 50); 
   /* win1 << setbk(CYAN); */
   win1.clrscr();   

   strcpy(actor[0].name, "system");
   actor[0].opacity=INVISIBLE;
   actor[0].x=24;
   actor[0].y=8;
    
    win1 << setxy(25, 1);
	 win1 << setattr(YELLOW | YELLOW) << "The WoRlD famous ASCII Theatre";
    win1 << setxy(25, 2);
     win1 << setattr(YELLOW | YELLOW) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	
	clear_scene();
	draw_window(1,1,23,70,2,"");
    
	
   /* main routine */
   do {
   
    clear_string(command);
	fflush(stdin);
    paint_window(1,23,70,2,32);
	win1 << setxy(2, 24);
    showCursor(true);
		 
	if (filemode==2) {
	 i=0;
	 c=0;
	 while (c!='\n' && c!=EOF) {
	  c=fgetc(pl);
	  command[i++]=c; }
	  command[--i]='\0';
	 win1 << setattr(BLACK | WHITE) << command; } 
	else 
	 gets(command);	 
 
	showCursor(false); 
	
	parse_result=parse_command(command);
	if (parse_result>=1)
	 ++moves; 
	if (parse_result<1) {
	 win1 << setxy(2, 24);
	 win1 << setattr(RED | RED) << "error: parser cannot recognise command structure!"; 
	 getch(); }
	  
	if (parse_result==98) {
     while(actor[1].x<((WINLIMIT_R-WINLIMIT_L+2)/2)+(WINLIMIT_L-2)+(actors/2)) {
	  for (i=1;i<actors+1;i++) {
	   clear_string(command);
	   strcat(command, "@");
	   strcat(command, actor[i].name);
	   strcat(command, " move e");
	   parse_result=parse_command(command);
	   place_actors(1, &actor[i]);
	   Sleep(500); } } }
	  	   
    for (i=1;i<actors+1;i++) {
     if (actor[i].opacity==VISIBLE)	
   	  place_actors(1, &actor[i]);  }
	
   } while(parse_result<99);
	
 end:	
  win1.clrscr();
  showCursor(true);
  printf("Thank you for watching the show!\n");
}

/* command line parser */
int parse_command(char command[])
{
 int i=0;
 int nwords;
 char c;
 char actorname[MAXNAME];
 char actions[20][999];
 int actorid=-1;
 int activity=0;
 int dialoguex, dialoguey;
 char *pstr[20];
 char *ps;
 FILE *f;
 void *str;

  if (command[0]!='@') 
   return -1;
  if (filemode==1) {
   fprintf(pl, command);
   fprintf(pl, "\n"); } 
  ps=&command[1];
  
  nwords=read_words(ps, pstr);
  
  for(i=0;i<nwords;i++) 
   strcpy(actions[i], pstr[i]);
  
  for (i=0;i<actors+1;i++) {
   if (!(strcmp(actions[0], actor[i].name))) {
	strcpy(actorname, actions[0]);
    actorid=i; } }

  if (actorid==-1)
   return -1;

  /* command interpeter */
  
  if (!actorid) {
	  
   if (!strcmp(actions[1], "title")) {
	++activity;
	clear_string(title);
	for (i=2;i<nwords;i++) {
     strcat(title, actions[i]);
	 strcat(title, " "); }	 
    draw_window(1,WINLIMIT_L-1,WINLIMIT_U-1,WINLIMIT_R-WINLIMIT_L+2,WINLIMIT_D-WINLIMIT_U+2,title); }
   
   if (!strcmp(actions[1], "clear")) {
	++activity;
	clear_scene(); }
	
   if (!strcmp(actions[1], "setscene")) {
	++activity;
	str=malloc(sizeof(actions[3]));
	memcpy(str, actions[3], sizeof(actions[3]));
   filenames[atoi(actions[2])]=(char *) str; }
	
   
   if (!strcmp(actions[1], "scene")) {
	scene=atoi(actions[2]);
    i=load_scene(); 
	if (i==-1) 
	 return -1; 
    else 
	 ++activity; }
   
   if (!strcmp(actions[1], "curtain")) {
	++activity;
   curtain(atoi(actions[2])); }
   
   if (!strcmp(actions[1], "finale")) {
	++activity;
	 for (i=1;i<actors+1;i++) {
	  place_actors(0, &actor[i]);
      actor[i].x=WINLIMIT_L+actors-i;
	  actor[i].y=WINLIMIT_D-2;
	  actor[i].opacity=VISIBLE; }
   return 98; }
	  
   if (!strcmp(actions[1], "exit")) {
	++activity;
	draw_window(1, 25, 9, 21, 2, "");
	win1 << setxy(26, 10);
	win1 << setattr(BLUE | RED) << "system will now exit" ;
   return 99; }
   
   if (!strcmp(actions[1], "filesave")) {
	++activity;
    pl=fopen(actions[2], "w");
    filemode=1;	}
	
   if (!strcmp(actions[1], "fileclose")) {
	++activity;
	fflush(pl);
    fclose(pl);
    filemode=0;	}
	
   if (!strcmp(actions[1], "fileplay")) {
    pl=fopen(actions[2], "r");
     if (!pl)
      return -1;
     else 
	  filemode=2;
	  clear_scene();	
      ++activity; }
	  
	if (!strcmp(actions[1], "report")) {
	 ++activity;
	 f=fopen(actions[2], "w");
	  if ((!f))
	   return -1;
	  fprintf(f,"ASCII Theatre report\n");
	  fprintf(f,"~~~~~~~~~~~~~~~~~~~~\n");
	  fprintf(f, "Title :%s | Scene :%d\n", title, scene);
	  fprintf(f, "number of actors :%d\n", actors);
	  for (i=1;i<actors+1;i++) {
	   fprintf(f, "Actor name: %s | number in catalogue :%d\n", actor[i].name, i);
	   fprintf(f, "character :%c | color :%d | opacity :%d\n", actor[i].character, actor[i].color, actor[i].opacity);
	   fprintf(f, "coordinate x :%d | coordinate y:%d\n", actor[i].x, actor[i].y);
	   fprintf(f, "------------------------------------\n"); }
	   fprintf(f, "time elapsed in sequential moves :%d\n",moves);
	 fclose(f); }
	 
	if (!strcmp(actions[1], "wait")) {
	++activity;
	Sleep(atof(actions[2])); } 
	
	if (!strcmp(actions[1], "announce")) {
	++activity;
	dialoguex=actor[0].x+1;
	dialoguey=actor[0].y-1;
	draw_window(1, dialoguex, dialoguey, 15, 3, ""); 
	paint_window(dialoguex, dialoguey, 15, 3, 32);
    f=fopen("dialogue.txt", "w");
	 for (i=2;i<nwords;i++)
      fprintf(f, "%s ", actions[i]);
    fclose(f);
	print_in_window(2, dialoguex, dialoguey, 15, 3, "dialogue.txt");
	Sleep(2500);
	load_scene(); }
	 
   if (!strcmp(actions[1], "create")) {
	 ++activity;
	 ++actors;
	 strcpy(actor[actors].name, actions[2]);
	 if (!strcmp(actions[3], "normal"))
	  actor[actors].character=1;
     else if (!strcmp(actions[3], "extended"))
	  actor[actors].character=2;
     else 
	  actor[actors].character=*actions[3];
     actor[actors].color=atoi(actions[4]);
	 actor[actors].x=atoi(actions[5]);
     actor[actors].y=atoi(actions[6]);
     actor[actors].opacity=atoi(actions[7]); }
	 
	 if (!strcmp(actions[1], "reset")) {	  
      actorid=-1;	  
	  for (i=1;i<actors+1;i++) {
       if (!(strcmp(actions[2], actor[i].name)))
        actorid=i; }
      if(actorid>-1) {
	   ++activity;
	   place_actors(0, &actor[actorid]); 
	   actor[actorid].color=atoi(actions[3]);
       actor[actorid].x=atoi(actions[4]);
       actor[actorid].y=atoi(actions[5]);
	   actor[actorid].opacity=atoi(actions[6]); }  }  
		 	 
	 }
	 
  else if (actorid>0 && actor[actorid].opacity==VISIBLE) {
	  
   if (!strcmp(actions[1], "say")) {
     
	++activity;
    dialoguex=(actor[actorid].x>WINLIMIT_R-15) ? actor[actorid].x-15 : actor[actorid].x+1;
    dialoguey=(actor[actorid].y<WINLIMIT_U+5) ? actor[actorid].y+1 : actor[actorid].y-4;  
    draw_window(1, dialoguex, dialoguey, 15, 3, actor[actorid].name); 
	paint_window(dialoguex, dialoguey, 15, 3, 32);
    f=fopen("dialogue.txt", "w");
	 for (i=2;i<nwords;i++)
      fprintf(f, "%s ", actions[i]);
    fclose(f);
	print_in_window(2, dialoguex, dialoguey, 15, 3, "dialogue.txt");
	Sleep(2500);
	load_scene();
	
	}
 
   if (!strcmp(actions[1], "move")) {
	
	++activity;
	place_actors(0, &actor[actorid]);
	if (!strcmp(actions[2], "n")) {
	 actor[actorid].y--; }
    if (!strcmp(actions[2], "s")) {
	 actor[actorid].y++; }
    if (!strcmp(actions[2], "w")) {
	 actor[actorid].x--; }
	if (!strcmp(actions[2], "e")) {
	 actor[actorid].x++; }
	if (!strcmp(actions[2], "nw")) {
	 actor[actorid].y--;
     actor[actorid].x--; }
	if (!strcmp(actions[2], "ne")) {
	 actor[actorid].y--;
     actor[actorid].x++; }
	if (!strcmp(actions[2], "sw")) {
	 actor[actorid].y++;
     actor[actorid].x--; }
	if (!strcmp(actions[2], "se")) {
	 actor[actorid].y++;
     actor[actorid].x++; }  
	 
	 }

   }
  
 return activity;  
}

/* load current scenery file */
int load_scene() 
{
 FILE *f;	
	
  f=fopen(filenames[scene], "r");
	if (!(f))
	 return -1;
  fclose(f);
  print_in_window(0, WINLIMIT_L-1,WINLIMIT_U-1,WINLIMIT_R-WINLIMIT_L+2,WINLIMIT_D-WINLIMIT_U+2,filenames[scene]);

 return 0;  
}

void clear_scene()
{
 actors=0;
 scene=0; 
 moves=0;
 clear_string(title);
 win1 << setxy(WINLIMIT_L-1, WINLIMIT_U-2); 
 win1 << setattr(BLACK | BLACK) << "                                               ";
 draw_window(1,WINLIMIT_L-1,WINLIMIT_U-1,WINLIMIT_R-WINLIMIT_L+2,WINLIMIT_D-WINLIMIT_U+2,title);
 paint_window(WINLIMIT_L-1,WINLIMIT_U-1,WINLIMIT_R-WINLIMIT_L+2,WINLIMIT_D-WINLIMIT_U+2,' ');
} 

/* draw curtain, flags 1 to open, 2 to close */
void curtain(int flag)
{
  int wx, wx2, wheight;
  int i;
 
   switch (flag) {
	   
	case 1:
     wx=((WINLIMIT_R-WINLIMIT_L+2)/2)+(WINLIMIT_L-2);
     wheight=(WINLIMIT_D-WINLIMIT_U+2)-2;
     wx2=wx+2;
  
	 while (wx>WINLIMIT_L-1 || wx2<WINLIMIT_R-1) {
      draw_window(0, wx, WINLIMIT_U, 1, wheight, "");
	  draw_window(0, wx2, WINLIMIT_U, 1, wheight, "");
	  if (wx>WINLIMIT_L-1) 
	   --wx; 
      if (wx2<WINLIMIT_R-1)
	   ++wx2;
      Sleep(12.5);   }
	 break;
	  
	 case 2:
	  for (i=1;i<actors+1;i++)
       actor[i].opacity=INVISIBLE;
	  wx=WINLIMIT_L;
	  wheight=(WINLIMIT_D-WINLIMIT_U+2)-2;
	  wx2=WINLIMIT_R-1;
	  
	  while (wx<(((WINLIMIT_R-WINLIMIT_L+2)/2)+(WINLIMIT_L-2)) || wx2>((WINLIMIT_R-WINLIMIT_L+2)/2)+(WINLIMIT_L-2)) {
      draw_window(flag, wx, WINLIMIT_U, 1, wheight, "");
	  draw_window(flag, wx2, WINLIMIT_U, 1, wheight, "");
	  if (wx<((WINLIMIT_R-WINLIMIT_L+2)/2)+8) 
	   ++wx; 
      if (wx2>((WINLIMIT_R-WINLIMIT_L+2)/2)+8)
	   --wx2;
      Sleep(12.5);   }
     break; 
	 
	 }
} 
  
/* place actors in their coordinates, draw scenery */
void place_actors(int flag, struct object *actor)
{	
   object_limits(actor);
	
   win1 << setxy(actor->x, actor->y);
	 
   switch(flag) {
    case 0:  
	 win1 << setattr(BLACK | BLACK) << ' '; 	 
    break;
	case 1:
 	 win1 << setattr(actor->color) << actor->character;
	break; } 
}
	 
/* check if objects leave declared boundaries */	 
void object_limits(struct object *tempobject) 
{
   if (tempobject->x<WINLIMIT_L) tempobject->x=WINLIMIT_L;
   if (tempobject->x>WINLIMIT_R) tempobject->x=WINLIMIT_R;
   if (tempobject->y<WINLIMIT_U) tempobject->y=WINLIMIT_U;
   if (tempobject->y>WINLIMIT_D) tempobject->y=WINLIMIT_D;
}

/* show / hide cursor */
void showCursor(bool showFlag)
{   //enable/disable cursor visibility
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}