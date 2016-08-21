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

#include "qstring_io_graphics_widget.h"

#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>

#include "utils/color_utils.h"


void QStringIOGraphicsWidget::createCenterWidget(QGraphicsWidget *centerWidget)
{
    m_layout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal, centerWidget);
    m_layout->setContentsMargins(2,0,2,0);

    m_label = new QLabel("Some Text"); // no need to destroy, QGraphicsProxyWidget handles it
    m_labelProxy = new QGraphicsProxyWidget(centerWidget);
    m_labelProxy->setWidget(m_label);

    m_layout->addItem(m_labelProxy);

    // Todo: Remove hacky code after debug
    {
        QPalette pal;
        pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());
        m_labelProxy->setAutoFillBackground(true);
        m_labelProxy->setPalette(pal);
    }


    centerWidget->setLayout(m_layout);
}
