#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"
#include "array.h"


//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }

    //POUR LA DEMO D'AFFICHAGE UNIQUEMENT, A SUPPRIMER
    //(les tours ici ne sont pas liées aux listes des unités de vos joueurs)
    //jeu[5][3]=creeTourSol(5,3);
    //jeu[3][3]=creeTourAir(3,3);
    jeu[4][1]=creeTourRoi(4,1);
    //jeu[4][15]=creeTourAir(4,15);
    jeu[5][17]=creeDragon(5,17);
    //FIN DEMO AFFICHAGE
}


/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, à partir d'un point x y donné

int **chemin  : tab de coordonnées x y du chemin
int *ichemin  : indice de la case du chemin d'où on part
int *xdepart, int *ydepart : valeur en x y de départ pouri la premiere case
int distance  : distance sur laquelle on va écrire des coordonnées dans le tab chemin
int *distanceMaxRestante : securité pour ne pas sortir de la plage d'indice de chemin
*/
void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int y;
        for (y=*ydepart;y>*ydepart-distance;y--){
            chemin[*ichemin][X]= *xdepart;
            chemin[*ichemin][Y]= y;
            (*ichemin)++;
        }
        *ydepart=y;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x<*xdepart+distance;x++){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x>*xdepart-distance;x--){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

int **initChemin(){
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);

    for (int j=0;j<NBCOORDPARCOURS;j++){
        chemin[j] = (int*)malloc(sizeof(int)*2);  //2 cases :indice 0 pour la coord en X, indice 1 pour la coord en Y
    }

    int ydepart = 18;  //et non 19
    int xdepart = 5;  //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;  //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS;

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 5, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);

    return chemin;  //tab2D contenant des pointeurs
}

void afficheCoordonneesParcours(int **chemin, int nbcoord){
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++){
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonnées\n");
}

void freeChemin(int **tab){
    for (int j=0;j<NBCOORDPARCOURS;j++){
        free(tab[j]);  //libere chaque case, qui est un tableau de 2 cases
    }
    free(tab);
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}

Tunite *creeTourSol(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 120;
    nouv->portee = 4;//5
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 180;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 180;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}


/*____________________________________________________________________________________*/
bool tourRoiDetruite(TListePlayer player){
    TListePlayer cellRoi=findCellbyNom(player,tourRoi);
    if(cellRoi==NULL || cellRoi->pdata->pointsDeVie<=0 ) return true;//IMPT :tout d'abbord on regarde cellRoi(puisque c dans if verifie de gauche a droite)
    return false;
}


void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite){
    *player=ajoutEnTete(*player,nouvelleUnite);//ptr et NON copie!
}
void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite, TplateauJeu jeu){
    TListePlayer celAsup = findUniteInCell(*player, UniteDetruite);

    jeu[UniteDetruite->posX][UniteDetruite->posY] = NULL;
    *player = suppCellule(*player, celAsup);
}
void supListTemp(TListePlayer *l){
    *l = suppListeSansTouchData(*l);
}
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu){
    TListePlayer cur=player;
    Tunite *unitCur;
    while(cur!=NULL){
        unitCur=getPtrData(cur);//on prend unite courante de la liste
        if(jeu[unitCur->posX][unitCur->posY]==NULL)//on regarde si les coord sont libres dans la grille
            jeu[unitCur->posX][unitCur->posY]=unitCur;//si oui on confirme son positionnement

        cur=getptrNextCell(cur);

    }
}
//"Weighted random",probabilite de la creatuin depend du "poids"
Tunite *creerRandomEnnemi(int posx,int posy){
    int archerWeight=35;//35%
    int gargouilleWeight=35;//35%
    int chevalierWeight=20;//20%
    //int dragonWeight=10;//10%
    int randomWeight=rand()%100;
    if(randomWeight<archerWeight)
        return creeArcher(posx,posy);
    randomWeight-=archerWeight;
    if(randomWeight<gargouilleWeight)
        return creeGargouille(posx,posy);
    randomWeight-=gargouilleWeight;
    if(randomWeight<chevalierWeight)
        return creeChevalier(posx,posy);
    randomWeight-=chevalierWeight;
    return creeDragon(posx,posy);
}
Tunite *creerRandomTour(int posx,int posy){
    int tourAirWeight=50;
    //int tourSolWeight=50;
    int randomWeight=rand()%100;
    if(randomWeight<tourAirWeight)
        return creeTourAir(posx,posy);
    return creeTourSol(posx,posy);
}
//calcule en utilisant formule de Chebishev
//distance = max(|dx|, |dy|)
int distanceTire(Tunite* unit_one,Tunite* unit_two){
    int dx=abs((unit_one->posX)-(unit_two->posX));
    int dy=abs((unit_one->posY)-(unit_two->posY));
    if(dx>dy) return dx;
    return dy;
}
bool attaquePossible(Tunite *UniteAttaquante,Tunite *Unite){
    if(UniteAttaquante==NULL || Unite==NULL || UniteAttaquante==Unite) return false;
    int dist=distanceTire(UniteAttaquante,Unite);
    if(dist<=UniteAttaquante->portee){
        if(UniteAttaquante->cibleAttaquable==Unite->maposition || UniteAttaquante->cibleAttaquable==solEtAir)
            return true;
    }
    return false;
}
bool estUnTourDefense(Tunite *unite){
    if(unite->nom==tourAir || unite->nom==tourSol) return true;
    return false;
}
bool appartienAHorde(Tunite *unite){
    if(unite->nom==gargouille||unite->nom==archer||unite->nom==dragon||unite->nom==chevalier)
        return true;
    return false;
}
bool appartienARoi(Tunite *unite){
    if(appartienAHorde(unite)==false) return true;
    return false;
}
bool estUnAmi(Tunite *uniteOne,Tunite *uniteTwo){
    if(appartienAHorde(uniteOne)==true&&appartienAHorde(uniteTwo)==true) return true;
    if(appartienARoi(uniteOne)==true &&appartienARoi(uniteTwo)==true) return true;
    return false;
}

//x от posX - r до posX + r
//y от posY - r до posY + r
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante){
        TListePlayer listOfUnits=NULL;

        int x0=UniteAttaquante->posX;
        int y0=UniteAttaquante->posY;
        int porte=UniteAttaquante->portee;
        int minX=x0-porte;
        int maxX=x0+porte;
        int minY=y0-porte;
        int maxY=y0+porte;

        if(minX<0) minX=0;
        if(maxX>=LARGEURJEU-1) maxX=LARGEURJEU-1;
        if(minY<0) minY=0;
        if(maxY>=HAUTEURJEU-1) maxY=HAUTEURJEU-1;

        for(int y=minY;y<=maxY;y++){
            for(int x=minX;x<=maxX;x++){
                if(jeu[x][y]==NULL) continue;
                if(jeu[x][y]==UniteAttaquante)continue;
                if(estUnAmi(jeu[x][y],UniteAttaquante)==true) continue;
                if(estUnTourDefense(jeu[x][y])==true && appartienAHorde(UniteAttaquante)==true) continue;
                if(attaquePossible(UniteAttaquante,jeu[x][y])==true)
                    AjouterUnite(&listOfUnits,jeu[x][y]);
            }
        }
        return listOfUnits;
}
void combat(SDL_Surface *surface , Tunite * UniteAttaquante, Tunite * UniteCible){
    if(UniteAttaquante==NULL || UniteCible==NULL) return;
    if(UniteAttaquante->peutAttaquer==1){
        int *hp=&(UniteCible->pointsDeVie);
        *hp-=UniteAttaquante->degats;
        dessineAttaque(surface,UniteAttaquante,UniteCible);
        UniteAttaquante->peutAttaquer=0;
    }
    else return;
}
//Question au professeur:peut on utiliser fork() avec semaphore pour les deux joueur ?
void phaseCombat(SDL_Surface *surface ,TplateauJeu jeu,TListePlayer *playerRoi,TListePlayer *playerHorde){
        TListePlayer curListRoi=playerRoi;
        Tunite *curUnitRoi=getPtrData(curListRoi);
        while(curListRoi!=NULL){
            TListePlayer listOfUnitsRoi=quiEstAPortee(jeu,curUnitRoi);

        }
}

