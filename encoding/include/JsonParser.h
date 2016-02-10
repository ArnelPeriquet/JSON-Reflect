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

#include <boost/property_tree/ptree.hpp>


namespace webo {

	namespace modeling {

		class Class;
		class Object;
		class Type;
		class ClassModel;

	}

	namespace encoding {

		class JsonParser {
		public:
			JsonParser(webo::modeling::ClassModel & classModel);

			std::shared_ptr<webo::modeling::Object> parse(std::string & jsonString, webo::modeling::Class & clazz, bool allowMissingAttributes = true);
            std::shared_ptr<webo::modeling::Object> parse(std::stringstream & jsonStream, webo::modeling::Class & clazz, bool allowMissingAttributes = true);

		private:
			std::shared_ptr<webo::modeling::Object> createObject(webo::modeling::Class & clazz, boost::property_tree::ptree & propTree, bool allowMissingAttributes);
			void createAttributes(webo::modeling::Class & clazz, std::shared_ptr<webo::modeling::Object> object, boost::property_tree::ptree & propTree, bool allowMissingAttributes);
			std::shared_ptr<webo::modeling::Object> createArray(std::string name, webo::modeling::Type & type, boost::property_tree::ptree & propTree);
			std::shared_ptr<webo::modeling::Object> createObjectArray(std::string name, webo::modeling::Type & type, boost::property_tree::ptree & propTree, bool allowMissingAttributes);
			std::shared_ptr<webo::modeling::Object> createPrimitive(std::string name, webo::modeling::Type & type, boost::property_tree::ptree & propTree);

			webo::modeling::ClassModel & mClassModel;
		};

	}

}
