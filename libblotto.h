#include <stdlib.h>
#include <stdbool.h>
#include "string_key.h"
#include "gmap.h"

/**
 * Headers for helper functions contained in libblotto
 * Author: Kadidia Sylla 
 */

/* Find index in line of given character */
int find_index(const char *s, char c);

/* Distribute points for each player given value in hash map */
void points(int* distribution1, int* distribution2, int* pointlist, double *score1, double *score2, int length);

/* Use hash map to extract values from keys and the pointlist to determine points for each player */
void matchup(char* line, gmap *gmap, int* pointlist, int length);

/* Function to read in entries and store to hash map */
void read_entry(char *line, int n, gmap *map);

/* Function to read in line. Uses read_entry */
gmap *take_input(gmap *map, char *line, int argc);

/* Function to free each value */
void free_value(const void *key, void *value, void *arg);
