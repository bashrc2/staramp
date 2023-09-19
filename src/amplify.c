/*********************************************************************
 *  staramp - amplification functions
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

void amplify_image(unsigned char * img,
                   int img_width, int img_height,
                   int bitsperpixel,
                   int amplify,
                   int min_y, int max_y,
                   int no_of_exclude_areas,
                   int exclude_areas[255][4],
                   int include_area[255],
                   unsigned char * output_img)
{
  int x, y, n, value, c, ex, tx, ty, bx, by, excluded;
  int proceed, adaptive_amp, adapt;
  int no_of_include_points = 0;
  int bytesperpixel = bitsperpixel/8;

  n = 0;
  while ((n < 253) && (include_area[n] != -1)) {
    n += 2;
    no_of_include_points++;
  }

  amplify += 100;
  if (max_y == 0) max_y = img_height;
  for (y = min_y; y < max_y; y++) {
    for (x = 5; x < img_width-5; x++) {
      /* is this inside of an exclusion area? */
      excluded = 0;
      if (no_of_exclude_areas > 0) {
        for (ex = 0; ex < no_of_exclude_areas; ex++) {
          tx = exclude_areas[ex][0];
          bx = exclude_areas[ex][2];
          if ((x >= tx) && (x <= bx)) {
            ty = exclude_areas[ex][1];
            by = exclude_areas[ex][3];
            if ((y >= ty) && (y <= by)) {
              excluded = 1;
              break;
            }
          }
        }
      }

      if (include_area[0] > -1) {
        if (point_in_polygon(x, y, include_area, no_of_include_points) == 0) {
          excluded = 1;
        }
      }

      if (excluded == 0) {
        n = (y*img_width + x)*bytesperpixel;

        /* when amplified does this pixel exceed 255? */
        proceed = 1;
        adaptive_amp = amplify;
        for (adapt = 0; adapt < 2; adapt++) {
          proceed = 1;
          for (c = 0; c < 3; c++) {
            if (img[n+c] == 0) continue;
            value = (int)output_img[n+c] * adaptive_amp / 100;
            if (value > 255) {
              proceed = 0;
              break;
            }
          }
          if (proceed == 1) break;
          adaptive_amp /= 2;
        }
        if (proceed == 0) continue;

        /* amplify the pixel */
        for (c = 0; c < 3; c++) {
          if (img[n+c] == 0) continue;
          value = (int)output_img[n+c] * adaptive_amp / 100;
          output_img[n+c] = (unsigned char)value;
        }
      }
    }
  }
}
