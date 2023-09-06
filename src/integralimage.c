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

#include "staramp.h"

/* update the integral image, using the given mono bitmap */
void update_integral_image(unsigned char * img,
                           int img_width, int img_height,
                           int bitsperpixel,
                           long * integral_image)
{
    int x, y, p, n = img_width, c;

    if (bitsperpixel == 8) {
        for (y = 1; y < img_height; y++) {
            p = 0;
            for (x = 0; x < img_width; x++, n++) {
                p += img[n];
                integral_image[n] =
                    p + integral_image[n - img_width];
            }
        }
        return;
    }
    if (bitsperpixel == 24) {
        for (y = 1; y < img_height; y++) {
            p = 0;
            for (x = 0; x < img_width; x++, n++) {
                for (c = 0; c < 3; c++) {
                    p += img[n*3 + c];
                }
                integral_image[n] =
                    p + integral_image[n - img_width];
            }
        }
        return;
    }
    if (bitsperpixel == 32) {
        for (y = 1; y < img_height; y++) {
            p = 0;
            for (x = 0; x < img_width; x++, n++) {
                for (c = 0; c < 3; c++) {
                    p += img[n*4 + c];
                }
                integral_image[n] =
                    p + integral_image[n - img_width];
            }
        }
        return;
    }
}

/* get the total pixel value for the given area */
long get_integral(long * integral_image,
                  int tx, int ty, int bx, int by, int img_width)
{
    int n1 = ty * img_width;
    int n2 = by * img_width;

    return (integral_image[n2 + bx] +
            integral_image[n1 + tx] -
            (integral_image[n2 + tx] +
             integral_image[n1 + bx]));
}
