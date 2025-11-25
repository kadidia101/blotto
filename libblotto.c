#include "libblotto.h"
#include <string.h>
#include <stdio.h>

/**
 * Helper functions for blotto
 * Author: Kadidia Sylla 
 */

int find_index(const char *s, char c) {
    int i = 0;
    for (; s[i] != '\0'; i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

void points(int* distribution1, int* distribution2, int* pointlist, double *score1, double *score2, int length) {
    double points[length];
    for (int i = 0; i < length; i++) {
        points[i] = (double)pointlist[i];
    }
    *score1 = 0;
    *score2 = 0;
    for (int i = 0; i < length; i++) {
        if (distribution1[i] > distribution2[i]) {
            *score1 += points[i];
        } else if (distribution1[i] < distribution2[i]) {
            *score2 += points[i];
        } else {
            *score1 += (points[i] / 2);
            *score2 += (points[i] / 2);
        }
    }

}

void matchup(char* line, gmap *gmap, int* pointlist, int length) {
    int index = find_index(line, ' ');
    if (index < 0) {
        fprintf(stderr, "Invalid input: matchup format");
        exit(1);
    }
    size_t len = strcspn(line, "\n");
    if (line[len] == '\n') {
        line[len] = '\0'; // remove new line
    }
    // adjust this to find player1 and player2
    // now that we have players' id and distribution, use another function to distibute points. 
    double score1, score2;
    // scan each line and save as player ids
    char player1[32];
    char player2[32];
    if (sscanf(line, "%31s %31s", player1, player2) != 2) {
        fprintf(stderr, "Failed to read in input\n");
        exit(1);
    }
    int *distribution1 = gmap_get(gmap, player1);
    int *distribution2 = gmap_get(gmap, player2);
    if (distribution1 == NULL || distribution2 == NULL) {
        fprintf(stderr, "Invalid input: player ID not found");
        exit(1);
    }
    points(distribution1, distribution2, pointlist, &score1, &score2, length);

    char *winner;
    char *loser;
    double winner_score;
    double loser_score;

    if (score1 >= score2) {
        winner = player1;
        winner_score = score1;
        loser = player2;
        loser_score = score2;
    } else {
        winner = player2;
        winner_score = score2;
        loser = player1;
        loser_score = score1;
    }

    printf("%s %.1f - %s %.1f\n", winner, winner_score, loser, loser_score);
}

void read_entry(char *line, int n, gmap *map) {
    int index = find_index(line, ',');
    if (index < 0) {
        fprintf(stderr, "Invalid input: error in finding comma");
        exit(1);
    } else if (index > 31) {
        fprintf(stderr, "Invalid input: length");
        exit(1);
    }
    // player id comes before this index. set comma equal to null
    char *id = line;  
    //strncpy(id, line, index);  // Copy the ID from the line.
    id[index] = '\0';

    // make pointer to one over after the comma and allocate memory for it
    char *pointer = line + index + 1;
    int *points = calloc(n, sizeof(int));

    for (size_t i = 0; i < n; i++) {
        // check if not a digit
        if (sscanf(pointer, "%d", &points[i]) != 1) {
            fprintf(stderr, "Invalid input: input format");
            exit(1);
        }
        pointer += find_index(pointer, ',') + 1;
    }
    gmap_put(map, id, points);
}

gmap *take_input(gmap *map, char *line, int argc) {
    if (map == NULL || line == NULL) {
        return NULL;
    }
    
    // extract input
    read_entry(line, argc - 1, map);
    return map;
}

void free_value(const void *key, void *value, void *arg)
{
    free((int *)value);
}
