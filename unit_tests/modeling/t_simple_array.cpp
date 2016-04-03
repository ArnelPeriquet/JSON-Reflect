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
#include "webo/modeling/Object.h"
#include "webo/modeling/tObject.h"
#include "webo/modeling/datatype/DataTypes.h"


using namespace webo::modeling;
using namespace webo::modeling::datatype;


BOOST_AUTO_TEST_CASE(tarray_array_of_ints_equals_array_of_ints)
{
    BOOST_CHECK(ARRAY_OF(tInteger).equals(ARRAY_OF(tInteger)));
}

BOOST_AUTO_TEST_CASE(tarray_array_of_strings_does_not_equals_array_of_ints)
{
    BOOST_CHECK(!ARRAY_OF(tString).equals(ARRAY_OF(tInteger)));
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(tarray_create_array_of_character_objects)
{
    char characters[] = { 'a', 'b', 'c' };
    std::shared_ptr<Object> arr = tArray<tCharacter>::value(characters, 3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asCharacter(), 'a');
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asCharacter(), 'b');
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asCharacter(), 'c');
}

BOOST_AUTO_TEST_CASE(tarray_create_array_of_integer_objects)
{
    int integers[] = { 1, 2, 3 };
    std::shared_ptr<Object> arr = tArray<tInteger>::value(integers, 3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asInteger(), 1);
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asInteger(), 2);
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asInteger(), 3);
}

BOOST_AUTO_TEST_CASE(tarray_create_array_of_float_objects)
{
    double floats[] = { 1.1, 2.2, 3.3 };
    std::shared_ptr<Object> arr = tArray<tFloat>::value(floats, 3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asFloat(), 1.1);
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asFloat(), 2.2);
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asFloat(), 3.3);
}

BOOST_AUTO_TEST_CASE(tarray_create_array_of_string_objects)
{
    std::string strings[] = { "test1", "test2", "test3" };
    std::shared_ptr<Object> arr = tArray<tString>::value(strings, 3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asString(), "test1");
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asString(), "test2");
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asString(), "test3");
}

BOOST_AUTO_TEST_CASE(tarray_create_array_of_boolean_objects)
{
    bool booleans[] = { true, false, true };
    std::shared_ptr<Object> arr = tArray<tBoolean>::value(booleans, 3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asBoolean(), true);
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asBoolean(), false);
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asBoolean(), true);
}

BOOST_AUTO_TEST_CASE(tarray_create_array_of_array_of_boolean_objects)
{
    bool booleans[] = { true, false, true };
    std::shared_ptr<Object> arr1 = tArray<tBoolean>::value(booleans, 3);
    std::shared_ptr<Object> arr2 = tArray<tBoolean>::value(booleans, 3);
    std::shared_ptr<Object> arr3 = tArray<tBoolean>::value(booleans, 3);

    std::shared_ptr<Object> arr = tArray<tArray<tBoolean>>::value(3);
    arr->asArray()[0] = arr1;
    arr->asArray()[1] = arr2;
    arr->asArray()[2] = arr3;

    BOOST_CHECK_EQUAL(arr->asArray()[0]->asArray()[0]->asBoolean(), true);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asArray()[1]->asBoolean(), false);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asArray()[2]->asBoolean(), true);
}

BOOST_AUTO_TEST_CASE(tarray_create_array_from_a_larger_array_literal)
{
    bool booleans[] = { true, false, true, true, true };
    std::shared_ptr<Object> arr = tArray<tBoolean>::value(booleans, 3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asBoolean(), true);
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asBoolean(), false);
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asBoolean(), true);
}

BOOST_AUTO_TEST_CASE(tarray_of_characters_has_default_value_zero)
{
    std::shared_ptr<Object> arr = tArray<tCharacter>::value(3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asCharacter(), 0);
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asCharacter(), 0);
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asCharacter(), 0);
}

BOOST_AUTO_TEST_CASE(tarray_of_integers_has_default_value_zero)
{
    std::shared_ptr<Object> arr = tArray<tInteger>::value(3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asInteger(), 0);
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asInteger(), 0);
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asInteger(), 0);
}

BOOST_AUTO_TEST_CASE(tarray_of_floats_has_default_value_zero_point_zero)
{
    std::shared_ptr<Object> arr = tArray<tFloat>::value(3);

    //std::cout << arr->asArray<tFloat>()[0]->asFloat() << std::endl;

    BOOST_CHECK(arr->asArray()[0]->asFloat() - 0.0 < 0.001);
    BOOST_CHECK(arr->asArray()[1]->asFloat() - 0.0 < 0.001);
    BOOST_CHECK(arr->asArray()[2]->asFloat() - 0.0 < 0.001);
}

BOOST_AUTO_TEST_CASE(tarray_of_strings_has_default_value_empty)
{
    std::shared_ptr<Object> arr = tArray<tString>::value(3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asString(), "");
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asString(), "");
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asString(), "");
}

BOOST_AUTO_TEST_CASE(tarray_of_booleans_has_default_value_false)
{
    std::shared_ptr<Object> arr = tArray<tBoolean>::value(3);
    BOOST_CHECK_EQUAL(arr->asArray()[0]->asBoolean(), false);
    BOOST_CHECK_EQUAL(arr->asArray()[1]->asBoolean(), false);
    BOOST_CHECK_EQUAL(arr->asArray()[2]->asBoolean(), false);
}

BOOST_AUTO_TEST_CASE(tarray_of_booleans_loop)
{
    std::shared_ptr<Object> arr = tArray<tBoolean>::value(3);
    std::shared_ptr<Object> * nativeArr = arr->asArray();

    for (size_t i = 0; i<arr->getArrayLength(); i++) {        
        BOOST_CHECK(nativeArr[i]->type == tBoolean::instance());
    }
}

BOOST_AUTO_TEST_CASE(tarray_has_tarray_type_name)
{
    Type & arrType = tArray<tString>::instance();
    BOOST_CHECK_EQUAL(arrType.name, "tArray<tString>");
}

BOOST_AUTO_TEST_CASE(tobject_supports_boolean_array_setter)
{
    Class myClass("MyClass");
    myClass.addAttribute("testBools", tArray<tBoolean>::instance());
    Object myObject(myClass);
    std::vector<bool> arr = { true, false, true };
    myObject.set("testBools", arr);

    BOOST_CHECK(myObject.get("testBools")->asArray()[0]->asBoolean() == true);
    BOOST_CHECK(myObject.get("testBools")->asArray()[1]->asBoolean() == false);
    BOOST_CHECK(myObject.get("testBools")->asArray()[2]->asBoolean() == true);
}