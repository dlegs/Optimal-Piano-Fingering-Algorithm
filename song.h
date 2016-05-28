#ifndef _song_h
#define _song_h

#include "note.h"

typedef struct{
    int length;
    note *notes;
} song;

/* takes an input file of notes in scientific pitch notation and convertes them to integers numbered 0 - 87 ... one for each note on the piano ... this will make it very each to calculate the stretch between consecutive notes */
void initialize_song(song *s, char *filename);

/* deletes the memory associates with the array of notes */
void delete_song(song *s);


#endif
