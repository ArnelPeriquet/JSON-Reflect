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
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/ModelExceptions.h"

using namespace webo::modeling::datatype;


namespace webo {

	namespace modeling {

        ClassModel::ClassModel(std::function<Class *(std::string name, std::string nameSpace)> factory) {
            mFactory = factory;
        }

        ClassModel::~ClassModel() {
            for (std::map<std::string, Class *>::iterator it = mClasses.begin(); it != mClasses.end(); ++it)
                delete it->second;         
        }

		// stored by fully qualified name rather than by ID to ensure types have unique names
		Class & ClassModel::createClass(std::string name, std::string nameSpace) {
            std::string realName = name;
            std::string realNameSpace = nameSpace;
            size_t index = name.find_last_of(".");

            // allow name to contain the namespace            
            if (index != std::string::npos) {
                realName = name.substr(index + 1);
                realNameSpace = name.substr(0, index);
            }

            Class * type = mFactory(realName, realNameSpace);

			std::string fullyQualifiedName = type->getFullyQualifiedName();

            if (mClasses.find(fullyQualifiedName) != mClasses.end()) {
                delete type;
                throw NameCollisionException("attempt to create a class whose name already exists, type=" + fullyQualifiedName);
            }

			mClasses[fullyQualifiedName] = type;

			return *mClasses[fullyQualifiedName];
		}

		bool ClassModel::hasClass(std::string name, std::string nameSpace) {
            std::string fullyQualifiedName;

            // allow name to contain the namespace  
            if (name.find(".") != std::string::npos)
                fullyQualifiedName = name;
            else
                fullyQualifiedName = Class::getFullyQualifiedName(name, nameSpace);

			return mClasses.find(fullyQualifiedName) != mClasses.end();
		}

		Class & ClassModel::getClass(std::string name, std::string nameSpace) {
            std::string fullyQualifiedName;

            // allow name to contain the namespace  
            if (name.find(".") != std::string::npos)
                fullyQualifiedName = name;
            else
                fullyQualifiedName = Class::getFullyQualifiedName(name, nameSpace);

			if (mClasses.find(fullyQualifiedName) == mClasses.end())
				throw ClassNotFoundException("class does not exist, name=" + fullyQualifiedName);

			return *mClasses[fullyQualifiedName];
		}

	}

}
