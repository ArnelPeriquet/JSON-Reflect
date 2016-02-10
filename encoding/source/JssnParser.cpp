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
#include "JssnParser.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/Type.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;

namespace webo {

	namespace encoding {

		JssnParser::JssnParser(ClassModel & classModel)
			: mClassModel(classModel) {
		}

		void JssnParser::parse(std::string & jssnString) {
			try {
                std::stringstream jssnStream(jssnString);
                parse(jssnStream);
			}
			catch (std::exception & ex) {
				throw std::runtime_error(std::string(ex.what()) + ", jssn=" + jssnString);
			}
		}

        void JssnParser::parse(std::stringstream & jssnStream) {
            try {
                ptree propTree;
                read_json(jssnStream, propTree);

                BOOST_FOREACH(ptree::value_type & child, propTree) {
                    parseClass(child.first, child.second);
                }
            }
            catch (std::exception & ex) {
                throw std::runtime_error(std::string(ex.what()));
            }
		}

		void JssnParser::parseClass(std::string className, boost::property_tree::ptree & propTree) {
			Class & c = mClassModel.createClass(className);

			BOOST_FOREACH(ptree::value_type & child, propTree) {
				Type & type = CreateType(propTree.get<std::string>(child.first));
				c.addAttribute(child.first, type);
			}
		}

		Type & JssnParser::CreateType(std::string typeName) {
			if (typeName == tCharacter::instance().name)
				return tCharacter::instance();

			if (typeName == tInteger::instance().name)
				return tInteger::instance();

            if (typeName == tFloat::instance().name)
                return tFloat::instance();

			if (typeName == tString::instance().name)
				return tString::instance();

			if (typeName == tBoolean::instance().name)
				return tBoolean::instance();

			if (typeName == tNull::instance().name)
				return tNull::instance();

			if (typeName == tArray<tCharacter>::instance().name)
				return tArray<tCharacter>::instance();

			if (typeName == tArray<tInteger>::instance().name)
				return tArray<tInteger>::instance();

            if (typeName == tArray<tFloat>::instance().name)
                return tArray<tFloat>::instance();

			if (typeName == tArray<tString>::instance().name)
				return tArray<tString>::instance();

			if (typeName == tArray<tBoolean>::instance().name)
				return tArray<tBoolean>::instance();

			if (typeName == tArray<tNull>::instance().name)
				return tArray<tNull>::instance();

			if (typeName.find("tObjectArray") != std::string::npos) {
				int vEndindex = typeName.find(">");
				std::string baseClassName = typeName.substr(13, vEndindex - 13);
				Class & baseClass = mClassModel.getClass(baseClassName);
				return tObjectArray::instance(baseClass);
			}

			return mClassModel.getClass(typeName);
		}

	}

}
