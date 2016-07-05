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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_nodeGridScene = new NodeGridScene;

    ui->nodeGridView->setScene(m_nodeGridScene);

    QList<NodeWidget*> nodes;

    for(int i=0; i<2; i++)
    {
        NodeWidget *nw = new NodeWidget;
        nw->setNodeName("Node" + QString::number(i));
        nodes.append(nw);
        m_nodeGridScene->addNodeWidget(nw);
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}
