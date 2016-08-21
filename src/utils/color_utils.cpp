/*
 * Copyright 2016  Niclas Roßberger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "color_utils.h"

#include <QtGlobal>
#include "math_util.h"

ColorUtils::ColorUtils()
{

}

// SOURCE: http://martin.ankerl.com/2009/12/09/how-to-create-random-colors-programmatically/
QColor ColorUtils::generateRandomColor(qreal alpha)
{
    QColor ret;
    ret.setHsvF(MathUtil::randD(), 0.5, alpha);
    return ret;
}
