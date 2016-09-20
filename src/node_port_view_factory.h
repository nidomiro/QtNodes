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


#ifndef NODEPORTVIEWFACTORY_H
#define NODEPORTVIEWFACTORY_H

#include "qtnodes_global.h"
#include "shared/node_port_info.h"
#include "abstract_node_port_view.h"


#include <QString>
#include <QMap>
#include <QDebug>

class QTNODES_EXPORT NodePortViewFactory
{
public:
    typedef AbstractNodePortView* (*CreateNodePortViewFunc)(NodePortInfo info, QGraphicsItem *parent);

    AbstractNodePortView *createNodePortView(const NodePortInfo &info, QGraphicsItem *parent = nullptr);



protected:
    NodePortViewFactory();


private:
    QMap<QString, CreateNodePortViewFunc> map;

public:


    static inline NodePortViewFactory& get()
    {
        static NodePortViewFactory reg;
        return reg;
    }

    template<class T>
    class RegistryEntry
    {
      public:
        static RegistryEntry<T>& Instance(const QString& name)
        {
            // Because I use a singleton here, even though `COMPONENT_REGISTER`
            // is expanded in multiple translation units, the constructor
            // will only be executed once. Only this cheap `Instance` function
            // (which most likely gets inlined) is executed multiple times.

            static RegistryEntry<T> inst(name);
            return inst;
        }

      private:
        RegistryEntry(const QString& name)
        {
            qDebug() <<"Adding Type:" <<name;
            NodePortViewFactory& reg = NodePortViewFactory::get();
            CreateNodePortViewFunc func = AbstractNodePortView::createA<T>;

            if(reg.map.contains(name))
                qWarning("overriding existing entry in Factory");

            reg.map.insert(name, func);


        }

        RegistryEntry(const RegistryEntry<T>&) = delete; // C++11 feature
        RegistryEntry& operator=(const RegistryEntry<T>&) = delete;
    };
};



#define REGISTER_NODE_PORT_VIEW_TYPE(TYPE, NAME)                                        \
    namespace                                                                 \
    {                                                                         \
        template<class T>                                                     \
        class NodePortViewTypeRegistration;                                          \
                                                                              \
        template<>                                                            \
        class NodePortViewTypeRegistration<TYPE>                                     \
        {                                                                     \
            static const ::NodePortViewFactory::RegistryEntry<TYPE>& reg;       \
        };                                                                    \
                                                                              \
        const ::NodePortViewFactory::RegistryEntry<TYPE>&                       \
            NodePortViewTypeRegistration<TYPE>::reg =                                \
                ::NodePortViewFactory::RegistryEntry<TYPE>::Instance(NAME);     \
    }

#endif // NODEPORTVIEWFACTORY_H
