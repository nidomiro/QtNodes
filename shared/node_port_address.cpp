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
    return gridAddress.isNull()
            && nodeAddress.isNull()
            && port < 0
            && ioType == NodePortIOType::NONE;
}

bool NodePortAddress::operator==(const NodePortAddress &other) const{
    return gridAddress == other.gridAddress
            && nodeAddress == other.nodeAddress
            && port == other.port
            && ioType == other.ioType;
}

bool NodePortAddress::operator!=(const NodePortAddress &other) const
{
    return !(*this == other);
}

QString NodePortAddress::toString() const
{
    return gridAddress.toString() + "::" + nodeAddress.toString() + "::" + QString::number(port) + "::" + enumToString(ioType);
}

QUrl nodePortAddressToUrl(const NodePortAddress &node)
{
    QUrl url;
    url.setScheme("node");

    url.setHost(node.nodeAddress.toString().replace("{", "s").replace("}", "t")
                + "."
                + node.gridAddress.toString().replace("{", "s").replace("}", "t")
                );
    url.setPort(node.port);
    QUrlQuery query;
    query.addQueryItem("type", enumToString(node.ioType));
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
//            qDebug() <<"sceneAddr=" <<sceneAddr <<" nodeAddr=" <<nodeAddr;
            node.gridAddress = QUuid(sceneAddr);
            node.nodeAddress = QUuid(nodeAddr);
        }

        node.port = url.port();
        QUrlQuery query(url.query());
        node.ioType = enumFromString(query.queryItemValue("type"));
    }
    return node;
}










