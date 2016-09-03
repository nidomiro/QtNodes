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

#ifndef NODEGRAPHICSWIDGET_H
#define NODEGRAPHICSWIDGET_H

class AbstractNodePortView;
class IConnectionRegister;

#include "qtnodes_global.h"
#include "shared/i_node_impl.h"
#include "shared/i_node_state_listener.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include <QUuid>

class QTNODES_EXPORT NodeView : public QGraphicsWidget, public INodeStateListener
{
    Q_OBJECT


public:
    typedef void (*WidgetCreationFunction)(NodeView *node, QGraphicsWidget *widgetToCreate);

    explicit NodeView(INodeImpl *nodeImpl, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    explicit NodeView(INodeImpl *nodeImpl, WidgetCreationFunction headerCreationFunc, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    explicit NodeView(INodeImpl *nodeImpl, WidgetCreationFunction headerCreationFunc, WidgetCreationFunction footerCreationFunc, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    ~NodeView();

    bool addPortView(AbstractNodePortView *portView);
    bool removePortView(AbstractNodePortView *portView);
    bool removeAllPortViews();

    QString nodeName() const;

    INodeImpl *getNodeImpl();



    void onNodeNameChanged(QString newName) override;
    void onPortCountChange() override;
    void onInputConnectionsChanged() override;
    void onOutputConnectionsChanged() override;
    void onPortValueChanged(int portNumber) override;




    static void createDefaultHeaderWidget(NodeView *node, QGraphicsWidget *headerWidget);

protected:

    void recreateNodePorts();


public slots:

    void closeNodeWidget();

signals:

    void nodeNameChanged(const QString &newName);


private:

    QUuid m_nodeAdress = QUuid::createUuid();

    QGraphicsLinearLayout *m_layout = nullptr;

    QGraphicsWidget *m_headerWidget = nullptr;
    QGraphicsWidget *m_centerWidget = nullptr;
    QGraphicsLinearLayout *m_centerWidgetLayout = nullptr;
    QGraphicsWidget *m_footerWidget = nullptr;

    QList<AbstractNodePortView *> m_nodePorts;

protected:

    INodeImpl *m_nodeImpl = nullptr;

};

#endif // NODEGRAPHICSWIDGET_H
