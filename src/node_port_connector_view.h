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

#ifndef CONNECTORGRAPHICSWIDGET_H
#define CONNECTORGRAPHICSWIDGET_H


#include "qtnodes_global.h"
#include "node_port_address.h"
#include "node_port_info.h"

#include <QObject>
#include <QGraphicsWidget>
#include <QColor>


class QTNODESSHARED_EXPORT NodePortConnectorView : public QGraphicsWidget
{
    Q_OBJECT

public:
    enum Position{
        POS_LEFT,
        POS_RIGHT
    };

public: // Methods
    NodePortConnectorView(Position pos, NodePortInfo info, QGraphicsItem *parent);


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

//    virtual void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
//    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QColor conectorColor() const;
    void setConectorColor(const QColor &conectorColor);

    QRectF getConnectorRect() const;
    void recalculateConnectorRect();

    bool isInput() const;
    bool isOutput() const;

    NodePortAddress decodeAddress(const QMimeData *data);

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

protected slots:
    void onGeometryChange();

protected: // Members

    Position m_connectorPos = POS_LEFT;
    NodePortInfo m_portInfo;


    QColor m_conectorColor = QColor(255,255,51);
    QRectF m_connectorRect;

private: // Members
    bool m_isRecalulatingRect = false;

public: // Static
    static qreal s_connectorRadius;
    static QString s_connectionRequestMimeType;

};

#endif // CONNECTORGRAPHICSWIDGET_H
