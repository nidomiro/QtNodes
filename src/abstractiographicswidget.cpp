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

#include "abstractiographicswidget.h"
#include "ui_abstractiowidget.h"

#include <QGraphicsLinearLayout>

#include "utils/colorutils.h"

AbstractIOGraphicsWidget::AbstractIOGraphicsWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QGraphicsWidget(parent, wFlags)
{
    //Do not call "init" here, because it calls the virtual method "createCenterWidget", use "AbstractIOGraphicsWidget::create<SubClass>()" instead

    m_layout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal, this);

    m_leftConnector = new QGraphicsWidget(this);
    m_centerWidget = new QGraphicsWidget(this);
    m_rightConnector = new QGraphicsWidget(this);

    m_layout->addItem(m_leftConnector);
    m_layout->addItem(m_centerWidget);
    m_layout->addItem(m_rightConnector);

    m_layout->setStretchFactor(m_leftConnector, 1);
    m_layout->setStretchFactor(m_centerWidget, 3);
    m_layout->setStretchFactor(m_rightConnector, 1);

    QPalette pal;

    pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());

    this->setPalette(pal);


}

AbstractIOGraphicsWidget::~AbstractIOGraphicsWidget()
{

}

void AbstractIOGraphicsWidget::init()
{
    createCenterWidget(m_centerWidget);
}

