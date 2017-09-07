#ifndef ANIMATION_H
#define ANIMATION_H

#endif /* ANIMATION_H*/
#ifndef STRUCTS_H
#include "structs.h"
#endif


typedef struct {
    int x, y;
    int w, h;
    int velX, velY;
    int dirX, dirY;

    ALLEGRO_BITMAP *image;

}background;

/*====================================================================================================
Initializes single frame sprite from given file
====================================================================================================*/

void initSpriteFromFile(sprite *spr, float drawCenterX, float drawCenterY, char *filename,
                         ALLEGRO_DISPLAY *display, float scaleX, float scaleY, float angle);


/*====================================================================================================
Initializes single frame sprite from main spritesheet
====================================================================================================*/

void initSpriteFromSheet(sprite *spr, int posX, int posY, int w, int h,
                         float drawX, float drawY, ALLEGRO_BITMAP *sheet, ALLEGRO_DISPLAY *display, float scaleX, float scaleY);




/*====================================================================================================
Initializes animation sprite with desired frame delay value, spritesheet must contain single row
Delaytick is in frames game runs at 60fps delay value should be calculated considering this
====================================================================================================*/

void initAnimation(sprite *spr, int maxF, int delayTick, float drawCenterX, float drawCenterY, char filename[]);





/*====================================================================================================
Draws animation sprite with desired frame delay, sprite itself contains that values, drawX and drawY
contains drawing point of the sprite, ex: thruster animation is drawing from center of its top.

if the animation is not looping returns true when animation ends
====================================================================================================*/

bool drawAnimation(sprite *spr, int drawX, int drawY, bool loop);



/*===================================================================================================================*/



/*====================================================================================================
Initializes background image, x and y value based on bottom left corner background image should be
bigger than screen size for proper non-gap scrolling
====================================================================================================*/

void initBackground(background *bg, int x, int y, int dirX, int dirY, int velX, int velY, char* filename);




/*====================================================================================================
Updates background image on given direction and speed for parallax effect
====================================================================================================*/

void updateBackground(background *bg, int screenH);




/*====================================================================================================
Draws background image with repeating it
====================================================================================================*/

void drawBackground(background *bg);
