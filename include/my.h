/*
** EPITECH PROJECT, 2018
** lol
** File description:
** lol
*/

#ifndef MY_H_
	#define MY_H_
    #include <SFML/Graphics.h>

    typedef struct sfSpriteduck
    {
        sfSprite *canardsprite;
        int conteur;
        sfVector2f positioncanard;
        int death;
        int timer;
        struct sfSpriteduck *next;
    }       t_spriteduck;

    typedef struct s_framebuffer
    {
        unsigned char *pixels;
        unsigned int width;
        unsigned int height;
    }       t_framebuffer;

    typedef struct s_score
    {
        int rank;
        char *name;
        long long score;
        struct s_score *next;
    }       t_score;

    char *createarray(char *nb);
    char *longtochar(long long nblist);
    void my_rev_list(t_score **begin);
    t_score *lecturescore();
    int loosescreen(sfRenderWindow *window, long long score);
    int menu();
    void affiche();
    long long jeu(sfRenderWindow *window);
    void save(t_score *list);
    char *inttocharspe(int combo);

#endif /* !MY_H_ */
