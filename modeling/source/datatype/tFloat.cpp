/*
* (C) Copyright 2015  Arnel I Periquet.
*
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v1.0
* which accompanies this distribution, and is available at
* http://www.eclipse.org/legal/epl-v10.html
*
*/

#include <stdafx.h>
#include "webo/modeling/datatype/tFloat.h"
#include "webo/modeling/Object.h"

using namespace webo::modeling;


namespace webo {

    namespace modeling {

        namespace datatype {

            tFloat & tFloat::instance() {
                static tFloat instance_;
                return instance_;
            }

            tFloat::tFloat()
                : DataType("tFloat") {
            }

            std::shared_ptr<Object> tFloat::value(double value) {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance());
                object->asFloat(value);
                return object;
            }

        }

    }

}

