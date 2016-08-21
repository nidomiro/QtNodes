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

#ifndef NODE_PORT_ADRESS_H
#define NODE_PORT_ADRESS_H

#include "qtnodesshare_global.h"

#include <QUuid>
#include <QMap>

struct QTNODESSHARESHARED_EXPORT NodePortAdress
{
public:

    enum Type {
        INPUT,
        OUTPUT,
        NULL
    };

    QUuid sceneAddress; // normally unused
    QUuid nodeAddress;
    qint16 port = -1;
    Type type = NULL;


};

#endif // NODE_PORT_ADRESS_H
