#ifndef STRUCTS_H
#define STRUCTS_H

#endif /* STRUCTS_H*/

#include <allegro5/allegro.h>

typedef enum  { DAMAGE, FAST, NORMAL}SHIPTYPE;
typedef enum  { BLUE, GREEN, ORANGE, RED}SHIPCOLOR;
typedef enum  { STATIC, FIRING_STATIC, MISSILE_STATIC, FIRING_DYNAMIC, FOLLOWING_DYNAMIC}ENEMYTYPE;



typedef struct {
        int maxFrame;
        int current;
        int delayTick,delayCount;
        int w,h;
        int x,y;    /*for collision detection with sprites*/
        int drawCenterX, drawCenterY;
        float scaleX, scaleY;
        ALLEGRO_BITMAP *image;
}sprite;



typedef struct {
        int speed;
        int x, y;
        bool live;
        int ammo;
        int bound;
        int lives;
        bool spawnable;


        sprite spr;

        SHIPTYPE type;




}ship;
