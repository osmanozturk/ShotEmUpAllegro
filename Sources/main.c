#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "coldetect.h"
#ifndef STRUCTS_H
#include "structs.h"
#endif
#include "ship.h"
#include "animation.h"
#include "shooting.h"

#define WIDTH 600
#define HEIGHT 900
#define FPS 60
#define MAXLASER 20
#define LASERDELAY 10
#define MAXENEMY 30
/*typedef enum  { false,true }bool;*/

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, ESC } ;
typedef enum { MENU, GAME, GAMEOVER }STATE;



void setState (int *gameState, int targetState, ALLEGRO_SAMPLE_ID *bgmID);

int main(void) {

    /*variables*/
    bool redraw = false;
    bool pressed[5] = {false,false,false,false,false,false};
    int gameState = -1;
    int laserDelayCount = 0;
    bool destroyed = false;
    int i,j; /*for loops*/
    float gameTime = 0;
    int frames = 0;
    int gameFPS = 0;
    int enemyDensity = 30;
    int densityCounter = 0;


    /*=============================
    ALLEGRO VARIABLES
    =============================*/
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER  *timer = NULL;
    ALLEGRO_EVENT_QUEUE *eventQ = NULL;
    ALLEGRO_EVENT input; /*for inputs and fps timer*/
    ALLEGRO_BITMAP *sheet = NULL;
    ALLEGRO_FONT  *arial18 = NULL;

    ALLEGRO_SAMPLE *laserSound, *bgm;
    ALLEGRO_SAMPLE_INSTANCE *laserInstance;
    ALLEGRO_SAMPLE_ID bgmID;

    /*=============================
    GAME VARIABLES
    =============================*/
    ship player;
    sprite thruster,laserSpr,laserExpSpr;
    /*sprite laserSpr;*/
    bullet *laser = NULL;
    background bg, fg;

    ship **enemy = NULL;


    /*=============================
    INITIALIZATIONS
    =============================*/
    if (!al_init()) {
        printf("failed to initialize allegro");
        gameState = -1;
    }
    else
        setState(&gameState, MENU, &bgmID);

    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();

    /*=========================================================*/
    display = al_create_display(WIDTH, HEIGHT);
    timer = al_create_timer(1.0 / FPS);
    eventQ = al_create_event_queue();
    sheet = al_load_bitmap("Resources/sheet.png");
    arial18 = al_load_font("Resources/Font/arial.ttf",18,0);
    laser = (bullet*)malloc(sizeof(bullet)*MAXLASER);
    enemy = (ship**)malloc(sizeof(ship*)*MAXENEMY);
    for (i=0; i<MAXENEMY; i++) {
        enemy[i] = (ship*)malloc(sizeof(ship));
    }

    al_reserve_samples(5);
    bgm = al_load_sample("Resources/Audio/Music/DST-RailJet [qubodup short-cut loop].ogg");

    laserSound = al_load_sample("Resources/Audio/Effects/laser4.ogg");
    laserInstance = al_create_sample_instance(laserSound);


    initShip(&player, sheet, NORMAL, BLUE, display);
    initAnimation(&thruster, 20, 2, 20, 0,"Resources/redthruster.png");
    initSpriteFromSheet(&laserSpr, 858, 475, 9, 37, 4.5, 0, sheet, display, 1, 0.8);
    initSpriteFromSheet(&laserExpSpr, 740, 724, 37, 37, 13.5, 13.5, sheet, display, 0.5, 0.5);
    initLaser(laser, MAXLASER, &laserSpr, &laserExpSpr);
    initBackground(&bg, 0, HEIGHT, 1, 1, 0, 1, "Resources/Background/blueFilled.png");
    initBackground(&fg, 0, HEIGHT, 1, 1, 0, 2, "Resources/Background/starfieldVFilled.png");
    initEnemyShip(enemy, MAXENEMY, sheet, STATIC, EBLACK, display);

    al_set_sample_instance_gain(laserInstance, 0.35);
    al_set_sample_instance_speed(laserInstance, 2.1);
    al_set_sample_instance_length(laserInstance, 14768);
    al_set_sample_instance_playmode(laserInstance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(laserInstance,al_get_default_mixer());


    /*=============================
    EVENT SOURCES
    =============================*/
    al_register_event_source(eventQ, al_get_timer_event_source(timer));
    al_register_event_source(eventQ, al_get_keyboard_event_source());
    al_register_event_source(eventQ, al_get_display_event_source(display));


    al_hide_mouse_cursor(display);
    al_start_timer(timer);
    gameTime = al_current_time();


                /*=============================
                        MENU STATE LOOP
                =============================*/

    while (gameState == MENU) {
        al_wait_for_event(eventQ, &input);
        al_draw_text(arial18, al_map_rgb(0,0,255), WIDTH/2, HEIGHT/2,
                     ALLEGRO_ALIGN_CENTER, "PRESS SPACE TO START GAME");
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        if (input.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (input.keyboard.keycode) {

            case ALLEGRO_KEY_SPACE:
                pressed[SPACE] = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                pressed[ESC] = true;
                break;
            }
        }

        else if (input.type == ALLEGRO_EVENT_KEY_UP) {
            switch (input.keyboard.keycode) {

            case ALLEGRO_KEY_SPACE:
                pressed[SPACE] = false;
                break;
            case ALLEGRO_KEY_ESCAPE:
                pressed[ESC] = false;
                break;
            }
        }

        if (pressed[SPACE])
            setState(&gameState, GAME, &bgmID);

        else if (pressed[ESC])
            setState(&gameState, GAMEOVER, &bgmID);
    }





                /*=============================
                        GAME STATE LOOP
                =============================*/
    al_play_sample(bgm, 0.4, 0, 1, ALLEGRO_PLAYMODE_LOOP,&bgmID);

    while (gameState == GAME) {/*main game loop*/
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
                pressed[ESC] = true;
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
                pressed[ESC] = false;
                break;
            }
        }



        /*=============================
                    UPDATE
        =============================*/

        if (input.type == ALLEGRO_EVENT_TIMER) {
            /*Rendering takes time so rendering outside of timer event is better choice*/
            redraw = true;
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

            if (player.lives == 0)
                setState(&gameState, GAMEOVER, &bgmID);

            updateLaser(laser, MAXLASER, &laserDelayCount, LASERDELAY, &player, laserInstance);
            updateEnemyShip(enemy, MAXENEMY, WIDTH, HEIGHT, enemyDensity, &densityCounter);
            updateBackground(&bg, HEIGHT);
            updateBackground(&fg, HEIGHT);


/*==============================================Enemy collision with laser================================================*/

            for (i=0; i<MAXENEMY; i++) {
                for (j=0; j<MAXLASER; j++) {
                    if (enemy[i]->live && laser[j].live &&
                            colliding(&enemy[i]->spr, &laserSpr, enemy[i]->x, enemy[i]->y, laser[j].x, laser[j].y)) {
                        laser[j].live =false;
                        enemy[i]->live = false;
                        laser[j].exploding = true;
                        laser[j].explosionSpr->current = 0;
                        break;
                    }
                }
            }

/*------------------------------------------------------------------------------------------------------------------------------*/








/*==============================================Enemy collision with ship================================================*/
            for (i=0; i<MAXENEMY; i++) {
                if (enemy[i]->y+enemy[i]->spr.h > player.bound && enemy[i]->live) {
                    /*if enemies are not inside of ship bound they can't collide*/
                    if (colliding(&player.spr, &enemy[i]->spr,/*giving upper left corners for all of the sprites*/
                                  player.x - player.spr.w/2, player.y - player.spr.h/2, enemy[i]->x, enemy[i]->y)) {
                        enemy[i]->live=false;
                        player.lives--;

                    }
                }
            }
/*==============================================Enemy collision with ship================================================*/

        }


        else if (input.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            setState(&gameState, GAMEOVER, &bgmID);
        else if (pressed[ESC])
            setState(&gameState, GAMEOVER, &bgmID);




                /*=============================
                      RENDERING OPERATIONS
                =============================*/

        if (redraw && al_is_event_queue_empty(eventQ)) {
            frames++;
            if(al_current_time() - gameTime >= 1) {
                gameTime = al_current_time();
                gameFPS = frames;
                drawAnimation(&thruster,player.x - thruster.drawCenterX, player.y + player.spr.h/2, true);
                drawEnemyShip(enemy,MAXENEMY);
                frames = 0;
            }

            redraw = false;

            drawBackground(&bg);
            drawBackground(&fg);
            al_draw_textf(arial18, al_map_rgb(255,255,255), 0, 0, 0, "FPS:%d",gameFPS);
            drawAnimation(&thruster,player.x - thruster.drawCenterX, player.y + player.spr.h/2, true);
            drawLaser(laser, MAXLASER);
            drawEnemyShip(enemy,MAXENEMY);
            drawShip(&player);


            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));

        }




    }


    /*=============================
            GAMEOVER STATE LOOP
    =============================*/


    while (gameState == GAMEOVER) {
        al_wait_for_event(eventQ, &input);
        al_draw_text(arial18, al_map_rgb(255,0,0), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "GAME IS NOW OVER");
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        if ( (input.type == ALLEGRO_EVENT_DISPLAY_CLOSE) && !destroyed){

            al_destroy_display(display);
            al_destroy_event_queue(eventQ);
            al_destroy_timer(timer);
            al_destroy_bitmap(sheet);
            al_destroy_bitmap(player.spr.image);
            al_destroy_bitmap(thruster.image);
            al_destroy_bitmap(laserSpr.image);
            al_destroy_bitmap(bg.image);
            al_destroy_bitmap(fg.image);
            al_destroy_font(arial18);

            al_destroy_sample(bgm);
            al_destroy_sample(laserSound);
            al_destroy_sample_instance(laserInstance);



            /*============================*/
            free(laser);
            for (i=0; i<MAXENEMY; i++) {
                free(enemy[i]);
            }
            free(enemy);
            destroyed = true;
            printf("everything destroyed\n");
            break;
            /*Breaking from gameover loop for ending the game properly*/

        }
    }


    return 0;
}


void setState (int *gameState, int targetState, ALLEGRO_SAMPLE_ID *bgmID) {

    /*

        will be used for destroying scene objejcts
    */
    switch (*gameState) {
    case MENU:
        printf("exiting menu\n");


        break;

    case GAME:
        printf("exiting game\n");


        break;

    case GAMEOVER:
        printf("exiting gameover\n");
        break;
    default:
        break;
    }

    *gameState = targetState;

    switch (targetState) {
    case MENU:
        printf("getting to menu\n");
        break;

    case GAME:
        printf("getting to game\n");
        break;

    case GAMEOVER:
        printf("getting to gameover\n");
        al_stop_sample(bgmID);
        break;
    default:
        printf("this is not a valid state for changing\n");
        break;
    }


}





