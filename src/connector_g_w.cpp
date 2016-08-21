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

#include "connector_g_w.h"

#include <QWidget>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

#include <QDrag>
#include <QMimeData>

#include "connection_request.h"
#include "abstract_node_port_g_w.h"

qreal ConnectorGW::s_connectorRadius = 5;
QString ConnectorGW::s_connectionRequestMimeType = QStringLiteral("application/nodeconnectrequest");


ConnectorGW::ConnectorGW(Position pos, AbstractNodePortGW *parent) :
    QGraphicsWidget(parent),
    m_connectorPos(pos),
    m_parent(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    setMinimumSize(s_connectorRadius*2, s_connectorRadius*2);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    setMaximumWidth(s_connectorRadius*2);
//    setPreferredSize(connectorRadius*2, connectorRadius*2);

    QObject::connect(this, SIGNAL(geometryChanged()), this, SLOT(onGeometryChange()));

    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    recalculateConnectorRect();
}

void ConnectorGW::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

//    QPointF center = QPointF(this->size().width() / 2, this->size().height() / 2);
//    qDebug() <<center;
    painter->setBrush(QBrush(m_conectorColor));
    QRectF connector = getConnectorRect();

    painter->drawEllipse(connector);

}

QPainterPath ConnectorGW::shape() const
{
    QPainterPath path;
    path.addEllipse(getConnectorRect());
    return path;
}

QColor ConnectorGW::conectorColor() const
{
    return m_conectorColor;
}

void ConnectorGW::setConectorColor(const QColor &conectorColor)
{
    m_conectorColor = conectorColor;
}

QRectF ConnectorGW::getConnectorRect() const
{
    return m_connectorRect;
}

void ConnectorGW::recalculateConnectorRect()
{
    if(!m_isRecalulatingRect) // Prevent possible infinate recursion
    {
        m_isRecalulatingRect = true;
        prepareGeometryChange();
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
    m_isRecalulatingRect = false;
    }
}

void ConnectorGW::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug() <<(int)this <<"Hover: " <<event->pos();
    QGraphicsWidget::hoverMoveEvent(event);
}

void ConnectorGW::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DragMove: " <<event->pos();
    QGraphicsWidget::dragMoveEvent(event);
}

void ConnectorGW::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DragEnter: " <<event->pos();
    QGraphicsWidget::dragEnterEvent(event);
}

void ConnectorGW::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DragLeave: " <<event->pos();
    QGraphicsWidget::dragLeaveEvent(event);
}

void ConnectorGW::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DropEvent: " <<event->pos();
    QGraphicsWidget::dropEvent(event);
}

void ConnectorGW::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() <<(int)this  <<"MousePressEvent: " <<event->pos();

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;

    ConnectionRequest con;
    con.source = this;

    QList<QUrl> urls;
    urls.append(QUrl("http://google.de"));
    mime->setUrls(urls);
//    mime->
    drag->setMimeData(mime);
   /* . . . */
    drag->exec(Qt::LinkAction);


    //QGraphicsWidget::mousePressEvent(event);
}

void ConnectorGW::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() <<(int)this  <<"MouseMoveEvent: " <<event->pos();
    QGraphicsWidget::mouseMoveEvent(event);
}

void ConnectorGW::onGeometryChange()
{
    recalculateConnectorRect();
}