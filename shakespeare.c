/*
Introduction
*/
#define MAX 255
#include <stdio.h>  /* standard from c */
#include <stdlib.h> /*constants like EXIT_SUCCESS or EXIT_FAILURE*/
#include <unistd.h> /* for arguments (getopt), R_OK */
#include <string.h> /* string copy and string length */
#include <time.h>   /* srand(time) */

#define DBG 1
#define DEBUG(fmt, ...) \
        do { if (DBG) fprintf(stderr, "\n%s:%d:%s(): " fmt "\n", __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

enum
{
    OFF,
    ON
};

struct
{
    int s;
    int l;
    int f;
} optflags = {ON, OFF, OFF};

struct Liste_s
{
    char info;
    int value;
    struct Liste_s *next;
};
typedef struct Liste_s LISTE_T;

struct binaerer_baum
{
    char keyword[MAX];
    int maxchars;
    struct Liste_s *list;
    struct binaerer_baum *left;
    struct binaerer_baum *right;
};
typedef struct binaerer_baum BAUM_T;

LISTE_T *insertNode(LISTE_T *aktuellenknoten, char zeichen);
BAUM_T *createnewTreeNode(char element[], char zeichen, int s_optarg);
BAUM_T *search_Baum(BAUM_T *baum, char zeichen[]);
BAUM_T *EinfuegenTree(BAUM_T *wurzel, char string[], int s_optarg);

void usage();
char randomChar(BAUM_T *head, char suchstr[]);
//void inorder(BAUM_T *root);

int main(int argc, char *argv[])
{
    int option;
    int zeichen = 0;
    int s_optarg = 1;
    int l_optarg = 0;
    int maxoutput = 0;
    FILE *fp = stdin;
    char z, c;
    char filename[MAX] = "";
    char suchstring[MAX] = "";
    char startstring[MAX] = "";

    // Startpunkt nur einmal vorne im Programm festlegen: Periode ist >= 2^^31 also ziemliich gross!
    srand((unsigned)time(NULL)); //start punkt festlegen

    while ((option = getopt(argc, argv, "hs:l:f:")) != -1)
    {

        switch (option)
        {
        case 'h':
            usage();
            break;
        case 's':
            s_optarg = atoi(optarg); // atoi = char* to int (ASCII to integer)
            break;
        case 'l':
            optflags.l = ON;
            l_optarg = atoi(optarg);
            maxoutput = l_optarg;
            break;
        case 'f':
            optflags.f = ON;
            strncpy(filename, optarg, MAX);
            break;
        case '?':
            usage();
            break;
        default:
            usage();
            break;
        }
    }
    if (optind < argc && optflags.f == OFF)
    {
        strncpy(filename, argv[optind], MAX);
    }
    if (strlen(filename) != 0)
    {
        if (access(filename, R_OK) == EXIT_SUCCESS) // check ob das file readable ist und beim returnwert kein fehler auftritt (EXIT_SUCCESS = 0)
        {
            fp = fopen(filename, "r");
        }
        else
        {
            printf("Error Lesbarkeit\n");
            exit(EXIT_FAILURE);
        }
    }
    // optflags.s ist doch immer ON ???!!! Was soll die Variable sagen?
    if (optflags.s == ON) 
    {
        BAUM_T *head = NULL;
        // Eingabephase
        while ((z = fgetc(fp)) && !feof(fp))
        {
            zeichen++;
            if (strlen(suchstring) == s_optarg + 1) // Länge + Folgezeichen erreicht ?
            {
                head = EinfuegenTree(head, suchstring, s_optarg);  // suchstring= suchstring + Folgezeichen !!
                for (int i = 0; i <= s_optarg + 1; i++)
                {
                    suchstring[i] = suchstring[i + 1];
                }
                suchstring[s_optarg] = z;
                suchstring[s_optarg + 1] = '\0';
            }
            else
            { // auffüllen auf Suchstringlänge
                strncat(suchstring, &z, 1);
            }
        } // Ende Eingabephase

        maxoutput = (optflags.l == ON)?l_optarg:zeichen;

        strncpy(startstring, head->keyword, MAX);
        printf("\n-----------------------------------------\n");
        printf("<%s>", startstring);
        maxoutput -= strlen(startstring); //erste ausgabe
        while (maxoutput != 0)
        {
            c = randomChar(head, startstring);
            printf("%c", c);
            maxoutput--;
            for (int i = 0; i < s_optarg; i++) // nur string nach links schieben
            {
                startstring[i] = startstring[i + 1];
            }
            startstring[s_optarg-1] = c; 
            startstring[s_optarg] = '\0';
        }
        printf("\n-----------------------------------------\n");
        free(head);
        fflush(stdout);
        return 0;
    }
}
void usage()
{
    printf("Usage : ./myprog [-h] [-s <n>] [-l <m>] [-f <inputfile>]\n");
    exit(EXIT_FAILURE);
}

BAUM_T *createNewTreeNode(char string[], char zeichen, int s_optarg)  // CamelCase Schreibweise beachten
{
    BAUM_T *newNode;
    newNode = malloc(sizeof(BAUM_T)); // newNode speicherreservieren in größe von BAUM_T
    if (newNode == NULL) // falls kein speicher für newNode reserviert werden kann
    {
        // Programm kann hier beendet werden
        printf("ERROR: Kein Speicher mehr!");
        exit(EXIT_FAILURE);
    }
    else
    {                                                // ansonsten definiere newNode
        newNode->list = malloc(sizeof(LISTE_T)); // newNode schiefgeht machte es keinen Sinn, deshalb hier
        strncpy(newNode->keyword, string, s_optarg); // information kopieren
        newNode->keyword[s_optarg] = '\0'; // Genau!
        newNode->maxchars = 1;
        newNode->right = NULL;
        newNode->left = NULL;          // zeigt auf ende der liste Ähhhh?????
        newNode->list->info = zeichen; //erstes zeichen nach suchstring erstellt listenanfang
        newNode->list->value = 1;
        newNode->list->next = NULL;
    }
    return newNode;
}

// Namenskonventinen !! Methoden beginnen mit kleinem Buchstaben!
BAUM_T *EinfuegenTree(BAUM_T *node, char string[], int s_optarg) // string ist suchstring + Folgezeichen
{ //übergibt suchstring in dem baum
    //BAUM_T *newTreeNode;
    char suchstring[s_optarg+1];
    strncpy(suchstring,string,s_optarg);
    suchstring[s_optarg]='\0';

    if (node == NULL){ // falls noch kein element am anfang ist
        node = createNewTreeNode(suchstring, string[s_optarg], s_optarg);
    }
    else{
        int vergleichswert = strncmp(suchstring, node->keyword, s_optarg); //vergleicht zeichenketten mit einander strcmp(cs, ct)
        if (vergleichswert > 0){   //>0 cs>ct
            /*folge knoten größer als vorheriger,rechter zeiger vom vorherigen knoten war auf null somit wird im nächsten durch gang ein neuer knoten erstellt(createnewTreeNode)*/
            node->right = EinfuegenTree(node->right, string, s_optarg);
        }
        if (vergleichswert < 0){ //<0 cs<ct
            /*folge knoten kleiner als vorheriger,linker zeiger vom vorherigen knoten war auf null somit wird im nächsten durch gang ein neuer knoten erstellt(createnewTreeNode)*/
            node->left = EinfuegenTree(node->left, string, s_optarg);
        }
        if (vergleichswert == 0){ //=0 cs==ct
            /*wenn der string aus dem übergebenen baumknoten einem bereits bestehenden baumknoten gleich ist,
            soll das zeichen in der liste, die mit dem aktuellen baumknoten verbunden ist, erst einmal gesucht werden und dann die value des zeichens erhöhen 
            oder falls das zeichen noch nicht in der liste ist hinzugefügt werden*/
            node->maxchars += 1;
            insertNode(node->list, string[s_optarg]);
        }
    }
    return node;
}


LISTE_T *insertNode(LISTE_T *aktuellenknoten, char zeichen) // im ersten fall vorgänger_knoten = root
{
    LISTE_T *neuer_knoten;
    if (aktuellenknoten->info == zeichen){ // gesuchtes zeichen gefunden
        aktuellenknoten->value += 1; //+= 1//erhöhte wertigkeit des zeichens um 1
        return aktuellenknoten;
    }
    else{ // 
        if (aktuellenknoten->next == NULL){ // ende gefunden -> neuen Knoten einfügen
            neuer_knoten = malloc(sizeof(LISTE_T));
            if (neuer_knoten == NULL)
            { // ist speicher für den neuen knoten reserviert worden?
                // Programm kann hier beendet werden
                printf("ERROR: Kein Speicher mehr!");
                exit(EXIT_FAILURE);
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

// Eingabe Baumknoten
// Return:  Zufalls char zurück
char randomChar(BAUM_T *head, char suchstr[]) // CamelCase !!!
{
    char retVal=' ';
    BAUM_T *myHead;
    LISTE_T *myListNode;

    myHead = search_Baum(head, suchstr);  // setzt head neu auf gefundenen Knoten !!!
    myListNode = myHead->list;  // current Listnode. Verändert sich während der Suche

    int intervall = myListNode->value;  // erste obere Intervallgrenze
    int randomnumber;

    int a=1;
    int e=myHead->maxchars;
    double range = e-a+1.0;
    randomnumber = a + (int)(range * rand() / (RAND_MAX + 1.0));

    while (intervall < randomnumber){ // head->list==NULL sollte nie passieren ->break;
        myListNode = myListNode->next; // zuletzt == NULL, aber dann greift auch intervall test
        if(myListNode == NULL){
            printf(".\n\n");
            printf("Sollte (fast) niemals erreicht werden. (Nur beim allerletzten Term ist das möglich)");
            exit(EXIT_SUCCESS);
        }
        intervall += myListNode->value; //intervall größe dem ersten wert in der liste anpassen
    }
    // intervall >= randomnumber
    retVal = myListNode->info;
    return retVal;
}
 
// 'zeichen' ist schlecht gewählter Name. Ist ein String!
// Gibt bei Treffer gefundenen Baumknoten zurück
// (was sehr umständlich ist.
// Besser hier gleich den Zufallschar ermitteln und den char zurückgeben)
BAUM_T *search_Baum(BAUM_T *baum, char zeichen[])
{
    // Besser mit nur einem Ausgang/return !!
    BAUM_T *retNode=NULL;
    int vergleich;
    vergleich = strcmp(zeichen, baum->keyword);
    if(baum == NULL){
        printf("DEBUG: Warum wird hier der Knoten NULL ??");
    }
    if (vergleich == 0){ // Baum sollte niemals NULL werden
        retNode = baum;
    }else if (vergleich < 0){
        retNode = search_Baum(baum->left, zeichen);
    }
    else if (vergleich > 0)
    {
        retNode = search_Baum(baum->right, zeichen);
    }
    return retNode;
}