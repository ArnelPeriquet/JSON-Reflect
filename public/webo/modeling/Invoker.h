/*
* (C) Copyright 2015  Arnel I Periquet.
*
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v1.0
* which accompanies this distribution, and is available at
* http://www.eclipse.org/legal/epl-v10.html
*
*/

#pragma once

#include "webo/modeling/datatype/tNull.h"
#include <memory>
#include <map>

namespace webo {

    namespace modeling {

        class Type;
        class Object;


        class MODELING_API Invoker {
        public:
            virtual std::shared_ptr<Object> invoke(std::map<std::string, std::shared_ptr<Object>> & arguments) {
                return datatype::tNull::value();
            }

            virtual std::shared_ptr<Object> invoke(std::vector<std::shared_ptr<Object>> & arguments) {
                return datatype::tNull::value();
            }

            virtual ~Invoker() {}
        };

    }

}

