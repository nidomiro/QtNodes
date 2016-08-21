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

class AbstractIOGraphicsWidget;
class IConnectionRegister;
class QGraphicsLinearLayout;

#include <QGraphicsWidget>
#include <QUuid>

class NodeGraphicsWidget : public QGraphicsWidget
{
    Q_OBJECT

    Q_PROPERTY(QString nodeName READ nodeName WRITE setNodeName NOTIFY nodeNameChanged)

public:
    typedef void (*WidgetCreationFunction)(NodeGraphicsWidget *node, QGraphicsWidget *widgetToCreate);

    explicit NodeGraphicsWidget(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    explicit NodeGraphicsWidget(WidgetCreationFunction headerCreationFunc, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    explicit NodeGraphicsWidget(WidgetCreationFunction headerCreationFunc, WidgetCreationFunction footerCreationFunc, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    ~NodeGraphicsWidget();

    bool addIOWidget(AbstractIOGraphicsWidget *ioWidget);
    bool removeIOWidget(AbstractIOGraphicsWidget *ioWidget);

    QString nodeName() const;
    QUuid getNodeAdress() const;

    const IConnectionRegister *getConnectionRegister() const;


    static void createDefaultHeaderWidget(NodeGraphicsWidget *node, QGraphicsWidget *headerWidget);



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

    IConnectionRegister *m_connections = nullptr;

};

#endif // NODEGRAPHICSWIDGET_H
