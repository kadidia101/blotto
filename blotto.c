#define _GNU_SOURCE
#include <stdio.h>
#include "string_key.h"
#include "libblotto.h"

/**
 * Driver for blotto
 * Author: Kadidia Sylla
 */

int main (int argc, char *argv[]) {
    gmap *map = gmap_create(duplicate, compare_keys, hash29, free);

    char *line = NULL;
    size_t linelen = 0;

    int* pointlist;
    int n = argc - 1;
    pointlist = calloc(n, sizeof(int));
    for (int i = 1; i < argc; i++) {
        pointlist[i - 1] = atoi(argv[i]);
    }

    while (getline(&line, &linelen, stdin) > 1) {
        map = take_input(map, line, argc);
    }
    while (getline(&line, &linelen, stdin) > 1) {
        matchup(line, map, pointlist, argc - 1);
    }
    if (line != NULL) {
        free(line);
    }
    free(pointlist);
    gmap_for_each(map, free_value, NULL);
    gmap_destroy(map);

    return 0;
}

