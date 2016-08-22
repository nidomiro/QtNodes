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

#include "node_port_address.h"

#include <QUrlQuery>

bool NodePortAddress::isNull() const{
    return sceneAddress.isNull()
            && nodeAddress.isNull()
            && port == -1
            && type == Type::NONE;
}

bool NodePortAddress::operator==(const NodePortAddress &other) const{
    return sceneAddress == other.sceneAddress
            && nodeAddress == other.nodeAddress
            && port == other.port
            && type == other.type;
}

QString toString(const NodePortAddress::Type &type)
{
//    using namespace NodePortAddress;
    QString ret;
    switch(type){
    case NodePortAddress::INPUT:
        ret=STR(INPUT);
        break;
    case NodePortAddress::OUTPUT:
        ret=STR(OUTPUT);
        break;
    case NodePortAddress::NONE:
    default:
        ret=STR(NONE);
        break;
    }
    return ret;
}

NodePortAddress::Type fromString(const QString &str)
{
//    using namespace NodePortAddress;
    NodePortAddress::Type ret = NodePortAddress::Type::NONE;

    if(str == STR(INPUT))
        ret = NodePortAddress::INPUT;
    else if(str == STR(OUTPUT))
        ret = NodePortAddress::OUTPUT;
    else
        ret = NodePortAddress::NONE;

    return ret;
}

QUrl toUrl(const NodePortAddress &node)
{
    QUrl url;
    url.setScheme("node");

    url.setHost(node.nodeAddress.toString() + "." + node.sceneAddress.toString());
    url.setPort(node.port);
    QUrlQuery query;
    query.addQueryItem("type", toString(node.type));
    url.setQuery(query);

    return url;
}

NodePortAddress fromUrl(const QUrl &url)
{
    NodePortAddress node;
    if(url.scheme() == "node"){
        QStringList host = url.host().split(".");
        if (host.length() >= 2){
            node.sceneAddress = host[host.length() - 1];
            node.nodeAddress = host[host.length() - 2];
        }

        node.port = url.port();
        QUrlQuery query(url.query());
        node.type = fromString(query.queryItemValue("type"));
    }
    return node;
}










