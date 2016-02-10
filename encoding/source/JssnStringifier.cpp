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
#include "JssnStringifier.h"
#include "webo/modeling/Type.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/ClassModel.h"

using namespace webo::modeling;


namespace webo {

    namespace encoding {

        JssnStringifier::JssnStringifier(ClassModel & classModel)
            : mClassModel(classModel), mIndentation(0) {
        }

        void JssnStringifier::indent(std::stringstream & ss) const {
            for (int i = 0; i < mIndentation * 3; i++)
                ss << " ";
        }

        std::string JssnStringifier::stringify(Class & clazz) {
            std::stringstream ss;

            ss << "{\n";
            mIndentation++;
            indent(ss);

            stringifyClass(ss, clazz);

            mIndentation--;
            indent(ss);
            ss << "\n}";

            return ss.str();
        }

        void JssnStringifier::stringifyClass(std::stringstream & ss, modeling::Class & clazz) {
            std::vector<std::string> & attribNames = clazz.getAttributeNames();

            ss << "\"" << ((clazz.nameSpace == Type::DEFAULT_NAME_SPACE) ? "" : clazz.nameSpace + ".") << clazz.name << "\" : {\n";
            mIndentation++;

            for (std::vector<std::string>::iterator attribName = attribNames.begin(); attribName != attribNames.end(); ++attribName) {
                indent(ss);

                ss << "\"" << *attribName << "\" : \"" << clazz.getAttributeType(*attribName).name << "\"" << "\n";

                if (attribName + 1 != attribNames.end())
                    ss << ",\n";
            }

            ss << "\n";

            mIndentation--;
            indent(ss);
            ss << "}";
        }

    }

}
