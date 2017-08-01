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
enum KEYS{ UP,DOWN,LEFT,RIGHT,SPACE} ;


void initShip(ship *ship,ALLEGRO_BITMAP *sheet ,SHIPTYPE type, SHIPCOLOR color);
void drawShip(ship *ship);

ALLEGRO_DISPLAY *display;
int main(void) {

    /*variables*/
    bool done=false,redraw = false;
    bool pressed[5] = {false,false,false,false,false};
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
    initShip(&player, sheet, FAST, RED);

    /*Event Sources*/
    al_register_event_source(eventQ, al_get_timer_event_source(timer));
    al_register_event_source(eventQ, al_get_keyboard_event_source());
    al_register_event_source(eventQ, al_get_display_event_source(display));

    al_start_timer(timer);
    while (!done) {/*main game loop*/
        al_wait_for_event(eventQ,&input);


        if (input.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (input.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                pressed[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                pressed[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                pressed[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                pressed[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                pressed[SPACE] = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }

        else if (input.type == ALLEGRO_EVENT_KEY_UP) {
            switch (input.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                pressed[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                pressed[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                pressed[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                pressed[RIGHT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                pressed[SPACE] = false;
                break;
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }

        else if (input.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }

        else if (input.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;



        /*Game update*/

        if (pressed[UP]) {
            player.y -= player.speed;
            if ( (player.y - player.spr.h/2 < player.bound) )/*Cannot go too far*/
                player.y = player.bound + player.spr.h/2;
        }

        else if (pressed[DOWN]) {
            player.y += player.speed;
            if ( (player.y + player.spr.h/2 > HEIGHT) )
                player.y = HEIGHT - player.spr.h/2;
        }


        if (pressed[LEFT]) {
            player.x -= player.speed;
            if ( (player.x - player.spr.w/2 < 0) )
                player.x = player.spr.w/2;
        }

        else if (pressed[RIGHT]) {
            player.x += player.speed;
            if ( (player.x + player.spr.w/2 > WIDTH) )
                player.x = WIDTH - player.spr.w/2;
        }







        if (redraw && al_is_event_queue_empty(eventQ)) {/*Rendering operations*/

            redraw = false;
            drawShip(&player);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));

        }




    }



    return 0;
}




void initShip(ship *ship, ALLEGRO_BITMAP *sheet,  SHIPTYPE type,SHIPCOLOR color) {
    switch (type) {
    case NORMAL:
        ship->live = true;
        ship->spr.w = 112;
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
            al_draw_bitmap_region(sheet, 112, 791, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case GREEN:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 112, 866, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case ORANGE:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 112, 716, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case RED:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 0, 941, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
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
        ship->x = WIDTH / 2;
        ship->y = HEIGHT - (ship->spr.h)/2;
        ship->ammo = 7;
        ship->speed = 10;
        ship->bound = WIDTH * 3 / 4;

        switch (color) {
        case BLUE:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 325, 739, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case GREEN:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 346, 75, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case ORANGE:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 336, 309, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case RED:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 325, 0, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
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
        ship->x = WIDTH / 2;
        ship->y = HEIGHT - (ship->spr.h)/2;
        ship->ammo = 12;
        ship->speed = 5;
        ship->bound = WIDTH * 3 / 4;

        switch (color) {
        case BLUE:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 211, 941, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case GREEN:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 237, 377, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case ORANGE:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 247, 84, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
            break;
        case RED:
            al_set_target_bitmap(ship->spr.image);
            al_draw_bitmap_region(sheet, 224, 832, ship->spr.w, ship->spr.h, 0, 0, 0);
            al_set_target_backbuffer(display);
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
    al_draw_bitmap(ship->spr.image, ship->x - (ship->spr.w)/2
                   ,ship->y - (ship->spr.h)/2, 0); /*Centered for upper left drawing*/
}
