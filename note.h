#ifndef _note_h
#define _note_h

#define MAX_NOTE_LENGTH 8

typedef struct{
    char spn[MAX_NOTE_LENGTH];    /* scientific pitch notation */
    int id;         /* note id ... between 0 and 87 */
    int color;      /* 0 for white, 1 for black */
} note;

void initialize_note(note *n, char *buffer);
int getID(note *n);
int getColor(note *n);

#endif
