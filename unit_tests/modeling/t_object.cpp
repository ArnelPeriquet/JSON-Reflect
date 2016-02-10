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
#include "webo/modeling/Object.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/ModelExceptions.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;


BOOST_AUTO_TEST_CASE( create_void_object_fails )
{
    BOOST_CHECK_THROW(new Object(tVoid::instance()), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( object_set_as_string_fails )
{
    Object myObject(tInteger::instance());
    BOOST_CHECK_THROW(myObject.asString("a string value"), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_character_fails )
{
    Object myObject(tInteger::instance());
    BOOST_CHECK_THROW(myObject.asCharacter('b'), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_integer_fails )
{
    Object myObject(tString::instance());
    BOOST_CHECK_THROW(myObject.asInteger(-98), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE(object_set_as_float_fails)
{
    Object myObject(tString::instance());
    BOOST_CHECK_THROW(myObject.asFloat(3.14), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_boolean_fails )
{
    Object myObject(tString::instance());
    BOOST_CHECK_THROW(myObject.asBoolean(false), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_string_fails )
{
    Object myObject(tCharacter::instance());
    myObject.asCharacter('b');
    BOOST_CHECK_THROW(myObject.asString(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_character_fails )
{
    Object myObject(tString::instance());
    myObject.asString("a string value");
    BOOST_CHECK_THROW(myObject.asCharacter(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_integer_fails )
{
    Object myObject(tString::instance());
    myObject.asString("a string value");
    BOOST_CHECK_THROW(myObject.asInteger(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE(object_get_as_float_fails)
{
    Object myObject(tString::instance());
    myObject.asString("a string value");
    BOOST_CHECK_THROW(myObject.asFloat(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_boolean_fails )
{
    Object myObject(tString::instance());
    myObject.asString("a string value");
    BOOST_CHECK_THROW(myObject.asBoolean(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_string )
{
    Object myObject(tString::instance());
    BOOST_CHECK_EQUAL(myObject.asString("a string value"), "a string value");
}

BOOST_AUTO_TEST_CASE( object_set_as_character )
{
    Object myObject(tCharacter::instance());
    BOOST_CHECK_EQUAL(myObject.asCharacter('b'), 'b');
}

BOOST_AUTO_TEST_CASE( object_set_as_integer )
{
    Object myObject(tInteger::instance());
    BOOST_CHECK_EQUAL(myObject.asInteger(-98), -98);
}

BOOST_AUTO_TEST_CASE(object_set_as_float)
{
    Object myObject(tFloat::instance());
    BOOST_CHECK_EQUAL(myObject.asFloat(3.14), 3.14);
}

BOOST_AUTO_TEST_CASE( object_set_as_boolean )
{
    Object myObject(tBoolean::instance());
    BOOST_CHECK_EQUAL(myObject.asBoolean(false), false);
}

BOOST_AUTO_TEST_CASE( object_get_as_string )
{
    Object myObject(tString::instance());
    myObject.asString("a string value");
    BOOST_CHECK_EQUAL(myObject.asString(), "a string value");
}

BOOST_AUTO_TEST_CASE( object_get_as_character )
{
    Object myObject(tCharacter::instance());
    myObject.asCharacter('b');
    BOOST_CHECK_EQUAL(myObject.asCharacter(), 'b');
}

BOOST_AUTO_TEST_CASE( object_get_as_integer )
{
    Object myObject(tInteger::instance());
    myObject.asInteger(-98);
    BOOST_CHECK_EQUAL(myObject.asInteger(), -98);
}

BOOST_AUTO_TEST_CASE(object_get_as_float)
{
    Object myObject(tFloat::instance());
    myObject.asFloat(3.14);
    BOOST_CHECK_EQUAL(myObject.asFloat(), 3.14);
}

BOOST_AUTO_TEST_CASE( object_get_as_boolean )
{
    Object myObject(tBoolean::instance());
    myObject.asBoolean(false);
    BOOST_CHECK_EQUAL(myObject.asBoolean(), false);
}

BOOST_AUTO_TEST_CASE( object_set_attribute_value_on_primitive_type_fails )
{
    BOOST_CHECK_THROW(tString::value("15")->set("attr1", tInteger::value(15)), ObjectIsNotAClassException);
}

BOOST_AUTO_TEST_CASE( object_set_attribute_value_on_unknown_attribute_fails )
{
    Class myClass("MyClass");
    Object myObject(myClass);
    BOOST_CHECK_THROW(myObject.set("attr1", tInteger::value(15)), UnknownAttributeException);
}

BOOST_AUTO_TEST_CASE( object_set_attribute_value_with_mismatched_type_fails )
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tInteger::instance());
    Object myObject(myClass);

    BOOST_CHECK_THROW(myObject.set("attr1", tString::value("15")), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_any_attribute_value_including_primitives_to_null_succeeds )
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tInteger::instance());
    Object myObject(myClass);

    BOOST_CHECK_NO_THROW(myObject.set("attr1", tNull::value()));
}

BOOST_AUTO_TEST_CASE( object_get_attribute_value_from_primitive_type_fails )
{
    BOOST_CHECK_THROW(tString::value("test")->get("attr1"), ObjectIsNotAClassException);
}

BOOST_AUTO_TEST_CASE( object_get_attribute_value_for_unknown_attribute_fails )
{
    Class myClass("MyClass");
    Object myObject(myClass);
    BOOST_CHECK_THROW(myObject.get("attr1"), UnknownAttributeException);
}

BOOST_AUTO_TEST_CASE( object_string_is_compared_by_contents )
{
    BOOST_CHECK(*tString::value("test1") == *tString::value("test1"));
    BOOST_CHECK(*tString::value("test1") != *tString::value("test2"));
    BOOST_CHECK(tString::value("test1")->equals(tString::value("test1")));
    BOOST_CHECK(tString::value("test1")->asString() == "test1");
}

BOOST_AUTO_TEST_CASE( object_integer_is_compared_by_contents )
{
    BOOST_CHECK(tInteger::value(-99)->equals(tInteger::value(-99)));
}

BOOST_AUTO_TEST_CASE(object_float_is_compared_by_contents)
{
    BOOST_CHECK(tFloat::value(3.14)->equals(tFloat ::value(3.14)));
}

BOOST_AUTO_TEST_CASE( object_character_is_compared_by_contents )
{
    BOOST_CHECK(tCharacter::value('a')->equals(tCharacter::value('a')));
}

BOOST_AUTO_TEST_CASE( object_boolean_is_compared_by_contents )
{
    BOOST_CHECK(tBoolean::value(false)->equals(tBoolean::value(false)));
}

BOOST_AUTO_TEST_CASE( object_null_equals_null )
{
    BOOST_CHECK(tNull::value()->equals(tNull::value()));
}

BOOST_AUTO_TEST_CASE( object_attribute_value_of_any_type_can_be_null )
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tInteger::instance());
    Object myObject(myClass);

    myObject.set("attr1", tNull::value());

    BOOST_CHECK(myObject.get("attr1")->equals(tNull::value()));
    BOOST_CHECK(myObject.get("attr1")->isNull());
}

BOOST_AUTO_TEST_CASE( object_add_attribute_after_creating_objects )
{
    Class myClass("MyClass");
    Object myObject1(myClass);
    Object myObject2(myClass);

    myClass.addAttribute("attr1", tInteger::instance());

    myObject1.set("attr1", tInteger::value(1));
    myObject2.set("attr1", tInteger::value(2));

    BOOST_CHECK(myObject1.get("attr1")->equals(tInteger::value(1)));
    BOOST_CHECK(myObject2.get("attr1")->equals(tInteger::value(2)));
}

BOOST_AUTO_TEST_CASE( object_attribute_simplearray_is_not_default_initialized )
{
    Class c("MyClass");
    Object o(c);

    c.addAttribute("arr", tArray<tString>::instance());
    std::shared_ptr<Object> arr = o.get("arr");

    BOOST_CHECK(!o.hasValue("arr"));
}

BOOST_AUTO_TEST_CASE(object_attribute_objectarray_is_not_default_initialized)
{
    Class c("MyClass");
    Object o(c);

    Class c2("MyClass2");
    c.addAttribute("arr", tObjectArray::instance(c2));
    std::shared_ptr<Object> arr = o.get("arr");

    BOOST_CHECK(!o.hasValue("arr"));
}

BOOST_AUTO_TEST_CASE(object_attribute_starts_off_empty)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tInteger::instance());
    Object myObject(myClass);

    BOOST_CHECK(!myObject.hasValue("attr1"));
}

BOOST_AUTO_TEST_CASE(object_set_integer_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tInteger::instance());
    Object myObject(myClass);

    BOOST_CHECK_EQUAL(myObject.set("attr1", tInteger::value(15))->asInteger(), 15);
}

BOOST_AUTO_TEST_CASE(object_get_integer_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tInteger::instance());
    Object myObject(myClass);

    myObject.set("attr1", tInteger::value(15));

    BOOST_CHECK_EQUAL(myObject.get("attr1")->asInteger(), 15);
}

BOOST_AUTO_TEST_CASE(object_set_float_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tFloat::instance());
    Object myObject(myClass);

    BOOST_CHECK_EQUAL(myObject.set("attr1", tFloat::value(3.14))->asFloat(), 3.14);
}

BOOST_AUTO_TEST_CASE(object_get_float_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tFloat::instance());
    Object myObject(myClass);

    myObject.set("attr1", tFloat::value(3.14));

    BOOST_CHECK_EQUAL(myObject.get("attr1")->asFloat (), 3.14);
}

BOOST_AUTO_TEST_CASE(object_set_string_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tString::instance());
    Object myObject(myClass);

    BOOST_CHECK_EQUAL(myObject.set("attr1", tString::value("hi"))->asString(), "hi");
}

BOOST_AUTO_TEST_CASE(object_get_string_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tString::instance());
    Object myObject(myClass);

    myObject.set("attr1", tString::value("hi"));

    BOOST_CHECK_EQUAL(myObject.get("attr1")->asString(), "hi");
}

BOOST_AUTO_TEST_CASE(object_set_character_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tCharacter::instance());
    Object myObject(myClass);

    BOOST_CHECK_EQUAL(myObject.set("attr1", tCharacter::value('a'))->asCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE(object_get_character_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tCharacter::instance());
    Object myObject(myClass);

    myObject.set("attr1", tCharacter::value('a'));

    BOOST_CHECK_EQUAL(myObject.get("attr1")->asCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE(object_set_boolean_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tBoolean::instance());
    Object myObject(myClass);

    BOOST_CHECK_EQUAL(myObject.set("attr1", tBoolean::value(true))->asBoolean(), true);
}

BOOST_AUTO_TEST_CASE(object_get_boolean_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tBoolean::instance());
    Object myObject(myClass);

    myObject.set("attr1", tBoolean::value(true));

    BOOST_CHECK_EQUAL(myObject.get("attr1")->asBoolean(), true);
}

BOOST_AUTO_TEST_CASE(object_set_null_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tNull::instance());
    Object myObject(myClass);

    BOOST_CHECK(myObject.set("attr1", tNull::value())->isNull());
}

BOOST_AUTO_TEST_CASE(object_get_null_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tNull::instance());
    Object myObject(myClass);

    myObject.set("attr1", tNull::value());

    BOOST_CHECK(myObject.get("attr1")->isNull());
}

BOOST_AUTO_TEST_CASE(object_set_simplearray_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tArray<tBoolean>::instance());
    Object myObject(myClass);

    std::shared_ptr<Object> arr = myObject.set("attr1", tArray<tBoolean>::value(2));
    BOOST_CHECK_EQUAL(arr->asArray<tBoolean>()[0]->asBoolean(), false);
}

BOOST_AUTO_TEST_CASE(object_get_simplearray_attribute_value)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tArray<tBoolean>::instance());
    Object myObject(myClass);

    std::shared_ptr<Object> arr = myObject.set("attr1", tArray<tBoolean>::value(2));
    arr->asArray<tBoolean>()[0]->asBoolean(true);

    std::shared_ptr<Object> arr2 = myObject.get("attr1");
    BOOST_CHECK_EQUAL(arr2->asArray<tBoolean>()[0]->asBoolean(), true);
}

BOOST_AUTO_TEST_CASE(object_set_objectarray_attribute_value)
{
    Class myClass("MyClass");
    Class c("c");
    c.addAttribute("a", tInteger::instance());
    myClass.addAttribute("attr1", tObjectArray::instance(c));
    Object myObject(myClass);

    std::shared_ptr<Object> arr = myObject.set("attr1", tObjectArray::value(c, 1));
    BOOST_CHECK_EQUAL(arr->asObjectArray(c)[0]->get("a")->asInteger(), 0);
}

BOOST_AUTO_TEST_CASE(object_get_object_attribute_value)
{
    Class myClass("MyClass");
    Class c("c");
    c.addAttribute("a", tInteger::instance());
    myClass.addAttribute("attr1", tObjectArray::instance(c));
    Object myObject(myClass);

    std::shared_ptr<Object> arr = myObject.set("attr1", tObjectArray::value(c, 1));
    arr->asObjectArray(c)[0]->get("a")->asInteger(5);

    std::shared_ptr<Object> arr2 = myObject.get("attr1");
    BOOST_CHECK_EQUAL(arr2->asObjectArray(c)[0]->get("a")->asInteger(), 5);
}