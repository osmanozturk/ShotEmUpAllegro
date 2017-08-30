#include <stdlib.h>
#include <stdio.h>

#include "ship.h"


#ifndef ANIMATION_H
#include "animation.h"
#endif

#ifndef COLDETECT_H
#include "coldetect.h"
#endif

#ifndef SHOOTING_H
#include "shooting.h"
#endif


/*====================================================================================================
Initializing ship from one huge spritesheet, got sheet coordinates from its xml file,
xml parsing will be used in the future instead of writing with hand, creating a bitmap
drawing inside it and changing  drawing target back to display,

There is three ship types and 4 different colors for each type
====================================================================================================*/


void initShip(ship *ship, ALLEGRO_BITMAP *sheet,  SHIPTYPE type, SHIPCOLOR color, ALLEGRO_DISPLAY *display) {
    int width = al_get_display_width(display);
    int height = al_get_display_height(display);


    switch (type) {
    case NORMAL:
        ship->live = true;
        ship->spr.w = 112;
        ship->spr.h = 75;
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width / 2;
        ship->y = height - (ship->spr.h)/2;
        ship->ammo = 10;
        ship->speed = 7;
        ship->bound = height * 5 / 8;
        ship->lives = 3;

        switch (color) {
        case BLUE:
            initSpriteFromSheet(&ship->spr, 112, 791, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case GREEN:
            initSpriteFromSheet(&ship->spr, 112, 866, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case ORANGE:
            initSpriteFromSheet(&ship->spr, 112, 716, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case RED:
            initSpriteFromSheet(&ship->spr, 0, 941, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        default:
            break;
        }

        break;
    case FAST:
        ship->live = true;
        ship->spr.w = 98;
        ship->spr.h = 75;
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width / 2;
        ship->y = height - (ship->spr.h)/2;
        ship->ammo = 7;
        ship->speed = 10;
        ship->bound = height * 5 / 8;
        ship->lives = 3;

        switch (color) {
        case BLUE:
            initSpriteFromSheet(&ship->spr, 325, 739, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case GREEN:
            initSpriteFromSheet(&ship->spr, 346, 75, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case ORANGE:
            initSpriteFromSheet(&ship->spr, 336, 309, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case RED:
            initSpriteFromSheet(&ship->spr, 325, 0, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        default:
            break;
        }

        break;
    case DAMAGE:
        ship->live = true;
        ship->spr.w = 99;
        ship->spr.h = 75;
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width / 2;
        ship->y = height - (ship->spr.h)/2;
        ship->ammo = 12;
        ship->speed = 5;
        ship->bound = height * 5 / 8;
        ship->lives = 3;

        switch (color) {
        case BLUE:
            initSpriteFromSheet(&ship->spr, 211, 941, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case GREEN:
            initSpriteFromSheet(&ship->spr, 237, 377, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case ORANGE:
            initSpriteFromSheet(&ship->spr, 247, 84, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        case RED:
            initSpriteFromSheet(&ship->spr, 224, 832, ship->spr.w, ship->spr.h, ship->spr.w/2, ship->spr.h/2, sheet, display, 1, 1);
            break;
        default:
            break;
        }

        break;


    default:
        ship->live = false;
        break;
    }
}

void drawShip(ship *ship) {
    al_draw_bitmap(ship->spr.image, ship->x - ship->spr.drawCenterX,
                   ship->y - ship->spr.drawCenterY, 0); /*Centered for upper left drawing*/
}


/*===================================================================================================================*/





void initEnemyShip(enemyShip *ship, ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr,
                   sprite *explosionSpr, ALLEGRO_SAMPLE_INSTANCE *laserInstance) {

    int width = al_get_display_width(display);
    int height = al_get_display_height(display);
    int random;

    /*srand(time(NULL));*/
    /*ship->spawnable = false;*/
    random = rand()%2;
    switch (random) {
    case 0:
        ship->type = STATIC;
        break;
    case 1:
        ship->type = FIRING_STATIC;
        break;
    default:
        break;
    }




    switch (ship->type) {

    case STATIC:

        ship->live = false;
        ship->spr.w = 82;
        ship->spr.h = 84;
        if (&ship->spr.image != NULL)
            al_destroy_bitmap(ship->spr.image); /*Destroying bitmap before creating new bitmap*/
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width/2;
        ship->y = height+1;
        ship->ammo = 0;
        ship->speed = 5;

        initSpriteFromSheet(&ship->spr, 518, 493, ship->spr.w, ship->spr.h,
                            ship->spr.w/2, ship->spr.h/2, sheet, display, 0.7, 0.8);
        break;

    case FIRING_STATIC:

        ship->live = false;
        ship->spr.w = 103;
        ship->spr.h = 84;
        if (&ship->spr.image != NULL)
            al_destroy_bitmap(ship->spr.image); /*Destroying bitmap before creating new bitmap*/
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width/2;
        ship->y = height+1;
        ship->ammo = 0;
        ship->laserAmount = 20;
        ship->laserInstance = laserInstance;
        ship->laserDelay = 35;
        ship->laserDelayCounter = 0;
        ship->laser = (bullet*)malloc(sizeof(bullet)*ship->laserAmount);
        initLaser(ship->laser, ship->laserAmount, laserSpr, explosionSpr, 1);
        ship->speed = 4;

        initSpriteFromSheet(&ship->spr, 144, 156, ship->spr.w, ship->spr.h,
                            ship->spr.w/2, ship->spr.h/2, sheet, display, 0.7, 0.8);

        break;
    case MISSILE_STATIC:

        break;
    case FIRING_DYNAMIC:

        break;
    case FOLLOWING_DYNAMIC:

        break;
    default:
        break;
    }

}







void updateEnemyShip(enemyShip **ship, int amount, int screenW, int screenH, int enemyDensity,int *densityCounter,
                     ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr, sprite *explosionSpr,
                     ALLEGRO_SAMPLE_INSTANCE *laserInstance) {

int i,random;


/*srand(time(NULL));*/
    *densityCounter +=1;




    for (i=0; i<amount; i++) {
        random = rand() % 2; /*randomizing spawn process a little*/

        switch (ship[i]->type) {

        case STATIC:
            staticUpdate(ship[i]);

            break;
        case FIRING_STATIC:
            firingStaticUpdate(ship[i], screenH);
        default:
            break;
        }

        if (!ship[i]->live && ship[i]->y > screenH && random  && *densityCounter >= enemyDensity ) {
            /*screenh rule prevents instant respawning*/


            ship[i]->y = - (ship[i]->spr.h)/2;
            ship[i]->x = ( (rand() % (screenW - 2*ship[i]->spr.w)) +ship[i]->spr.w );
            ship[i]->live = true;
            *densityCounter = 0;

        }



        if (ship[i]->live && ship[i]->y > screenH) {

            ship[i]->live = false;
            initEnemyShip(ship[i], sheet, display, laserSpr, explosionSpr, laserInstance);



        }

    }

}



void drawEnemyShip(enemyShip **ship, int amount) {
    int i;

    for (i=0; i<amount; i++) {
        if (ship[i]->live)
            al_draw_bitmap(ship[i]->spr.image, ship[i]->x, ship[i]->y, 0);
    }
}



void staticUpdate(enemyShip *ship){
    ship->y += ship->speed;
}
void firingStaticUpdate(enemyShip *ship, int screenH){
    ship->y += ship->speed;
    shootLaser(ship->laser, ship->laserAmount, &ship->laserDelayCounter, screenH,
                ship->x+(ship->spr.w)/2*ship->spr.scaleX, ship->y + ship->spr.h, ship->laserDelay, ship->laserInstance);
    updateLaser(ship->laser, ship->laserAmount, screenH);


}
void missileStaticUpdate(ship **ship, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter);
void firingDynamicUpdate(ship **ship, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter);
void followingDynamicUpdate(ship **ship, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter);














