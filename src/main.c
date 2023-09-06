/*********************************************************************
 *  staramp - star amplification
 *  Copyright (c) 2023, Bob Mottram
 *  bashrc@tutanota.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "png2.h"
#include "staramp.h"

int main(int argc, char* argv[])
{
    int i, c, n, idx;
    char * filename = NULL;
    char output_filename[255];
    char dog_filename[255];
    char numstr[255];
    unsigned char * image_data = NULL;
    unsigned char * dog_image = NULL;
    unsigned int image_width=0;
    unsigned int image_height=0;
    unsigned int image_bitsperpixel=0;
    long * integral_image;
    int difference_of_gaussians = 8;
    int dog_threshold = 145;
    int amplify_with_dog = 80;
    int minimum_y = 0;
    int maximum_y = 0;
    int no_of_exclude_areas = 0;
    int exclude_areas[255][4];

    sprintf((char*)output_filename,"%s","result.png");
    sprintf((char*)dog_filename,"%s","dog.png");

    for (i=1;i<argc;i+=2) {
        if ((strcmp(argv[i],"-f")==0) ||
            (strcmp(argv[i],"--filename")==0)) {
            filename = argv[i+1];
        }
        if ((strcmp(argv[i],"-o")==0) ||
            (strcmp(argv[i],"--output")==0)) {
            sprintf((char*)output_filename,"%s",argv[i+1]);
        }
        if (strcmp(argv[i],"--dog")==0) {
            difference_of_gaussians = atoi(argv[i+1]);
        }
        if (strcmp(argv[i],"--dogthresh")==0) {
          dog_threshold = atoi(argv[i+1]);
        }
        if (strcmp(argv[i],"--dogamp")==0) {
          amplify_with_dog = atoi(argv[i+1]);
        }
        if (strcmp(argv[i],"--miny")==0) {
          minimum_y = atoi(argv[i+1]);
        }
        if (strcmp(argv[i],"--maxy")==0) {
          maximum_y = atoi(argv[i+1]);
        }
        if (strcmp(argv[i],"--exclude")==0) {
          idx = 0;
          n = 0;
          numstr[0] = 0;
          for (c = 0; c < strlen(argv[i+1]); c++) {
            if ((argv[i+1][c] >= '0') && (argv[i+1][c] <= '9')) {
              numstr[n++] = argv[i+1][c];
            }
            if ((argv[i+1][c] == ',') ||
                (argv[i+1][c] == ';') ||
                (c == strlen(argv[i+1])-1)) {
              if (numstr[0] != 0) {
                numstr[n] = 0;
                exclude_areas[no_of_exclude_areas][idx++] = atoi(numstr);
              }
              n = 0;
              numstr[0] = 0;
              if (idx == 4) {
                no_of_exclude_areas++;
                idx = 0;
              }
            }
          }
        }
    }

    /* was a file specified */
    if (filename == NULL) {
        printf("No image file specified\n");
        return 0;
    }

    image_data = read_png_file(filename, &image_width, &image_height, &image_bitsperpixel);
    if (image_data == NULL) {
        printf("Couldn't load image %s\n", filename);
        return 0;
    }
    if ((image_width == 0) || (image_height==0)) {
        printf("Couldn't load image size %dx%d\n", image_width, image_height);
        return 0;
    }
    if (image_bitsperpixel == 0) {
        printf("Couldn't load image depth\n");
        return 0;
    }

    printf("Image: %s\n", filename);
    printf("Resolution: %dx%d\n", image_width, image_height);
    printf("Depth: %d\n", image_bitsperpixel);

    if (difference_of_gaussians > 0) {
        integral_image = (long*)malloc(image_width*image_height*
                                       sizeof(long));
        if (amplify_with_dog != 0) {
          dog_image = (unsigned char*)malloc(image_width*image_height*
                                             image_bitsperpixel);
        }
        else {
          dog_image = image_data;
        }

        update_centre_surround(image_data,
                               image_width, image_height, image_bitsperpixel,
                               integral_image,
                               difference_of_gaussians,
                               dog_threshold,
                               dog_image,
                               image_width, image_height);
        free(integral_image);

        /* save the difference of gaussians image */
        write_png_file(dog_filename, image_width, image_height, 24, dog_image);

        if (amplify_with_dog != 0) {
          amplify_image(dog_image, image_width, image_height, image_bitsperpixel,
                        amplify_with_dog, minimum_y, maximum_y,
                        no_of_exclude_areas, exclude_areas,
                        image_data);
          free(dog_image);
        }
    }

    /* save the image */
    write_png_file(output_filename, image_width, image_height, 24, image_data);

    /* free memory */
    free(image_data);

    printf("Ended Successfully\n");
    return 0;
}
