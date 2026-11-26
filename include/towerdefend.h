#ifndef TOWERDEFEND_H_INCLUDED
#define TOWERDEFEND_H_INCLUDED

#define LARGEURJEU 11
#define HAUTEURJEU 19
#define NBCOORDPARCOURS 34
#define X 0
#define Y 1

#include "typesJeu.h"
#include "listeDouble.h"



typedef T_liste TListePlayer; //////////////////MODULE_list
typedef Tunite* ** TplateauJeu;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des pointeurs (Tunite*)
////
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);
void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite,TplateauJeu jeu);
void supListTemp(TListePlayer *l);


TplateauJeu AlloueTab2D(int largeur, int hauteur);
void afficheCoordonneesParcours(int **t, int nbcoord);
int **initChemin();         //retourne le chemin emprunter par la horde, sous forme d'un tableau[NBCOORDPARCOURS][2]
void freeChemin(int **tab);

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

Tunite *creeTourSol(int posx, int posy);
Tunite *creeTourAir(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);

Tunite *creeArcher(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);
Tunite *creeDragon(int posx, int posy);

Tunite *creerRandomEnnemi(int posx,int posy);
Tunite *creerRandomTour(int posx,int posy);

//fonction aux
int distanceTire(Tunite* unit_one,Tunite* unit_two);
bool attaquePossible(Tunite *UniteAttaquante,Tunite *Unite);
bool estUnTourDefense(Tunite *unite);
bool appartienAHorde(Tunite *unite);
bool appartienARoi(Tunite *unite);
bool estUnAmi(Tunite *uniteOne,Tunite *uniteTwo);

// fonctions du noyau que vous avez à coder


TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante) ; //retourne la liste des cibles possibles
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);
bool tourRoiDetruite(TListePlayer player);
void combat(SDL_Surface *surface , Tunite * UniteAttaquante, Tunite * UniteCible);  //qui utilise dessineAttaque (de maSDL.h)



#endif // TOWERDEFEND_H_INCLUDED
