#include "../typedefs.hpp"
#include "ncurses.h"
#include "stdio.h"
#include <unistd.h>

void InitScreen() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
}

void InitColors() {
  if (has_colors()) {
    start_color();
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
  }
}

int main() {
  InitScreen();
  InitColors();

  s32 x = 0;
  s32 y = 0;
  char player = '@';
  while (true) {
    clear();

    // Input
    char c = getch();
    if (c == 'h') {
      x -= 1;
    } else if (c == 'j') {
      y += 1;
    } else if (c == 'k') {
      y -= 1;
    } else if (c == 'l') {
      x += 1;
    }

    // Render
    attron(COLOR_PAIR(COLOR_RED));
    mvaddch(y, x, player);
    attroff(COLOR_PAIR(COLOR_RED));

    refresh();
    usleep(30000);
  }

  endwin();
  return 0;
}
