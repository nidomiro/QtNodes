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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>

#include "abstractiographicswidget.h"
#include "iowidgets/qstringiographicswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_nodeGridScene = new NodeGridScene;

    ui->nodeGridView->setScene(m_nodeGridScene);

    QList<NodeGraphicsWidget*> nodes;

    for(int i=0; i<2; i++)
    {
        NodeGraphicsWidget *nw = new NodeGraphicsWidget;
        nw->setNodeName("Node" + QString::number(i));
        nodes.append(nw);

        for( int j=0; j<3; j++){
            nw->addIOWidget(AbstractIOGraphicsWidget::create<QStringIOGraphicsWidget>());
        }

        m_nodeGridScene->addNodeWidget(nw);
    }

    //AbstractIOGraphicsWidget *aiogw = AbstractIOGraphicsWidget::create<AbstractIOGraphicsWidget>();
//    AbstractIOGraphicsWidget *aiogw2 = AbstractIOGraphicsWidget::create<MainWindow>();



}

MainWindow::~MainWindow()
{
    delete ui;
}
