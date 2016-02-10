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

namespace webo {

	namespace modeling {

		class MODELING_API Type {
		public:
            static const std::string DEFAULT_NAME_SPACE;
			static std::string getFullyQualifiedName(std::string name, const std::string nameSpace);

			Type(std::string name, std::string nameSpace = DEFAULT_NAME_SPACE);
            Type(const Type & type);
            virtual ~Type();

			bool operator ==(const Type & type);
			bool operator !=(const Type & type);

			virtual bool equals(const Type & type);
			virtual bool isBuiltIn();
			virtual bool isArray();
			virtual bool isObjectArray();

			std::string getFullyQualifiedName() const;

			std::string name;
			std::string nameSpace; // name space can change at run-time
		};

	}

}



