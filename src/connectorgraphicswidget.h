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

#include <QObject>
#include <QGraphicsWidget>
#include <QColor>

class ConnectorGraphicsWidget : public QGraphicsWidget
{
    Q_OBJECT

public:
    enum Position{
        POS_LEFT,
        POS_RIGHT
    };

public:
    ConnectorGraphicsWidget(Position pos, QGraphicsItem *parent = nullptr);


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

//    virtual void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
//    QRectF boundingRect() const override;
//    QPainterPath shape() const override;

    QColor conectorColor() const;
    void setConectorColor(const QColor &conectorColor);

protected:
    Position m_connectorPos = POS_LEFT;

    QColor m_conectorColor = QColor(255,255,51);

public:
    static qreal connectorRadius;



};

#endif // CONNECTORGRAPHICSWIDGET_H
