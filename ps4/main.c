#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "transformations.h"

int main(const int argc, const char ** argv) {

    FILE *f1 = fopen("assets/lenna.bmp", "r");
    FILE *f2 = fopen("assets/lenna_new.bmp", "w");

    struct bmp_image *img = read_bmp(f1);
    struct bmp_image *new_image = rotate_left(img);
    flip_vertically(NULL);
    extract(NULL, NULL);
    crop(NULL, 1, 2, 3, 4);
    free_bmp_image(scale(img, 5));

    write_bmp(f2, new_image);

    fclose(f1);
    fclose(f2);

    free_bmp_image(img);
    free_bmp_image(new_image);

    /*read_data(NULL, NULL);
    read_bmp(NULL);
    write_bmp(NULL, NULL);

    flip_vertically(NULL);

    rotate_left(NULL);*/

    return EXIT_SUCCESS;
}
