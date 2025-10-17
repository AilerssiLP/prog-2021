#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "track.h"

struct track* create_track(const char* title, int duration){
    struct track* track = calloc(1, sizeof(struct track));
    track->title = calloc(strlen(title)+1, sizeof(char));
    strcpy(track->title, title);    
    track->duration = duration;
    return track;
}

void free_track(struct track* track){
    if(track != NULL){    
        free(track);
    }

}
