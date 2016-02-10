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
#include "boost/test/unit_test.hpp"
#include "webo/modeling/Class.h"
#include "webo/modeling/ClassModel.h"
#include "webo/encoding/JSON.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;
using namespace webo::encoding;


namespace {
    std::string testSchema = 
        "{" 
        "	Query : {"
        "       val             : tInteger      "   // bug: JsonStr inserts an empty "" into an object resulting in invalid JSON
        "	},"
        "	Request : {"
        "		char_val        : tCharacter,   "
        "		str_val         : tString,      "
        "		int_val         : tInteger,     "
        "		bool_val        : tBoolean,     "
        "		null_val        : tNull,        "
        "       obj_val         : Query         "
            "}"
        "}";

    std::string OEWPLan_Schema =
        "{"
        "   CockpitCrew : {"
        "       #included       : tString,      "
        "       #code           : tString,      "
        "       @adultCount     : tInteger,     "
        "       @maleCount      : tInteger,     "
        "       @femaleCount    : tInteger      "
        "   },                                  "
        "   OEWPlan : {"
        "       node1           : CockpitCrew   "
        "   }"
        "}";


}

BOOST_AUTO_TEST_CASE( jssn_parse_class_list_as_string )
{  
	ClassModel cm;
    JSON json(cm);
    json.parseSchema(JsonStr(testSchema));
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_list_as_stream ) {
    ClassModel cm;
    JSON json(cm);

    json.parseSchema(std::stringstream(JsonStr(testSchema)()));
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_character )
{
    ClassModel cm;
    JSON json(cm);
    json.parseSchema(JsonStr(testSchema));
    Class & request = cm.getClass("Request");

    BOOST_CHECK(request.getAttributeType("char_val") == tCharacter::instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_string )
{
    ClassModel cm;
    JSON json(cm);
    json.parseSchema(JsonStr(testSchema));
    Class & request = cm.getClass("Request");

    BOOST_CHECK(request.getAttributeType("str_val") == tString::instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_integer )
{
    ClassModel cm;
    JSON json(cm);
    json.parseSchema(JsonStr(testSchema));
    Class & request = cm.getClass("Request");

    BOOST_CHECK(request.getAttributeType("int_val") == tInteger::instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_boolean )
{
    ClassModel cm;
    JSON json(cm);
    json.parseSchema(JsonStr(testSchema));
    Class & request = cm.getClass("Request");

    BOOST_CHECK(request.getAttributeType("bool_val") == tBoolean::instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_null )
{
    ClassModel cm;
    JSON json(cm);
    json.parseSchema(JsonStr(testSchema));
    Class & request = cm.getClass("Request");

    BOOST_CHECK(request.getAttributeType("null_val") == tNull::instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_object )
{
    ClassModel cm;
    JSON json(cm);
    json.parseSchema(JsonStr(testSchema));
    Class & request = cm.getClass("Request");
    Class & query = cm.getClass("Query");

    BOOST_CHECK(request.getAttributeType("obj_val") == query);
}

