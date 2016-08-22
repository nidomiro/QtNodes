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
#include <QUrl>

struct QTNODESSHARESHARED_EXPORT NodePortAddress
{
public:

    enum Type {
        INPUT,
        OUTPUT,
        NONE
    };

    QUuid sceneAddress; // normally unused
    QUuid nodeAddress;
    qint16 port = -1;
    Type type = Type::NONE;


    bool isNull() const;
    bool operator==(const NodePortAddress &other) const;


};

extern "C" QTNODESSHARESHARED_EXPORT QString toString(const NodePortAddress::Type & type);
extern "C" QTNODESSHARESHARED_EXPORT NodePortAddress::Type fromString(const QString & str);

extern "C" QTNODESSHARESHARED_EXPORT QUrl toUrl(const NodePortAddress &node);
extern "C" QTNODESSHARESHARED_EXPORT NodePortAddress fromUrl(const QUrl &url);


#endif // NODE_PORT_ADRESS_H
