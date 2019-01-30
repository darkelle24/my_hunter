/*
** EPITECH PROJECT, 2018
** my_hunter
** File description:
** display menu and loose screen
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

int loosescreen(sfRenderWindow *window, long long score)
{
    sfTexture* menutextu =
    sfTexture_createFromFile("ressource/scoreboard.png", NULL);
    sfSprite* menusprites = sfSprite_create();
    sfTexture* entertextu =
    sfTexture_createFromFile("ressource/entrez un nom.png", NULL);
    sfSprite* entersprites = sfSprite_create();
    t_score *list = lecturescore();
    t_score *backup = list;
    t_score *new = malloc(sizeof(* new));
    t_score *after;
    sfEvent event;
    sfFont* font;
    sfText* nom;
    sfText** text;
    sfText** textscore;
    sfVector2f position;
    char buffer[12] = "           ";
    int pass = 0;
    int nb = 0;
    int count = 0;

    sfSprite_setTexture(menusprites, menutextu, sfTrue);
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    font = sfFont_createFromFile("ressource/DejaVuSansMono.ttf");
    text = malloc(sizeof(sfText*) * 10);
    textscore = malloc(sizeof(sfText*) * 10);
    while (nb < 10) {
        text[nb] = sfText_create();
        position.x = 640;
        position.y = 210 + (65 * nb);
        sfText_setPosition(text[nb], position);
        sfText_setString(text[nb], list->name);
        sfText_setFont(text[nb], font);
        sfText_setColor(text[nb], sfWhite);
        sfText_setCharacterSize(text[nb], 34);
        textscore[nb] = sfText_create();
        position.x = 1225;
        position.y = 210 + (65 * nb);
        sfText_setPosition(textscore[nb], position);
        sfText_setString(textscore[nb], longtochar(list->score));
        sfText_setFont(textscore[nb], font);
        sfText_setColor(textscore[nb], sfWhite);
        sfText_setCharacterSize(textscore[nb], 34);
        if (list->next == NULL && score > list->score) {
            pass = 1;
            sfSprite_setTexture(entersprites, entertextu, sfTrue);
            position.x = 706;
            position.y = 291;
            sfSprite_setPosition(entersprites, position);
            nom = sfText_create();
            position.x = 777;
            position.y = 437;
            sfText_setPosition(nom, position);
            sfText_setString(nom, "           ");
            sfText_setFont(nom, font);
            sfText_setColor(nom, sfWhite);
            sfText_setCharacterSize(nom, 50);
        }
        list = list->next;
        nb++;
    }
    list = backup;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtMouseButtonReleased &&
                event.mouseButton.button == sfMouseLeft) {
                    if (event.mouseButton.x >= 47 && event.mouseButton.x <= 47 + 490
            && event.mouseButton.y >= 875 &&
            event.mouseButton.y <= 875 + 80 && pass != 1) {
                sfTexture_destroy(menutextu);
                sfSprite_destroy(menusprites);
                sfTexture_destroy(entertextu);
                sfSprite_destroy(entersprites);
                nb = 0;
                while (nb < 10) {
                    sfText_destroy(text[nb]);
                    sfText_destroy(textscore[nb]);
                    nb++;
                }
                sfFont_destroy(font);
                sfRenderWindow_destroy(window);
                return (0);
            }
                if (event.mouseButton.x >= 1391
                && event.mouseButton.x <= 1391 + 490
                && event.mouseButton.y >= 879 && event.mouseButton.y
                <= 879 + 80 && pass != 1) {
                    sfTexture_destroy(menutextu);
                    sfSprite_destroy(menusprites);
                    sfTexture_destroy(entertextu);
                    sfSprite_destroy(entersprites);
                    nb = 0;
                    while (nb < 10) {
                        sfText_destroy(text[nb]);
                        sfText_destroy(textscore[nb]);
                        nb++;
                    }
                    sfFont_destroy(font);
                    jeu(window);
                    return (0);
                }
            }
            if (event.mouseButton.x >= 860 && event.mouseButton.x <= 860 + 233
            && event.mouseButton.y >= 899 &&
            event.mouseButton.y <= 899 + 38 && pass != 1) {
                list = backup;
                nb = 0;
                while (nb < 10) {
                    list->name = "           ";
                    list->score = 0;
                    sfText_setString(text[nb], list->name);
                    sfText_setString(textscore[nb], longtochar(list->score));
                    nb++;
                    list = list->next;
                }
                list = backup;
                save(list);
            }
            if (((event.mouseButton.x >= 758 && event.mouseButton.x <= 758 + 402
            && event.mouseButton.y >= 611 && event.mouseButton.y <= 611 + 42) ||
            (event.type == sfEvtTextEntered && event.key.code == 13)) &&
            pass == 1) {
                pass = 0;
                list = backup;
                nb = 1;
                while (score < list->score) {
                    nb++;
                    after = list;
                    list = list->next;
                }
                new->rank = nb;
                new->name = buffer;
                new->score = score;
                if (nb != 10) {
                    new->next = list;
                } else {
                    new->next = NULL;
                }
                if (nb != 1) {
                    after->next = new;
                } else {
                    backup = new;
                }
                while (list != NULL) {
                    list->rank++;
                    if (list->next == NULL && nb != 10) {
                        after->next = NULL;
                        free(list->name);
                        free(list);
                    }
                    after = list;
                    list = list->next;
                }
                list = backup;
                nb = 0;
                while (nb < 10) {
                    sfText_setString(text[nb], list->name);
                    sfText_setString(textscore[nb], longtochar(list->score));
                    nb++;
                    list = list->next;
                }
                list = backup;
                save(list);
            }
            if (event.type == sfEvtTextEntered && pass == 1) {
                if (event.key.code == 8) {
                    count--;
                    buffer[count] = ' ';
                }else if (count != 11 && event.key.code != 13) {
                    buffer[count] = event.key.code;
                    count++;
                }
                sfText_setString(nom, buffer);
                if (count == -1) {
                    count = 0;
                }
            }
        }
        sfRenderWindow_drawSprite(window, menusprites, NULL);
        nb = 0;
        while (nb < 10) {
            sfRenderWindow_drawText(window, text[nb], NULL);
            sfRenderWindow_drawText(window, textscore[nb], NULL);
            nb++;
        }
        if (pass == 1) {
            sfRenderWindow_drawSprite(window, entersprites, NULL);
            sfRenderWindow_drawText(window, nom, NULL);
        }
        sfRenderWindow_display(window);
    }
    sfTexture_destroy(menutextu);
    sfSprite_destroy(menusprites);
    sfTexture_destroy(entertextu);
    sfSprite_destroy(entersprites);
    nb = 0;
    while (nb < 10) {
        sfText_destroy(text[nb]);
        sfText_destroy(textscore[nb]);
        nb++;
    }
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);
    return (0);
}

int menu()
{
    sfRenderWindow *window;
    sfVideoMode video_mode;
    sfTexture *menutext;
    sfSprite *menusprite = sfSprite_create();
    sfVector2f position;
    sfEvent event;
    sfColor colortext;
    int change = -1;
    t_score *list = lecturescore();
    sfFont* font = sfFont_createFromFile("ressource/DejaVuSansMono.ttf");
    sfText* score = sfText_create();
    sfText* name = sfText_create();

    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create
    (video_mode, "My Hunter", sfDefaultStyle, NULL);
    menutext = sfTexture_createFromFile
    ("ressource/backgroundmenu.png", NULL);
    if (list->score != 0 && list->name[0] != ' ') {
        position.x = 930;
        position.y = 840;
        sfText_setPosition(score, position);
        sfText_setString(score, longtochar(list->score));
        sfText_setFont(score, font);
        colortext.r = 255;
        colortext.b = 0;
        colortext.g = 255;
        colortext.a = 255;
        sfText_setColor(score, colortext);
        sfText_setCharacterSize(score, 40);
        position.x = 670;
        position.y = 840;
        sfText_setPosition(name, position);
        sfText_setString(name, list->name);
        sfText_setFont(name, font);
        sfText_setColor(name, colortext);
        sfText_setCharacterSize(name, 40);
    } else {
        position.x = 860;
        position.y = 840;
        sfText_setPosition(score, position);
        sfText_setString(score, "No score");
        sfText_setFont(score, font);
        colortext.r = 255;
        colortext.b = 0;
        colortext.g = 255;
        colortext.a = 255;
        sfText_setColor(score, colortext);
        sfText_setCharacterSize(score, 50);
    }
    sfSprite_setTexture(menusprite, menutext, sfTrue);
    sfSprite_setTexture(menusprite, menutext, sfTrue);
    position.x = 0;
    position.y = 0;
    sfSprite_setPosition(menusprite, position);
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtMouseButtonReleased &&
            event.mouseButton.button == sfMouseLeft) {
                if (event.mouseButton.x >= 683 &&
                event.mouseButton.x <= 683 + 594
                && event.mouseButton.y >= 417 &&
                event.mouseButton.y <= 417 + 62) {
                    sfTexture_destroy(menutext);
                    sfFont_destroy(font);
                    sfText_destroy(score);
                    sfText_destroy(name);
                    sfSprite_destroy(menusprite);
                    jeu(window);
                    return (0);
                }
                if (event.mouseButton.x >= 683
                && event.mouseButton.x <= 683 + 594
                && event.mouseButton.y >= 651
                && event.mouseButton.y <= 651 + 62) {
                    sfTexture_destroy(menutext);
                    sfSprite_destroy(menusprite);
                    sfFont_destroy(font);
                    sfText_destroy(score);
                    sfText_destroy(name);
                    sfRenderWindow_destroy(window);
                    return (0);
                }
            }
        }
        sfRenderWindow_drawSprite(window, menusprite, NULL);
        if (colortext.r == 5) {
            change = 10;
        } else if (colortext.r == 250) {
            change = -10;
        }
        colortext.r = colortext.r + change;
        colortext.g = colortext.g + change;
        sfText_setColor(score, colortext);
        sfRenderWindow_drawText(window, score, NULL);
        if (list->score != 0 && list->name[0] != ' ') {
            sfText_setColor(name, colortext);
            sfRenderWindow_drawText(window, name, NULL);
        }
        sfRenderWindow_display(window);
    }
    return (0);
}

void affiche()
{
    write(1, "\n", 1);
    write(1, "MANUAL OF my_hunter :\n", 22);
    write(1, "\n", 1);
    write(1, "     RULES : The player is a hunter who shoots ducks\n", 53);
    write(1, "             Ducks appear on the screen and ", 44);
    write(1, "move from one side to another\n", 30);
    write(1, "             The player can click on them to shoot them\n", 56);
    write(1, "             If ducks escape the player loose one life\n", 55);
    write(1, "             If the player kill a duck, he win 100 point\n", 57);
    write(1, "             If the player kill 4 duck, he win + 1 of combo\n"
    , 60);
    write(1, "             If the player miss the duck, his combo return to 1\n"
    , 64);
    write(1, "             Every 5000 points you win one life\n", 48);
    write(1, "             Every 1000 points the ", 35);
    write(1, "duck move a little bit faster\n", 30);
    write(1, "\n", 1);
    write(1, "     CONTROLS : Left click = Shoot\n", 35);
    write(1, "                R key = Reload\n", 31);
    write(1, "                P key & Escape Key = Pause\n", 43);
    write(1, "\n", 1);
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h')
    {
        affiche();
    }
    else if (ac == 1)
    {
        menu();
    }
    else
    {
        return (84);
    }
    return (0);
}