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


#ifndef I_NODE_STATE_LISTENER_H
#define I_NODE_STATE_LISTENER_H

#include "qtnodesshared_global.h"


class INodeStateListener{
public:
    virtual void onNodeNameChanged(QString newName) = 0;
    virtual void onPortCountChange() = 0;
    virtual void onInputConnectionsChanged() = 0;
    virtual void onOutputConnectionsChanged() = 0;
    virtual void onPortValueChanged(int portNumber) = 0;
};

#endif // I_NODE_STATE_LISTENER_H
