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
#include <QDebug>

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

bool NodePortAddress::operator!=(const NodePortAddress &other) const
{
    return !(*this == other);
}

QString NodePortAddress::toString() const
{
    return sceneAddress.toString() + "::" + nodeAddress.toString() + "::" + QString::number(port) + "::" + enumToString(type);
}

QString enumToString(const NodePortAddress::Type &type)
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

NodePortAddress::Type enumFromString(const QString &str)
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

QUrl nodePortAddressToUrl(const NodePortAddress &node)
{
    QUrl url;
    url.setScheme("node");

    url.setHost(node.nodeAddress.toString().replace("{", "s").replace("}", "t")
                + "."
                + node.sceneAddress.toString().replace("{", "s").replace("}", "t")
                );
    url.setPort(node.port);
    QUrlQuery query;
    query.addQueryItem("type", enumToString(node.type));
    url.setQuery(query);

    return url;
}

NodePortAddress nodePortAddressFromUrl(const QUrl &url)
{
    NodePortAddress node;
    if(url.scheme() == "node"){
        QStringList hosts = url.host().split(".");
        if (hosts.length() >= 2){ // If more "subdomains" -> don't care, take the two top-level ones
            QString sceneAddr = hosts[hosts.length() - 1].replace("s", "{").replace("t", "}");
            QString nodeAddr = hosts[hosts.length() - 2].replace("s", "{").replace("t", "}");
            qDebug() <<"sceneAddr=" <<sceneAddr <<" nodeAddr=" <<nodeAddr;
            node.sceneAddress = QUuid(sceneAddr);
            node.nodeAddress = QUuid(nodeAddr);
        }

        node.port = url.port();
        QUrlQuery query(url.query());
        node.type = enumFromString(query.queryItemValue("type"));
    }
    return node;
}










