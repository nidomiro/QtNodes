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

#include "node_g_w.h"
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

#include <QLabel>
#include <QPushButton>
#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QUuid>



#include "abstract_node_port_g_w.h"
#include "utils/color_utils.h"

NodeGW::NodeGW(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    NodeGW(&NodeGW::createDefaultHeaderWidget, parent, wFlags)
{

}

NodeGW::NodeGW(WidgetCreationFunction headerCreationFunc, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    NodeGW(headerCreationFunc, nullptr, parent, wFlags)
{

}

NodeGW::NodeGW(NodeGW::WidgetCreationFunction headerCreationFunc, NodeGW::WidgetCreationFunction footerCreationFunc, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QGraphicsWidget(parent, wFlags)
{
    m_layout = new QGraphicsLinearLayout(Qt::Orientation::Vertical, this);
    this->setLayout(m_layout);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    m_headerWidget = new QGraphicsWidget(this);
    m_layout->addItem(m_headerWidget);
    m_centerWidget = new QGraphicsWidget(this);
    m_layout->addItem(m_centerWidget);
    m_centerWidgetLayout = new QGraphicsLinearLayout(Qt::Orientation::Vertical, m_centerWidget);
    m_centerWidgetLayout->setSpacing(0);
    m_centerWidgetLayout->setContentsMargins(0,2,0,2);
    m_centerWidget->setLayout(m_centerWidgetLayout);
    m_footerWidget = new QGraphicsWidget(this);
    m_footerWidget->setPreferredHeight(5);
    m_layout->addItem(m_footerWidget);


    headerCreationFunc(this, m_headerWidget);
    if(footerCreationFunc != nullptr){
        footerCreationFunc(this, m_footerWidget);
    }

    // Todo: Remove hacky code after debug
    {
        QPalette pal;
        pal.setColor(QPalette::Window, QColor(200,50,50));
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    }

}

NodeGW::~NodeGW()
{
}

bool NodeGW::addIOWidget(AbstractNodePortGW *ioWidget)
{
    m_centerWidgetLayout->addItem(ioWidget);
    m_centerWidgetLayout->setSpacing(0);
    m_nodePorts.append(ioWidget);

    return true;
}

bool NodeGW::removeIOWidget(AbstractNodePortGW *ioWidget)
{
    m_centerWidgetLayout->removeItem(ioWidget);
    m_nodePorts.removeOne(ioWidget);
    return false;
}

QString NodeGW::nodeName() const
{
    return m_nodeName;
}

void NodeGW::createDefaultHeaderWidget(NodeGW *node, QGraphicsWidget *headerWidget)
{
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal, headerWidget);

    QLabel *headerLabel = new QLabel(node->nodeName());
    QObject::connect(node, SIGNAL(nodeNameChanged(QString)), headerLabel, SLOT(setText(QString)));
    QSizePolicy spHeaderLabel(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spHeaderLabel.setHorizontalStretch(2);
    headerLabel->setSizePolicy(spHeaderLabel);

    QGraphicsProxyWidget *headerLabelProxy = new QGraphicsProxyWidget(headerWidget);
    headerLabelProxy->setWidget(headerLabel);
    layout->addItem(headerLabelProxy);

    QPushButton *closeButton = new QPushButton("X");
    QObject::connect(closeButton, SIGNAL(clicked()), node, SLOT(closeNodeWidget()));
    QSizePolicy spCloseButton(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spCloseButton.setHorizontalStretch(1);
    closeButton->setSizePolicy(spCloseButton);
    QGraphicsProxyWidget *closeButtonProxy = new QGraphicsProxyWidget(headerWidget);
    closeButtonProxy->setWidget(closeButton);
    layout->addItem(closeButtonProxy);

    headerWidget->setLayout(layout);

    headerWidget->setAutoFillBackground(true);

    QPalette pal;

    pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());

    headerWidget->setPalette(pal);


}

void NodeGW::setNodeName(const QString &name)
{
    m_nodeName = name;
    emit nodeNameChanged(m_nodeName);
}

void NodeGW::closeNodeWidget()
{
    qDebug() <<"NodeGraphicsWidget::closeNodeWidget() not implemented!!";
}

QUuid NodeGW::getNodeAdress() const
{
    return m_nodeAdress;
}

qint16 NodeGW::getPortNumber(AbstractNodePortGW *nodePort) const
{
   return m_nodePorts.indexOf(nodePort, -1);
}

bool NodeGW::connectionRequest(const NodePortAddress &source, NodePortAddress &thisAddress, const bool &test)
{
    bool ret = true;
    thisAddress.nodeAddress = m_nodeImpl->getNodeAddress();
    if(test){
        ret = m_nodeImpl->canConnect(source, thisAddress);
    } else {
        Connection c = m_nodeImpl->connect(source, thisAddress);
        ret = !(c.isNull());
    }
    return ret;
}

