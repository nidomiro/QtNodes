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


#include "node_connection_view.h"

#include <QtMath>
#include <QPainter>


NodeConnectionView::NodeConnectionView(const Connection &con, NodeView *source, NodeView *target, QGraphicsItem *parent):
    QGraphicsPathItem(parent),
    m_connection(con),
    m_sourceNode(source),
    m_targetNode(target)
{

    QObject::connect(m_sourceNode, SIGNAL(nodePositionChanged(QPointF)), this, SLOT(onSourceNodePositionChanged()));
    QObject::connect(m_targetNode, SIGNAL(nodePositionChanged(QPointF)), this, SLOT(onTargetNodePositionChanged()));

    onSourceNodePositionChanged();
    onTargetNodePositionChanged();
    updatePath();
}

void NodeConnectionView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    QGraphicsPathItem::paint(painter, option, widget);
}

QPainterPath NodeConnectionView::getBezier(QPointF p1, QPointF p2)
{
    QPainterPath myPath;
    myPath.moveTo(p1);

    double dist = (p2.x() - p1.x());
    double offset = dist/1.5;

    QPointF c1 = p1 + QPointF(offset,0);
    QPointF c2 = p2 - QPointF(offset,0);

    myPath.cubicTo(c1, c2, p2);
    return myPath;
}

void NodeConnectionView::updatePath()
{
    m_path = getBezier(m_SourceNodeConnectorPosCache, m_TargetNodeConnectorPosCache);
    setPath(m_path);
}

void NodeConnectionView::onSourceNodePositionChanged()
{
    m_SourceNodeConnectorPosCache = m_sourceNode->getPortConnectorMiddleInSceneSpace(m_connection.source);
    updatePath();
}

void NodeConnectionView::onTargetNodePositionChanged()
{
    m_TargetNodeConnectorPosCache = m_targetNode->getPortConnectorMiddleInSceneSpace(m_connection.target);
    updatePath();
}
