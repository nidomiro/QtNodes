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


#include "test_node_grid_impl.h"

TestNodeGridImpl::TestNodeGridImpl()
{

    m_nodes.append(new StringTestNodeImpl("Node 1"));
    m_nodes.append(new StringTestNodeImpl("Node 2"));
    m_nodes.append(new StringTestNodeImpl("Node 3"));

}

QList<INodeImpl *> TestNodeGridImpl::getAllNodes()
{
    return m_nodes;
}

bool TestNodeGridImpl::addNewNode(const QString &nodeClassName)
{
    return false;
}

bool TestNodeGridImpl::removeNode(const NodePortAddress &nodeAddress)
{
    return false;
}

QUuid TestNodeGridImpl::getNodeSceneAddress()
{
    return m_sceneAddress;
}

INodeGridStateListener *TestNodeGridImpl::setINodeGridStateListener(INodeGridStateListener *listener)
{
    m_listener = listener;
}

INodeGridStateListener *TestNodeGridImpl::getINodeGridStateListener()
{
    return m_listener;
}
