#ifndef COLDETECT_H
#define COLDETECT_H

#endif /* COLDETECT_H*/
#ifndef STRUCTS_H
#include "structs.h"
#endif
#include <allegro5/allegro.h>

/*====================================================================================================
Returns true if given sprites are colliding, it is pixel perfect
====================================================================================================*/

bool colliding(sprite *s1, sprite *s2, int x1, int y1, int x2, int y2);



/*====================================================================================================
Returns true if given sprites are colliding with box collision method
====================================================================================================*/


bool boxCollision(sprite *s1, sprite *s2, int x1, int y1, int x2, int y2);





/*========================================
Helper functions for collision detection
========================================*/

int max(int a, int b);
int min(int a, int b);
