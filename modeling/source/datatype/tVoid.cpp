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
#include "webo/modeling/datatype/tVoid.h"
#include "webo/modeling/Object.h"

using namespace webo::modeling;


namespace webo {

    namespace modeling {

        namespace datatype {

            tVoid & tVoid::instance() {
                static tVoid instance_;
                return instance_;
            }

            tVoid::tVoid()
                : DataType("tVoid") {
            }

        }

    }

}
