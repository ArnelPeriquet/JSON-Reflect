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

#include "webo/encoding/JsonStr.h" // by convenience so user does not have to include this seperately

namespace webo {

	namespace modeling {

        class Type;
		class Class;
		class Object;
		class ClassModel;

	}

	namespace encoding {

		class JsonStr;


		//
		// This class is a facade and is the only thing exported from this library.
		//
		// - This library requires modeling.dll which itself has no library dependencies at all (for usage, nor for building).
		// - No external 3rd party libraries are needed to use this library. (However, you'll need boost ptree header, to build the source code.)
		//
		//
		class ENCODING_API JSON {
		public:
			JSON(webo::modeling::ClassModel & classModel);

			void parseSchema(JsonStr & adapter);
			void parseSchema(std::string & jssnString); // JSSN (Jazzin') JavaScript Schema Notation
            void parseSchema(std::stringstream & jssnStream); // JSSN (Jazzin') JavaScript Schema Notation
			std::string stringifySchema(modeling::Class & clazz);

			std::shared_ptr<modeling::Object> parse(std::string & jsonString, modeling::Class & clazz, bool allowMissingAttributes = true);
            std::shared_ptr<modeling::Object> parse(std::stringstream & jsonStream, modeling::Class & clazz, bool allowMissingAttributes = true);
			std::string stringify(modeling::Object & object, modeling::Type & type, bool allowMissingAttributes = true);

		private:
			modeling::ClassModel & mClassModel;
		};

	}

}
