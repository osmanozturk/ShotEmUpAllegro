#include "ui.h"
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


void initScoreboard(scoreboard *board, int maxLength, int usernameLength) {
    int i;
    board->boldIndex = -1;
    board->maxLength = maxLength;
    board->usernameLength = usernameLength;
    board->usernames = (char**)malloc(sizeof(char*)*maxLength);

    board->scores = (int*)malloc(sizeof(int)*maxLength);
    for (i=0;i<maxLength;i++) {
        board->usernames[i] = (char*)malloc(sizeof(char)*(usernameLength+1));/* +1 for null*/
        strcpy(board->usernames[i],"empty");
        board->scores[i] = 0;
    }
}
int readScoreboard(char *filename, scoreboard *board) {
    int i=0;
    char scan;

    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("error with opening score file\n in read func");
        return 0;
    }

    do {
        scan = fscanf(file, "%s %d\n", board->usernames[i], &board->scores[i]);
        i++;
    }while(scan!=EOF);
    fclose(file);
    return 1;
}
void writeScoreboard(char *filename, scoreboard *board) {
    int i;
    FILE *file = fopen(filename, "w+");
    if (file == NULL)
        printf("error with opening score file\n in write func");

    for (i=0;i<board->maxLength;i++) {
        fprintf(file, "%s %d\n", board->usernames[i], board->scores[i]);

    }
    fclose(file);
}
void sortScoreboard(scoreboard* board) {
    int tempInt, i,j;
    char *tempStr = (char*)malloc(sizeof(char)*(board->usernameLength+1));
    /*char tempStr[9];*/
    board->boldIndex = board->maxLength-1;
    /*Last element of the board is always recent
    score at start since we are inserting it from latest index always*/

    for(i=0;i<board->maxLength-1;i++) {

        for (j=0;j<board->maxLength-i-1;++j) {

            if (board->scores[j+1] > board->scores[j]) {
                if ((j+1) == board->boldIndex)
                    board->boldIndex-=1;
                /*
                If we are moving the recent score index
                updating its position for printing it bold
                */

                tempInt = board->scores[j+1];
                strcpy(tempStr, board->usernames[j+1]);

                board->scores[j+1] = board->scores[j];
                strcpy(board->usernames[j+1], board->usernames[j]);

                board->scores[j] = tempInt;
                strcpy(board->usernames[j], tempStr);
            }


        }
    }
    free(tempStr);
}
void addToScoreboard(scoreboard *board, int score, char *username) {

    sortScoreboard(board);
    if (board->scores[board->maxLength-1] < score) {
        board->scores[board->maxLength-1] = score;
        strcpy(board->usernames[board->maxLength-1], username);
        sortScoreboard(board);
    }
}

void drawScoreboard(scoreboard *board, ALLEGRO_FONT* font, ALLEGRO_FONT* boldFont, int drawWidth, int drawHeight) {
    int i;

    al_draw_text(boldFont,al_map_rgb(210,255,190), drawWidth, drawHeight - 40,
                 ALLEGRO_ALIGN_CENTER, "HIGH SCORES");

    for (i=0;i<board->maxLength;i++) {
        if (i == board->boldIndex) {
            al_draw_textf(boldFont,al_map_rgb(255,255,255), drawWidth,drawHeight,
                          ALLEGRO_ALIGN_CENTER, "%s: %d",board->usernames[i], board->scores[i]);
            drawHeight+=al_get_font_line_height(font);
        }
        else {

            al_draw_textf(font,al_map_rgb(255,255,255), drawWidth, drawHeight,
                          ALLEGRO_ALIGN_CENTER, "%s: %d",board->usernames[i], board->scores[i]);
                    drawHeight+=al_get_font_line_height(font);
        }
    }


}
