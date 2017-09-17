#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdlib.h>
#include <ctype.h>
#include <time.h>


#include "coldetect.h"
#ifndef STRUCTS_H
#include "structs.h"
#endif

#ifndef SHIP_H
#include "ship.h"
#endif

#ifndef ANIMATION_H
#include "animation.h"
#endif

#ifndef SHOOTING_H
#include "shooting.h"
#endif

#ifndef UI_H
#include "ui.h"
#endif

#define PI 3.14
#define WIDTH 600
#define HEIGHT 900
#define FPS 60
#define MAXLASER 10
#define LASERDELAY 15
#define MAXENEMY 30
#define MAXTYPE 5
#define TOPLIST 10
#define USERNAMELEN 8
/*typedef enum  { false,true }bool;*/

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, ESC, ENTER, BACKSPACE } ;
typedef enum { MENU, GAME, GAMEOVER }STATE;



void setState (int *gameState, int targetState, ALLEGRO_SAMPLE_ID *bgmID);

int main(void) {

    /*variables*/
    bool redraw = false;
    bool pressed[8] = {false,false,false,false,false,false,false, false};
    int gameState = -1;
    int laserDelayCount = 0;
    bool destroyed = false;
    int i,j; /*for loops*/
    float gameTime = 0;
    int frames = 0;
    int gameFPS = 0;
    int enemyDensity = 27;
    int densityCounter = 0;
    int enemyDeath = 0;
    int score = 0;
    char textInput;
    char *username = NULL;
    int currUsernamelen = 0;
    char* boardname = "scoreboard.txt";



    int spawnCredentials[][2] = {
        {110,8},
        {110,7},
        {215,10},
        {0,12},
        {70,15}
/*
First dimension indicates enemy type, first element of the second dimension indicates elimination
treshold for making it spawnable and second element indicates spawn randomness of that type
*/
    };


    /*=============================
    ALLEGRO VARIABLES
    =============================*/
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER  *timer = NULL;
    ALLEGRO_EVENT_QUEUE *eventQ = NULL;
    ALLEGRO_EVENT input; /*for inputs and fps timer*/
    ALLEGRO_BITMAP *sheet = NULL;
    ALLEGRO_FONT  *arial18 = NULL, *boldArial18 = NULL;

    ALLEGRO_SAMPLE *laserSound, *bgm;
    ALLEGRO_SAMPLE_INSTANCE *laserInstance;
    ALLEGRO_SAMPLE_ID bgmID;


    /*=============================
    GAME VARIABLES
    =============================*/
    playerShip player;
    sprite thruster,laserSpr,laserExpSpr, beamSpr;
    sprite enemyLsrSpr,enemyLsrExpSpr, enemyMissileSpr;
    /*sprite laserSpr;*/
    bullet *laser = NULL;
    background bg, fg;
    scoreboard *board;
    enemyShip **enemy = NULL;


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
    boldArial18 = al_load_font("Resources/Font/Arial Bold.ttf",18,0);
    laser = (bullet*)malloc(sizeof(bullet)*MAXLASER);
    enemy = (enemyShip**)malloc(sizeof(enemyShip*)*MAXENEMY);
    board = (scoreboard*)malloc(sizeof(scoreboard));
    username = (char*)malloc(sizeof(char)*USERNAMELEN+1); /* +1 for null*/
    username[0] = '\0';





    al_reserve_samples(5);
    bgm = al_load_sample("Resources/Audio/Music/DST-RailJet [qubodup short-cut loop].ogg");

    laserSound = al_load_sample("Resources/Audio/Effects/laser4.ogg");
    laserInstance = al_create_sample_instance(laserSound);


    initShip(&player, sheet, NORMAL, RED, display, &beamSpr);
    initAnimation(&thruster, 20, 2, 20, 0,"Resources/redthruster.png");
    initSpriteFromSheet(&laserSpr, 858, 475, 9, 37, 4.5, 0, sheet, display, 1, 0.8);
    initSpriteFromSheet(&laserExpSpr, 740, 724, 37, 37, 13.5, 13.5, sheet, display, 0.5, 0.5);
    initLaser(laser, MAXLASER, &laserSpr, &laserExpSpr, -1, 10);

    /*----------------------------------------EnemyLaser--------------------------------------------*/
    initSpriteFromSheet(&enemyLsrSpr, 856, 983, 9, 37, 4.5, 0, sheet, display, 1, 0.7);
    initSpriteFromSheet(&enemyLsrExpSpr, 580, 661, 48, 46, 24, 23, sheet, display, 0.5, 0.5);
    initSpriteFromFile(&enemyMissileSpr, 10, 35, "Resources/Missiles/spaceMissiles_001.png", display, 1, 1, PI);

    initSpriteFromSheet(&beamSpr, 858, 230, 9, 54, 4.5, 9*5, sheet, display, 1,5);
    initAnimation(&beamSpr, 1, 240, 4.5, 9*5, NULL);
    initBackground(&bg, 0, HEIGHT, 1, 1, 0, 1, "Resources/Background/blueFilled.png");
    initBackground(&fg, 0, HEIGHT, 1, 1, 0, 2, "Resources/Background/starfieldVFilled.png");
    initScoreboard(board, TOPLIST, USERNAMELEN);
    /*initEnemyShip(enemy, MAXENEMY, sheet, display);*/

    al_set_sample_instance_gain(laserInstance, 0.35);
    al_set_sample_instance_speed(laserInstance, 2.1);
    al_set_sample_instance_length(laserInstance, 14768);
    al_set_sample_instance_playmode(laserInstance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(laserInstance,al_get_default_mixer());


    for (i=0; i<MAXENEMY; i++) {
        enemy[i] = (enemyShip*)malloc(sizeof(enemyShip));
        enemy[i]->spr.image = NULL;
        enemy[i]->laser = NULL;
        enemy[i]->missile = NULL;
        enemy[i]->type = NOT_INITIALIZED;
        initEnemyShip(enemy[i], sheet, display, &enemyLsrSpr, &enemyMissileSpr, &enemyLsrExpSpr, laserInstance,
                      enemyDeath, spawnCredentials);
    }


    /*=============================
    EVENT SOURCES
    =============================*/
    al_register_event_source(eventQ, al_get_timer_event_source(timer));
    al_register_event_source(eventQ, al_get_keyboard_event_source());
    al_register_event_source(eventQ, al_get_display_event_source(display));

    srand(time(NULL));
    al_hide_mouse_cursor(display);
    al_start_timer(timer);
    gameTime = al_current_time();


                /*=============================
                        MENU STATE LOOP
                =============================*/

    while (gameState == MENU) {
        al_wait_for_event(eventQ, &input);
        al_draw_text(arial18, al_map_rgb(0,0,255), WIDTH/2, HEIGHT/2,
                     ALLEGRO_ALIGN_CENTER, "ENTER YOUR USERNAME TO START THE GAME");
        if (username != NULL) {
            al_draw_text(arial18, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 + 150,
                          ALLEGRO_ALIGN_CENTER, username); /*Drawing username*/
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        switch (input.type) {
        case ALLEGRO_EVENT_KEY_DOWN:

            switch (input.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
                pressed[ENTER] = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                pressed[ESC] = true;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                pressed[BACKSPACE] = true;
                if (currUsernamelen >= 0) {
                    username[currUsernamelen] = '\0';
                    currUsernamelen-=1;
                }

                break;
            default:
                break;
            }

            break;

        case ALLEGRO_EVENT_KEY_UP:
            switch (input.keyboard.keycode) {

            case ALLEGRO_KEY_ENTER:
                pressed[ENTER] = false;
                break;
            case ALLEGRO_KEY_ESCAPE:
                pressed[ESC] = false;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                pressed[BACKSPACE] = false;
                break;
            default:
                break;
            }

            break;

        case ALLEGRO_EVENT_KEY_CHAR:
            textInput = input.keyboard.unichar;
            if (isalpha(textInput) && currUsernamelen < USERNAMELEN) {
                /*If input contains characters*/
                username[currUsernamelen] = textInput;
                username[currUsernamelen+1] = '\0';
                currUsernamelen+=1;
            }
            break;

        default:
            break;
}

        if (pressed[ENTER] && currUsernamelen > 0)
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


            if (pressed[SPACE]) {
                shootLaser(laser, MAXLASER, &laserDelayCount, HEIGHT, player.x, player.y, LASERDELAY, laserInstance);
            }

            if (player.lives == 0)
                setState(&gameState, GAMEOVER, &bgmID);

            updateLaser(laser, MAXLASER, HEIGHT);
            updateEnemyShip(enemy, &player, MAXENEMY, WIDTH, HEIGHT, enemyDensity, &densityCounter, sheet, display,
                            &enemyLsrSpr, &enemyMissileSpr, &enemyLsrExpSpr, laserInstance, enemyDeath, spawnCredentials);
            updateBackground(&bg, HEIGHT);
            updateBackground(&fg, HEIGHT);



        }


        else if (input.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            setState(&gameState, GAMEOVER, &bgmID);
        else if (pressed[ESC])
            setState(&gameState, GAMEOVER, &bgmID);


/*==============================================Player collision with laser================================================*/

            for (i=0; i<MAXENEMY; i++) {
                if(enemy[i]->type == FIRING_STATIC || enemy[i]->type == FIRING_DYNAMIC ||  enemy[i]->type == FOLLOWING_DYNAMIC) {

                    for (j=0; j<enemy[i]->laserAmount; j++) {
                        if (enemy[i]->laser[j].live &&
                                colliding(&player.spr, enemy[i]->laser[j].spr, player.x-player.spr.drawCenterX,
                                          player.y-player.spr.drawCenterY, enemy[i]->laser[j].x, enemy[i]->laser[j].y)) {
                            enemy[i]->laser[j].exploding = true;
                            enemy[i]->laser[j].explosionSpr->current = 0;
                            player.lives -= 1;
                            enemy[i]->laser[j].live =false;
                            break;
                        }
                    }
                }
            }

/*------------------------------------------------------------------------------------------------------------------------------*/

/*==============================================Player collision with missile================================================*/

            for (i=0; i<MAXENEMY; i++) {
                if(enemy[i]->type == MISSILE_STATIC) {

                    for (j=0; j<enemy[i]->ammo; j++) {
                        if (enemy[i]->missile[j].live &&
                                colliding(&player.spr, enemy[i]->missile[j].spr, player.x-player.spr.drawCenterX,
                                          player.y - player.spr.drawCenterY, enemy[i]->missile[j].x, enemy[i]->missile[j].y)) {
                            enemy[i]->missile[j].live =false;
                            player.lives -= 1;
                            enemy[i]->missile[j].exploding = true;
                            enemy[i]->missile[j].explosionSpr->current = 0;
                            break;
                        }
                    }
                }
            }

/*------------------------------------------------------------------------------------------------------------------------------*/

/*==============================================Enemy collision with laser================================================*/

            for (i=0; i<MAXENEMY; i++) {
                for (j=0; j<MAXLASER; j++) {
                    if (enemy[i]->type != NOT_INITIALIZED && enemy[i]->live && laser[j].live &&
                            colliding(&enemy[i]->spr, &laserSpr, enemy[i]->x, enemy[i]->y, laser[j].x, laser[j].y)) {
                        laser[j].live =false;
                        enemy[i]->lives -=1;
                        if (enemy[i]->lives == 0) {
                            enemyDeath+=1;
                            score+=enemy[i]->scorePts;
                        }
                        laser[j].exploding = true;
                        laser[j].explosionSpr->current = 0;
                        break;
                    }
                }
            }

/*------------------------------------------------------------------------------------------------------------------------------*/

/*==============================================Enemy collision with ship================================================*/
            for (i=0; i<MAXENEMY; i++) {
                if (enemy[i]->y+enemy[i]->spr.h > player.bound && enemy[i]->type != NOT_INITIALIZED && enemy[i]->live) {
                    /*if enemies are not inside of ship bound they can't collide*/
                    if (colliding(&player.spr, &enemy[i]->spr,/*giving upper left corners for all of the sprites*/
                                  player.x - player.spr.w/2, player.y - player.spr.h/2, enemy[i]->x, enemy[i]->y)) {
                        enemy[i]->live=false;
                        enemy[i]->lives=0; /*collision kills instantly*/
                    }
                }
            }
/*==============================================Enemy collision with ship================================================*/
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
            al_draw_textf(arial18, al_map_rgb(255,0,255), WIDTH, 0,ALLEGRO_ALIGN_RIGHT, "Eliminations:%d",enemyDeath);
            al_draw_textf(arial18, al_map_rgb(255,0,255), WIDTH, 20,ALLEGRO_ALIGN_RIGHT, "Score:%d",score);

            drawAnimation(&thruster,player.x - thruster.drawCenterX, player.y + player.spr.h/2, true);
            drawLaser(laser, MAXLASER);
            for (i=0;i<MAXENEMY;i++) {
                if ((enemy[i]->type == FIRING_STATIC || enemy[i]->type == FIRING_DYNAMIC || enemy[i]->type == FOLLOWING_DYNAMIC))
                    drawLaser(enemy[i]->laser, enemy[i]->laserAmount);

                else if (enemy[i]->type == MISSILE_STATIC)
                     drawMissile(enemy[i]->missile, enemy[i]->ammo);

            }
            drawEnemyShip(enemy,MAXENEMY);
            drawShip(&player);


            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));

        }




    }


    /*=============================
            GAMEOVER STATE LOOP
    =============================*/


    i=0;
    while (gameState == GAMEOVER) {
        al_wait_for_event(eventQ, &input);
        al_draw_text(arial18, al_map_rgb(255,0,0), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "GAME IS NOW OVER");
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        if(i==0){/*Running once*/
            readScoreboard(boardname, board);
            addToScoreboard(board, score, username);
            writeScoreboard(boardname, board);
            i++;
        }
        drawScoreboard(board, arial18, boldArial18, WIDTH/2, HEIGHT/2+100);
        if ( input.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {



            if (!destroyed) {

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
                al_destroy_font(boldArial18);

                al_destroy_sample(bgm);
                al_destroy_sample(laserSound);
                al_destroy_sample_instance(laserInstance);



                /*============================*/
                free(laser);
                for (i=0; i<MAXENEMY; i++) {
                    free(enemy[i]->laser);
                    free(enemy[i]);
                }
                free(enemy);
                for (i=0;i<board->maxLength;i++) {
                    free(board->usernames[i]);
                }
                free(board->usernames);
                destroyed = true;
                printf("everything destroyed\n");
                break;
            }
            /*Breaking from gameover loop for ending the game properly*/

        }

        else if (input.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (input.keyboard.keycode == ALLEGRO_KEY_R) {
                setState(&gameState, GAME, &bgmID);
            }
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





