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
		class ClassModel;

	}

	namespace encoding_xml {

		//
		// This class is a facade and is the only thing exported from this library.
		//
		// - This library requires modeling.dll which itself has no library dependencies at all (for usage, nor for building).
		// - No external 3rd party libraries are needed to use this library. (However, you'll need boost ptree header, to build the source code.)
		//
		//
		class ENCODING_XML_API XML {
		public:
			XML(webo::modeling::ClassModel & classModel);

			/*
				void parseSchema(JsonStr iAdapter);
				void parseSchema(std::string iJssnString); // JSSN (Jazzin') JavaScript Schema Notation
				//std::string stringifySchema();

				std::shared_ptr<Object> parse(std::string iJsonString, Class & iClass, bool iAllowMissingAttributes = true);*/
			std::string stringify(webo::modeling::Object& object, webo::modeling::Class & clazz, bool allowMissingAttributes = true);

		private:
			webo::modeling::ClassModel & mClassModel;
		};

	}

}
