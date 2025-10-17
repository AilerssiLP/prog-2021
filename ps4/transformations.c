#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "transformations.h"

struct bmp_image* flip_horizontally(const struct bmp_image* image) {

    if(image == NULL) {
        return NULL;
    }

    if(image->header == NULL) {
        return NULL;
    }

    if(image->data == NULL) {
        return NULL;
    }

    int height;
    int width;

    struct bmp_header *header_old = image->header;

    height = header_old->height;
    width = header_old->width;

    struct bmp_image *flipped = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    flipped->header = (struct bmp_header *)malloc(54);
    flipped->data = (struct pixel *)malloc(3 * height * width);

    memcpy(flipped->header, image->header, 54);

    for(int i = 0; i < height; i++) {

        int oposit = width - 1;

        for(int j = 0; j < width; j++) {

            flipped->data[i * width + oposit].red = image->data[i * width + j].red;
            flipped->data[i * width + oposit].green = image->data[i * width + j].green;
            flipped->data[i * width + oposit].blue = image->data[i * width + j].blue;

            oposit--;

        }
    }

    return flipped;
}

struct bmp_image* flip_vertically(const struct bmp_image* image) {

    if(image == NULL) {
        return NULL;
    }

    if(image->header == NULL) {
        return NULL;
    }

    if(image->data == NULL) {
        return NULL;
    }

    struct bmp_image *images[3];
    images[0] = rotate_right(image);
    images[1] = rotate_right(images[0]);

    struct bmp_image *i = flip_horizontally(images[1]);

    free_bmp_image(images[0]);
    free_bmp_image(images[1]);

    return i;
}

struct bmp_image* rotate_right(const struct bmp_image* image) {

    if(image == NULL) {
        return NULL;
    }

    if(image->header == NULL) {
        return NULL;
    }

    if(image->data == NULL) {
        return NULL;
    }

    int height;
    int width;
    int actual;
    int pixel_number;

    struct bmp_header *header_old = image->header;

    height = header_old->height;
    width = header_old->width;
    actual = -1;
    pixel_number = height * width;

    struct bmp_image *rotated = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    rotated->header = (struct bmp_header *)malloc(54);
    rotated->data = (struct pixel *)malloc(3 * pixel_number);

    memcpy(rotated->header, image->header, 54);

    struct bmp_header *header_new = rotated->header;

    header_new->height = width;
    header_new->width = height;
    header_new->image_size = 3 * pixel_number + (height % 4) * header_new->height;
    header_new->size = header_new->image_size + 54;

    for(int i = width - 1; i >= 0; i--) {
        for(int j = 0; j < height; j++) {

            actual += 1;

            rotated->data[actual].red = image->data[i + j * width].red;
            rotated->data[actual].green = image->data[i + j * width].green;
            rotated->data[actual].blue = image->data[i + j * width].blue;

        }
    }

    return rotated;
}

struct bmp_image* rotate_left(const struct bmp_image* image) {

    if(image == NULL) {
        return NULL;
    }

    if(image->header == NULL) {
        return NULL;
    }

    if(image->data == NULL) {
        return NULL;
    }

    struct bmp_image *images[3];
    images[0] = rotate_right(image);
    images[1] = rotate_right(images[0]);
    images[2] = rotate_right(images[1]);

    free_bmp_image(images[0]);
    free_bmp_image(images[1]);

    return images[2];
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep) {

    if(colors_to_keep == NULL) {
        return NULL;
    }

    int len;

    if(strlen(colors_to_keep) == 0) {
        len = 0;
    } else if(strlen(colors_to_keep) == 1) {
        len = 1;
    } else if(strlen(colors_to_keep) == 2) {
        len = 2;
    } else if(strlen(colors_to_keep) == 3) {
        len = 3;
    } else {
        return NULL;
    }

    if(image == NULL) {
        return NULL;
    }

    if(image->header == NULL) {
        return NULL;
    }

    if(image->data == NULL) {
        return NULL;
    }

    int height;
    int width;

    struct bmp_header *header_old = image->header;

    height = header_old->height;
    width = header_old->width;

    struct bmp_image *extracted = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    extracted->header = (struct bmp_header *)malloc(54);
    extracted->data = (struct pixel *)malloc(3 * height * width);

    memcpy(extracted->header, image->header, 54);

    for(int i = 0; i < len; i++) {

        switch(colors_to_keep[i]) {
            case 'r':
                break;
            case 'g':
                break;
            case 'b':
                break;
            default:

                if(extracted != NULL) {
                    free_bmp_image(extracted);
                }

                return NULL;

                break;
        }

    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {

            extracted->data[i * width + j].red = image->data[i * width + j].red;
            extracted->data[i * width + j].green = image->data[i * width + j].green;
            extracted->data[i * width + j].blue = image->data[i * width + j].blue;

            if(strchr(colors_to_keep, 'r') == NULL) {
                extracted->data[i * width + j].red = 0;
            }

            if(strchr(colors_to_keep, 'g') == NULL) {
                extracted->data[i * width + j].green = 0;
            }

            if(strchr(colors_to_keep, 'b') == NULL) {
                extracted->data[i * width + j].blue = 0;
            }
            
        }
    }

    return extracted;
}

struct bmp_image* scale(const struct bmp_image* image, float factor) {

    if(factor < 0) {
        return NULL;
    }

    if(image == NULL) {
        return NULL;
    }

    if(image->header == NULL) {
        return NULL;
    }

    if(image->data == NULL) {
        return NULL;
    }

    int new_height;
    int old_height;

    int new_width;
    int old_width;

    int pixel_number;

    struct bmp_header *header_old = image->header;

    new_height = (int)round(header_old->height * factor);
    old_height = header_old->height;

    new_width = (int)round(header_old->width * factor);
    old_width = header_old->width;

    pixel_number = new_height * new_width;

    struct bmp_image *scaled = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    scaled->header = (struct bmp_header *)malloc(54);
    scaled->data = (struct pixel *)malloc(3 * pixel_number);

    memcpy(scaled->header, image->header, 54);

    struct bmp_header *header_new = scaled->header;

    header_new->height = new_height;
    header_new->width = new_width;
    header_new->image_size = 3 * pixel_number + (new_width % 4) * new_height;
    header_new->size = header_new->image_size + 54;

    float my_new_factor = (float)new_height / old_height;

    for(int i = 0; i < new_height; i++) {
        for(int j = 0; j < new_width; j++) {
    
            int sh = (int)(i / my_new_factor);
            int sw = (int)(j * old_width) / new_width;
            int position = sh * old_width + sw;

            scaled->data[i * new_width + j].red = image->data[position].red;
            scaled->data[i * new_width + j].green = image->data[position].green;
            scaled->data[i * new_width + j].blue = image->data[position].blue;
            
        }
    }

    return scaled;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width) {

    if(image == NULL) {
        return NULL;
    }

    if(image->header == NULL) {
        return NULL;
    }

    if(image->data == NULL) {
        return NULL;
    }

    int final_pixel_width = start_x + width;
    int final_pixel_height = start_y + height;

    if(final_pixel_width > image->header->width) {
        return NULL;
    }

    if(final_pixel_height > image->header->height) {
        return NULL;
    }

    int pixel_number;
    pixel_number = height * width;

    struct bmp_header *header_old = image->header;

    struct bmp_image *cropped = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    cropped->header = (struct bmp_header *)malloc(54);
    cropped->data = (struct pixel *)malloc(3 * pixel_number);

    memcpy(cropped->header, image->header, 54);

    struct bmp_header *header_new = cropped->header;

    header_new->height = height;
    header_new->width = width;
    header_new->image_size = 3 * pixel_number + (width % 4) * height;
    header_new->size = header_new->image_size + 54;

    int new_img_position = 0;

    int h_start = header_old->height - height - start_y;
    int h_end = header_old->height - start_y;

    for(int i = 0; i < header_old->height; i++) {
        for(int j = 0; j < header_old->width; j++) {

            if(i >= h_start && i < h_end && j >= start_x && j < final_pixel_width) {
                
                cropped->data[new_img_position].red = image->data[i * header_old->width + j].red;
                cropped->data[new_img_position].green = image->data[i * header_old->width + j].green;
                cropped->data[new_img_position].blue = image->data[i * header_old->width + j].blue;

                new_img_position++;
            }

        }
    }

    return cropped;
}
