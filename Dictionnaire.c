#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char a[27];
    char b[27];
}traduction;

char* recherche(traduction *dico,int n,char *s)  //recherche decotomique
{
    int x=n/2;                                   //x est le milieu de tableau
    if (strcmp(s,(dico+x)->a)==0)                //si le condition est vérifié 's' existe
        return (dico+x)->b;
    if(n<=0)                                     //si n<0 donc 's' n'existe pas dans le dictionnaire
        return NULL;
    else if (strcmp(s,(dico+x)->a)>0)            
        return recherche(dico+x+1,n-x-1,s);      //on cherche dans le demi tableau droit si la condition est vérifié
    return recherche(dico,n-x-1,s);              //else on cherche dans le demi tableau gauche
}

int nombre_espaces(char *s)
{
    int n=0;
    for(int i=0;s[i]!='\0';i++)
        if(s[i]==' ')
            n++;
    return n;
}

char **decoupe(char *s)
{
    char **ch;                             //'ch' tableau de chaine
    int j=0,k=0;                           //'j' compteur, 'k' longueur des mots
    int x=nombre_espaces(s);
    ch=(char **)malloc(sizeof(char *)*x+2);
    for(int i=0;i<x;i++)
    {
        k=strchr(s,' ')-s;                 //longueur du mot
        *(ch+i)=(char *)malloc(k+1);       //allocation avec la même longueur du mot + \0
        strncpy(*(ch+i),s,k);
        *(*(ch+i)+k)='\0';
        s+=k+1;                            //faire sortir le mot traité de la chaine
    }
    *(ch+x)=(char *)malloc(strlen(s));
    strcpy(*(ch+x),s);                     //l'ajout du dernier mot
    *(ch+x+1)=NULL;
    return ch;
}

char *reconstruit(char **tab)
{
    char *ch;
    int i;
    ch=(char *)malloc(strlen(*tab)+2);
    strcpy(ch,*tab);
    strcat(ch," ");
    for(i=1;*(tab+i+1)!=NULL;i++)
    {
        ch=realloc(ch,strlen(ch)+strlen(*(tab+i)));         //on modifie la taille de mémoire allouer en fonction de nombre des mots
        strcat(ch,*(tab+i));
        strcat(ch," ");
    }
    ch=realloc(ch,strlen(ch)+strlen(*(tab+i)));             //traitement de dernier mot
    strcat(ch,*(tab+i));
    return ch;
}

char *traducteur(traduction *dico,int n, char *s)
{
    char **ch=decoupe(s);                           //phrase découpé
    char *t;                                        
    int i,j;
    for(i=0;ch[i+1]!=NULL;i++)
    {
        t=recherche(dico,n,ch[i]);
        if(t==NULL)
            continue;                               //si le mot ne pas existante dans le dictionnaire donc on la recrire le même
        strcpy(ch[i],t);                            //remplacement de mot par sa traduction
    }   
    j=strlen(ch[i]);
    if(ch[i][j-1]=='\n')                            //si on utilise fgets '\n' s'ajoute a la fin de chaine, il faut l'éléminer
        ch[i][j-1]='\0';
    t=recherche(dico,n,ch[i]);
    if(i==0)                                        //si on entre un seule mot
    {
        if(t==NULL)
            return ch[i];
        else
            return t;
    }
        if(t==NULL)                                 //traitement de dernier mot
            return reconstruit(ch);
        strcpy(ch[i],t);
    return reconstruit(ch);
}

void main()
{
    char c[5000];
    printf("Entrer un phrase a traduire (max 5000 caractere):\n");
    fgets(c,5000,stdin);
    traduction a[20]={{"bonjour","hello"},{"cinq","five"},{"deux","two"}
                     ,{"est","is"},{"huit","eight"},{"neuf","nine"},{"nom","name"}
                     ,{"quatre","four"},{"quel","what"},{"sept","seven"},{"six","six"}
                     ,{"trois","three"},{"un","one"},{"votre","your"}};
    printf("%s",traducteur(a,14,c));
}