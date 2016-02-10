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
#include <vector>

namespace webo {

	namespace modeling {

		class Type;
		class Class;
		class Object;
		class ClassModel;

	}

	namespace encoding_xml {

		class XmlStringifier {
		public:
			XmlStringifier(webo::modeling::ClassModel & classModel);
			std::string stringify(webo::modeling::Object & object, webo::modeling::Class & clazz, bool allowMissingAttributes = true);

		private:			
			static bool isAttribute(std::string & attribName);
			static bool isDirectNode(std::string & attribName);
            static void stringifyText(std::stringstream & ss, webo::modeling::Object & object, webo::modeling::Type & type);

            void indent(std::stringstream & ss) const;
			void stringifyObject(std::stringstream & ss, webo::modeling::Object & object, webo::modeling::Class & clazz, bool allowMissingAttributes);
			void stringifyAttributes(std::stringstream & ss, webo::modeling::Object & object, webo::modeling::Class & clazz, bool allowMissingAttributes);
			void stringifyNodes(std::stringstream & ss, webo::modeling::Object & object, webo::modeling::Class & clazz, bool allowMissingAttributes);
			void extractNodes(std::vector<std::string> & oNodeNames, webo::modeling::Object & object, webo::modeling::Class & clazz, bool allowMissingAttributes);
			void stringifyDirectNodeOrFreeText(std::stringstream & ss, std::string & name, webo::modeling::Object & value);
			void stringifyNestedNode(std::stringstream & ss, webo::modeling::Object & value, bool allowMissingAttributes);
			
			webo::modeling::ClassModel & mClassModel;
			int mIndentation;
		};

	}

}
