#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


LISTE_T *createlist(char element)
{
    LISTE_T *root;
    root = malloc(sizeof(LISTE_T)); // root speicherreservieren in größe von LISTE_T
    if (root == NULL)               // falls kein speicher für root reserviert werden kann
    {
        printf("Speicher voll");
        return NULL;
    }
    else
    {                      // ansonsten definiere root
        root->next = NULL; // zeigt auf ende der liste
        root->value = 1;
        root->info = element; // information kopieren
        return root;
    }
}
LISTE_T *search_Liste(LISTE_T *knotenlist, char zeichen)
{
    while (knotenlist != NULL)
    { // von anfang bis ende
        if (knotenlist->info == zeichen)
        {
            printf("%c gefunden", knotenlist->info); //gibt gesuchtes zeichen aus
            printf("%d mal\n", knotenlist->value);      //gibt häufigkeit des gesuchten zeichens aus
        }
        else
        { //ansonsten gib aktuelles zeichen aus + häufigkeit des aktuellen zeichens
            printf("%c", knotenlist->info);
            printf("%d\n", knotenlist->value);
        }
        if (knotenlist->next != NULL)
        {
            search_Liste(knotenlist->next, zeichen); //such weiter
        }
        break;
    }
    return NULL;
}
LISTE_T *insertNode(LISTE_T *aktuellenknoten, char zeichen) // im ersten fall vorgänger_knoten = root
{
    LISTE_T *neuer_knoten;
    if (aktuellenknoten->info == zeichen) // gesuchtes zeichen gefunden
    {
        aktuellenknoten->value += 1; //+= 1//erhöhte wertigkeit des zeichens um 1
        return aktuellenknoten;
    }
    else
    {
        if (aktuellenknoten->next == NULL) // ende gefunden
        {
            neuer_knoten = malloc(sizeof(LISTE_T));
            if (neuer_knoten == NULL)
            { // ist speicher für den neuen knoten reserviert worden?
                printf("Speicher voll");
                return NULL;
            }
            neuer_knoten->info = zeichen;
            neuer_knoten->value = 1;
            neuer_knoten->next = NULL;
            aktuellenknoten->next = neuer_knoten; // vorgängerknoten zeigt auf nachfolgeknoten
        }
        else
        {
            insertNode(aktuellenknoten->next, zeichen); // wiederholung des prozesses
        }
        return aktuellenknoten;
    }
}