#ifndef STRUCTS_H
#define STRUCTS_H

#endif /* STRUCTS_H*/

#include <allegro5/allegro.h>

typedef struct {
        int maxFrame;
        int current;
        int delay;
        int w,h;

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

typedef struct {
        int x, y;
        bool live;
        int speed;
        int size;

}bullet;
