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


#include "stringtestnodeimpl.h"

#include <QDebug>

StringTestNodeImpl::StringTestNodeImpl(QString name):
    m_nodeName(name),
    m_incommingConn(new QList<Connection>()),
    m_outgoingConn(new QList<Connection>())
{

}

StringTestNodeImpl::~StringTestNodeImpl()
{
    delete m_incommingConn;
    delete m_outgoingConn;
}

QString StringTestNodeImpl::getNodeName() const
{
    return m_nodeName;
}

void StringTestNodeImpl::setNodeName(QString name)
{
    m_nodeName = name;
    if(m_nodeStateListener != nullptr)
        m_nodeStateListener->onNodeNameChanged(m_nodeName);
}

QList<NodePortInfo> StringTestNodeImpl::getNodePorts()
{
    QList<NodePortInfo> nodePorts;
    const int count = 4;
    for(int i = 0; i < count; i++){
        NodePortInfo port;
        port.parentNode = this;
        port.portNumber = i;
        port.type = (i < (count/2))? NodePortType::OUTPUT : NodePortType::INPUT;
//        qDebug() <<"PortType=" <<static_cast<int>(port.type);
        nodePorts.append(port);
    }
    return nodePorts;
}

QList<Connection> *StringTestNodeImpl::getIncomingConnections()
{
    return m_incommingConn;
}

QList<Connection> *StringTestNodeImpl::getOutgoingConnections()
{
    return m_outgoingConn;
}

bool StringTestNodeImpl::canConnect(const NodePortAddress &source, const NodePortAddress &target)
{
    if(source == target)
        return false;
    if(source.type == target.type)
        return false;

    return true;
}

Connection StringTestNodeImpl::connect(const NodePortAddress &source, const NodePortAddress &target)
{
    Connection con;
    if(canConnect(source, target)){
        con.source = source;
        con.target = target;
    }
    return con;
}

QUuid StringTestNodeImpl::getLocalNodeAddress()
{
    return m_nodeAddress;
}

void StringTestNodeImpl::setNodeSceneAddress(const QUuid &sceneAddress)
{
    m_sceneAddress = sceneAddress;
}

QUuid StringTestNodeImpl::getNodeSceneAddress()
{
    return m_sceneAddress;
}

NodePortAddress StringTestNodeImpl::getNodePortAddress(int portNumber, NodePortType type)
{
    NodePortAddress address;
    address.port = portNumber;
    address.sceneAddress = getNodeSceneAddress();
    address.type = type;
    address.nodeAddress = getLocalNodeAddress();
    return address;
}

NodePortAddress StringTestNodeImpl::getNodePortAddress(NodePortInfo info)
{
    NodePortAddress address;
    address.port = info.portNumber;
    address.sceneAddress = getNodeSceneAddress();
    address.type = info.type;
    address.nodeAddress = getLocalNodeAddress();
    return address;
}

INodeStateListener *StringTestNodeImpl::setINodeStateListener(INodeStateListener *listener)
{
    INodeStateListener *old = m_nodeStateListener;
    m_nodeStateListener = listener;
    return old;
}

INodeStateListener *StringTestNodeImpl::getINodeStateListener()
{
    return m_nodeStateListener;
}














