#include <stdlib.h>
#include <stdio.h>
#include "song.h"


#define MAX_NOTE_LENGTH 8

void initialize_song(song *s, char *filename){
    /* going to pass in a test file with the sequence of notes in scientific pitch notation */
    /* example: the first A is A0, second A is A1, third A is A2, etc. */

    int i, counter;
    char buffer[MAX_NOTE_LENGTH];
    FILE *input;

    input = fopen(filename, "r");
    /* first scan through to get the number of notes */
    while(fscanf(input, "%s", buffer) != EOF){
        counter++;
    }
    s->length = counter;
    s->notes = (note *)malloc(sizeof(note) * counter);
    /* rewind the file position so that you are back at the beginning of the file */
    rewind(input);
    /* store notes in array of notes */
    for(i = 0; i < counter; i++){
        fscanf(input, "%s", buffer);
        initialize_note(s->notes + i, buffer);
    }
    
    fclose(input);

}

void delete_song(song *s){
    free(s->notes);

}
