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
#include <QPainter>


//QColor NodeView::defaultBackgroundColor = QColor(150,150,150);
QColor NodeView::defaultBackgroundColor = QColor(136, 205, 204);

qreal NodeView::outerMargin = 5;



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
    this->setFlag(QGraphicsProxyWidget::ItemIsMovable);
    this->setFlag(QGraphicsProxyWidget::ItemIsSelectable);
    this->setFlag(QGraphicsProxyWidget::ItemSendsGeometryChanges);

    m_layout = new QGraphicsLinearLayout(Qt::Orientation::Vertical, this);
    this->setLayout(m_layout);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    m_headerWidget = new QGraphicsWidget(this);
    m_headerWidget->setContentsMargins(NodeView::outerMargin, 0, NodeView::outerMargin, 0);
    m_layout->addItem(m_headerWidget);
    m_centerWidget = new QGraphicsWidget(this);
    m_layout->addItem(m_centerWidget);
    m_centerWidgetLayout = new QGraphicsLinearLayout(Qt::Orientation::Vertical, m_centerWidget);
    m_centerWidgetLayout->setSpacing(0);
    m_centerWidgetLayout->setContentsMargins(0,2,0,2);
    m_centerWidget->setLayout(m_centerWidgetLayout);
    m_footerWidget = new QGraphicsWidget(this);
    m_footerWidget->setContentsMargins(NodeView::outerMargin, 0, NodeView::outerMargin, 0);
    m_footerWidget->setPreferredHeight(5);
    m_layout->addItem(m_footerWidget);


    headerCreationFunc(this, m_headerWidget);
    if(footerCreationFunc != nullptr){
        footerCreationFunc(this, m_footerWidget);
    }

    QPalette pal;
    pal.setColor(QPalette::Window, NodeView::defaultBackgroundColor);
    //this->setAutoFillBackground(true);
    this->setPalette(pal);


    recreateNodePorts();

    setOpacity(.99);

}

NodeView::~NodeView()
{
}

bool NodeView::addPortView(AbstractNodePortView *portView)
{
    portView->setParentItem(this);
    m_centerWidgetLayout->addItem(portView);
    m_centerWidgetLayout->setSpacing(0);
    m_nodePorts.append(portView);

    return true;
}

bool NodeView::removePortView(AbstractNodePortView *portView)
{
    m_centerWidgetLayout->removeItem(portView);
    portView->setParentItem(nullptr);
    m_nodePorts.removeOne(portView);
    return true;
}

bool NodeView::removeAllPortViews()
{
    for(auto port: m_nodePorts){
        m_centerWidgetLayout->removeItem(port);
        port->setParentItem(nullptr);
        port->deleteLater();
    }
    m_nodePorts.clear();
    return true;
}

QPointF NodeView::getPortConnectorMiddleInSceneSpace(const NodePortAddress &address)
{
    QPointF ret;
    if(address.port < m_nodePorts.size()){
        ret = m_nodePorts[address.port]->getPortConnectorMiddleInSceneSpace();
    }
    return ret;
}

QString NodeView::nodeName() const
{
    return m_nodeImpl->getNodeName();
}

void NodeView::createDefaultHeaderWidget(NodeView *node, QGraphicsWidget *headerWidget)
{
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal, headerWidget);

    QLabel *headerLabel = new QLabel(node->nodeName());
    QObject::connect(node, SIGNAL(nodeNameChanged(QString)), headerLabel, SLOT(setText(QString)));
    QSizePolicy spHeaderLabel(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spHeaderLabel.setHorizontalStretch(2);
    headerLabel->setSizePolicy(spHeaderLabel);
    headerLabel->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsProxyWidget *headerLabelProxy = new QGraphicsProxyWidget(headerWidget);
    headerLabelProxy->setWidget(headerLabel);
    layout->addItem(headerLabelProxy);



    QPushButton *closeButton = new QPushButton("X");
    QObject::connect(closeButton, SIGNAL(clicked()), node, SLOT(closeNodeWidget()));
    QSizePolicy spCloseButton(QSizePolicy::Minimum, QSizePolicy::Minimum);
    spCloseButton.setHorizontalStretch(1);
    closeButton->setSizePolicy(spCloseButton);
    closeButton->setMaximumSize(QSize(25,25));

    QGraphicsProxyWidget *closeButtonProxy = new QGraphicsProxyWidget(headerWidget);
    closeButtonProxy->setWidget(closeButton);
    layout->addItem(closeButtonProxy);

    layout->setAlignment(headerLabelProxy, Qt::AlignCenter);
    layout->setAlignment(closeButtonProxy, Qt::AlignCenter);

    headerWidget->setLayout(layout);

    /*
    QPalette pal;
    headerWidget->setAutoFillBackground(true);
    pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());
    headerWidget->setPalette(pal);
    */

}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);


    QBrush brush(NodeView::defaultBackgroundColor);

    //painter->setBackground(brush);
    //painter->eraseRect(this->boundingRect());
    //QRectF rect = this->boundingRect();
    //rect.adjust(outerMargin, 0, -outerMargin, 0);
    //QPainterPath path = Shape;
    //path.addRoundedRect(rect, 10,10);
    painter->fillPath(this->shape(), brush);
    //painter->setBrush(brush);
    //painter->drawRoundedRect(this->boundingRect(), 10,10);

    qDebug() << "paint: " << this->boundingRect();
}

QPainterPath NodeView::shape() const
{
    QPainterPath path;
    QRectF rect = this->boundingRect();
    rect.adjust(outerMargin, 0, -outerMargin, 0);
    path.addRoundedRect(rect, 10,10);
    return path;
}

void NodeView::recreateNodePorts()
{
    removeAllPortViews();

    NodePortViewFactory &fac = NodePortViewFactory::get();
    for(auto port : m_nodeImpl->getNodePorts()){
        auto portView = fac.createNodePortView(port, this);
        this->addPortView(portView);

    }
}

QVariant NodeView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
            QPointF newPos = value.toPointF();
            emit nodePositionChanged(newPos);
        }
    return QGraphicsWidget::itemChange(change, value);
}


void NodeView::closeNodeWidget()
{
    qDebug() <<"NodeGraphicsWidget::closeNodeWidget() not implemented!!";
}

INodeImpl *NodeView::getNodeImpl()
{
    return m_nodeImpl;
}

void NodeView::onNodeNameChanged(QString newName)
{
    emit nodeNameChanged(newName);
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


