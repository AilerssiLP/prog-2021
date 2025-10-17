#include "bmp.h"

#include <stdlib.h>

void free_bmp_image(struct bmp_image* image) {

    bool img = image != NULL;
    bool data = false;
    bool header = false;

    if(img) {
        data = image->data != NULL;
    }

    if(img) {
        header = image->header != NULL;
    }

    if(header) {
        free(image->header);
    }

    if(data) {
        free(image->data);
    }

    if(img) {
        free(image);
    }

}

struct bmp_header* read_bmp_header(FILE* stream) {

    struct bmp_header *header = NULL;
    size_t bmp_header_size = sizeof(struct bmp_header);

    switch ((int)(stream == NULL)) {
        case 1:
            header = NULL;
            break;
        
        default:

            header = malloc(bmp_header_size);

            rewind(stream);

            if(fread(header, bmp_header_size, 1, stream) == 1) {
                
                if(header->type != 0x4d42) {

                    free(header);
                    header = NULL;

                }

            } else {

                free(header);
                header = NULL;

            }

            break;
    }

    return header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header) {

   	if(stream == NULL) {
		return NULL;
	}
	if(header == NULL) {
		return NULL;
	}

    size_t pix = sizeof(struct pixel);
	long padding = header->width % 4;

	struct pixel* pixels = malloc(pix * header->height * header->width);

	fseek(stream, 54, SEEK_SET);

	for(int y = 0; y < header->height; y++) {

		for(int z = 0; z < header->width; z++) {
			fread(pixels + y * header->width + z, pix, 1, stream);		
		}

		fseek(stream, padding, SEEK_CUR);	
	}

    return pixels;
}

struct bmp_image* read_bmp(FILE* stream) {

    if(stream == NULL) return NULL;

	struct bmp_image *img;
    img = (struct bmp_image *)calloc(1, sizeof(struct bmp_image));

    bool i = img != NULL;

    if(i) {
    	img->header = read_bmp_header(stream);
    }

    if(i) {
    	img->data = read_data(stream, img->header);
    }

    bool i_h = false;
    bool i_d = false;

    if(i) {
        i_h = img->header == NULL;
    }

    if(i) {
        i_d = img->data == NULL;
    }

    if(i && i_h) {
        fprintf(stderr, "Error: This is not a BMP file.\n");

        if(i && (i_h || i_d)) {
            free_bmp_image(img);
        }

        return NULL;
    }

    if(i && i_d) {
        fprintf(stderr, "Error: Corrupted BMP file.\n");

        if(i && (i_h || i_d)) {
            free_bmp_image(img);
        }

        return NULL;
    }

    if(i && (i_h || i_d)) {
        free_bmp_image(img);
    }

    if(i && (i_h || i_d)) {
        return NULL;
    }

    return img;
}

bool write_bmp(FILE* stream, const struct bmp_image* image) {

    bool stream_null = stream == NULL;
    bool image_null = image == NULL;

    if(stream_null) {
        return false;
    }

    if(image_null) {
        return false;
    } else {

        size_t bmp_header_size = sizeof(struct bmp_header);
        size_t bmp_data_pixel = sizeof(struct pixel);
        int position = 0;

        fwrite(image->header, bmp_header_size, 1, stream);

        for(int i = 0; i < image->header->height; i++) {

            for(int j = 0; j < image->header->width; j++) {

                fwrite(image->data + position, bmp_data_pixel, 1, stream);
                position++;

            }

            long padding = image->header->width % 4;
            for(int k = 0; k < padding; k++) {
                fwrite("", 1, 1, stream);
            }

        }

        return true;

    }

}
