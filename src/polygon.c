/*********************************************************************
 *  staramp - polygon functions
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

/* returns non-zero if the given point is in the given polygon */
int point_in_polygon(int x, int y, int * points, int no_of_points)
{
  int i, j, c = 0;

  for(i = 0, j = no_of_points - 1; i < no_of_points; j = i++) {
    if (((points[i*2+1] >= y) != (points[j*2+1] >= y)) &&
        (x <= (points[j*2] - points[i*2]) * (y - points[i*2+1]) /
         (points[j*2+1] - points[i*2+1]) + points[i*2]))
      c = 1 - c;
  }

  return c;
}
