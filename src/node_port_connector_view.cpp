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

#include "node_port_connector_view.h"
#include "abstract_node_port_view.h"

#include "shared/node_port_address.h"
#include "shared/i_node_impl.h"

#include <QWidget>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

#include <QDrag>
#include <QMimeData>
#include <QSizePolicy>




qreal NodePortConnectorView::s_connectorRadius = 5;
QString NodePortConnectorView::s_connectionRequestMimeType = QStringLiteral("application/nodeconnectrequest");


NodePortConnectorView::NodePortConnectorView(Position pos, NodePortInfo info, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    m_connectorPos(pos),
    m_portInfo(info)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    setMinimumSize(s_connectorRadius*2, s_connectorRadius*2);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    setMaximumWidth(s_connectorRadius*2);

    QSizePolicy sizePolicy = this->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    setSizePolicy(sizePolicy);
//    setPreferredSize(connectorRadius*2, connectorRadius*2);

    QObject::connect(this, SIGNAL(geometryChanged()), this, SLOT(onGeometryChange()));

    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    recalculateConnectorRect();
}

void NodePortConnectorView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing, true);

//    QPointF center = QPointF(this->size().width() / 2, this->size().height() / 2);
//    qDebug() <<center;
    painter->setBrush(QBrush(m_conectorColor));
    QRectF connector = getConnectorRect();

    painter->drawEllipse(connector);

}

QPainterPath NodePortConnectorView::shape() const
{
    QPainterPath path;
    path.addEllipse(getConnectorRect());
    return path;
}

QColor NodePortConnectorView::conectorColor() const
{
    return m_conectorColor;
}

void NodePortConnectorView::setConectorColor(const QColor &conectorColor)
{
    m_conectorColor = conectorColor;
}

QRectF NodePortConnectorView::getConnectorRect() const
{
    return m_connectorRect;
}

void NodePortConnectorView::recalculateConnectorRect()
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

QPointF NodePortConnectorView::getConnectorMiddleInSceneSpace()
{
    return mapToScene(m_connectorRect.center());
}

bool NodePortConnectorView::isInput() const
{
    return m_connectorPos == POS_LEFT;
}

bool NodePortConnectorView::isOutput() const
{
    return !isInput();
}

NodePortAddress NodePortConnectorView::decodeAddress(const QMimeData *data)
{
    NodePortAddress source;
    QList<QUrl> urls = data->urls();
    if(!urls.empty()){
        source = nodePortAddressFromUrl(urls.first());
        //qDebug() << "Decoding url " <<urls.first() <<" -> " <<source.toString();
    }else
        qWarning() <<"urls is empty";
    return source;
}

void NodePortConnectorView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug() <<(int)this <<"Hover: " <<event->pos();
    QGraphicsWidget::hoverMoveEvent(event);
}

void NodePortConnectorView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DragMove: " <<event->pos();
    QGraphicsWidget::dragMoveEvent(event);
}

void NodePortConnectorView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DragEnter: " <<event->pos();
    NodePortAddress source = decodeAddress(event->mimeData());
    if(!m_portInfo.parentNode->canConnect(source, m_portInfo.parentNode->getNodePortAddress(m_portInfo)))
        event->ignore();
    QGraphicsWidget::dragEnterEvent(event);
    //event->ignore();
}

void NodePortConnectorView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DragLeave: " <<event->pos();
    QGraphicsWidget::dragLeaveEvent(event);
}

void NodePortConnectorView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() <<(int)event->source() <<"->" <<(int)this  <<"DropEvent: " <<event->pos();

    NodePortAddress source = decodeAddress(event->mimeData());
    if(!source.isNull()){
        event->acceptProposedAction();
        qDebug() <<"Connection made? "<< connectionRequest(source);
    }
    //TODO: error handling?

    QGraphicsWidget::dropEvent(event);
}

void NodePortConnectorView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() <<(long)this  <<"MousePressEvent: " <<event->pos();

    dragStart(event->widget());


    //QGraphicsWidget::mousePressEvent(event);
}

void NodePortConnectorView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() <<(int)this  <<"MouseMoveEvent: " <<event->pos();
    QGraphicsWidget::mouseMoveEvent(event);
}

bool NodePortConnectorView::dragStart(QObject *dragSource)
{
    bool ret = false;
    NodePortAddress address = m_portInfo.parentNode->getNodePortAddress(m_portInfo);

    if(m_portInfo.parentNode->canStartConnect(address))
    {
        QDrag *drag = new QDrag(dragSource);
        QMimeData *mime = new QMimeData;

        QList<QUrl> urls;

        urls.append(nodePortAddressToUrl(address));
        //qDebug() << "Encoding NodePortAddress " <<address.toString() <<" -> " <<urls.first();
        mime->setUrls(urls);
        drag->setMimeData(mime);
        drag->exec(Qt::LinkAction);
        ret = true;
    }
    return ret;
}

bool NodePortConnectorView::connectionRequest(const NodePortAddress &otherAddress)
{
    Connection con;
    NodePortAddress thisAdress = m_portInfo.parentNode->getNodePortAddress(m_portInfo);

    if(otherAddress.ioType == NodePortIOType::OUTPUT){
        con = m_portInfo.parentNode->connect(otherAddress, thisAdress);
    }else if(otherAddress.ioType == NodePortIOType::INPUT){
        con = m_portInfo.parentNode->connect(thisAdress, otherAddress);
    }

    //TODO: error handling?


    return !con.isNull();
}

void NodePortConnectorView::onGeometryChange()
{
    recalculateConnectorRect();
}

