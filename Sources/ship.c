#include <stdlib.h>
#include <time.h>

#include "ship.h"
/*#include "structs.h"*/

#ifndef ANIMATION_H
#include "animation.h"
#endif

#ifndef COLDETECT_H
#include "coldetect.h"
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





void initEnemyShip(ship **ship, int amount,  ALLEGRO_BITMAP *sheet,  ENEMYTYPE type, ENEMYCOLOR color, ALLEGRO_DISPLAY *display) {

    int width = al_get_display_width(display);
    int height = al_get_display_height(display);
    int i;

    srand(time(NULL));


    for (i=0; i<amount; i++) {



        switch (type) {

        case STATIC:
            ship[i]->live = false;
            ship[i]->spr.w = 103;
            ship[i]->spr.h = 84;
            ship[i]->spr.image = al_create_bitmap(ship[i]->spr.w, ship[i]->spr.h);
            ship[i]->x = width/2;
            ship[i]->y = height+1;
            ship[i]->ammo = 0;
            ship[i]->speed = 4;


            switch (color) {
            case EBLUE:
                initSpriteFromSheet(&ship[i]->spr, 0, 739, ship[i]->spr.w, ship[i]->spr.h,
                                    ship[i]->spr.w/2, ship[i]->spr.h/2, sheet, display, 1, 1);
                break;
            case EGREEN:
                initSpriteFromSheet(&ship[i]->spr, 346, 75, ship[i]->spr.w, ship[i]->spr.h,
                                    ship[i]->spr.w/2, ship[i]->spr.h/2, sheet, display, 1, 1);
                break;
            case EORANGE:
                initSpriteFromSheet(&ship[i]->spr, 336, 309, ship[i]->spr.w, ship[i]->spr.h,
                                    ship[i]->spr.w/2, ship[i]->spr.h/2, sheet, display, 1, 1);
                break;
            case EBLACK:
                initSpriteFromSheet(&ship[i]->spr, 144, 156, ship[i]->spr.w, ship[i]->spr.h,
                                    ship[i]->spr.w/2, ship[i]->spr.h/2, sheet, display, 0.7, 0.8);
                break;
            default:
                break;
            }

            break;
        case FIRING_STATIC:

            break;
        case MISSILE_STATIC:

            break;
        case FIRING_DYNAMIC:

            break;
        case MISSILE_DYNAMIC:

            break;
        default:
            break;
        }
    }





}


void updateEnemyShip(ship **ship, int amount, int screenW, int screenH) {
    int i,random;


    srand(time(NULL));

    for (i=0; i<amount; i++) {
        random = rand() % 500;
        ship[i]->y += ship[i]->speed;



        if (ship[i]->live && ship[i]->y > screenH) {

            ship[i]->live=false;
            /*ship[i]->y = - (ship[i]->spr.h)/2;
            ship[i]->x = ( (rand() % (screenW - 2*ship[i]->spr.w)) +ship[i]->spr.w );*/
        }

        else if (!ship[i]->live && ship[i]->y > screenH && random < 15) {/*screenh rule prevents from instant respawning*/
            ship[i]->y = - (ship[i]->spr.h)/2;
            ship[i]->x = ( (rand() % (screenW - 2*ship[i]->spr.w)) +ship[i]->spr.w );
            /*for (j=0; j<amount; j++) {
                if (i != j && ship[j]->live &&
                        boxCollision(&ship[i]->spr, &ship[j]->spr, ship[i]->x, ship[i]->y, ship[j]->x, ship[j]->y) ) {
                    inside = true;
                    break;
                }
            }
                if (!inside) */
            ship[i]->live = true;



        }



    }

}

void drawEnemyShip(ship **ship, int amount) {
    int i;

    for (i=0; i<amount; i++) {
        if (ship[i]->live)
            al_draw_bitmap(ship[i]->spr.image, ship[i]->x, ship[i]->y, 0);
    }
}
