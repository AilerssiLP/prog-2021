#include "hof.h"
#include <stdlib.h>
#include <stdio.h>
#include "ui.h"
#include "k.h"
#include <math.h>

int main(){
// game is won
struct game game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};



printf("is won: %d\n", is_game_won(game));
// stdout: 1

bool result = update(&game, 0, 1);
printf("%d",result);

struct player list[10];
struct player player = {
    .name = "john",
    .score = 400
};
int size = load(list);
bool result1 = add_player(list, &size, player);
printf("%d",result1);
    //printf("%d",size);
save(list,size);
    //printf("%d",size);
render(game);
add_random_tile(&game);
}
