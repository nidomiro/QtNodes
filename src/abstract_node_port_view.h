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

class NodeView;

#include "qtnodes_global.h"
#include "node_port_connector_view.h"
#include "shared/node_port_info.h"

#include "shared/node_port_address.h"

#include <QMimeData>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
//#include <type_traits>




class QTNODES_EXPORT AbstractNodePortView : public QGraphicsWidget
{
    Q_OBJECT

public:
    ~AbstractNodePortView();

    QPointF getPortConnectorMiddleInSceneSpace();



protected:
    AbstractNodePortView(NodePortInfo info, QGraphicsItem *parent);
    void init();
    virtual void createCenterWidget(QGraphicsWidget *centerWidget) = 0;

private:

    QGraphicsLinearLayout *m_layout = nullptr;

    NodePortConnectorView *m_leftConnector = nullptr;
    QGraphicsWidget *m_centerWidget = nullptr;
    NodePortConnectorView *m_rightConnector = nullptr;

protected:
    NodePortInfo m_portInfo;


// BEGIN static part
public:
    // only callable if template-parameter is derived from AbstractNodePortGW
    template<typename CLAZZ, typename std::enable_if<std::is_base_of<AbstractNodePortView, CLAZZ>::value>::type* = nullptr>
    static CLAZZ *create(NodePortInfo info, QGraphicsItem *parent){
        CLAZZ *instance = new CLAZZ(info, parent);
        instance->init();

        return instance;
    }

};

#endif // ABSTRACTIOGRAPHICSWIDGET_H
