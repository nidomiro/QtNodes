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

class AbstractNodePortGW;
class IConnectionRegister;

#include "qtnodes_global.h"
#include "i_node_impl.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include <QUuid>

class QTNODESSHARED_EXPORT NodeGW : public QGraphicsWidget
{
    Q_OBJECT

    Q_PROPERTY(QString nodeName READ nodeName WRITE setNodeName NOTIFY nodeNameChanged)

public:
    typedef void (*WidgetCreationFunction)(NodeGW *node, QGraphicsWidget *widgetToCreate);

    explicit NodeGW(INodeImpl *nodeImpl, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    explicit NodeGW(INodeImpl *nodeImpl, WidgetCreationFunction headerCreationFunc, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    explicit NodeGW(INodeImpl *nodeImpl, WidgetCreationFunction headerCreationFunc, WidgetCreationFunction footerCreationFunc, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    ~NodeGW();

    bool addIOWidget(AbstractNodePortGW *ioWidget);
    bool removeIOWidget(AbstractNodePortGW *ioWidget);

    QString nodeName() const;
    QUuid getNodeAdress() const;

    const INodeImpl *getNodeImpl() const;


    qint16 getPortNumber(const AbstractNodePortGW *nodePort) const;
    bool connectionRequest(const NodePortAddress &source, const NodePortAddress &thisAddress, const bool &isTest=false);
    void constructWholeAddress(NodePortAddress &addressToConstruct) const;






    static void createDefaultHeaderWidget(NodeGW *node, QGraphicsWidget *headerWidget);


public slots:
    void setNodeName(const QString &name);

    void closeNodeWidget();

signals:

    void nodeNameChanged(const QString &newName);


private:

    QString m_nodeName = "Unnamed Node";
    QUuid m_nodeAdress = QUuid::createUuid();

    QGraphicsLinearLayout *m_layout = nullptr;

    QGraphicsWidget *m_headerWidget = nullptr;
    QGraphicsWidget *m_centerWidget = nullptr;
    QGraphicsLinearLayout *m_centerWidgetLayout = nullptr;
    QGraphicsWidget *m_footerWidget = nullptr;

    QList<AbstractNodePortGW *> m_nodePorts;

protected:

    INodeImpl *m_nodeImpl = nullptr;

};

#endif // NODEGRAPHICSWIDGET_H
