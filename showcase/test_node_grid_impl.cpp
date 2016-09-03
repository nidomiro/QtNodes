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

    addNode(new StringTestNodeImpl(this, "Node 1"));
    addNode(new StringTestNodeImpl(this, "Node 2"));
    addNode(new StringTestNodeImpl(this, "Node 3"));

}

QList<INodeImpl *> TestNodeGridImpl::getAllNodes()
{
    return m_nodes.values();
}

INodeImpl *TestNodeGridImpl::getNode(const NodePortAddress &address)
{
    INodeImpl *node = nullptr;
    if(address.gridAddress == this->getNodeGridAddress()){
        node = m_nodes.value(address.nodeAddress, nullptr);
    }
    return node;
}

bool TestNodeGridImpl::addNewNode(const QString &nodeClassName)
{



    return false;
}

bool TestNodeGridImpl::addNode(INodeImpl *node)
{
    bool ret = false;

    if(!m_nodes.contains(node->getLocalNodeAddress())){
        m_nodes.insert(node->getLocalNodeAddress(), node);
        ret = true;
    }

    if( ret && m_listener != nullptr)
        m_listener->onNodeAdded(node);

    return ret;
}

bool TestNodeGridImpl::removeNode(const NodePortAddress &nodeAddress)
{
    return false;
}

QUuid TestNodeGridImpl::getNodeGridAddress()
{
    return m_sceneAddress;
}

INodeGridStateListener *TestNodeGridImpl::setINodeGridStateListener(INodeGridStateListener *listener)
{
    INodeGridStateListener *old = m_listener;
    m_listener = listener;
    return old;
}

INodeGridStateListener *TestNodeGridImpl::getINodeGridStateListener()
{
    return m_listener;
}
