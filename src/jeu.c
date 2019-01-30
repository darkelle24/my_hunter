/*
** EPITECH PROJECT, 2018
** my_hunter
** File description:
** play game
*/

#include <SFML/Graphics.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <SFML/Audio.h>
#include "../include/my.h"

long long jeu(sfRenderWindow *window)
{
    sfTexture *backgroundtext;
    sfTexture *backgroundtextpause;
    sfSprite *backgroundsprite;
    sfTexture **canardtext;
    sfTexture *canarddietext;
    sfSprite *canardsprite;
    sfVector2f positioncanard;
    sfTexture *viseurtext;
    sfEvent event;
    sfTexture *nuagetext;
    sfTexture *hearthtext;
    sfMusic *soundofgun;
    sfMusic *music;
    sfMusic *hit;
    sfMusic *reload;
    sfMusic *soundofdeath;
    sfColor colorbackinter;
    sfColor colorinter;
    sfSprite *viseursprite;
    sfSprite **hearthsprite;
    sfSprite *nuagesrpite1;
    sfSprite *nuagesrpite2;
    sfSprite **Bulletsprite;
    sfVector2f positioneviseur;
    sfVector2f positionnuage1;
    sfVector2f positionnuage2;
    sfVector2f positiontext;
    sfVector2f positiontir;
    sfVector2f positionbullet;
    sfVector2f scale;
    sfIntRect *rectangle;
    sfTexture *Bullet;
    sfFont *font;
    sfText *combotext = sfText_create();
    sfClock *clockanime = sfClock_create();
    sfClock *clockdeplace = sfClock_create();
    long long score = 0;
    char *textsc;
    sfText *scoretext = sfText_create();
    int conteur = 0;
    int inverse = 1;
    int nbrofbullet = 0;
    int tir = 0;
    int nbrdevie = 0;
    int i = 0;
    int nbrdevieajouter = 0;
    int r;
    int loose = 0;
    int changey = 10;
    int changeyn = rand() % 3;
    int pause = 0;
    int combo = 4;
    int a = 1;

    Bulletsprite = malloc(sizeof(sfSprite *) * 10);
    hearthsprite = malloc(sizeof(sfSprite *) * 3);
    if (changeyn == 0) {
        changey = 5;
    } else if (changeyn == 1) {
        changey = -5;
    } else {
        changey = 0;
    }
    colorbackinter.r = 0;
    colorbackinter.g = 0;
    colorbackinter.b = 0;
    colorbackinter.a = 255;
    srand(time(NULL));
    font = sfFont_createFromFile("ressource/DejaVuSansMono.ttf");
    backgroundtext = sfTexture_createFromFile("ressource/stage.png", NULL);
    backgroundtextpause = sfTexture_createFromFile
    ("ressource/backgroundpause.png", NULL);
    canarddietext = sfTexture_createFromFile
    ("ressource/Duckhuntdie.png", NULL);
    viseurtext = sfTexture_createFromFile("ressource/viseur.png", NULL);
    hearthtext = sfTexture_createFromFile("ressource/coeur.png", NULL);
    nuagetext = sfTexture_createFromFile("ressource/Nuage.png", NULL);
    Bullet = sfTexture_createFromFile("ressource/Bullet.png", NULL);
    soundofgun = sfMusic_createFromFile("ressource/Barrett .50Cal.ogg");
    music = sfMusic_createFromFile("ressource/Music.ogg");
    hit = sfMusic_createFromFile("ressource/Villager_Hit.ogg");
    soundofdeath = sfMusic_createFromFile("ressource/duckdeath.ogg");
    reload = sfMusic_createFromFile("ressource/Reload.ogg");
    sfMusic_setVolume(soundofgun, 35);
    sfMusic_setVolume(reload, 45);
    sfMusic_setVolume(hit, 55);
    sfMusic_setVolume(music, 25);
    sfMusic_setVolume(soundofdeath, 97);
    canardtext = malloc(sizeof(sfTexture *) * 3);
    rectangle = malloc(sizeof(sfIntRect *));
    positioncanard.y = 200;
    positioncanard.x = -100;
    scale.x = -1;
    scale.y = -1;
    while (conteur < 3) {
        rectangle->top = 0;
        rectangle->left = conteur * 110;
        rectangle->height = 110;
        rectangle->width = 110;
        canardtext[conteur] = sfTexture_createFromFile
        ("ressource/B-MUL-100_Bootstrap_my_hunter_spritesheet.png"
        , rectangle);
        conteur++;
    }
    conteur = 0;
    backgroundsprite = sfSprite_create();
    viseursprite = sfSprite_create();
    canardsprite = sfSprite_create();
    nuagesrpite1 = sfSprite_create();
    nuagesrpite2 = sfSprite_create();
    while (nbrdevie < 3) {
        hearthsprite[nbrdevie] = sfSprite_create();
        sfSprite_setTexture(hearthsprite[nbrdevie], hearthtext, sfTrue);
        nbrdevie++;
    }
    sfSprite_setTexture(nuagesrpite1, nuagetext, sfTrue);
    sfSprite_setTexture(nuagesrpite2, nuagetext, sfTrue);
    sfSprite_setTexture(backgroundsprite, backgroundtext, sfTrue);
    sfSprite_setTexture(viseursprite, viseurtext, sfTrue);
    while (nbrofbullet < 10) {
        Bulletsprite[nbrofbullet] = sfSprite_create();
        sfSprite_setTexture(Bulletsprite[nbrofbullet], Bullet, sfTrue);
        nbrofbullet++;
    }
    sfText_setString(combotext, inttocharspe(combo / 4));
    positiontext.x = 1465;
    positiontext.y = 906;
    sfText_setPosition(combotext, positiontext);
    sfText_setFont(combotext, font);
    sfText_setCharacterSize(combotext, 30);
    sfText_setOutlineColor(combotext, sfWhite);
    sfText_setString(scoretext, longtochar(score));
    positiontext.x = 1185;
    positiontext.y = 853;
    sfText_setPosition(scoretext, positiontext);
    sfText_setFont(scoretext, font);
    sfText_setCharacterSize(scoretext, 40);
    sfText_setOutlineColor(scoretext, sfWhite);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    positionnuage1.x = 210;
    positionnuage2.x = 1310;
    positionnuage1.y = rand() % 150;
    positionnuage2.y = rand() % 150;
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);
    sfClock_restart(clockanime);
    while (sfRenderWindow_isOpen(window) && loose == 0) {
        if (pause == 0) {
            if (tir == 4 && sfMusic_getStatus(reload) == sfStopped) {
                tir = 0;
                nbrofbullet = 10;
            }
        }
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtMouseMoved) {
                positioneviseur.x = event.mouseMove.x - 100;
                positioneviseur.y = event.mouseMove.y - 100;
                sfSprite_setPosition(viseursprite, positioneviseur);
            }
            if (pause == 0) {
                if (event.type == sfEvtMouseButtonReleased &&
                    event.mouseButton.button == sfMouseLeft) {
                    if (nbrofbullet != 0 && tir != 4) {
                        if (sfMusic_getStatus(soundofgun) == sfStopped) {
                            positiontir.x = event.mouseButton.x;
                            positiontir.y = event.mouseButton.y;
                            sfMusic_play(soundofgun);
                            tir = 1;
                        }
                    } else if (tir != 4) {
                        tir = 4;
                        sfMusic_play(reload);
                    }
                }
                if (event.type == 6) {
                    if (event.key.code == sfKeyR && tir != 4) {
                        tir = 4;
                        sfMusic_play(reload);
                    }
                    if (event.key.code == sfKeyEscape
                    || event.key.code == sfKeyP) {
                        sfSprite_setTexture(backgroundsprite
                        , backgroundtextpause, sfTrue);
                        pause = 1;
                    }
                }
            } else if (pause == 1) {
                if (event.type == sfEvtMouseButtonReleased &&
                    event.mouseButton.button == sfMouseLeft) {
                    if (event.mouseButton.x >= 720
                    && event.mouseButton.x <= 720 + 480
                    && event.mouseButton.y >= 400 &&
                    event.mouseButton.y <= 400 + 50) {
                        pause = 0;
                        sfSprite_setTexture
                        (backgroundsprite, backgroundtext, sfTrue);
                    }
                    if (event.mouseButton.x >= 720
                    && event.mouseButton.x <= 720 + 480
                    && event.mouseButton.y >= 521 &&
                    event.mouseButton.y <= 521 + 50) {
                        sfRenderWindow_close(window);
                    }
                }
                if (event.type == 6) {
                    if (event.key.code == sfKeyEscape
                    || event.key.code == sfKeyP) {
                        pause = 0;
                        sfSprite_setTexture
                        (backgroundsprite, backgroundtext, sfTrue);
                    }
                }
            }
        }
        if (pause == 0) {
            if (tir == 1) {
                nbrofbullet--;
                if (!(positiontir.x >= positioncanard.x -
                (10 * inverse) &&
                positiontir.x <= positioncanard.x -
                (10 * inverse) + 115 &&
                positiontir.y >= positioncanard.y  &&
                positiontir.y <= positioncanard.y + 115)) {
                    tir = 0;
                    combo = 4;
                    sfText_setString(combotext, inttocharspe(combo / 4));
                } else {
                    tir = 3;
                    sfMusic_play(soundofdeath);
                    combo++;
                    sfText_setString(combotext, inttocharspe(combo / 4));
                    score = score + (100 * (combo / 4));
                    if (nbrdevieajouter < score / 5000) {
                        nbrdevieajouter++;
                        nbrdevie++;
                        if (nbrdevie > 3) {
                            nbrdevie = 3;
                        }
                    }
                    sfText_setString(scoretext, longtochar(score));
                    sfClock_restart(clockanime);
                }
            }
            sfRenderWindow_drawSprite(window, backgroundsprite, NULL);
            if (tir == 0 || tir == 4) {
                if (sfClock_getElapsedTime(clockanime).microseconds
                >= 50000 + (-4000 * (score / 1000))) {
                    if (changey + positioncanard.y > 700 && changeyn == 0) {
                        changey = changey * - 1;
                        changeyn = 1;
                    }else if (positioncanard.y <= 0 && changeyn == 1) {
                        changey = changey * - 1;
                        changeyn = 0;
                    }
                    positioncanard.y = positioncanard.y + changey;
                    sfSprite_setPosition(canardsprite, positioncanard);
                    sfSprite_setTexture
                    (canardsprite, canardtext[conteur], sfTrue);
                    if (inverse == -1) {
                        rectangle->top = 0;
                        rectangle->left = 110;
                        rectangle->width = -110;
                        rectangle->height = 110;
                        sfSprite_setTextureRect(canardsprite, *rectangle);
                    }
                    positioncanard.x = positioncanard.x + 15 * inverse;
                    conteur++;
                    if (conteur == 3) {
                        conteur = 0;
                    }
                    if (positioncanard.x >= 1980 || positioncanard.x <= -110) {
                        nbrdevie--;
                        combo = 4;
                        sfText_setString(combotext, inttocharspe(combo / 4));
                        sfMusic_play(hit);
                        if (nbrdevie == 0) {
                            loose = 1;
                        }
                        positioncanard.y = rand() % 700;
                        changeyn = rand() % 3;
                        if (changeyn == 0) {
                            changey = 5;
                        } else if (changeyn == 1) {
                            changey = -5;
                        } else {
                            changey = 0;
                        }
                        inverse = rand() % 2;
                        if (inverse == 0) {
                            inverse = 1;
                            positioncanard.x = -100;
                        } else {
                            inverse = -1;
                            positioncanard.x = 1979;
                        }
                    }
                    sfClock_restart(clockanime);
                }
                sfRenderWindow_drawSprite(window, canardsprite, NULL);
            } else {
                sfSprite_setTexture(canardsprite, canarddietext, sfTrue);
                if (inverse == -1) {
                    rectangle->top = 0;
                    rectangle->left = 110;
                    rectangle->width = -110;
                    rectangle->height = 110;
                    sfSprite_setTextureRect(canardsprite, *rectangle);
                }
                sfRenderWindow_drawSprite(window, canardsprite, NULL);
                if (sfClock_getElapsedTime(clockanime).microseconds >= 200000) {
                    tir = 0;
                    positioncanard.y = rand() % 700;
                    changeyn = rand() % 3;
                    if (changeyn == 0) {
                        changey = 5;
                    } else if (changeyn == 1) {
                        changey = -5;
                    } else {
                        changey = 0;
                    }
                    inverse = rand() % 2;
                    if (inverse == 0) {
                        inverse = 1;
                        positioncanard.x = -100;
                    } else {
                        inverse = -1;
                        positioncanard.x = 1970;
                    }
                    sfClock_restart(clockanime);
                }
            }
            if (sfClock_getElapsedTime(clockdeplace).microseconds
                >= 10000) {
                positionnuage1.x += a;
                sfSprite_setPosition(nuagesrpite1, positionnuage1);
                positionnuage2.x += a;
                sfSprite_setPosition(nuagesrpite2, positionnuage2);
                if (positionnuage1.x == 1920) {
                    positionnuage1.x = -500;
                    positionnuage1.y = rand() % 150;
                }
                if (positionnuage2.x == 1920) {
                    positionnuage2.x = -500;
                    positionnuage2.y = rand() % 150;
                }
                sfClock_restart(clockdeplace);
            }
        } else if (pause == 1) {
            sfRenderWindow_drawSprite(window, backgroundsprite, NULL);
            sfRenderWindow_drawSprite(window, canardsprite, NULL);
        }
        i = 0;
        while (i < nbrofbullet) {
            positionbullet.x = 274 + (23 * i);
            positionbullet.y = 840;
            sfSprite_setPosition(Bulletsprite[i], positionbullet);
            sfRenderWindow_drawSprite(window, Bulletsprite[i], NULL);
            i++;
        }
        i = 0;
        while (i < nbrdevie) {
            positionbullet.x = 748 + (80 * i);
            positionbullet.y = 850;
            sfSprite_setPosition(hearthsprite[i], positionbullet);
            sfRenderWindow_drawSprite(window, hearthsprite[i], NULL);
            i++;
        }
        sfRenderWindow_drawSprite(window, nuagesrpite1, NULL);
        sfRenderWindow_drawSprite(window, nuagesrpite2, NULL);
        sfRenderWindow_drawSprite(window, viseursprite, NULL);
        sfRenderWindow_drawText(window, combotext, NULL);
        sfRenderWindow_drawText(window, scoretext, NULL);
        sfRenderWindow_display(window);
    }
    sfSprite_destroy(backgroundsprite);
    sfSprite_destroy(viseursprite);
    sfSprite_destroy(canardsprite);
    sfSprite_destroy(nuagesrpite1);
    sfSprite_destroy(nuagesrpite2);
    i = 0;
    while (i < 3) {
        sfSprite_destroy(hearthsprite[i]);
        i++;
    }
    sfMusic_destroy(soundofgun);
    sfMusic_destroy(music);
    sfMusic_destroy(reload);
    sfMusic_destroy(hit);
    sfMusic_destroy(soundofdeath);
    sfTexture_destroy(hearthtext);
    sfTexture_destroy(viseurtext);
    sfTexture_destroy(nuagetext);
    sfTexture_destroy(canarddietext);
    sfTexture_destroy(backgroundtextpause);
    sfTexture_destroy(backgroundtext);
    sfText_destroy(scoretext);
    conteur = 0;
    i = 0;
    sfTexture_destroy(Bullet);
    while (i < 10) {
        sfSprite_destroy(Bulletsprite[i]);
        i++;
    }
    while (conteur < 3) {
        sfTexture_destroy(canardtext[conteur]);
        conteur++;
    }
    free(canardtext);
    sfFont_destroy(font);
    sfClock_destroy(clockanime);
    sfClock_destroy(clockdeplace);
    if (loose == 0) {
        sfRenderWindow_destroy(window);
        return (0);
    }
    loosescreen(window, score);
    return (score);
}