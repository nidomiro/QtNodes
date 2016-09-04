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

StringTestNodeImpl::StringTestNodeImpl(INodeGridImpl *nodeGrid, QString name):
    m_nodeName(name),
    m_nodeGrid(nodeGrid),
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
        port.type = (i < (count/2))? NodePortIOType::OUTPUT : NodePortIOType::INPUT;
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
    if(source.ioType == target.ioType)
        return false;

    return true;
}

Connection StringTestNodeImpl::connect(const NodePortAddress &source, const NodePortAddress &target)
{
    Connection con;
    if (source.isNull() || target.isNull()){
        qWarning() <<"Cannot connect if source or target is null.";
        return con;
    }

    if(canConnect(source, target)){
        con.source = source;
        con.target = target;

        if(!m_outgoingConn->contains(con)){
            m_outgoingConn->append(con);
            m_connectionStateListener->onConnectionAdded(con);
        }else
            con = Connection();

    }

    if(con.isNull()){
        qDebug() << "Not Connected: m_outgoingConn=" << m_outgoingConn->size();
    }else{
        qDebug() << "Connected: m_outgoingConn=" << m_outgoingConn->size();
    }

    return con;
}

QUuid StringTestNodeImpl::getLocalNodeAddress()
{
    return m_nodeAddress;
}

INodeGridImpl *StringTestNodeImpl::getNodeGrid()
{
    return m_nodeGrid;
}

NodePortAddress StringTestNodeImpl::getNodePortAddress(int portNumber, NodePortIOType type)
{
    NodePortAddress address;
    address.port = portNumber;
    address.gridAddress = getNodeGrid()->getNodeGridAddress();
    address.ioType = type;
    address.nodeAddress = getLocalNodeAddress();
    return address;
}

NodePortAddress StringTestNodeImpl::getNodePortAddress(NodePortInfo info)
{
    NodePortAddress address;
    address.port = info.portNumber;
    address.gridAddress = getNodeGrid()->getNodeGridAddress();
    address.ioType = info.type;
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

IConnectionStateListener *StringTestNodeImpl::setIConnectionStateListener(IConnectionStateListener *listener)
{
    IConnectionStateListener *old = m_connectionStateListener;
    m_connectionStateListener = listener;
    return old;
}

IConnectionStateListener *StringTestNodeImpl::getIConnectionStateListener()
{
    return m_connectionStateListener;
}

bool StringTestNodeImpl::canStartConnect(const NodePortAddress &address)
{
    Q_UNUSED(address)
    return true;
}














