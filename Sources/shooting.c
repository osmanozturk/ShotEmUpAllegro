#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include "shooting.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

void initLaser (bullet laser[], int amount){
    int i;
    for (i = 0; i < amount; i++) {
        laser[i].live = false;
        laser[i].speed = 8;
        laser[i].y = -1;

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
            laser[i].y -= laser[i].speed;
            if (laser[i].y < 0)
                laser[i].live = false;
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

void drawLaser (bullet laser[], int amount, sprite *laserSprite) {
    int i;

    for (i=0; i<amount; i++) {
        if (laser[i].live) {
            al_draw_bitmap(laserSprite->image, laser[i].x - laserSprite->drawCenterX, laser[i].y - 2*laserSprite->h, 0);
        }
    }
}




