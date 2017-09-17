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


void initShip(playerShip *ship, ALLEGRO_BITMAP *sheet,  SHIPTYPE type, SHIPCOLOR color, ALLEGRO_DISPLAY *display,
              sprite *beamSpr) {
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

        ship->beam = (bullet*)malloc(sizeof(bullet)); /*Superpower laser beam is just one laser*/
        initLaser(ship->beam, 1, beamSpr, NULL, 1,0);


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

void drawShip(playerShip *ship) {
    al_draw_bitmap(ship->spr.image, ship->x - ship->spr.drawCenterX,
                   ship->y - ship->spr.drawCenterY, 0); /*Centered for upper left drawing*/
}


/*===================================================================================================================*/





void initEnemyShip(enemyShip *ship, ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr, sprite *missileSpr,
                   sprite *explosionSpr, ALLEGRO_SAMPLE_INSTANCE *laserInstance, int enemyDeath, int spawnCredentials[][2]) {

    int width = al_get_display_width(display);
    int height = al_get_display_height(display);
    int random;
    bool selected = false;



            /*randomness of harder enemies will be get lower over time*/

    if (spawnCredentials[FOLLOWING_DYNAMIC][TRESHOLD] <= enemyDeath && !selected) {
        random = rand()%spawnCredentials[FOLLOWING_DYNAMIC][RANDOMNESS];
        if (random == 0) {
            ship->type = FOLLOWING_DYNAMIC;
            selected = true;

        }
    }

    if (spawnCredentials[MISSILE_STATIC][TRESHOLD] <= enemyDeath && !selected) {
        random = rand()%spawnCredentials[MISSILE_STATIC][RANDOMNESS];
        if (random == 0){
            ship->type = MISSILE_STATIC;
            selected = true;
        }
    }

    if (spawnCredentials[FIRING_DYNAMIC][TRESHOLD] <= enemyDeath && !selected) {
        random = rand()%spawnCredentials[FIRING_DYNAMIC][RANDOMNESS];
        if (random == 0){
            ship->type = FIRING_DYNAMIC;
            selected = true;
        }
    }

    if (spawnCredentials[FIRING_STATIC][TRESHOLD] <= enemyDeath && !selected) {
        random = rand()%spawnCredentials[FIRING_STATIC][RANDOMNESS];
        if (random == 0) {
            ship->type = FIRING_STATIC;
            selected = true;
        }
    }
    if (spawnCredentials[STATIC][TRESHOLD] <= enemyDeath  && !selected) {
        random = rand()%spawnCredentials[STATIC][RANDOMNESS];
        if (random == 0){
            ship->type = STATIC;
            selected = true;
        }
    }



    switch (ship->type) {

    case STATIC:
        ship->scorePts = 1;
        ship->lives = 3;
        ship->live = false;
        ship->spr.w = 82;
        ship->spr.h = 84;
        if (&ship->spr.image != NULL)
            al_destroy_bitmap(ship->spr.image); /*Destroying bitmap before creating new bitmap*/
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width/2;
        ship->y = height+1;
        ship->ammo = 0;
        ship->speedY = 5;
        ship->speedX = 5;

        initSpriteFromSheet(&ship->spr, 518, 493, ship->spr.w, ship->spr.h,
                            ship->spr.w/2, ship->spr.h/2, sheet, display, 0.7, 0.8);
        break;

    case FIRING_STATIC:
        ship->scorePts = 2;
        ship->lives = 3;
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
        if (ship->laser != NULL) {
            free(ship->laser);
        }
        ship->laser = (bullet*)malloc(sizeof(bullet)*ship->laserAmount);
        initLaser(ship->laser, ship->laserAmount, laserSpr, explosionSpr, 1, 8);
        ship->speedY = 4;
        ship->speedX = 4;

        initSpriteFromSheet(&ship->spr, 144, 156, ship->spr.w, ship->spr.h,
                            ship->spr.w/2, ship->spr.h/2, sheet, display, 0.7, 0.8);
        break;

    case FIRING_DYNAMIC:
        ship->scorePts = 3;
        ship->lives = 3;
        ship->live = false;
        ship->spr.w = 97;
        ship->spr.h = 84;
        if (&ship->spr.image != NULL)
            al_destroy_bitmap(ship->spr.image); /*Destroying bitmap before creating new bitmap*/
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width/2;
        ship->y = height+1;
        ship->ammo = 0;
        ship->pathCounter = 0;
        ship->laserAmount = 20;
        ship->laserInstance = laserInstance;
        ship->laserDelay = 20;
        ship->laserDelayCounter = 0;
        if (ship->laser != NULL) {
            free(ship->laser);
        }
        ship->laser = (bullet*)malloc(sizeof(bullet)*ship->laserAmount);
        initLaser(ship->laser, ship->laserAmount, laserSpr, explosionSpr, 1, 12);
        ship->speedY = 4;
        ship->speedX = 2;

        initSpriteFromSheet(&ship->spr, 423, 644, ship->spr.w, ship->spr.h,
                            ship->spr.w/2, ship->spr.h/2, sheet, display, 0.7, 0.7);
        break;

    case MISSILE_STATIC:
        ship->scorePts = 5;
        ship->lives = 3;
        ship->live = false;
        ship->spr.w = 104;
        ship->spr.h = 84;
        if (&ship->spr.image != NULL)
            al_destroy_bitmap(ship->spr.image); /*Destroying bitmap before creating new bitmap*/
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width/2;
        ship->y = height+1;
        ship->ammo = 1;
        ship->laserAmount = 20;
        ship->laserInstance = laserInstance;
        ship->laserDelay = 35;
        ship->laserDelayCounter = 0;
        ship->speedX = 0;
        ship->speedY = 0;
        if (ship->missile != NULL) {
            free(ship->laser);
        }
        ship->missile = (bullet*)malloc(sizeof(bullet)*ship->ammo);
        initMissile(ship->missile, ship->ammo, missileSpr, explosionSpr, 6, 1);
        ship->speedY = 3;
        ship->speedX = 0;

        initSpriteFromSheet(&ship->spr, 120, 604, ship->spr.w, ship->spr.h,
                            ship->spr.w/2, ship->spr.h/2, sheet, display, 0.7, 0.7);
        break;
    case FOLLOWING_DYNAMIC:
        ship->scorePts = 6;
        ship->lives = 3;
        ship->live = false;
        ship->spr.w = 93;
        ship->spr.h = 84;
        if (&ship->spr.image != NULL)
            al_destroy_bitmap(ship->spr.image); /*Destroying bitmap before creating new bitmap*/
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = width/2;
        ship->y = height+1;
        ship->ammo = 0;
        ship->pathCounter = 0;
        ship->laserAmount = 20;
        ship->laserInstance = laserInstance;
        ship->laserDelay = 20;
        ship->laserDelayCounter = 0;
        if (ship->laser != NULL) {
            free(ship->laser);
        }
        ship->laser = (bullet*)malloc(sizeof(bullet)*ship->laserAmount);
        initLaser(ship->laser, ship->laserAmount, laserSpr, explosionSpr, 1, 12);
        ship->speedY = 5;
        ship->speedX = 2;

        initSpriteFromSheet(&ship->spr, 425, 468, ship->spr.w, ship->spr.h,
                            ship->spr.w/2, ship->spr.h/2, sheet, display, 0.7, 0.7);
        break;

    default:
        break;
    }

}







void updateEnemyShip(enemyShip **ship, playerShip *player, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter,
                     ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr, sprite *missileSpr, sprite *explosionSpr,
                     ALLEGRO_SAMPLE_INSTANCE *laserInstance, int enemyDeath, int spawnCredentials[][2]) {

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
            break;

        case FIRING_DYNAMIC:
            firingDynamicUpdate(ship[i], screenH);
            break;

        case MISSILE_STATIC:
            missileStaticUpdate(ship[i], player, screenW, screenH, player->x, player->y);
            break;

        case FOLLOWING_DYNAMIC:
            followingDynamicUpdate(ship[i], player, screenH);
            break;

        default:
            break;
        }
        if (ship[i]->lives == 0) {
            ship[i]->live = false;
        }

        if (!ship[i]->live && ship[i]->y > screenH && random  && *densityCounter >= enemyDensity ) {
            /*screenh rule prevents instant respawning*/


            ship[i]->y = - (ship[i]->spr.h)/2;
            ship[i]->x = ( (rand() % (screenW - 2*ship[i]->spr.w)) +ship[i]->spr.w );
            ship[i]->lives = 3;
            ship[i]->live = true;
            *densityCounter = 0;

        }



        if (ship[i]->live && ship[i]->y > screenH) {

            ship[i]->live = false;
            initEnemyShip(ship[i], sheet, display, laserSpr, missileSpr, explosionSpr, laserInstance, enemyDeath, spawnCredentials);

        }

        /*preventing from going outside of the screen*/
        if (ship[i]->x - ship[i]->spr.w * ship[i]->spr.scaleX < 0)
            ship[i]->x = ship[i]->spr.w * ship[i]->spr.scaleX;
        else if (ship[i]->x + ship[i]->spr.w * ship[i]->spr.scaleX > screenW)
            ship[i]->x = screenW - ship[i]->spr.w * ship[i]->spr.scaleX;


    }

}



void drawEnemyShip(enemyShip **ship, int amount) {
    int i;

    for (i=0; i<amount; i++) {
        if (ship[i]->live && ship[i]->type != NOT_INITIALIZED)
            al_draw_bitmap(ship[i]->spr.image, ship[i]->x, ship[i]->y, 0);
    }
}



void staticUpdate(enemyShip *ship){
    ship->y += ship->speedY;
}
void firingStaticUpdate(enemyShip *ship, int screenH){
    ship->y += ship->speedY;
    if (ship->live) {
        shootLaser(ship->laser, ship->laserAmount, &ship->laserDelayCounter, screenH, ship->x+(ship->spr.w)/2*ship->spr.scaleX,
                   ship->y + 2*ship->spr.h*ship->spr.scaleY, ship->laserDelay, ship->laserInstance);
    }
    updateLaser(ship->laser, ship->laserAmount, screenH);


}
void missileStaticUpdate(enemyShip *ship, playerShip *player, int screenW, int screenH, int targetX, int targetY) {
    ship->y += ship->speedY;

    if (ship->live && ship->y+(ship->spr.h*ship->spr.scaleY) < player->y - (player->spr.h*player->spr.scaleY)) {
        shootMissile(ship->missile, ship->ammo, &ship->laserDelayCounter, screenH, ship->x+(ship->spr.w)/2*ship->spr.scaleX,
                   ship->y + ship->spr.h*ship->spr.scaleY, ship->laserDelay, ship->laserInstance);

    }

    updateMissile(ship->missile, ship->ammo, screenW, screenH, targetX, targetY);
}

void firingDynamicUpdate(enemyShip *ship, int screenH) {
    ship->y += ship->speedY;

    if (ship->pathCounter < 80)
        ship->x += ship->speedX;
    else if (ship->pathCounter < 160)
        ship->x -= ship->speedX;
    else
        ship->pathCounter = 0;

    ship->pathCounter += 1;

    if (ship->live) {
        shootLaser(ship->laser, ship->laserAmount, &ship->laserDelayCounter, screenH, ship->x+(ship->spr.w)/2*ship->spr.scaleX,
                   ship->y + 2*ship->spr.h*ship->spr.scaleY+1, ship->laserDelay, ship->laserInstance);
    }
    updateLaser(ship->laser, ship->laserAmount, screenH);

}
void followingDynamicUpdate(enemyShip *ship, playerShip *player, int screenH) {

    ship->y += ship->speedY;


    if  (player->x > ship->x+ship->spr.w/2*ship->spr.scaleX)
        /*if right side of the enemy ship is more left than the player's left side*/
        ship->followingDirection = 1;


    else if  (player->x < ship->x+ship->spr.w/2*ship->spr.scaleX)
        /*if left side of the enemy ship is more right than the player's left side*/
        ship->followingDirection = -1;

    else if (player->x == ship->x+ship->spr.w/2*ship->spr.scaleX)
         ship->followingDirection = 0;

    ship->x += ship->followingDirection * ship->speedX;

    if (ship->live) {
        shootLaser(ship->laser, ship->laserAmount, &ship->laserDelayCounter, screenH, ship->x+(ship->spr.w)/2*ship->spr.scaleX,
                   ship->y + 2*ship->spr.h*ship->spr.scaleY+1, ship->laserDelay, ship->laserInstance);
    }
    updateLaser(ship->laser, ship->laserAmount, screenH);
}














