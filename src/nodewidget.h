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

#ifndef NODEWIDGET_H
#define NODEWIDGET_H

class AbsractIOWidget;

#include <QWidget>

namespace Ui {
class NodeWidget;
}

class NodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NodeWidget(QWidget *parent = nullptr);
    ~NodeWidget();

    bool setHeaderWidget(QWidget *widget);
    bool removeHeaderWidget(QWidget *widget);

    bool addIOWidget(AbsractIOWidget *ioWidget);
    bool removeIOWidget(AbsractIOWidget *ioWidget);

    bool setFooterWidget(QWidget *widget);
    bool removeFooterWidget(QWidget *widget);


private:
    Ui::NodeWidget *ui;
};

#endif // NODEWIDGET_H
