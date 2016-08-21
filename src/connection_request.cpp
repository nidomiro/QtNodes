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

#include "connection_request.h"


#include <QDataStream>

void ConnectionRequest::serialize(QByteArray& byteArray)
{
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    //stream.setVersion(QDataStream::Qt_5_5);

    stream << this->source
           << this->target;
}

void ConnectionRequest::deserialize(const QByteArray& byteArray)
{
   QDataStream stream(byteArray);
   //stream.setVersion(QDataStream::Qt_5_5);


   //stream >> (void*)this->source
   //       >> (void*)this->target;
}
