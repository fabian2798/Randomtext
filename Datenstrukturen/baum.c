
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baum.h"
#include "liste.h"


BAUM_T *createnewTreeNode(char element[], char zeichen)
{
    BAUM_T *newNode;
    newNode = malloc(sizeof(BAUM_T)); // newNode speicherreservieren in größe von LISTE_T
    newNode->list = malloc(sizeof(LISTE_T));
    if (newNode == NULL) // falls kein speicher für newNode reserviert werden kann
    {
        printf("Speicher voll");
        return NULL;
    }
    else
    { // ansonsten definiere newNode
        newNode->right = NULL;
        newNode->left = NULL;          // zeigt auf ende der liste
        newNode->list->info = zeichen; //erstes zeichen nach suchstring erstellt listenanfang
        newNode->list->value = 1;
        newNode->list->next = NULL;
        strncpy(newNode->keyword, element, 255); // information kopieren
    }
    return newNode;
}

BAUM_T *search_Baum(BAUM_T *baum, char zeichen[])
{
    int vergleich;
    while (baum != NULL)
    { // bis ende
        vergleich = strcmp(zeichen, baum->keyword);
        if (vergleich == 0)
        {
            printf("gefunden");
            return baum; //string bereits im baum
        }
        if (baum->left != NULL) //blatt nicht erreicht
        {
            search_Baum(baum->left, zeichen);
        }
        if (baum->right != NULL) //blatt nicht erreicht
        {
            search_Baum(baum->right, zeichen);
        }
        break;
    }
    return NULL;
}
BAUM_T *EinfuegenTree(BAUM_T *wurzel, char string[])
{ //übergibt suchstring in dem baum
    BAUM_T *newTreeNode;
    if (wurzel == NULL)
    { // falls noch kein element am anfang ist
        wurzel = createnewTreeNode(string, string[s_optarg]);
    }
    else
    {
        int vergleichswert = strcmp(string, wurzel->keyword); //vergleicht zeichenketten mit einander strcmp(cs, ct)
        if (vergleichswert > 0)                               //>0 cs>ct
        {
            newTreeNode = createnewTreeNode(string, string[s_optarg]);
            wurzel->right = newTreeNode;
        }
        if (vergleichswert < 0) //<0 cs<ct
        {
            newTreeNode = createnewTreeNode(string, string[s_optarg]);
            wurzel->left = newTreeNode;
        }
        if (vergleichswert == 0) //=0 cs==ct
        {                        /*wenn der string aus dem übergebenen baumknoten einem bereits bestehenden baumknoten gleich ist,
            soll das zeichen in der liste, die mit dem aktuellen baumknoten verbunden ist, erst einmal gesucht werden und dann die value des zeichens erhöhen 
            oder falls das zeichen noch nicht in der liste ist hinzugefügt werden*/
            wurzel = search_Baum(wurzel, string);
            wurzel->list = insertNode(wurzel->list, string[s_optarg]);
        }
    }
    return wurzel;
}