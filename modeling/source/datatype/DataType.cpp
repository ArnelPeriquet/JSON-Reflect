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
#include "webo/modeling/datatype/DataType.h"

using namespace webo::modeling;


namespace webo {

    namespace modeling {

        namespace datatype {

            DataType::DataType(std::string name, std::string  nameSpace)
                : Type(name, nameSpace) {
            }

            bool DataType::isBuiltIn() {
                return true;
            }

        }

    }

}
