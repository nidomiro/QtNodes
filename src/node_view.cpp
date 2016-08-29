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

#include "node_view.h"
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

#include "abstract_node_port_view.h"
#include "utils/color_utils.h"
#include "node_port_view_factory.h"

#include <QLabel>
#include <QPushButton>
#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QUuid>





NodeView::NodeView(INodeImpl *nodeImpl, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    NodeView(nodeImpl, &NodeView::createDefaultHeaderWidget, parent, wFlags)
{

}

NodeView::NodeView(INodeImpl *nodeImpl, WidgetCreationFunction headerCreationFunc, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    NodeView(nodeImpl, headerCreationFunc, nullptr, parent, wFlags)
{

}

NodeView::NodeView(INodeImpl *nodeImpl, NodeView::WidgetCreationFunction headerCreationFunc, NodeView::WidgetCreationFunction footerCreationFunc, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QGraphicsWidget(parent, wFlags),
    m_nodeImpl(nodeImpl)
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


    recreateNodePorts();

}

NodeView::~NodeView()
{
}

bool NodeView::addIOWidget(AbstractNodePortView *ioWidget)
{
    m_centerWidgetLayout->addItem(ioWidget);
    m_centerWidgetLayout->setSpacing(0);
    m_nodePorts.append(ioWidget);

    return true;
}

bool NodeView::removeIOWidget(AbstractNodePortView *ioWidget)
{
    m_centerWidgetLayout->removeItem(ioWidget);
    m_nodePorts.removeOne(ioWidget);
    return false;
}

QString NodeView::nodeName() const
{
    return m_nodeName;
}

void NodeView::createDefaultHeaderWidget(NodeView *node, QGraphicsWidget *headerWidget)
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

void NodeView::recreateNodePorts()
{
    NodePortViewFactory *fac = nullptr;
    for(auto port : m_nodeImpl->getNodePorts()){
        auto portView = fac->createNodePortView(port, this);
        this->addIOWidget(portView);

    }
}

void NodeView::setNodeName(const QString &name)
{
    m_nodeName = name;
    emit nodeNameChanged(m_nodeName);
}

void NodeView::closeNodeWidget()
{
    qDebug() <<"NodeGraphicsWidget::closeNodeWidget() not implemented!!";
}

QUuid NodeView::getNodeAdress() const
{
    return m_nodeAdress;
}

const INodeImpl *NodeView::getNodeImpl() const
{
    return m_nodeImpl;
}

qint16 NodeView::getPortNumber(const AbstractNodePortView *nodePort) const
{

    return m_nodePorts.indexOf((AbstractNodePortView *)nodePort); // returns -1 if not found
}

bool NodeView::connectionRequest(const NodePortAddress &source, const NodePortAddress &thisAddress, const bool &isTest)
{
    bool ret = true;
    if(isTest){
        ret = m_nodeImpl->canConnect(source, thisAddress);
    } else {
        Connection c = m_nodeImpl->connect(source, thisAddress);
        ret = !(c.isNull());
    }
    qDebug() <<source.toString() << " -> " <<thisAddress.toString() <<" = " <<ret;
    return ret;
}

void NodeView::onPortCountChange()
{
    recreateNodePorts();
}

void NodeView::onInputConnectionsChanged()
{

}

void NodeView::onOutputConnectionsChanged()
{

}

void NodeView::onPortValueChanged(int portNumber)
{

}


