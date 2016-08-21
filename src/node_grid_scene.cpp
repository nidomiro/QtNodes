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

#include "node_grid_scene.h"


NodeGridScene::NodeGridScene(QObject *parent):
    QGraphicsScene(parent)
{

}

NodeGridScene::NodeGridScene(const QRectF &sceneRect, QObject *parent):
    QGraphicsScene(sceneRect, parent)
{

}

NodeGridScene::NodeGridScene(qreal x, qreal y, qreal width, qreal height, QObject *parent):
    QGraphicsScene(x, y, width, height, parent)
{

}

bool NodeGridScene::addNodeWidget(NodeGraphicsWidget *node)
{
    bool ret = false;
    if( !m_nodes.contains(node)){
        this->addItem(node);
        m_nodes.append(node);
        node->setFlag(QGraphicsProxyWidget::ItemIsMovable);
        node->setFlag(QGraphicsProxyWidget::ItemIsSelectable);
        node->setFlag(QGraphicsProxyWidget::ItemSendsGeometryChanges);
        ret = true;
    }
    return ret;
}
