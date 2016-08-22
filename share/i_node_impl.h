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

#ifndef INODEIMPL_H
#define INODEIMPL_H

#include "qtnodesshare_global.h"
#include "node_port_address.h"
#include "connection.h"

#include <QUuid>

class QTNODESSHARESHARED_EXPORT INodeImpl {
public:

    virtual bool canConnect(const NodePortAddress &source, const NodePortAddress &target) = 0;
    virtual Connection connect(const NodePortAddress &source, const NodePortAddress &target) = 0;

    virtual QUuid getNodeAddress() = 0;


};

#endif // INODEIMPL_H
