#include "coldetect.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
int colliding(Sprite *s1, Sprite *s2) {
    int top, bottom, left, right;
    int y,x; /*for for loops*/
    /*ALLEGRO_LOCKED_REGION *lk1 = NULL, *lk2 = NULL;*/
    ALLEGRO_COLOR px1, px2;


    if ((s1->x > s2->x + s2->w - 1) ||
        (s1->y > s2->y + s2->h - 1) ||
        (s2->x > s1->x + s1->w - 1) ||
        (s2->y > s1->y + s1->h - 1))
    {
        /* no collision*/
        return 0;
    }

    else {
        /* box collision*/
        top = max(s1->y, s2->y);
        bottom = min(s1->y + s1->w, s2->y + s2->w);
        left = max(s1->x, s2->x);
        right = min(s1->x + s1->w, s2->x + s2->w);

        al_lock_bitmap(s1->image, al_get_bitmap_format(s1->image), ALLEGRO_LOCK_READONLY);
        al_lock_bitmap(s2->image, al_get_bitmap_format(s2->image), ALLEGRO_LOCK_READONLY);

        for (y = top; y < bottom; y++) {
            for (x = left; x < right; x++) {
                px1 = al_get_pixel(s1->image, x - s1->x, y - s1->y);
                if (px1.a) {
                    px2 = al_get_pixel(s2->image, x - s2->x, y - s2->y);
                    if (px2.a) {/*if one of the pixels are transparent skipping for efficiency*/
                        al_unlock_bitmap(s1->image);
                        al_unlock_bitmap(s2->image);
                        return 1;
                    }

                }

            }
        }

        al_unlock_bitmap(s1->image);
        al_unlock_bitmap(s2->image);
        return 0;
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
