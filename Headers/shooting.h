#ifndef SHOOTING_H
#define SHOOTING_H

#endif /* SHOOTING_H*/

#ifndef STRUCTS_H
#include "structs.h"
#endif

typedef struct {
    int x, y;
    bool live;
    int speed;
    bool exploding;

    sprite *laserSpr;
    sprite *explosionSpr;


}bullet;

/*====================================================================================================
Initializes lasers as false and assigns speed values
====================================================================================================*/

void initLaser (bullet laser[], int amount, sprite *laserSpr, sprite *explosionSpr);




/*====================================================================================================
Shoots a laser according to delay and updates the position of already shot lasers, delay is in
frames considering constant 60 fps and drawing point can be included to prototype
====================================================================================================*/

void updateLaser (bullet laser[], int amount, int *delayCounter, int firingDelay, ship *ship, ALLEGRO_SAMPLE_INSTANCE *shootingSound);



/*====================================================================================================
Draws lasers but drawing lasers little bit back from ship's nose causes late shooting effect
that should be investigated later
====================================================================================================*/

void drawLaser (bullet laser[], int amount);
