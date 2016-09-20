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

#include "qstring_node_port_view.h"

#include "utils/color_utils.h"

#include <QMetaType>


QStringNodePortView::QStringNodePortView(NodePortInfo info, QGraphicsItem *parent):
    AbstractNodePortView(info, parent)
{
}

QString QStringNodePortView::getValueType() const
{
    return "QString";
}

void QStringNodePortView::displayValue(QVariant val)
{
    m_lineEdit->setText(val.toString());
}

void QStringNodePortView::setConfig(QString key, QVariant value)
{

}

void QStringNodePortView::onEditableChanged(bool val)
{
    m_lineEdit->setReadOnly(!val);
}

void QStringNodePortView::createCenterWidget(QGraphicsWidget *centerWidget)
{
    m_layout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal, centerWidget);
    m_layout->setContentsMargins(2,0,2,0);

    m_lineEdit = new QLineEdit("Text"); // no need to delete, QGraphicsProxyWidget handles it
    m_lineEditProxy = new QGraphicsProxyWidget(centerWidget);
    m_lineEditProxy->setWidget(m_lineEdit);

    m_layout->addItem(m_lineEditProxy);

    QObject::connect(m_lineEdit, &QLineEdit::textEdited,
                     this, &QStringNodePortView::valueChangedInUi);

    // Todo: Remove hacky code after debug
    {
        QPalette pal;
        pal.setColor(QPalette::Window, ColorUtils::generateRandomColor());
        m_lineEditProxy->setAutoFillBackground(true);
        m_lineEditProxy->setPalette(pal);
    }


    centerWidget->setLayout(m_layout);
}
