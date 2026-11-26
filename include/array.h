#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
#include "typesJeu.h"
#include "cases.h"

typedef struct{
    Tunite** data;
    int length;
    int capacity;
}TarrayUnite;

typedef struct{
    TcaseScore* data;
    int length;
    int capacity;
}TarrayCaseScore;

TarrayUnite create_arrayUnite(int n);
void sort_arrayUnite_byHP(TarrayUnite* arr);
void free_arrayUnite(TarrayUnite* arr);

TarrayCaseScore create_arrayCaseScore(int n);
void sort_arrayCaseScore(TarrayCaseScore* arr);
void free_arrayCaseScore(TarrayCaseScore* arr);

#endif // ARRAY_H_INCLUDED
