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
#include "ui_nodewidget.h"

#include <QLabel>
#include <QPushButton>
#include <QDebug>

NodeWidget::NodeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeWidget)
{
    ui->setupUi(this);
    createHeaderWidget(ui->headerWidget); //TODO: change -> always calles "createHeaderWidget" of this class (ignoring override because it's not known in this constructor)
}

NodeWidget::~NodeWidget()
{
    delete ui;
}

bool NodeWidget::addIOWidget(AbsractIOWidget *ioWidget)
{
    return false;
}

bool NodeWidget::removeIOWidget(AbsractIOWidget *ioWidget)
{
    return false;
}

bool NodeWidget::setFooterWidget(QWidget *widget)
{
    return false;
}

bool NodeWidget::removeFooterWidget(QWidget *widget)
{
    return false;
}

QString NodeWidget::nodeName()
{
    return m_nodeName;
}

void NodeWidget::createHeaderWidget(QWidget *headerWidget)
{
    QLayout *layout = new QHBoxLayout(headerWidget);

    QLabel *headerLabel = new QLabel(nodeName(), headerWidget);
    layout->addWidget(headerLabel);

    QPushButton *closeButton = new QPushButton("X", headerWidget);
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(closeNodeWidget()));
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

