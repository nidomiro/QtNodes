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

#ifndef NODEGRIDSCENE_H
#define NODEGRIDSCENE_H

#include "qtnodes_global.h"
#include "node_view.h"
#include "shared/i_node_grid_impl.h"
#include "shared/i_node_grid_state_listener.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QMap>




class QTNODES_EXPORT NodeGridScene : public QGraphicsScene, public INodeGridStateListener
{
    Q_OBJECT
public:
    explicit NodeGridScene(INodeGridImpl *nodeGrid, QObject *parent = 0);
    NodeGridScene(const QRectF &sceneRect, INodeGridImpl *nodeGrid, QObject *parent = 0);
    NodeGridScene(qreal x, qreal y, qreal width, qreal height, INodeGridImpl *nodeGrid, QObject *parent = 0);

    bool addNodeView(NodeView * node);
    bool removeNodeView(NodeView * node);

    // INodeGridStateListener interface
    void onNodeAdded(INodeImpl *node) override;
    void onNodeRemoved(INodeImpl *node) override;

signals:

public slots:

private:
    void init();



private:
    INodeGridImpl *m_nodeGrid = nullptr;
    QMap<INodeImpl *, NodeView *> m_nodeViews;


};

#endif // NODEGRIDSCENE_H
