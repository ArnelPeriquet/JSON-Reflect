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
#include "webo/encoding_xml/XML.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/ClassModel.h"
//#include "XmlParser.h"
#include "XmlStringifier.h"

using namespace webo::modeling;


namespace webo {

	namespace encoding_xml {

		XML::XML(ClassModel & classModel)
			: mClassModel(classModel) {
		}

		/*
		void JSON::parseSchema(JsonStr adapter) {
			ParseSchema(adapter());
		}

		void JSON::parseSchema(std::string jssnString) {
			JssnParser parser(mClassModel);
			return parser.parse(jssnString);
		}

		std::shared_ptr<Object> JSON::parse(std::string jsonString, Class & clazz, bool allowMissingAttributes) {
			JsonParser parser(mClassModel);
			return parser.parse(jsonString, clazz, allowMissingAttributes);
		}
		*/

		std::string XML::stringify(Object& object, Class & clazz, bool allowMissingAttributes) {
			XmlStringifier stringifier(mClassModel);
			return stringifier.stringify(object, clazz, allowMissingAttributes);
		}

	}

}
