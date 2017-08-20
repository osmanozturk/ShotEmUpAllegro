#include <allegro5/allegro.h>

#include "animation.h"
/*#include "structs.h"*/

void initSpriteFromSheet(sprite *spr, int posX, int posY, int w, int h,
                         float drawCenterX, float drawCenterY, ALLEGRO_BITMAP *sheet,
                         ALLEGRO_DISPLAY *display, float scaleX, float scaleY) {

    ALLEGRO_TRANSFORM firstTrans, scaler;
    al_copy_transform(&firstTrans, al_get_current_transform());
    al_identity_transform(&scaler);
    al_scale_transform(&scaler,scaleX, scaleY);
    /*drawing sprite*/
    spr->image = al_create_bitmap(w,h);
    al_set_target_bitmap(spr->image);


    al_use_transform(&scaler);
    al_draw_bitmap_region(sheet, posX, posY, w, h, 0, 0, 0);
    al_use_transform(&firstTrans);
    al_set_target_backbuffer(display);

    spr->delayTick = 0;
    spr->maxFrame = 1;
    spr->w = w;
    spr->h = h;
    spr->current = 0;
    spr->delayCount = 0;

    spr->drawCenterX = drawCenterX;
    spr->drawCenterY = drawCenterY;


}


void initAnimation(sprite *spr, int maxF, int delayTick, float drawCenterX, float drawCenterY, char filename[]) {

    spr->image = al_load_bitmap(filename);
    spr->delayTick = delayTick;
    spr->maxFrame = maxF;
    spr->w = al_get_bitmap_width(spr->image)/maxF;
    spr->h = al_get_bitmap_height(spr->image);
    spr->current = 0;
    spr->delayCount = 0;

    spr->drawCenterX = drawCenterX;
    spr->drawCenterY = drawCenterY;

}

void drawAnimation(sprite *spr, int drawX, int drawY) {
    spr->delayCount++;

    if (spr->delayCount >= spr->delayTick) {
        spr->delayCount = 0;
        spr->current++;
    }

    if (spr->current >= spr->maxFrame)
        spr->current = 0;

    al_draw_bitmap_region(spr->image, spr->current*spr->w, 0, spr->w, spr->h, drawX, drawY ,0);

}


/*============================================================================================================*/


void initBackground (background *bg, int x, int y, int dirX, int dirY, int velX, int velY, char* filename) {


    bg->image = al_load_bitmap(filename);
    bg->w = al_get_bitmap_width(bg->image);
    bg->h = al_get_bitmap_height(bg->image);

    bg->x = x;
    bg->y = y - bg->h;
    bg->dirX = dirX;
    bg->dirY = dirY;
    bg->velX = velX;
    bg->velY = velY;
}

void updateBackground (background *bg, int screenH) {
   bg->x += bg->dirX * bg->velX;
   bg->y += bg->dirY * bg->velY;

   if (bg->y > screenH) {
       bg->y = screenH - bg->h;
   }
}




void drawBackground(background *bg) {
    al_draw_bitmap(bg->image, bg->x, bg->y, 0);

    if (bg->y >= 0) {
        al_draw_bitmap(bg->image, bg->x, bg->y - bg->h, 0);
    }


/*
    if (bg->x + bg->w < 0) {
        al_draw_bitmap(bg->image, bg->x + bg->w, bg->y, 0);
    }*/
}



