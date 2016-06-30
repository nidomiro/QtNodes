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

#include "nodewidget.h"
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

#include "ui_nodewidget.h"

#include <QLabel>
#include <QPushButton>
#include <QDebug>

#include "abstractiowidget.h"

NodeWidget::NodeWidget(QWidget *parent):
    NodeWidget(&NodeWidget::createDefaultHeaderWidget, parent)
{

}

NodeWidget::NodeWidget(WidgetCreationFunction headerCreationFunc, QWidget *parent):
    NodeWidget(headerCreationFunc, nullptr, parent)
{

}

NodeWidget::NodeWidget(NodeWidget::WidgetCreationFunction headerCreationFunc, NodeWidget::WidgetCreationFunction footerCreationFunc, QWidget *parent):
    QWidget(parent),
    ui(new Ui::NodeWidget)
{
    ui->setupUi(this);
    headerCreationFunc(this, ui->headerWidget);
    if(footerCreationFunc != nullptr){
        footerCreationFunc(this, ui->footerWidget);
    }
}

NodeWidget::~NodeWidget()
{
    delete ui;
}

bool NodeWidget::addIOWidget(AbstractIOWidget *ioWidget)
{
    ui->centerWidget->layout()->addWidget(ioWidget);
    return true;
}

bool NodeWidget::removeIOWidget(AbstractIOWidget *ioWidget)
{
    ui->centerWidget->layout()->removeWidget(ioWidget);
    return false;
}

QString NodeWidget::nodeName()
{
    return m_nodeName;
}

void NodeWidget::createDefaultHeaderWidget(NodeWidget *node, QWidget *headerWidget)
{
    QLayout *layout = new QHBoxLayout(headerWidget);

    QLabel *headerLabel = new QLabel(node->nodeName(), headerWidget);
    QObject::connect(node, SIGNAL(nodeNameChanged(QString)), headerLabel, SLOT(setText(QString)));
    QSizePolicy spHeaderLabel(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spHeaderLabel.setHorizontalStretch(2);
    headerLabel->setSizePolicy(spHeaderLabel);
    layout->addWidget(headerLabel);

    QPushButton *closeButton = new QPushButton("X", headerWidget);
    QObject::connect(closeButton, SIGNAL(clicked()), node, SLOT(closeNodeWidget()));
    QSizePolicy spCloseButton(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spCloseButton.setHorizontalStretch(1);
    closeButton->setSizePolicy(spCloseButton);
    layout->addWidget(closeButton);


    headerWidget->setLayout(layout);
}

void NodeWidget::setNodeName(const QString &name)
{
    m_nodeName = name;
}

void NodeWidget::closeNodeWidget()
{
    qDebug() <<"NodeWidget::closeNodeWidget() not implemented!!";
}

