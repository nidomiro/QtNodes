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

#include "nodegraphicswidget.h"
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



#include "abstractiographicswidget.h"
#include "utils/colorutils.h"

NodeGraphicsWidget::NodeGraphicsWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    NodeGraphicsWidget(&NodeGraphicsWidget::createDefaultHeaderWidget, parent, wFlags)
{

}

NodeGraphicsWidget::NodeGraphicsWidget(WidgetCreationFunction headerCreationFunc, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    NodeGraphicsWidget(headerCreationFunc, nullptr, parent, wFlags)
{

}

NodeGraphicsWidget::NodeGraphicsWidget(NodeGraphicsWidget::WidgetCreationFunction headerCreationFunc, NodeGraphicsWidget::WidgetCreationFunction footerCreationFunc, QGraphicsItem *parent, Qt::WindowFlags wFlags):
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

NodeGraphicsWidget::~NodeGraphicsWidget()
{
}

bool NodeGraphicsWidget::addIOWidget(AbstractIOGraphicsWidget *ioWidget)
{
    m_centerWidgetLayout->addItem(ioWidget);
    m_centerWidgetLayout->setSpacing(0);

    return true;
}

bool NodeGraphicsWidget::removeIOWidget(AbstractIOGraphicsWidget *ioWidget)
{
    m_centerWidgetLayout->removeItem(ioWidget);
    return false;
}

QString NodeGraphicsWidget::nodeName()
{
    return m_nodeName;
}

void NodeGraphicsWidget::createDefaultHeaderWidget(NodeGraphicsWidget *node, QGraphicsWidget *headerWidget)
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

void NodeGraphicsWidget::setNodeName(const QString &name)
{
    m_nodeName = name;
    emit nodeNameChanged(m_nodeName);
}

void NodeGraphicsWidget::closeNodeWidget()
{
    qDebug() <<"NodeGraphicsWidget::closeNodeWidget() not implemented!!";
}

