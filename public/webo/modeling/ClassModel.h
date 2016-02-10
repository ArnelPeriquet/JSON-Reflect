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

#include <map>

#include "webo/modeling/Type.h"


namespace webo {

	namespace modeling {

		class Class;

		class MODELING_API ClassModel {           
		public:
            virtual ~ClassModel();
			virtual Class & createClass(std::string name, std::string nameSpace = Type::DEFAULT_NAME_SPACE);
			virtual bool hasClass(std::string name, std::string nameSpace = Type::DEFAULT_NAME_SPACE);
			virtual Class & getClass(std::string name, std::string nameSpace = Type::DEFAULT_NAME_SPACE);

		private:
			std::map<std::string, Class *> mClasses;
		};

	}

}
