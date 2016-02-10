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

#include "webo/modeling/Type.h"


namespace webo {

    namespace modeling {

        namespace datatype {

            class MODELING_API DataType : public Type {
            public:
                DataType(std::string name, std::string nameSpace = Type::DEFAULT_NAME_SPACE);
                virtual bool isBuiltIn();
            };

        }

    }

}
