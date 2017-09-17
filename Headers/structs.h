#ifndef STRUCTS_H
#define STRUCTS_H

#endif /* STRUCTS_H*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



typedef enum  { DAMAGE, FAST, NORMAL}SHIPTYPE;
typedef enum  { BLUE, GREEN, ORANGE, RED}SHIPCOLOR;
typedef enum  { STATIC, FIRING_STATIC, FIRING_DYNAMIC,
                MISSILE_STATIC, FOLLOWING_DYNAMIC, NOT_INITIALIZED}ENEMYTYPE;

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

