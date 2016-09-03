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

#ifndef NODEPORTINFO_H
#define NODEPORTINFO_H

class INodeImpl;

#include "qtnodesshared_global.h"

#include "node_port_io_type.h"

#include <QString>

class QTNODESSHARED_EXPORT NodePortInfo{
public:

    NodePortIOType type  = NodePortIOType::NONE;
    QString dataType = "default:unsetDataType";
    QString visualHint = "default:unsetVisualHint";
    int portNumber = -1;
    INodeImpl *parentNode = nullptr;

};

#endif // NODEPORTINFO_H


