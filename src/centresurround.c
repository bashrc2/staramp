/*********************************************************************
 *  staramp - centre/surround functions
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

/* this is similar to a difference of gaussian (DoG) filter */
void update_centre_surround(unsigned char * img,
                            int img_width, int img_height,
                            int bitsperpixel,
                            long * integral_image,
                            int patch_width,
                            int threshold,
                            unsigned char * output_img,
                            int output_img_width,
                            int output_img_height)
{
    int x, y, x0, y0, n=0, tx, ty, bx, by, c;
    int outer = patch_width/2;
    int inner = patch_width/4;
    int patch_pixels = patch_width*patch_width/2;
    long response_outer, response_inner, v;
    int bytesperpixel = bitsperpixel/8;

    /* update the integral image */
    update_integral_image(img, img_width, img_height, bitsperpixel,
                          integral_image);

    for (y = 0; y < output_img_height; y++) {
        y0 = y * img_height / output_img_height;
        ty = y0 - outer;
        by = ty + patch_width;
        if (ty < 0) ty = 0;
        if (by >= img_height) by = img_height-1;

        for (x = 0; x < output_img_width; x++) {
            n = y*output_img_width + x;

            x0 = x * img_width / output_img_width;
            tx = x0 - outer;
            bx = tx + patch_width;
            if (tx < 0) tx = 0;
            if (bx >= img_width) bx = img_width-1;

            response_outer =
                get_integral(integral_image,
                             tx, ty, bx, by, img_width);
            response_inner =
                get_integral(integral_image,
                             tx + inner, ty + inner,
                             tx + inner + outer, ty + inner + outer,
                             img_width)*4;
            v = 127 + ((response_inner - response_outer)/
                       patch_pixels);
            if (v < threshold) v = 0;
            if (v < 0) v = 0;
            if (v > 255) v = 255;
            for (c = 0; c < bytesperpixel; c++) {
                output_img[n*bytesperpixel + c] = (unsigned char)v;
            }
        }
    }
}
