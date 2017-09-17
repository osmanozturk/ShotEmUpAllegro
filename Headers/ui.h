#ifndef UI_H
#define UI_H
#endif /* UI_H*/

#include <stdio.h>

#include <allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


typedef struct {
      char **usernames;
      int *scores;
      int maxLength;
      int boldIndex;
      int usernameLength;
}scoreboard;

void initScoreboard(scoreboard *board, int maxLength, int usernameLength);
int readScoreboard(char *filename, scoreboard *board);
void writeScoreboard(char *filename, scoreboard *board);
void sortScoreboard(scoreboard* board);
void addToScoreboard(scoreboard *board, int score, char *username);
void drawScoreboard(scoreboard *board, ALLEGRO_FONT* font, ALLEGRO_FONT* boldFont, int drawWidth, int drawHeight);
