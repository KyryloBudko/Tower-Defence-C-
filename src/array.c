#include <stdio.h>
#include <stdlib.h>

#include "array.h"

TarrayUnite create_arrayUnite(int n){
    TarrayUnite arr;
    arr.length=0;
    arr.capacity =n;
    arr.data=malloc(n * sizeof(Tunite*));
    return arr;
}
//EX of usage T_array a = create_array(10, sizeof(int));


void free_arrayUnite(TarrayUnite* arr) {
    free(arr->data);
    arr->data = NULL;
    arr->length = 0;
    arr->capacity=0;
}

void sort_arrayUnite_byHP(TarrayUnite* arr){

}

