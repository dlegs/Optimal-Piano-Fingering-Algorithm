#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "note.h"

void initialize_note(note *n, char *buffer){
    int i;
    char letter;
    int number;
    int offset_num[9] = {0, 3, 15, 27, 39, 51, 63, 75, 87};
    int offset_letter[72];
    offset_letter['C'] = 0;
    offset_letter['D'] = 2;
    offset_letter['E'] = 4;
    offset_letter['F'] = 5;
    offset_letter['G'] = 7;
    offset_letter['A'] = 9;
    offset_letter['B'] = 11;

    i = 0;
    while(1){
        (n->spn)[i] = buffer[i];
        if(buffer[i] == 0){
            break;
        }
        i++;
    }

    if(strlen(n->spn) == 2){
        n->color = 0;
    } else {
        n->color = 1;
    }

    sscanf(n->spn, "%1c%1d", &letter, &number);
   
    if(!(n->color)){ /* white key */
        if(!number){
            if(letter == 'A'){
                n->id = 0;
            } else {
                n->id = 2;
            }
        } else {
            n->id = offset_num[number] + offset_letter[(int)letter];
        }
    } else { /* black key */
        if(!number){
            n->id = 1;
        } else {
            n->id = offset_num[number] + offset_letter[(int)letter] + 1;
        }
    }
}

int getID(note *n){
    return n->id;

}
int getColor(note *n){
    return n->color;
}
