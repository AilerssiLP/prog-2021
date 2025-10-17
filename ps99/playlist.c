#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "playlist.h"
#include "track.h"

struct playlist* create_playlist(char* name)
{
    if(name == NULL)
        return NULL;

    if(strlen(name) > 100)
        return NULL;

    struct playlist* playlist = calloc(1, sizeof(struct playlist));
    playlist->name = calloc(strlen(name)+1, sizeof(char));
    strcpy(playlist->name,name);
    playlist->mode = REPEAT;
    return playlist;
}

void append_track_to_playlist(struct playlist *playlist, struct track *track)
{
    if(playlist == NULL)
        return;

    if(track == NULL)
        return;

    playlist->duration = playlist->duration + track->duration;
    playlist->size = playlist->size+1;
    
    struct entry* new_entry = calloc(1,sizeof(struct entry));
    new_entry->track = track;

    printf("blabla\n");

    if(playlist->first != NULL)
    {
        struct entry* current_entry = playlist->first;
        while(current_entry->next != NULL)
            current_entry = current_entry->next;
        
        current_entry->next = new_entry;
        new_entry->prev = current_entry;
    }
    else
    {
        playlist->current = new_entry;
        playlist->first = new_entry;
        return;
    }  
}

struct track* play(struct playlist* playlist)
{
    if(playlist == NULL || playlist->current == NULL)
        return NULL;

    printf("Teraz hrám pieseň '%s' z '%s'\n", playlist->current->track->title, playlist->name);

    if(playlist->mode == REPEAT)
    {
        if(playlist->current->next == NULL)
            playlist->current = playlist->first;
        else
            playlist->current = playlist->current->next;
    }
    else if(playlist->mode == DONT_REPEAT)
    {
        if(playlist->current->next != NULL)
            playlist->current = playlist->current->next;
    } else if(playlist->mode == ONE_SONG)
    {
        
    }

    return playlist->current->track;
}

struct track* next(struct playlist* playlist)
{
    if(playlist == NULL || playlist->first == NULL)
        return NULL;

    if(playlist->current->next != NULL)
        playlist->current = playlist->current->next;

    return playlist->current->track;
}

struct track* prev(struct playlist* playlist)
{
    if(playlist == NULL || playlist->first == NULL)
        return NULL;

    if(playlist->current->prev != NULL)
        playlist->current = playlist->current->prev;

    return playlist->current->track;
}

void change_mode(struct playlist* playlist, enum play_mode mode)
{
    if(playlist == NULL)
        return;

    if(mode == DONT_REPEAT || mode == REPEAT || mode == ONE_SONG)
        playlist->mode = mode;   
}

void free_playlist(struct playlist* playlist)
{
    if(playlist != NULL)
    {
        free(playlist);
    }
}


int main()
{

    struct playlist* playlist= create_playlist("BOI");
    append_track_to_playlist(playlist, create_track("ree",366));
    append_track_to_playlist(playlist, create_track("re",300));
    append_track_to_playlist(playlist, create_track("r",200));
    play(playlist);
    next(playlist);
    prev(playlist);
    change_mode(playlist, DONT_REPEAT);
    free_playlist(playlist);
    struct track* track= create_track("Dievca moje", 100);
    free_track(track);
}
