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


#ifndef NODECONNECTIONVIEW_H
#define NODECONNECTIONVIEW_H

#include "qtnodes_global.h"
#include "shared/connection.h"
#include "node_view.h"

#include <QGraphicsPathItem>
#include <QObject>

class QTNODES_EXPORT NodeConnectionView : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:
    NodeConnectionView(const Connection &con, NodeView *source, NodeView *target, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QPainterPath getBezier(QPointF p1, QPointF p2);

    void updatePath();



public slots:
    void onSourceNodePositionChanged();
    void onTargetNodePositionChanged();

protected:
    Connection m_connection;
    NodeView *m_sourceNode = nullptr;
    NodeView *m_targetNode = nullptr;
    QPointF m_SourceNodeConnectorPosCache;
    QPointF m_TargetNodeConnectorPosCache;
    QPainterPath m_path;


};

#endif // NODECONNECTIONVIEW_H
