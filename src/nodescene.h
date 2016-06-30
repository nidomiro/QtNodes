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

#ifndef NODESCENE_H
#define NODESCENE_H

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QMap>

#include "nodewidget.h"


class NodeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NodeScene(QObject *parent = 0);
    NodeScene(const QRectF &sceneRect, QObject *parent = 0);
    NodeScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);

    bool addNodeWidget(NodeWidget * node);

signals:

public slots:



private:
    QMap<NodeWidget*, QGraphicsProxyWidget*> m_nodeMapping;
};

#endif // NODESCENE_H
