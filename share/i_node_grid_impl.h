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


#ifndef I_NODE_GRID_IMPL_H
#define I_NODE_GRID_IMPL_H

#include "qtnodesshare_global.h"

#include "i_node_impl.h"
#include "i_node_grid_state_listener.h"
#include "node_port_address.h"

#include <QList>
#include <QString>
#include <QUuid>

class INodeGridImpl{
public:

    virtual QList<INodeImpl*> getAllNodes() = 0;
    virtual bool addNewNode(const QString &nodeClassName) = 0;
    /*!
     * \brief removeNode
     * \param nodeAddress only sceneAddress and nodeAddress are used, the rest can be uset.
     * \return true if removing was successful
     */
    virtual bool removeNode(const NodePortAddress &nodeAddress) = 0;

    virtual QUuid getNodeSceneAddress() = 0;

    virtual INodeGridStateListener *setINodeGridStateListener(INodeGridStateListener *listener) = 0;
    virtual INodeGridStateListener *getINodeGridStateListener() = 0;

};

#endif // I_NODE_GRID_IMPL_H
