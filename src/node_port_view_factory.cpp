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

#include "node_port_view_factory.h"

#include "nodeports/qstring_node_port_view.h"

NodePortViewFactory::NodePortViewFactory()
{

}

AbstractNodePortView *NodePortViewFactory::createNodePortView(const NodePortInfo &info, QGraphicsItem *parent)
{
    // TODO: replace with dynamic selection!

    QString visualType = info.visualHint;

    if(visualType == "default:unsetVisualHint")
        visualType = "default:string";

    CreateNodePortViewFunc f = this->map.value(visualType, nullptr);

    //qDebug() << "f is " <<f <<"and visualHint is " <<visualType;

    if(f == nullptr)
        return nullptr;


    AbstractNodePortView *nodePort = f(info, parent);
    return nodePort;
}
