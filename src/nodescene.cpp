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

#include "nodescene.h"


NodeScene::NodeScene(QObject *parent):
    QGraphicsScene(parent)
{

}

NodeScene::NodeScene(const QRectF &sceneRect, QObject *parent):
    QGraphicsScene(sceneRect, parent)
{

}

NodeScene::NodeScene(qreal x, qreal y, qreal width, qreal height, QObject *parent):
    QGraphicsScene(x, y, width, height, parent)
{

}

bool NodeScene::addNodeWidget(NodeWidget *node)
{
    bool ret = false;
    if( !m_nodeMapping.keys().contains(node)){
        QGraphicsProxyWidget *proxy = this->addWidget(node);
        m_nodeMapping.insert(node, proxy);
        ret = true;
    }
    return ret;
}
