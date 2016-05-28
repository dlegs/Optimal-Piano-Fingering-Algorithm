#include <stdlib.h>
#include <stdio.h>
#include "tables.h"

#define ROWS 14
#define COLUMNS 13

void initialize_tables(){
    int i, j, r, d;
    FILE *table_ww, *table_wb, *table_bw, *table_bb;

    /* initialize white to white table */    
    table_ww = fopen("table_ww.txt", "r");
    for(i = 0; i < ROWS; i++){
        fscanf(table_ww, "%d", &r);
        for(j = 0; j < COLUMNS; j++){
            fscanf(table_ww, "%d", &d);
            ww[r][j] = d; 
        }
    } 

    /* initialize white to black table */    
    table_wb = fopen("table_wb.txt", "r");
    for(i = 0; i < ROWS; i++){
        fscanf(table_wb, "%d", &r);
        for(j = 0; j < COLUMNS; j++){
            fscanf(table_wb, "%d", &d);
            wb[r][j] = d; 
        }
    } 

    /* initialize black to white table */    
    table_bw = fopen("table_bw.txt", "r");
    for(i = 0; i < ROWS; i++){
        fscanf(table_bw, "%d", &r);
        for(j = 0; j < COLUMNS; j++){
            fscanf(table_bw, "%d", &d);
            bw[r][j] = d; 
        }
    } 

    /* initialize black to black table */    
    table_bb = fopen("table_bb.txt", "r");
    for(i = 0; i < ROWS; i++){
        fscanf(table_bb, "%d", &r);
        for(j = 0; j < COLUMNS; j++){
            fscanf(table_bb, "%d", &d);
            bb[r][j] = d; 
        }
    } 

    /* close files */
    fclose(table_ww);
    fclose(table_wb);
    fclose(table_bw);
    fclose(table_bb);
}

