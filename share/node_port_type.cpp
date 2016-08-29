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


#include "node_port_type.h"

QString enumToString(const NodePortType &type)
{
//    using namespace NodePortInfo;
    QString ret;
    switch(type){
    case NodePortType::INPUT:
        ret=STR(INPUT);
        break;
    case NodePortType::OUTPUT:
        ret=STR(OUTPUT);
        break;
    case NodePortType::NONE:
    default:
        ret=STR(NONE);
        break;
    }
    return ret;
}

NodePortType enumFromString(const QString &str)
{
//    using namespace NodePortInfo;
    NodePortType ret = NodePortType::NONE;

    if(str == STR(INPUT))
        ret = NodePortType::INPUT;
    else if(str == STR(OUTPUT))
        ret = NodePortType::OUTPUT;
    else
        ret = NodePortType::NONE;

    return ret;
}
