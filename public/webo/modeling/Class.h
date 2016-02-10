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

#include <memory>
#include <map>
#include <vector>
#include "webo/modeling/Type.h"
#include "webo/modeling/Operation.h"

namespace webo {

	namespace modeling {

	    namespace datatype
        {
            class tObjectArray;
        }

		class MODELING_API Class : public Type {
            friend datatype::tObjectArray;

		public:
			Class(std::string name, std::string nameSpace = Type::DEFAULT_NAME_SPACE);

			virtual bool isBuiltIn();

			virtual void addSuperClass(Class & superClass);

			virtual std::vector<std::string> & getAttributeNames();
			virtual bool hasAttribute(std::string name);
			virtual Type & getAttributeType(std::string name);
			virtual Class & addAttribute(std::string name, Type & type);
            
            virtual void addOperation(Operation & operation);
            virtual std::vector<Operation *> lookup(std::string name);

		private:
			std::vector<Class *> mSupers;
			std::vector<std::string> mKeys;
			std::map<std::string, Type *> mAttributes;
            std::multimap<std::string, Operation *> mOperations;

            std::shared_ptr<datatype::tObjectArray> mObjectArrayType;
		};

	}

}

