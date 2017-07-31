#ifndef COLDETECT_H
#define COLDETECT_H

#endif /* COLDETECT_H*/
#include <allegro5/allegro.h>
typedef struct
{
        float x;
        float y;
        float velX;
        float velY;
        int dirX;
        int dirY;
        int w;
        int h;

        ALLEGRO_BITMAP *image;

}Sprite;

int colliding(Sprite *s1, Sprite *s2);
int max(int a, int b);
int min(int a, int b);
