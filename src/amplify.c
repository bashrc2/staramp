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
                   unsigned char * output_img)
{
  int x, y, n, value, c, ex, tx, ty, bx, by, excluded;
  int bytesperpixel = bitsperpixel/8;

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

      if (excluded == 0) {
        n = (y*img_width + x)*bytesperpixel;
        for (c = 0; c < 3; c++) {
          if (img[n+c] == 0) continue;
          value = (int)output_img[n+c] * amplify / 100;
          if (value > 255) value = 255;
          output_img[n+c] = (unsigned char)value;
        }
      }
    }
  }
}
