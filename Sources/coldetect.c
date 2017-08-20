#include "coldetect.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

bool boxCollision(sprite *s1, sprite *s2, int x1, int y1, int x2, int y2) {
    if ((x1 > x2 + s2->w - 1) ||
        (y1 > y2 + s2->h - 1) ||
        (x2 > x1 + s1->w - 1) ||
        (y2 > y1 + s1->h - 1))
    {

        return false;
    }

    else {
        return true;
    }
}

bool colliding(sprite *s1, sprite *s2, int x1, int y1, int x2, int y2) {
    int top, bottom, left, right;
    int y,x; /*for loop variables*/

    ALLEGRO_COLOR px1, px2;

  /*
    ALLEGRO_LOCKED_REGION *lk1 = NULL, *lk2 = NULL;
    pixel information can be read from locked region in the future
  */




    /*=========================================
    Checking for box collision at first not
    executing pixel operations on every cycle
    =========================================*/


    if ((x1 > x2 + s2->w - 1) ||
        (y1 > y2 + s2->h - 1) ||
        (x2 > x1 + s1->w - 1) ||
        (y2 > y1 + s1->h - 1))
    {

        return false;
    }

    else {
        /* box collision*/
        top = max(y1, y2);
        bottom = min(y1 + s1->w, y2 + s2->w);
        left = max(x1, x2);
        right = min(x1 + s1->w, x2 + s2->w);


        /*====================================================================================================
        if two non transparent pixel sharing same space that means collision occured.
        locking bitmaps before using get pixel operations massively increases efficiency
        ====================================================================================================*/

        al_lock_bitmap(s1->image, al_get_bitmap_format(s1->image), ALLEGRO_LOCK_READONLY);
        al_lock_bitmap(s2->image, al_get_bitmap_format(s2->image), ALLEGRO_LOCK_READONLY);

        for (y = top; y < bottom; y++) {
            for (x = left; x < right; x++) {
                px1 = al_get_pixel(s1->image, x - x1, y - y1);
                if (px1.a) {
                    px2 = al_get_pixel(s2->image, x - x2, y - y2);
                    if (px2.a) {
                        /*if one of the pixels are transparent skipping for efficiency*/
                        al_unlock_bitmap(s1->image);
                        al_unlock_bitmap(s2->image);
                        return true;
                    }

                }

            }
        }

        al_unlock_bitmap(s1->image);
        al_unlock_bitmap(s2->image);
        return false;
    }



}



int max(int a, int b) {
    if (a > b) return a;
    else return b;
}
int min(int a, int b) {
    if (a < b) return a;
    else return b;
}
