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
        int speedX, speedY;
        int x, y;
        bool live;
        int ammo; /*Missile ammo*/
        int bound;
        int lives;
        int laserDelay;
        int laserDelayCounter;
        int laserAmount;
        int pathCounter;
        int spawnTreshold;
        int followingDirection;
        int scorePts;
        sprite spr, *laserSpr, *explosionSpr;
        ENEMYTYPE type;
        bullet *laser;
        bullet *missile;
        ALLEGRO_SAMPLE_INSTANCE *laserInstance;

}enemyShip;


typedef struct {
        int speed;
        int x, y;
        bool live;
        int ammo;
        int bound;
        int lives;
        bool spawnable;


        sprite spr;
        bullet *beam;/*superpower*/
        SHIPTYPE type;

}playerShip;

enum { TRESHOLD , RANDOMNESS };

/*typedef enum  { EBLUE, EGREEN, EORANGE, EBLACK }ENEMYCOLOR;*/


/*====================================================================================================
User ship not has animation now,in the future bitmap will be changed to sprite and initanimation
will be used inside that function, ship type and color will be selectable from menu.

This header will also contain enemy ship operations
====================================================================================================*/

void initShip(playerShip *ship, ALLEGRO_BITMAP *sheet , SHIPTYPE type, SHIPCOLOR color, ALLEGRO_DISPLAY *display, sprite *beamSpr);




/*====================================================================================================
Can be merged into update functions later
====================================================================================================*/

void drawShip(playerShip *ship);




/*================================================================================================================*/




/*====================================================================================================
Can be merged into initShip function later
====================================================================================================*/

void initEnemyShip(enemyShip *ship, ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr, sprite *missileSpr, sprite *explosionSpr,
                   ALLEGRO_SAMPLE_INSTANCE *laserInstance, int enemyDeath, int spawnCredentials[][2]);

void updateEnemyShip(enemyShip **ship, playerShip *player, int amount, int screenW, int screenH, int enemyDensity, int *densityCounter,
                     ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, sprite *laserSpr, sprite *missileSpr, sprite *explosionSpr,
                     ALLEGRO_SAMPLE_INSTANCE *laserInstance, int enemyDeath, int spawnCredentials[][2]);

void drawEnemyShip(enemyShip **ship, int amount);



void staticUpdate(enemyShip *ship);
void firingStaticUpdate(enemyShip *ship, int screenH);
void missileStaticUpdate(enemyShip *ship, playerShip *player, int screenW, int screenH, int targetX, int targetY);
void firingDynamicUpdate(enemyShip *ship, int screenH);
void followingDynamicUpdate(enemyShip *ship, playerShip *player, int screenH);
