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

#ifndef ABSTRACTIOGRAPHICSWIDGET_H
#define ABSTRACTIOGRAPHICSWIDGET_H

class NodeGW;

#include "qtnodes_global.h"
#include "node_port_connector_g_w.h"

#include "node_port_address.h"

#include <QMimeData>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
//#include <type_traits>




class QTNODESSHARED_EXPORT AbstractNodePortGW : public QGraphicsWidget
{
    Q_OBJECT

public:
    ~AbstractNodePortGW();

    bool connectionRequest(const NodePortAddress &source, const NodePortAddress &thisAddress, const bool &isTest=false);

    void constructWholeAddress(NodePortAddress &addressToConstruct) const;


protected:
    AbstractNodePortGW(NodeGW *parent);
    void init();
    virtual void createCenterWidget(QGraphicsWidget *centerWidget) = 0;

private:

    QGraphicsLinearLayout *m_layout = nullptr;

    NodePortConnectorGW *m_leftConnector = nullptr;
    QGraphicsWidget *m_centerWidget = nullptr;
    NodePortConnectorGW *m_rightConnector = nullptr;

protected:
    NodeGW *m_parent = nullptr;


// BEGIN static part
public:
    // only callable if template-parameter is derived from AbstractNodePortGW
    template<typename CLAZZ, typename std::enable_if<std::is_base_of<AbstractNodePortGW, CLAZZ>::value>::type* = nullptr>
    static CLAZZ *create(NodeGW *parent){
        CLAZZ *instance = new CLAZZ(parent);
        instance->init();

        return instance;
    }

};

#endif // ABSTRACTIOGRAPHICSWIDGET_H
