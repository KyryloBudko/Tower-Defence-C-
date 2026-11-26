#include <stdio.h>
#include <stdlib.h>

#include "listeDouble.h"


//initListe ne fait pas de malloc, juste une initialisation à NULL du pointeur de liste
void initListe(T_liste *l){//razobratsa v etoi stroke
*l=NULL;
}


bool listeVide( T_liste l){
    return (l==NULL);
}

// Crée une cellule de liste contenant un pointeur vers une unité (Tunite)
// L'unité est créée ailleurs (ex: creeDragon) et on stocke simplement son adresse
T_liste createCell(Tunite* mydata)
{
    T_liste newL=(T_liste)malloc(sizeof(struct T_cell));
        if(newL==NULL)
            return NULL;
    newL->prec=NULL;
    newL->pdata=mydata;
    newL->suiv=NULL;
    return newL;
}

//A vous la suite
void afficheListeV1( T_liste l)
{
    T_liste cur=l;//pourquoi on fait copie?
    if(listeVide(l))
        printf("Liste est vide\n");
    else
        {
            while(cur!=NULL)
        {
            printf("%d ",cur->pdata->nom);
            cur=cur->suiv;
        }
        printf("\n");
        }
}

//verifications pour listVide sont pas neccessaire
//puisque on avait fait cela dans createCell
T_liste ajoutEnTete(T_liste l, Tunite* mydata)
{
    T_liste newL=createCell(mydata);
    if(newL==NULL) return NULL;
    if(listeVide(l)){
        newL->prec=NULL;
        newL->suiv=NULL;
    }
    else{
        newL->prec=NULL;
        newL->suiv=l;
        l->prec=newL;
    }
    return newL;
}

T_liste ajoutEnFin(T_liste l, Tunite* mydata)
{
    T_liste newL=createCell(mydata);
    if(newL==NULL && l!=NULL) return l;
    T_liste cur=l; // cur parcourt la liste sans modifier la tête
    if(l==NULL)
        return newL;
    else{
        while(cur->suiv!=NULL){//tant que node suiv pas vide on avance
            cur=cur->suiv;//a cette moment cur= le dernier node de la liste
        }
        newL->prec=cur;
        cur->suiv=newL;
        newL->suiv=NULL;
    }
    return l;//on retourne liste complet
}
//doit etre ici car si on met au debut on sauvgarde pas bon adr (2eme cel)
T_liste ajoutEnN(T_liste l,int pos,Tunite* mydata)
{
    if((l==NULL && pos!=0)|| pos<0){
        //printf("Liste est vide,pos=%d trop grand",pos);
        return l;
    }
    if(pos==0)
        return ajoutEnTete(l,mydata);
    T_liste cur=l;
    T_liste cellSuiv=NULL;
    int count=0;
    while(cur!=NULL && count<pos-1){
        cur=cur->suiv;
        count++;
    }
    if(cur==NULL){
            //printf("pos=%d est trop grand,longeur de la liste=%d",pos,count);
            return l;
    }
    if(cur->suiv==NULL){
         return ajoutEnFin(l,mydata);
    }
    cellSuiv = cur->suiv;

    T_liste newL=createCell(mydata);
    if(newL==NULL) return l;
    newL->prec=cur;
    cur->suiv=newL;
    newL->suiv=cellSuiv;
    cellSuiv->prec=newL;
    return l;
}
// On supprime la cellule de la liste, mais pas l'unité pointée par pdata
T_liste suppListeSansTouchData(T_liste l){
    if(l==NULL) return NULL;
    T_liste cur = l;
    while(cur != NULL){
        T_liste next = cur->suiv;
        free(cur);
        cur = next;
    }
    return NULL;
}
T_liste suppEnTete(T_liste l){
    if(l==NULL)
        return NULL;
    T_liste celASup=l;
    T_liste celSuiv=l->suiv;
    if(celSuiv!=NULL)
        celSuiv->prec=NULL;

    free(celASup->pdata);
    free(celASup);

    return celSuiv;
}

T_liste suppEnFin(T_liste l){
        T_liste cur=l;
        T_liste celAGard=NULL;
        if(l==NULL){
            return NULL;
        }
        if(l->suiv==NULL){
            return suppEnTete(l);
        }
        else{
            while(cur->suiv!=NULL){
                cur=cur->suiv;
            }
            celAGard=cur->prec;
            free(cur->pdata);
            free(cur);
            celAGard->suiv=NULL;
        }
        return l;
}

T_liste suppEnN(T_liste l, int pos){
    T_liste cur=l;
    T_liste celPrec=NULL,celSuiv=NULL;
    int count=0;
    if(pos<0) return l;
    if(l==NULL){
        //printf("Liste est vide,impossible suprimer en %d\n",pos);
        return NULL;
    }

    if(pos==0)
        return suppEnTete(l);
    while(cur!=NULL && count<pos){
        cur=cur->suiv;
        count++;
    }
    if(cur==NULL){
        //printf("val de pos=%d est trop grand,list cintient %d elements",pos,count);
        return l;
    }
    if(cur->suiv==NULL)
        return suppEnFin(l);

    celPrec=cur->prec;
    celSuiv=cur->suiv;

    celPrec->suiv=celSuiv;
    celSuiv->prec=celPrec;
    free(cur->pdata);
    free(cur);
    return l;
}

T_liste suppCellule(T_liste l, T_liste cellASup){
    if(l == NULL || cellASup == NULL)
        return l;
    if(cellASup == l){
        return suppEnTete(l);
    }
    if(cellASup->suiv == NULL){
        return suppEnFin(l);
    }
    // cas 3 : cellule au milieu
    T_liste celPrec = cellASup->prec;
    T_liste celSuiv = cellASup->suiv;

    celPrec->suiv = celSuiv;
    celSuiv->prec = celPrec;

    free(cellASup->pdata);
    free(cellASup);

    return l;
}

T_liste getptrFirstCell(T_liste l){
    if(l==NULL) return NULL;
    T_liste head=l;
    while(head->prec!=NULL)
        head=head->prec;
    return head;
}

T_liste getptrLastCell(T_liste l){
    if(l==NULL) return NULL;
    T_liste tail=l;
    while(tail->suiv!=NULL)
        tail=tail->suiv;
    return tail;
}

T_liste getptrNextCell(T_liste l){
    if(l==NULL || l->suiv==NULL) return NULL;
    T_liste nextCell=l->suiv;
    return nextCell;
}

T_liste getptrPrevCell(T_liste l){
    if(l==NULL || l->prec==NULL) return NULL;
    return l->prec;
}

Tunite* getPtrData(T_liste l)
{
    if (l == NULL)
        return NULL;
    return l->pdata;
}
//Permuter le contenu de deux cellules ( ! ) via les pointeurs sur données
void swapPtrData( T_liste source, T_liste destination ){
    if(source==NULL || destination==NULL) return;
    Tunite *tmp=NULL;

    tmp=source->pdata;
    source->pdata=destination->pdata;
    destination->pdata=tmp;
}

int getNbreCell(T_liste l){
    if(l==NULL) return 0;
    T_liste cur=l;
    int count=0;
    while(cur!=NULL){
        cur=cur->suiv;
        count++;
    }
    return count;
}

/*
int getSizeBytes(T_liste l){
    if(l==NULL) return 0;
    int nbCell=getNbreCell(l);
    return nbCell * (sizeof(struct T_cell) + sizeof(Tunite));
}

T_liste creatNewListeFromFusion(T_liste l1, T_liste l2){
    T_liste copListOne=l1;
    T_liste copListTwo=l2;
    T_liste newlist=NULL;

    int size=getNbreCell(copListOne) + getNbreCell(copListTwo);

    while(copListOne!=NULL){
        newlist=ajoutEnFin(newlist,*(copListOne->pdata));
        copListOne=copListOne->suiv;
        }


    while(copListTwo!=NULL){
        newlist=ajoutEnFin(newlist,*(copListTwo->pdata));
        copListTwo=copListTwo->suiv;
    }

    int nbInNewList=getNbreCell(newlist);
    if(size==nbInNewList)
        return newlist;
    else{
        printf("Fusion a ete pas fait correctement");
        return NULL;
    }
}
*/

T_liste addBehind(T_liste debut, T_liste suite){
    if(debut==NULL) return suite;
    if(suite==NULL) return debut;
    T_liste LastCelleOfFirst=getptrLastCell(debut);
    T_liste firstCellOfSecond=getptrFirstCell(suite);

    LastCelleOfFirst->suiv=firstCellOfSecond;
    firstCellOfSecond->prec=LastCelleOfFirst;
    return debut;

}

T_liste findCellbyNom(T_liste l, int data){
    T_liste ptr=l;
    if(l==NULL) return NULL;
    while(ptr!=NULL &&((int)ptr->pdata->nom!=data)){
        ptr=ptr->suiv;
    }
    if(ptr==NULL){
        return NULL;
    }
    return ptr;
}
T_liste findUniteInCell(T_liste l, Tunite* data){
    T_liste ptr=l;
    if(l==NULL) return NULL;
    while(ptr!=NULL &&(ptr->pdata!=data)){
        ptr=ptr->suiv;
    }
    if(ptr==NULL){
        return NULL;
    }
    return ptr;
}

/*
int getOccurences(T_liste l, int data){
    int count=0;
    if(l==NULL) return count;
    T_liste cur=l;

    while(cur!=NULL){
        if(*(cur->pdata)==data) count++;
        cur=cur->suiv;
    }
    return count;
}

void afficheListeV2( T_liste l){
    T_liste cur=getptrFirstCell(l);
    int nb= getNbreCell(l);
    for(int i=0;i<nb;i++){
        int *data=getPtrData(cur);
        printf("%d ",*data);
        cur=getptrNextCell(cur);
    }
}
*/





