#ifndef LISTE_H//include guard, schaut ob es eine überschneidung mit einer anderen headerdabei gibt
#define LISTE_H//definiert die headerdatei

struct Liste_s
{
    char info;
    int value;
    struct Liste_s *next;
};
typedef struct Liste_s LISTE_T;

LISTE_T *createlist(char element);
LISTE_T *search_Liste(LISTE_T *knotenlist, char zeichen);
LISTE_T *insertNode(LISTE_T *aktuellenknoten, char zeichen);

#endif//beendet definition