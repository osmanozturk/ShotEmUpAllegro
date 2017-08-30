#ifndef SHIP_H
#define SHIP_H

#endif /*SHIP_H*/



#ifndef STRUCTS_H
#include "structs.h"
#endif
#ifndef SHOOTING_H
#include "shooting.h"
#endif

typedef struct {
        int speed;
        int x, y;
        bool live;
        int ammo;
        int bound;
        int lives;
        int laserDelay;
        int laserDelayCounter;
        int laserAmount;

        sprite spr, *laserSpr, *explosionSpr;
        ENEMYTYPE type;
        bullet *laser;
        ALLEGRO_SAMPLE_INSTANCE *laserInstance;

}enemyShip;





/*typedef enum  { EBLUE, EGREEN, EORANGE, EBLACK }ENEMYCOLOR;*/


/*====================================================================================================
User ship not has animation now,in the future bitmap will be changed to sprite and initanimation
will be used inside that function, ship type and color will be selectable from menu.

This header will also contain enemy ship operations
====================================================================================================*/

void initShip(ship *ship, ALLEGRO_BITMAP *sheet , SHIPTYPE type, SHIPCOLOR color, ALLEGRO_DISPLAY *display);




/*====================================================================================================
Can be merged into update functions later
====================================================================================================*/

void drawShip(ship *ship);




/*================================================================================================================*/




/*====================================================================================================
Can be merged into initShip function later
====================================================================================================*/

void initEnemyShip(enemyShip *ship, ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr, sprite *explosionSpr, ALLEGRO_SAMPLE_INSTANCE *laserInstance);
void updateEnemyShip(enemyShip **ship, int amount,
                     int screenW, int screenH, int enemyDensity, int *densityCounter, ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr, sprite *explosionSpr, ALLEGRO_SAMPLE_INSTANCE *laserInstance);
void drawEnemyShip(enemyShip **ship, int amount);



void staticUpdate(enemyShip *ship);
void firingStaticUpdate(enemyShip *ship, int screenH);
void missileStaticUpdate(ship **ship, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter);
void firingDynamicUpdate(ship **ship, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter);
void followingDynamicUpdate(ship **ship, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter);

