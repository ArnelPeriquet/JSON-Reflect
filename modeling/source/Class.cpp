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
#include "webo/modeling/Class.h"
#include "webo/modeling/tObject.h"
#include <webo/modeling/datatype/tVoid.h>


namespace webo {

	namespace modeling {

		Class::Class(std::string name, std::string nameSpace)
			: Type(name, nameSpace) {
            if (name != "tObject") {
                mSupers.push_back(&tObject::instance());
                //AddSuperClass(tObject::instance());  this would be statically resolved
            }
		}

		bool Class::isBuiltIn() {
			return false;
		}

		void Class::addSuperClass(Class & superClass) {
			mSupers.push_back(&superClass);
		}

		std::vector<std::string> & Class::getAttributeNames() {
			return mKeys;
		}

		bool Class::hasAttribute(std::string name) {
			return mAttributes.find(name) != mAttributes.end();
		}

		Type & Class::getAttributeType(std::string name) {
			if (mAttributes.find(name) == mAttributes.end())
				throw std::invalid_argument("attempt to get attribute type for unknown attribute");

			return *mAttributes[name];
		}

		Class & Class::addAttribute(std::string name, Type & type) {
            if (type == datatype::tVoid::instance())
                throw std::invalid_argument("unable to add attribute of type tVoid");

			if (mAttributes.find(name) != mAttributes.end())
				throw std::invalid_argument("attempt to add attribute that already exists, name=" + name);

			mKeys.push_back(name);
			mAttributes[name] = &type;

			return *this;
		}

        void Class::addOperation(Operation & operation) {
            mOperations.insert(std::pair<std::string, Operation *>(operation.getSignature(), &operation));
        }

        std::vector<Operation *> Class::lookup(std::string name) {
            std::vector<Operation *> operations;

            for (std::pair<std::string, Operation *> entry : mOperations) {
                if (entry.second->name == name)
                    operations.push_back(entry.second);
            }

            return operations;
        }

	}

}
