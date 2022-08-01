#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char version [3] = "1.1";
char date [16] = "07-31-22";

int main(){
  //Routine to Init NCurses
  initscr();
  cbreak();
  noecho();
  start_color();

  //Time Init Routine
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 83333333;    //Runs at 15FPS
  
  //Window-Size Math Routine
  int ymax,xmax,optpos;
  getmaxyx(stdscr,ymax,xmax);
  if(ymax < 15 || xmax < 72){  //Error-Check Routine
    clear();
    endwin();
    printf("\nError: ymax/xmax too low!\n");
    printf("\nymax:  %d\nxmax:  %d",ymax,xmax);
    printf("\nymax must be at least 14,\nxmax must be at least 72.\n\n");
    return 1;
  }
  optpos = (xmax - 72) / 2;

  //Main Menu Routine
  init_pair(8,COLOR_BLACK,COLOR_WHITE);
  init_pair(9,COLOR_CYAN,COLOR_CYAN);
  WINDOW * titlewin = newwin(12,72,2,optpos);
  wbkgd(stdscr,COLOR_PAIR(9));
  wattron(titlewin,COLOR_PAIR(8));
  wbkgd(titlewin,COLOR_PAIR(8));
  box(titlewin,0,0);

  //Information Routine
  mvwprintw(titlewin,1,25,"ACT's Rainbow Machine");
  mvwprintw(titlewin,2,29,"Version %s",version);
  mvwprintw(titlewin,3,31,"%s",date);
  mvwprintw(titlewin,4,22,"Press any key to start.");
  mvwprintw(titlewin,5,22,"Warning: may cause seizures.");
  mvwprintw(titlewin,6,24,"Do not use if epileptic.");
  mvwprintw(titlewin,9,13,"Copyright 2022, released under the GNU GPL 3.0"); 
  mvwprintw(titlewin,10,20,"https://github.com/act17/nrainbow");

  //Refresh & Getch With Clear
  refresh();
  wrefresh(titlewin);
  getch();
  clear();

  //Colour-Redefinition Routine
  init_color(COLOR_BLACK,1000,500,0);  //Redefined as orange.
  init_color(COLOR_WHITE,270,0,400);   //Redefined as indigo.
  init_color(COLOR_MAGENTA,470,0,70);  //Redefined as violet.

  //Colour Pairing Routine
  init_pair(1,COLOR_RED,COLOR_RED);
  init_pair(2,COLOR_BLACK,COLOR_BLACK);
  init_pair(3,COLOR_YELLOW,COLOR_YELLOW);
  init_pair(4,COLOR_GREEN,COLOR_GREEN);
  init_pair(5,COLOR_BLUE,COLOR_BLUE);
  init_pair(6,COLOR_WHITE,COLOR_WHITE);
  init_pair(7,COLOR_MAGENTA,COLOR_MAGENTA);

  //Window Creation
  WINDOW * rainbow = newwin(ymax,xmax,0,0);
  
  //Loop Routine
  while(1){
    for(int i = 1; i < 8; i++){
      wbkgd(rainbow,COLOR_PAIR(i));
      wrefresh(rainbow);
      nanosleep(&ts,&ts);
    }
  }
  return 0;
}
