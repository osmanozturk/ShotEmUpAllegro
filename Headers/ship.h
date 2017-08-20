#ifndef SHIP_H
#define SHIP_H

#endif /*SHIP_H*/



#ifndef STRUCTS_H
#include "structs.h"
#endif

typedef enum  { DAMAGE, FAST, NORMAL }SHIPTYPE;
typedef enum  { BLUE, GREEN, ORANGE, RED}SHIPCOLOR;


typedef enum  { STATIC, FIRING_STATIC, MISSILE_STATIC, FIRING_DYNAMIC, MISSILE_DYNAMIC  }ENEMYTYPE;
typedef enum  { EBLUE, EGREEN, EORANGE, EBLACK }ENEMYCOLOR;


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

void initEnemyShip(ship **ship, int amount, ALLEGRO_BITMAP *sheet,  ENEMYTYPE type, ENEMYCOLOR color, ALLEGRO_DISPLAY *display);
void updateEnemyShip(ship **ship, int amount, int screenW, int screenH);
void drawEnemyShip(ship **ship, int amount);
