#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include "shooting.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

#ifndef ANIMATION_H
#include "animation.h"
#endif

void initLaser (bullet laser[], int amount, sprite *laserSpr, sprite *explosionSpr){
    int i;
    for (i = 0; i < amount; i++) {
        laser[i].live = false;
        laser[i].speed = 8;
        laser[i].y = -1;
        laser[i].exploding = false;
        laser[i].laserSpr = laserSpr;
        laser[i].explosionSpr = explosionSpr;
        laser[i].explosionSpr->delayTick = 5;

    }

}

void updateLaser (bullet laser[], int amount, int *delayCounter, int firingDelay, ship *ship,
                  ALLEGRO_SAMPLE_INSTANCE *shootingSound) {

    int i,bulletIndex;


    for (i=0; i<amount; i++) {
        if (!laser[i].live && laser[i].y < 0) {
            bulletIndex = i;
            al_play_sample_instance(shootingSound);
        }

        else {

            if (laser[i].y < 0)
                laser[i].live = false;

            if (!laser[i].exploding)
                laser[i].y -= laser[i].speed;
        }


    }

    *delayCounter+=1;
    if (*delayCounter >= firingDelay) {
        *delayCounter = 0;

        laser[bulletIndex].x = ship->x;
        laser[bulletIndex].y = ship->y;
        laser[bulletIndex].live = true;

    }


}

void drawLaser (bullet laser[], int amount) {
    int i;

    for (i=0; i<amount; i++) {
        if (laser[i].live) {
            al_draw_bitmap(laser[i].laserSpr->image, laser[i].x - laser[i].laserSpr->drawCenterX,
                           laser[i].y - 2*laser[i].laserSpr->h, 0);
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




