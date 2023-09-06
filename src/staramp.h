/*********************************************************************
 *  staramp - function headers
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

#ifndef STARAMP_HEADERS_H
#define STARAMP_HEADERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <omp.h>

/* integralimage.c */

void update_integral_image(unsigned char * img,
                           int img_width, int img_height,
                           int bitsperpixel,
                           long * integral_image);

long get_integral(long * integral_image,
                  int tx, int ty, int bx, int by, int img_width);

/* centresurround.c */

void update_centre_surround(unsigned char * img,
                            int img_width, int img_height,
                            int bitsperpixel,
                            long * integral_image,
                            int patch_width,
                            int threshold,
                            unsigned char * output_img,
                            int output_img_width,
                            int output_img_height);

/* amplify.c */

void amplify_image(unsigned char * img,
                   int img_width, int img_height,
                   int bitsperpixel,
                   int amplify,
                   int min_y, int max_y,
                   unsigned char * output_img);

#endif
