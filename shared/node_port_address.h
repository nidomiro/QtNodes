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

#include "qtnodesshared_global.h"
#include "node_port_io_type.h"

#include <QUuid>
#include <QMap>
#include <QUrl>

class QTNODESSHARED_EXPORT NodePortAddress
{
public:

    QUuid gridAddress;
    QUuid nodeAddress;
    int port = -1;
    NodePortIOType ioType = NodePortIOType::NONE;


    bool isNull() const;
    bool operator==(const NodePortAddress &other) const;
    bool operator!=(const NodePortAddress &other) const;

    bool operator<(const NodePortAddress &other) const;

    QString toString() const;


};


extern "C" QTNODESSHARED_EXPORT QUrl nodePortAddressToUrl(const NodePortAddress &node);
extern "C" QTNODESSHARED_EXPORT NodePortAddress nodePortAddressFromUrl(const QUrl &url);


#endif // NODE_PORT_ADRESS_H
