#ifndef STRUCTS_H
#define STRUCTS_H

#endif /* STRUCTS_H*/

#include <allegro5/allegro.h>

typedef struct {
        int maxFrame;
        int current;
        int delayTick,delayCount;
        int w,h;
        int x,y;    /*for collision detection with sprites*/
        int drawCenterX,drawCenterY;
        ALLEGRO_BITMAP *image;
}sprite;

typedef struct {
        int speed;
        int x, y;
        bool live;
        int ammo;
        int bound;
        sprite spr;
}ship;

typedef struct {
        int speed;
        int colx, coly;
        int x, y;
        bool live;
        int ammo;
        int amount;

}comet;

