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
#include "webo/modeling/Object.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;
using namespace webo::encoding;


#define MAKE_CLASS_AND_OBJECT(type) \
ClassModel cm; \
Class & c = cm.createClass("MyClass").addAttribute("myValue", ##type::instance()); \
Object o(c); \
JSON json(cm);


BOOST_AUTO_TEST_CASE( json_stringify_char ) {
    MAKE_CLASS_AND_OBJECT(tCharacter);
    o.set("myValue", tCharacter::value('a'));
    //std::cout << json.stringify(o, myClass) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      \"a\"\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_int ) {
    MAKE_CLASS_AND_OBJECT(tInteger);
    o.set("myValue", tInteger::value(1));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      1\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE(json_stringify_float) {
    MAKE_CLASS_AND_OBJECT(tFloat);
    o.set("myValue", tFloat::value(3.14));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      3.14\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_string ) {
    MAKE_CLASS_AND_OBJECT(tString);
    o.set("myValue", tString::value("test"));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      \"test\"\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_bool ) {
    MAKE_CLASS_AND_OBJECT(tBoolean);
    o.set("myValue", tBoolean::value(true));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      true\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_null ) {
    MAKE_CLASS_AND_OBJECT(tNull);
    o.set("myValue", tNull::value());
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      null\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_chars ) {
    MAKE_CLASS_AND_OBJECT(tArray<tCharacter>);
    char arr[] = { 'a', 'b', 'c' };
    o.set("myValue", tArray<tCharacter>::value(arr, 3));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      [\n         \"a\",\n         \"b\",\n         \"c\"\n      ]\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_ints ) {
    MAKE_CLASS_AND_OBJECT(tArray<tInteger>);
    int arr[] = { 1, 2, 3 };
    o.set("myValue", tArray<tInteger>::value(arr, 3));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      [\n         1,\n         2,\n         3\n      ]\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_floats) {
    MAKE_CLASS_AND_OBJECT(tArray<tFloat>);
    double arr[] = { 1.1, 2.2, 3.3 };
    o.set("myValue", tArray<tFloat>::value(arr, 3));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      [\n         1.1,\n         2.2,\n         3.3\n      ]\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_strings ) {
    MAKE_CLASS_AND_OBJECT(tArray<tString>);
    std::string arr[] = { "a", "b", "c" };
    o.set("myValue", tArray<tString>::value(arr, 3));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      [\n         \"a\",\n         \"b\",\n         \"c\"\n      ]\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_bools ) {
    MAKE_CLASS_AND_OBJECT(tArray<tBoolean>);
    bool arr[] = { true, false, true };
    o.set("myValue", tArray<tBoolean>::value(arr, 3));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      [\n         true,\n         false,\n         true\n      ]\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_nulls) {
    MAKE_CLASS_AND_OBJECT(tArray<tNull>);
    o.set("myValue", tArray<tNull>::value(3));
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"myValue\" :\n      [\n         null,\n         null,\n         null\n      ]\n}", json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE(json_stringify_array_of_array_of_bools) {
    MAKE_CLASS_AND_OBJECT(tArray<tArray<tBoolean>>);

    bool booleans[] = { true, false, true };
    std::shared_ptr<Object> arr1 = tArray<tBoolean>::value(booleans, 3);
    std::shared_ptr<Object> arr2 = tArray<tBoolean>::value(booleans, 3);
    std::shared_ptr<Object> arr3 = tArray<tBoolean>::value(booleans, 3);

    std::shared_ptr<Object> arr = tArray<tArray<tBoolean>>::value(3);
    arr->asArray()[0] = arr1;
    arr->asArray()[1] = arr2;
    arr->asArray()[2] = arr3;

    o.set("myValue", arr);
    //std::cout << json.stringify(o, c) << std::endl;
}

BOOST_AUTO_TEST_CASE(json_stringify_embedded_object_with_array_of_bools) {
    ClassModel cm;
    Class & embeddedClass = cm.createClass("EmbeddedClass").addAttribute("myValue", tArray<tBoolean>::instance());
    Class & c = cm.createClass("MyClass").addAttribute("embedded", embeddedClass);

    Object o(c);
    std::shared_ptr<Object> embedded = o.get("embedded");
    bool arr[] = { true, false, true };
    embedded->set("myValue", tArray<tBoolean>::value(arr, 3));

    JSON json(cm);
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"embedded\" :\n      {\n         \"myValue\" :\n            [\n               true,\n               false,\n               true\n            ]\n      }\n}",
        json.stringify(o, c));
}

BOOST_AUTO_TEST_CASE(json_stringify_embedded_object_with_array_of_objects) {
    ClassModel cm;
    Class & elementClass = cm.createClass("ElementClass").addAttribute("myValue", tInteger::instance());
    Class & embeddedClass = cm.createClass("EmbeddedClass").addAttribute("myArray", tObjectArray::instance(elementClass));
    Class & c = cm.createClass("MyClass").addAttribute("embedded", embeddedClass);

    Object o(c); 
    std::shared_ptr<Object> embedded = o.get("embedded");
    std::shared_ptr<Object> arr = embedded->set("myArray", tObjectArray::value(elementClass, 3));

    std::shared_ptr<Object> * nativeArr = arr->asObjectArray();
    nativeArr[0]->set("myValue", tInteger::value(1));
    nativeArr[1]->set("myValue", tInteger::value(2));
    nativeArr[2]->set("myValue", tInteger::value(3));

    JSON json(cm);
    //std::cout << json.stringify(o, c) << std::endl;
    BOOST_CHECK_EQUAL("{\n   \"embedded\" :\n      {\n         \"myArray\" :\n            [\n"
        "               {\n                  \"myValue\" :\n                     1\n               },\n"
        "               {\n                  \"myValue\" :\n                     2\n               },\n"
        "               {\n                  \"myValue\" :\n                     3\n               }\n" 
        "            ]\n      }\n}",
        json.stringify(o, c));
}

