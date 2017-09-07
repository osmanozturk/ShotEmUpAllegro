#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <math.h>
#include "shooting.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

#ifndef SHIP_H
#include "ship.h"
#endif

#ifndef ANIMATION_H
#include "animation.h"
#endif

#define M_PI_2 1.57079632679489661923 /*math.h constants not usable on ansi standard*/
void initLaser (bullet laser[], int amount, sprite *laserSpr, sprite *explosionSpr, int direction, int speed){
    int i;
    for (i = 0; i < amount; i++) {
        laser[i].live = false;
        laser[i].speed = speed;
        laser[i].speedY = speed;
        laser[i].y = -1;
        laser[i].direction = direction;
        laser[i].exploding = false;
        laser[i].spr = laserSpr;
        laser[i].explosionSpr = explosionSpr;
        laser[i].explosionSpr->delayTick = 5;

    }

}
void shootLaser (bullet laser[], int amount, int *delayCounter, int screenH, int posX, int posY,
                  int firingDelay, ALLEGRO_SAMPLE_INSTANCE *shootingSound) {

    int i,bulletIndex=0;

    *delayCounter+=1;

    for (i=0; i<amount; i++) {
        if (!laser[i].live && (laser[i].y < 0 || laser[i].y > screenH)) {
            bulletIndex = i;
        }
    }

    if (*delayCounter >= firingDelay && !laser[bulletIndex].live) {
        *delayCounter = 0;

        laser[bulletIndex].x = posX;
        laser[bulletIndex].y = posY;
        laser[bulletIndex].live = true;
        al_play_sample_instance(shootingSound);
    }


}
void updateLaser (bullet laser[], int amount, int screenH) {

    int i;


    for (i=0; i<amount; i++) {


        if (laser[i].y < 0 || laser[i].y > screenH)
            laser[i].live = false;

        if (!laser[i].exploding)
            laser[i].y += laser[i].speed*laser[i].direction;

    }

}

void drawLaser (bullet *laser, int amount) {
    int i;

    for (i=0; i<amount; i++) {
        if (laser[i].live) {
            al_draw_bitmap(laser[i].spr->image, laser[i].x - laser[i].spr->drawCenterX,
                           laser[i].y - 2*laser[i].spr->h, 0);
        }

         else if (laser[i].exploding) {
            if (drawAnimation(laser[i].explosionSpr, laser[i].x - laser[i].explosionSpr->drawCenterX,
                              laser[i].y + laser[i].explosionSpr->drawCenterY, false)) {
                /*drawanimation returns true if not in loop mode and finished playing*/
                laser[i].exploding = false;
            }
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
void initMissile (bullet missile[], int amount, sprite *missileSpr, sprite *explosionSpr, int speed, int direction) {
    int i;
    for (i = 0; i < amount; i++) {
        missile[i].live = false;
        missile[i].speed = speed;
        missile[i].y = -1;
        missile[i].direction = direction;
        missile[i].exploding = false;
        missile[i].spr = missileSpr;
        missile[i].explosionSpr = explosionSpr;
        missile[i].explosionSpr->delayTick = 5;
        missile[i].angle = 0;

    }
}

void shootMissile (bullet missile[], int amount, int *delayCounter, int screenH, int posX, int posY,
                  int firingDelay, ALLEGRO_SAMPLE_INSTANCE *shootingSound){

    int i,bulletIndex=0;

    *delayCounter+=1;

    for (i=0; i<amount; i++) {
        if (!missile[i].live && (missile[i].y < 0 || missile[i].y > screenH)) {
            bulletIndex = i;
        }
    }

    if (*delayCounter >= firingDelay && !missile[bulletIndex].live) {
        *delayCounter = 0;

        missile[bulletIndex].x = posX;
        missile[bulletIndex].y = posY;
        missile[bulletIndex].live = true;
        missile[bulletIndex].exploding = false;
        al_play_sample_instance(shootingSound);
    }
}

void updateMissile (bullet missile[], int amount, int screenW, int screenH, int targetX, int targetY) {
    int i;


    for (i=0; i<amount; i++) {


        if (missile[i].y < 0 || missile[i].y > screenH || missile[i].x < 0 || missile[i].x > screenW )
            missile[i].live = false;

        if (!missile[i].exploding && missile[i].live) {
            if (missile[i].y <= targetY)
            missileFollow(&missile[i],targetX, targetY);
            /*missile should continue on its way if misses*/

            missile[i].x += missile[i].speedX;
            missile[i].y += missile[i].speedY;

        }

    }
}

void drawMissile (bullet *missile, int amount) {
    int i;

    for (i=0; i<amount; i++) {
        if (missile[i].live) {
            al_draw_rotated_bitmap(missile[i].spr->image, missile[i].spr->w/2, missile[i].spr->h/2,
                missile[i].x, missile[i].y, missile[i].angle-(M_PI_2), 0);
            /*al_draw_bitmap(missile[i].spr->image, missile[i].x, missile[i].x, 0);*/
        }

         else if (missile[i].exploding) {
            if (drawAnimation(missile[i].explosionSpr, missile[i].x - missile[i].explosionSpr->drawCenterX,
                              missile[i].y + missile[i].explosionSpr->drawCenterY, false)) {
                /*drawanimation returns true if not in loop mode and finished playing*/
                missile[i].exploding = false;
            }
        }
    }
}

void missileFollow (bullet *missile, int targetX, int targetY) {

    missile->angle = atan2(targetY - missile->y, targetX - missile->x);
    missile->speedX = missile->speed * cos(missile->angle);
    missile->speedY = abs(missile->speed * sin(missile->angle));
    /*missile must continiue going further used abs for that purpose*/

}
