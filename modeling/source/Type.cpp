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
#include "webo/modeling/Type.h"

namespace webo {

    namespace modeling {

        const std::string Type::DEFAULT_NAME_SPACE = "default";

        std::string Type::getFullyQualifiedName(std::string name, const std::string nameSpace) {
            return nameSpace + "." + name;
        }

        Type::Type(std::string name, std::string nameSpace)
            : name(name), nameSpace(nameSpace) {
        }

        Type::Type(const Type & type) : name(type.name), nameSpace(type.nameSpace) {
        }

        Type::~Type() {
        }

        bool Type::operator ==(const Type & type) {
            return equals(type);
        }

        bool Type::operator !=(const Type & type) {
            return !equals(type);
        }

        bool Type::equals(const Type & type) {
            return getFullyQualifiedName(name, nameSpace) == getFullyQualifiedName(type.name, type.nameSpace);
        }

        bool Type::isBuiltIn() {
            return false;
        }

        bool Type::isSimpleArray() {
            return false;
        }

        bool Type::isObjectArray() {
            return false;
        }

        std::string Type::getFullyQualifiedName() const {
            return getFullyQualifiedName(name, nameSpace);
        }

    }

}
