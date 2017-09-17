#ifndef SHOOTING_H
#define SHOOTING_H

#endif /* SHOOTING_H*/

#include <math.h>

#include <allegro5/allegro_audio.h>

#ifndef STRUCTS_H
#include "structs.h"
#endif


typedef struct {
    int x, y;
    bool live;
    int speed;
    bool exploding;
    int direction;
    double angle;
    double speedX, speedY;

    sprite *spr;
    sprite *explosionSpr;


}bullet;



/*====================================================================================================
Initializes lasers as false and assigns speed values
====================================================================================================*/

void initLaser (bullet laser[], int amount, sprite *laserSpr, sprite *explosionSpr, int direction, int speed);




/*====================================================================================================
shoots laser according to given delay actual shooting process is handling by updatelaser this function
simply just creates them
====================================================================================================*/

void shootLaser (bullet laser[], int amount, int *delayCounter, int screenH, int posX, int posY,
                  int firingDelay, ALLEGRO_SAMPLE_INSTANCE *shootingSound);


/*====================================================================================================
Shoots a laser according to delay and updates the position of already shot lasers, delay is in
frames considering constant 60 fps and drawing point can be included to prototype
====================================================================================================*/

void updateLaser (bullet laser[], int amount, int screenH);



/*====================================================================================================
Draws lasers but drawing lasers little bit back from ship's nose causes late shooting effect
that should be investigated later
====================================================================================================*/

void drawLaser (bullet *laser, int amount);


/*-------------------------------------------------------------------------------------------------------------------*/


/*====================================================================================================
Initializes missiles
====================================================================================================*/

void initMissile (bullet missile[], int amount, sprite *missileSpr, sprite *explosionSpr, int speed, int direction);




/*====================================================================================================
Shoots missile according to given delay actual shooting and following process is handling by
updatemissile this function simply just creates them
====================================================================================================*/

void shootMissile (bullet missile[], int amount, int *delayCounter, int screenH, int posX, int posY,
                  int firingDelay, ALLEGRO_SAMPLE_INSTANCE *shootingSound);



/*====================================================================================================
Shoots a missile according to delay and updates the position of already shot lasers, delay is in
frames considering constant 60 fps and drawing point can be included to prototype
====================================================================================================*/

void updateMissile (bullet missile[], int amount, int screenW, int screenH, int targetX, int targetY);



/*====================================================================================================
Draws missiles to the screen with calculaten angle
====================================================================================================*/

void drawMissile (bullet *missile, int amount);





void missileFollow (bullet *missile, int targetX, int targetY);
