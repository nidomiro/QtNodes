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

class INodeGridImpl;

#include "qtnodesshared_global.h"
#include "node_port_address.h"
#include "connection.h"
#include "node_port_info.h"
#include "i_node_state_listener.h"
#include "i_connection_state_listener.h"

#include <QUuid>
#include <QList>

// Do not use QTNODESSHARESHARED_EXPORT on Interfaces
class INodeImpl {
public:

    virtual QString getNodeName() const = 0;
    virtual void setNodeName(QString name) = 0;

    virtual QList<NodePortInfo> getNodePorts() = 0;

    virtual QList<Connection> *getIncomingConnections() = 0;
    virtual QList<Connection> *getOutgoingConnections() = 0;

    virtual bool canConnect(const NodePortAddress &source, const NodePortAddress &target) = 0;
    virtual Connection connect(const NodePortAddress &source, const NodePortAddress &target) = 0;

    virtual QUuid getLocalNodeAddress() = 0;

    virtual INodeGridImpl *getNodeGrid() = 0;

    virtual NodePortAddress getNodePortAddress(int portNumber, NodePortIOType type) = 0;
    virtual NodePortAddress getNodePortAddress(NodePortInfo info) = 0;

    virtual INodeStateListener *setINodeStateListener(INodeStateListener *listener) = 0;
    virtual INodeStateListener *getINodeStateListener() = 0;

    virtual IConnectionStateListener *setIConnectionStateListener(IConnectionStateListener *listener) = 0;
    virtual IConnectionStateListener *getIConnectionStateListener() = 0;

    /*!
     * \brief Checks if an connectionrequest can start from this NodePort (address.nodeAddress has to be getLocalNodeAddress()).
     * \param address The address of the NodePort
     * \return true if the NodePort at adress can start a connection, false otherwise.
     */
    virtual bool canStartConnect(const NodePortAddress &address) = 0;



};

#endif // INODEIMPL_H
