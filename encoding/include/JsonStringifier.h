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

		class Class;
		class Object;
		class Type;
		class ClassModel;

	}

	namespace encoding {

		class JsonStringifier {
		public:
			JsonStringifier(modeling::ClassModel & classModel);
            std::string stringify(modeling::Object & object, modeling::Type & type, bool allowMissingAttributes = true);

		private:
			void indent(std::stringstream & ss) const;
			void stringifyObject(std::stringstream & ss, modeling::Object & object, modeling::Class & clazz, bool allowMissingAttributes);
			void stringifyArray(std::stringstream & ss, modeling::Object & object, modeling::Type & type);
			void stringifyObjectArray(std::stringstream & ss, modeling::Object & object, modeling::Type & type, bool allowMissingAttributes);
			void stringifyPrimitive(std::stringstream & ss, modeling::Object & object, modeling::Type & type);

			modeling::ClassModel & mClassModel;
			int mIndentation;
		};

	}

}
