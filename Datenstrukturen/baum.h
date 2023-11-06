#ifndef BAUM_H
#define BAUM_H

struct binaerer_baum
{
    char keyword[255];
    int charcount;
    struct Liste_s *list;
    struct binaerer_baum *left;
    struct binaerer_baum *right;
};

typedef struct binaerer_baum BAUM_T;

BAUM_T *createnewTreeNode(char element[], char zeichen);
BAUM_T *EinfuegenTree(BAUM_T *wurzel, char string[]);
BAUM_T *search_Baum(BAUM_T *baum, char zeichen[]);

#endif