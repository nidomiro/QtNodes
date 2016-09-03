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


NodeGridScene::NodeGridScene(INodeGridImpl *nodeGrid, QObject *parent):
    QGraphicsScene(parent),
    m_nodeGrid(nodeGrid)
{
    init();
}

NodeGridScene::NodeGridScene(const QRectF &sceneRect, INodeGridImpl *nodeGrid, QObject *parent):
    QGraphicsScene(sceneRect, parent),
    m_nodeGrid(nodeGrid)
{
    init();
}

NodeGridScene::NodeGridScene(qreal x, qreal y, qreal width, qreal height, INodeGridImpl *nodeGrid, QObject *parent):
    QGraphicsScene(x, y, width, height, parent),
    m_nodeGrid(nodeGrid)
{
    init();
}

bool NodeGridScene::addNodeView(NodeView *node)
{
    bool ret = false;
    if(node != nullptr
            && !m_nodeViews.contains(node->getNodeImpl())
    ){
        this->addItem(node);
        m_nodeViews.insert(node->getNodeImpl(), node);
        ret = true;
    }
    return ret;
}

bool NodeGridScene::removeNodeView(NodeView *node)
{
    if(node == nullptr)
        return false;
    return m_nodeViews.remove(node->getNodeImpl()) > 0;
}

void NodeGridScene::onNodeAdded(INodeImpl *node)
{
    // TODO: Custom header-/footer- creators
    NodeView *nodeView = new NodeView(node);
    addNodeView(nodeView);
}

void NodeGridScene::onNodeRemoved(INodeImpl *node)
{
    this->removeNodeView(m_nodeViews.value(node, nullptr));
}

void NodeGridScene::init()
{
    for( INodeImpl *node :m_nodeGrid->getAllNodes()){
        onNodeAdded(node);
    }
}
