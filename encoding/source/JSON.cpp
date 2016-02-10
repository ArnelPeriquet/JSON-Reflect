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
#include "webo/encoding/JSON.h"
#include "webo/modeling/Type.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/ClassModel.h"
#include "JsonParser.h"
#include "JsonStringifier.h"
#include "JssnParser.h"
#include "webo/encoding/JsonStr.h"
#include "JssnStringifier.h"

using namespace webo::modeling;


namespace webo {

	namespace encoding {

		JSON::JSON(ClassModel & classModel)
			: mClassModel(classModel) {
		}

		void JSON::parseSchema(JsonStr & adapter) {
			parseSchema(adapter());
		}

		void JSON::parseSchema(std::string & jssnString) {
			JssnParser parser(mClassModel);
			return parser.parse(jssnString);
		}

        void JSON::parseSchema(std::stringstream & iJssnStream) {
            JssnParser parser(mClassModel);
            return parser.parse(iJssnStream);
		}

        std::string JSON::stringifySchema(modeling::Class & clazz) {
            JssnStringifier stringifier(mClassModel);
            return stringifier.stringify(clazz);
        }

		std::shared_ptr<Object> JSON::parse(std::string & jsonString, Class & iClass, bool allowMissingAttributes) {
			JsonParser parser(mClassModel);
			return parser.parse(jsonString, iClass, allowMissingAttributes);
		}

        std::shared_ptr<Object> JSON::parse(std::stringstream & jsonStream, Class & iClass, bool allowMissingAttributes) {
            JsonParser parser(mClassModel);
            return parser.parse(jsonStream, iClass, allowMissingAttributes);
        }

		std::string JSON::stringify(Object& object, Type & type, bool allowMissingAttributes) {
			JsonStringifier stringifier(mClassModel);
			return stringifier.stringify(object, type, allowMissingAttributes);
		}

	}

}
