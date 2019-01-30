/*
** EPITECH PROJECT, 2018
** my_hunter
** File description:
** other function 2
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

char *createarray(char *nb)
{
    int temp = 0;

    nb = malloc(sizeof(char) * 15 + 1);
    nb[15] = '\0';
    while (temp < 15) {
        nb[temp] = 48;
        temp++;
    }
    return (nb);
}

char *longtochar(long long nblist)
{
    int i = 0;
    long long temp = nblist;
    char *nb;

    while (temp != 0) {
        temp = temp / 10;
        i++;
    }
    nb = createarray(nb);
    temp = 0;
    while (temp < i) {
        nb[14 - temp] = nblist % 10 + 48;
        nblist = nblist / 10;
        temp++;
    }
    return (nb);
}

void my_rev_list(t_score **begin)
{
    int i;
    t_score **array;
    int count = 0;
    int end;
    int mid = 0;
    t_score *tmp;

    i = 10;
    array = malloc(sizeof(t_score *)*i+1);
    array[0] = *begin ;
    while (count < i) {
        array[count+1] = array[count]->next;
        count++;
    }
    end = i - 1;
    count = 0;
    mid = i / 2;
    while (count < mid) {
        tmp = array[count];
        array[count] = array[end];
        array[end] = tmp;
        end--;
        count++;
    }
    count = 0;
    *begin = array[0];
    while (count < i) {
        array[count]->next = array[count+1];
        count++;
    }
    free(array);
}

t_score *lecturescore()
{
    int fichier;
    char buffer[28];
    int nb = 0;
    int nbr2 = 0;
    t_score *list = NULL;
    t_score *backup;
    t_score *element;

    while (nb < 10) {
        element = malloc(sizeof(* element));
        element->next = list;
        element->rank = nb + 1;
        element->score = 0;
        list = element;
        nb++;
    }
    my_rev_list(&list);
    backup = list;
    fichier = open("score/score", O_RDONLY);
    nb = 0;
    while (nb < 10) {
        read(fichier, buffer, 28);
        nbr2 = 0;
        list->name = malloc(sizeof(char)*11+1);
        list->name[11] = '\0';
        while (nbr2 < 11) {
            list->name[nbr2] = buffer[nbr2];
            nbr2++;
        }
        nbr2++;
        while (nbr2 < 27) {
            list->score = (buffer[nbr2] - 48) + 10 * list->score;
            nbr2++;
        }
        list = list->next;
        nb++;
    }
    close(fichier);
    list = backup;
    return (list);
}

void freelist(t_score *list)
{
    t_score *temp;

    while (list != NULL) {
        free(list->name);
        temp = list->next;
        free(list);
        list = temp;
        list = list->next;
    }
}