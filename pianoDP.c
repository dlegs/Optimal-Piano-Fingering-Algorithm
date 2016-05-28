#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "tables.h"
#include "song.h"
#include "note.h"

#define NUM_ROWS 52
#define NUM_COLUMNS 13
#define NUM_FINGERS 5
#define MAX_DIFFICULTY 4

/* input is a test file with scientific pitch notation ... makes it very easy to decode */

/* these two functions calculate optimal fingering for a song played with one hand, only one note at a time, same finger can't play consecutive notes */
void piano_DP_simple(song *s);
int piano_DP_Aux_simple(song *s, int **memo, int index, int last, int finger);

/* calculates difficulty in going from note q with finger f to note q with finger g */
int difficulty(song *s, int p, int f, int q, int g);

/* makes sure that transition is viable ... some transitions are impossible are in our model */
int viable(int f, int g);

/* min function */
int min(int current, int new);

/* free memo matrix */
void freeMemo(int **memo, int length);

/* void printTrace(trace **memo); */

int main(int argc, char **argv){

    song s; 

    if(argc != 2){
        fprintf(stderr, "Usage: %s <intput_song.txt>", argv[0]);
        exit(1);
    }

    initialize_tables();
    initialize_song(&s, argv[1]);
    piano_DP_simple(&s);
    
    return 0;

}

void piano_DP_simple(song *s){
    int i, j, optimal, length;
    int **memo; /* matrix to hold solutions to subproblems */
    length = s->length; /* for better locality of reference */

    /* initialize memo table to have impossible values */
    memo = (int **)malloc(sizeof(int *) * length);
    for(i = 0; i < length; i++){
        memo[i] = (int *)malloc(sizeof(int) * (NUM_FINGERS + 1)); /* want to use array indexex 1 through 5 so allocate one extra spot */
        for(j = 1; j <= NUM_FINGERS; j++){ /* initialize to impossible values */
            memo[i][j] = -1;
        }
    }   

    /* find the minimum difficulty starting the song with each finger, and then take the minimum of that */
    optimal = length * (MAX_DIFFICULTY + 1); /* set it to an impossibly high value */
    for(i = 1; i <= 5; i++){
        optimal = min(optimal, piano_DP_Aux_simple(s, memo, 0, i, length-1));
    } 

    printf("Least difficult way to play this song: %d\n", optimal);
    /* printTrace(memo); */

    /* free memory allocated for memo table */
    freeMemo(memo, length);   
}


int piano_DP_Aux_simple(song *s, int **memo, int note, int f, int n){
   
    int i, optimal;
    if(memo[note][f] >= 0){
        return memo[note][f];
    } 
    if(note == n){
        optimal = 0;
    } else {
        optimal = s->length * (MAX_DIFFICULTY + 1); /* higher than any possible value ... equivalent to every transition having a difficulty of 5, which is impossible */ 
        for(i = 1; i <= 5; i++){       
            /* just makes sure that it is a viable finger transition ... some are impossible so there is no need to check them */
            if(viable(f, i)){
                optimal = min(optimal, piano_DP_Aux_simple(s, memo, note+1, i, n) + difficulty(s, note, f, note+1, i));
            }
        }
        memo[note][f] = optimal;
    }
    return optimal;
}

int difficulty(song *s, int p, int f, int q, int g){
    note *lower, *upper;
    int low_f, up_f;
    int stretch;
    int row_index;

    /* need to switch directions if going down the piano */
    
    if(getID(s->notes + p) < getID(s->notes + q)){
        lower = s->notes + p;
        upper = s->notes + q;
        low_f = f;
        up_f = g;
    } else {
        lower = s->notes + q;
        upper = s->notes + p;
        low_f = g;
        up_f = f;
    }

    stretch = getID(upper) - getID(lower);
    row_index = low_f * 10 + up_f;
    if(!getColor(lower)){ 
        if(!getColor(upper)){ /* both notes are white */
            return ww[row_index][stretch];    
        } else { /* lower note is white and upper note is black */
            return wb[row_index][stretch];    
        }
    } else {
        if(!getColor(upper)){ /* lower note is black and upper note is white */
            return bw[row_index][stretch];    
        } else { /* both notes are black */
            return bb[row_index][stretch];    
        }
    }   
}

int viable(int f, int g){
    /* needs to pass all tests to be a viable transition */
    if(f == g)
        return 0;
    if(f == 3 && g == 2)
        return 0;
    if(f == 4 && (g == 2 || g == 3))
        return 0;
    if(f == 5 && (g > 1))
        return 0;

    return 1;
    
}

int min(int current, int new){
    return (current > new) ? new : current;
}

void freeMemo(int **memo, int length){
    int i;
    for(i = 0; i < length; i++){
        free(*(memo + i));
    }
    free(memo);

}
