#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "coldetect.h"
#include "structs.h"


#define WIDTH 600
#define HEIGHT 900
#define FPS 60

/*typedef enum  { false,true }bool;*/
typedef enum  { DAMAGE, FAST, NORMAL }SHIPTYPE;
typedef enum  { BLUE, GREEN, ORANGE, RED }SHIPCOLOR;


void initShip(ship *ship,ALLEGRO_BITMAP *sheet ,SHIPTYPE type, SHIPCOLOR color);
void drawShip(ship *ship);

ALLEGRO_DISPLAY *display;
int main(void) {

    /*variables*/
    bool done=false,redraw = false;

    /*Allegro variables*/

    ALLEGRO_TIMER  *timer;
    ALLEGRO_EVENT_QUEUE *eventQ;
    ALLEGRO_EVENT input; /*for inputs and fps timer*/
    ALLEGRO_BITMAP *sheet = NULL;

    ship player;

    /*initializations*/
    if (!al_init()) {
        printf("failed to initialize allegro");
        done = true;
    }


    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    display = al_create_display(WIDTH, HEIGHT);
    timer = al_create_timer(1.0 / FPS);
    eventQ = al_create_event_queue();
    sheet = al_load_bitmap("sheet.png");
    initShip(&player, sheet, NORMAL, BLUE);

    /*Event Sources*/
    al_register_event_source(eventQ, al_get_timer_event_source(timer));
    al_register_event_source(eventQ, al_get_keyboard_event_source());
    al_register_event_source(eventQ, al_get_display_event_source(display));

    al_start_timer(timer);
    while (!done) {/*main game loop*/
        al_wait_for_event(eventQ,&input);

        if (input.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        else if (input.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (input.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }

        if (redraw && al_is_event_queue_empty(eventQ)) {

            redraw = false;
            drawShip(&player);
            al_flip_display();

        }




    }



    return 0;
}




void initShip(ship *ship, ALLEGRO_BITMAP *sheet,  SHIPTYPE type,SHIPCOLOR color) {
    switch (type) {
    case NORMAL:
        ship->live = true;
        ship->spr.w = 99;
        ship->spr.h = 75;
        ship->spr.image = al_create_bitmap(ship->spr.w, ship->spr.h);
        ship->x = WIDTH / 2;
        ship->y = HEIGHT - (ship->spr.h)/2;
        ship->ammo = 10;
        ship->speed = 7;
        ship->bound = WIDTH * 3 / 4;

        switch (color) {
        case BLUE:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 224, 832, 99, 75, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case GREEN:
            break;
        case ORANGE:
            break;
        case RED:
            break;
        default:
            break;
        }

        break;
    case FAST:
        ship->ammo = 7;
        ship->live = true;
        ship->speed = 10;
        ship->x = WIDTH / 2;
        ship->y = 0;
        ship->bound = WIDTH * 3 / 4;

        switch (color) {
        case BLUE:
            break;
        case GREEN:
            break;
        case ORANGE:
            break;
        case RED:
            break;
        default:
            break;
        }

        break;
    case DAMAGE:
        ship->ammo = 12;
        ship->live = true;
        ship->speed = 5;
        ship->x = WIDTH / 2;
        ship->y = 0;
        ship->bound = WIDTH * 3 / 4;

        switch (color) {
        case BLUE:
            break;
        case GREEN:
            break;
        case ORANGE:
            break;
        case RED:
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
    al_draw_bitmap(ship->spr.image, ship->x,
                   ship->y, 0); /*Centered for upper left drawing*/
}
