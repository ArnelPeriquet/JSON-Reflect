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

#include <string>

namespace webo {

    namespace modeling {

        class Type;
        class Class;
        class Object;
        class ClassModel;

    }

    namespace encoding {

        class JssnStringifier {
        public:
            JssnStringifier(modeling::ClassModel & classModel);
            std::string stringify(modeling::Class & clazz);

        private:
            void indent(std::stringstream & ss) const;
            void stringifyClass(std::stringstream & ss, modeling::Class & clazz);

            modeling::ClassModel & mClassModel;
            int mIndentation;
        };

    }

}
