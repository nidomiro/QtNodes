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

StringTestNodeImpl::StringTestNodeImpl():
    m_incommingConn(new QList<Connection>()),
    m_outgoingConn(new QList<Connection>())
{

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
    return source != target;
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

QUuid StringTestNodeImpl::getNodeAddress()
{
    return m_nodeAdress;
}
