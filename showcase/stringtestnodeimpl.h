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


#ifndef STRINGTESTNODEIMPL_H
#define STRINGTESTNODEIMPL_H

#include "i_node_impl.h"

class StringTestNodeImpl: public INodeImpl
{
public:
    StringTestNodeImpl();

    QList<Connection> *getIncomingConnections() override;
    QList<Connection> *getOutgoingConnections() override;

    bool canConnect(const NodePortAddress &source, const NodePortAddress &target) override;
    Connection connect(const NodePortAddress &source, const NodePortAddress &target) override;

    QUuid getNodeAddress() override;

protected:

    QUuid m_nodeAdress = QUuid::createUuid();
    QList<Connection> *m_incommingConn = nullptr;
    QList<Connection> *m_outgoingConn = nullptr;
};

#endif // STRINGTESTNODEIMPL_H
