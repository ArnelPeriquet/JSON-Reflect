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
		class Type;
		class ClassModel;

	}

	namespace encoding {

		// JavaScript Schema Notation (Jazzin')
		class JssnParser {
		public:
			JssnParser(webo::modeling::ClassModel & classModel);
			void parse(std::string & jssnString);
            void parse(std::stringstream & jssnStream);

		private:
			void parseClass(std::string className, boost::property_tree::ptree & propTree);
			webo::modeling::Type & CreateType(std::string typeName);

			webo::modeling::ClassModel & mClassModel;
		};

	}

}
