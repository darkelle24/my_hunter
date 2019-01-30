/*
** EPITECH PROJECT, 2018
** my_hunter
** File description:
** other function 1
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

int my_strlen(char const *str)
{
    int nbchar;

    nbchar = 0;
    while ( *str != '\0') {
        nbchar++;
        str++;
    }
    return (nbchar);
}

void save(t_score *list)
{
    int fichier = open("score/score", O_WRONLY);
    int lenght;

    while (list != NULL) {
        lenght = my_strlen(list->name);
        write(fichier, list->name, lenght);
        while (lenght != 11) {
            write(fichier, " ", 1);
            lenght++;
        }
        write(fichier, ";", 1);
        write(fichier, longtochar(list->score), 15);
        write(fichier, "\n", 1);
        list = list->next;
    }
    close(fichier);
}

char *inttocharspe(int combo)
{
    int i = 0;
    int temp = combo;
    char *nb;

    while (temp != 0) {
        temp = temp / 10;
        i++;
    }
    nb = malloc(sizeof(char) * (i + 2));
    nb[0] = 'x';
    nb[i + 1] = '\0';
    temp = 0;
    while (temp < i) {
        nb[i - temp] = combo % 10 + 48;
        combo = combo / 10;
        temp++;
    }
    return (nb);
}