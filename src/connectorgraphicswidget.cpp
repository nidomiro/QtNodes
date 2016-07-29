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

#include "connectorgraphicswidget.h"

#include <QWidget>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

 qreal ConnectorGraphicsWidget::s_connectorRadius = 5;

ConnectorGraphicsWidget::ConnectorGraphicsWidget(Position pos, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    m_connectorPos(pos)
{

    setMinimumSize(s_connectorRadius*2, s_connectorRadius*2);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    setMaximumWidth(s_connectorRadius*2);
//    setPreferredSize(connectorRadius*2, connectorRadius*2);

    QObject::connect(this, SIGNAL(geometryChanged()), this, SLOT(onGeometryChange()));

    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    recalculateConnectorRect();
}

void ConnectorGraphicsWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

//    QPointF center = QPointF(this->size().width() / 2, this->size().height() / 2);
//    qDebug() <<center;
    painter->setBrush(QBrush(m_conectorColor));
    QRectF connector = getConnectorRect();

    painter->drawEllipse(connector);

}

QPainterPath ConnectorGraphicsWidget::shape() const
{
    QPainterPath path;
    path.addEllipse(getConnectorRect());
    return path;
}

QColor ConnectorGraphicsWidget::conectorColor() const
{
    return m_conectorColor;
}

void ConnectorGraphicsWidget::setConectorColor(const QColor &conectorColor)
{
    m_conectorColor = conectorColor;
}

QRectF ConnectorGraphicsWidget::getConnectorRect() const
{
    return m_connectorRect;
}

void ConnectorGraphicsWidget::recalculateConnectorRect()
{
    switch (m_connectorPos) {
    case POS_LEFT:
        m_connectorRect = QRectF(0, this->size().height() / 2 - s_connectorRadius, s_connectorRadius*2, s_connectorRadius*2);
        break;
    case POS_RIGHT:
        m_connectorRect = QRectF(this->size().width() - s_connectorRadius*2, this->size().height() / 2 - s_connectorRadius, s_connectorRadius*2, s_connectorRadius*2);
        break;
    default:
        m_connectorRect = QRectF();
    }
}

void ConnectorGraphicsWidget::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() <<(int)this <<"Hover: " <<event->pos();
}

void ConnectorGraphicsWidget::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() <<"Drag: " <<event->pos();
}

void ConnectorGraphicsWidget::onGeometryChange()
{
    recalculateConnectorRect();
}
