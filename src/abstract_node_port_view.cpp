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
#include "node_view.h"

#include "utils/color_utils.h"

AbstractNodePortView::AbstractNodePortView(NodePortInfo info, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    m_portInfo(info)
{
    //Do not call "init" here, because it calls the virtual method "createCenterWidget", use "AbstractIOGraphicsWidget::create<SubClass>()" instead

    m_layout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal, this);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,2,0,2);
    this->setLayout(m_layout);

    m_leftConnector = new NodePortConnectorView(NodePortConnectorView::POS_LEFT, m_portInfo, this);
    m_centerWidget = new QGraphicsWidget(this);
    m_rightConnector = new NodePortConnectorView(NodePortConnectorView::POS_RIGHT, m_portInfo, this);

    m_layout->addItem(m_leftConnector);
    m_layout->addItem(m_centerWidget);
    m_layout->addItem(m_rightConnector);

    m_layout->setStretchFactor(m_leftConnector, 1);
    m_layout->setStretchFactor(m_centerWidget, 20);
    m_layout->setStretchFactor(m_rightConnector, 1);

    m_centerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    switch(info.type){
    case NodePortIOType::INPUT:
        m_leftConnector->setVisible(true);
        m_rightConnector->setVisible(false);
        break;
    case NodePortIOType::OUTPUT:
        m_leftConnector->setVisible(false);
        m_rightConnector->setVisible(true);
        break;
    default:
        m_leftConnector->setVisible(true);
        m_rightConnector->setVisible(true);
        break;
    }


    // Todo: Remove hacky code after debug
    {
        QPalette pal;
        pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    }
/*    // Todo: Remove hacky code after debug
    {
        QPalette pal;
        pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());
        m_leftConnector->setPalette(pal);
        m_leftConnector->setAutoFillBackground(true);
    }
    // Todo: Remove hacky code after debug
    {
        QPalette pal;
        pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());
        m_rightConnector->setPalette(pal);
        m_rightConnector->setAutoFillBackground(true);
    }*/
    // Todo: Remove hacky code after debug
    {
        QPalette pal;
        pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());
        m_centerWidget->setPalette(pal);
        m_centerWidget->setAutoFillBackground(true);
    }


}

AbstractNodePortView::~AbstractNodePortView()
{

}

QPointF AbstractNodePortView::getPortConnectorMiddleInSceneSpace() const
{
    QPointF ret;
    switch(m_portInfo.type){
    case NodePortIOType::INPUT:
        ret = m_leftConnector->getConnectorMiddleInSceneSpace();
        break;
    case NodePortIOType::OUTPUT:
        ret = m_rightConnector->getConnectorMiddleInSceneSpace();
        break;
    default:
        break;
    }
    return ret;
}

bool AbstractNodePortView::isEditable() const
{
    return m_isEditable;
}

void AbstractNodePortView::setEditable(bool val)
{
    m_isEditable = val;
    emit editableChanged(m_isEditable);
}


void AbstractNodePortView::init()
{
    createCenterWidget(m_centerWidget);
}

