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
#include <QDebug>

#include "abstract_io_graphics_widget.h"
#include "iowidgets/qstring_io_graphics_widget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_nodeGridScene = new NodeGridScene;

    ui->nodeGridView->setScene(m_nodeGridScene);
    m_nodeGridScene->setSceneRect(QRect(QPoint(0,0),ui->nodeGridView->size()));



    NodeGraphicsWidget *nw = new NodeGraphicsWidget;
    nw->setNodeName("Node" + QString::number(m_nodes.size()));
    m_nodes.append(nw);

    for( int j=0; j<3; j++){
        nw->addIOWidget(AbstractIOGraphicsWidget::create<QStringIOGraphicsWidget>());
    }

    m_nodeGridScene->addNodeWidget(nw);


    ui->nodeGridView->setSceneRect(0, 0, ui->nodeGridView->width(), ui->nodeGridView->height());
    ui->nodeGridView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->nodeGridView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    AbstractIOGraphicsWidget *aiogw = AbstractIOGraphicsWidget::create<AbstractIOGraphicsWidget>();
//    AbstractIOGraphicsWidget *aiogw2 = AbstractIOGraphicsWidget::create<MainWindow>();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addNode_clicked()
{

    NodeGraphicsWidget *nw = new NodeGraphicsWidget;
    nw->setNodeName("Node" + QString::number(m_nodes.size()));
    m_nodes.append(nw);
    qDebug() <<"Node: " <<nw->nodeName() <<"j: -1" <<" NodeGraphicsWidgetSize: " <<nw->size();
    for( int j=0; j<3; j++){
        nw->addIOWidget(AbstractIOGraphicsWidget::create<QStringIOGraphicsWidget>());
        qDebug() <<"Node: " <<nw->nodeName() <<"j: " <<j <<" NodeGraphicsWidgetSize: " <<nw->size();
    }

    m_nodeGridScene->addNodeWidget(nw);

}

void MainWindow::on_addIOWidget_clicked()
{
    if(m_nodes.size() < 1)
        return;

    NodeGraphicsWidget *nw = m_nodes[m_nodes.size() - 1];
    nw->addIOWidget(AbstractIOGraphicsWidget::create<QStringIOGraphicsWidget>());
    qDebug() <<"Node: " <<nw->nodeName() <<"j: **" <<" NodeGraphicsWidgetSize: " <<nw->size();

}
