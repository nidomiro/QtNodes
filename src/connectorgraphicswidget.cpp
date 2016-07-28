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

 qreal ConnectorGraphicsWidget::connectorRadius = 4;

ConnectorGraphicsWidget::ConnectorGraphicsWidget(Position pos, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    m_connectorPos(pos)
{
    setMinimumSize(connectorRadius*2, connectorRadius*2);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    setMaximumWidth(connectorRadius*2);
//    setPreferredSize(connectorRadius*2, connectorRadius*2);
}

void ConnectorGraphicsWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

//    QPointF center = QPointF(this->size().width() / 2, this->size().height() / 2);
//    qDebug() <<center;
    painter->setBrush(QBrush(m_conectorColor));
    QRect connector;
    switch (m_connectorPos) {
    case POS_LEFT:
        connector = QRect(0, this->size().height() / 2 - connectorRadius, connectorRadius*2, connectorRadius*2);
        break;
    case POS_RIGHT:
        connector = QRect(this->size().width() - connectorRadius*2, this->size().height() / 2 - connectorRadius, connectorRadius*2, connectorRadius*2);
        break;
    default:
        break;
    }

    painter->drawEllipse(connector);

}

QColor ConnectorGraphicsWidget::conectorColor() const
{
    return m_conectorColor;
}

void ConnectorGraphicsWidget::setConectorColor(const QColor &conectorColor)
{
    m_conectorColor = conectorColor;
}
