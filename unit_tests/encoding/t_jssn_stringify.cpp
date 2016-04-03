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
#include <boost/test/unit_test.hpp>
#include "webo/encoding/JSON.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;
using namespace webo::encoding;


#define CHECK_CLASS(type) \
ClassModel cm; \
Class & myClass = cm.createClass("MyClass").addAttribute("myValue", ##type::instance()); \
JSON json(cm); \
std::string schema = json.stringifySchema(myClass); \
/*std::cout << schema << std::endl;*/ \
ClassModel cm2; \
JSON json2(cm2); \
BOOST_CHECK_NO_THROW(json2.parseSchema(schema)); \
Object o(cm2.getClass("MyClass"));


BOOST_AUTO_TEST_CASE(json_stringify_type_with_package)
{
    ClassModel cm;
    Class & myClass = cm.createClass("MyClass", "this.that.other");
    JSON json(cm);
    std::string schema = json.stringifySchema(myClass);
    //std::cout << schema << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"this.that.other.MyClass\" : {\n\n   }\n}", schema);
}

BOOST_AUTO_TEST_CASE(json_stringify_char_type) {
    CHECK_CLASS(tCharacter);
    BOOST_CHECK_NO_THROW(o.set("myValue", tCharacter::value('a')));
    BOOST_CHECK(o.get("myValue")->asCharacter() == 'a');
}

BOOST_AUTO_TEST_CASE(json_stringify_integer_type) {
    CHECK_CLASS(tInteger);
    BOOST_CHECK_NO_THROW(o.set("myValue", tInteger::value(5)));
    BOOST_CHECK(o.get("myValue")->asInteger() == 5);
}

BOOST_AUTO_TEST_CASE(json_stringify_float_type) {
    CHECK_CLASS(tFloat);
    BOOST_CHECK_NO_THROW(o.set("myValue", tFloat::value(3.14)));
    BOOST_CHECK(o.get("myValue")->asFloat () - 3.14 < 0.001);
}

BOOST_AUTO_TEST_CASE(json_stringify_string_type) {
    CHECK_CLASS(tString);
    BOOST_CHECK_NO_THROW(o.set("myValue", tString::value("test")));
    BOOST_CHECK(o.get("myValue")->asString() == "test");
}

BOOST_AUTO_TEST_CASE(json_stringify_bool_type) {
    CHECK_CLASS(tBoolean);
    BOOST_CHECK_NO_THROW(o.set("myValue", tBoolean::value(true)));
    BOOST_CHECK(o.get("myValue")->asBoolean() == true);
}

BOOST_AUTO_TEST_CASE(json_stringify_null_type) {
    CHECK_CLASS(tNull);
    BOOST_CHECK_NO_THROW(o.set("myValue", tNull::value()));
    BOOST_CHECK(o.get("myValue")->isNull());
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_chars_type) {
    CHECK_CLASS(tArray<tCharacter>);
    char arr[] = { 'a', 'b', 'c' };
    BOOST_CHECK_NO_THROW(o.set("myValue", tArray<tCharacter>::value(arr, 3)));
    BOOST_CHECK_EQUAL(o.get("myValue")->asArray()[0]->asCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_ints_type) {
    CHECK_CLASS(tArray<tInteger>);
    int arr[] = { 1, 2, 3 };
    BOOST_CHECK_NO_THROW(o.set("myValue", tArray<tInteger>::value(arr, 3)));
    BOOST_CHECK_EQUAL(o.get("myValue")->asArray()[0]->asInteger(), 1);
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_floats_type) {
    CHECK_CLASS(tArray<tFloat>);
    double arr[] = { 1.1, 2.2, 3.3 };
    BOOST_CHECK_NO_THROW(o.set("myValue", tArray<tFloat>::value(arr, 3)));
    BOOST_CHECK_EQUAL(o.get("myValue")->asArray()[0]->asFloat(), 1.1);
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_strings_type) {
    CHECK_CLASS(tArray<tString>);
    std::string arr[] = { "a", "b", "c" };
    BOOST_CHECK_NO_THROW(o.set("myValue", tArray<tString>::value(arr, 3)));
    BOOST_CHECK_EQUAL(o.get("myValue")->asArray()[0]->asString(), "a");
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_bools_type) {
    CHECK_CLASS(tArray<tBoolean>);
    bool arr[] = { true, false, true };
    BOOST_CHECK_NO_THROW(o.set("myValue", tArray<tBoolean>::value(arr, 3)));
    BOOST_CHECK_EQUAL(o.get("myValue")->asArray()[0]->asBoolean(), true);
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_nulls_type) {
    CHECK_CLASS(tArray<tNull>);
    BOOST_CHECK_NO_THROW(o.set("myValue", tArray<tNull>::value(3)));
    BOOST_CHECK(o.get("myValue")->asArray()[0]->isNull());
}

BOOST_AUTO_TEST_CASE(json_stringify_embedded_class_with_array_of_bools_type) {
    ClassModel cm;
    Class & embeddedClass = cm.createClass("EmbeddedClass").addAttribute("myValue", tArray<tBoolean>::instance());
    Class & c = cm.createClass("MyClass").addAttribute("embedded", embeddedClass);

    JSON json(cm);
    std::string schema1 = json.stringifySchema(embeddedClass);
    std::string schema2 = json.stringifySchema(c);
    //std::cout << schema1 << std::endl;
    //std::cout << schema2 << std::endl;

    ClassModel cm2;
    JSON json2(cm2);
    BOOST_CHECK_NO_THROW(json2.parseSchema(schema1));
    BOOST_CHECK_NO_THROW(json2.parseSchema(schema2));
}

BOOST_AUTO_TEST_CASE(json_stringify_embedded_class_with_array_of_objects_type) {
    ClassModel cm;
    Class & elementClass = cm.createClass("ElementClass").addAttribute("myValue", tInteger::instance());
    Class & embeddedClass = cm.createClass("EmbeddedClass").addAttribute("myArray", tObjectArray::instance(elementClass));
    Class & c = cm.createClass("MyClass").addAttribute("embedded", embeddedClass);

    JSON json(cm);
    std::string schema1 = json.stringifySchema(elementClass);
    std::string schema2 = json.stringifySchema(embeddedClass);
    std::string schema3 = json.stringifySchema(c);
    //std::cout << schema1 << std::endl;
    //std::cout << schema2 << std::endl;
    //std::cout << schema3 << std::endl;

    ClassModel cm2;
    JSON json2(cm2);
    BOOST_CHECK_NO_THROW(json2.parseSchema(schema1));
    BOOST_CHECK_NO_THROW(json2.parseSchema(schema2));
    BOOST_CHECK_NO_THROW(json2.parseSchema(schema3));
}
