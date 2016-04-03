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
#include "webo/modeling/Object.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;
using namespace webo::encoding;


BOOST_AUTO_TEST_CASE( json_parse_invalid_json_fails )
{    
    ClassModel cm;
    Class & myClass = cm.createClass("MyClass");
    
    JSON json(cm);
    BOOST_CHECK_THROW(json.parse(std::string("invalid json"), myClass), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( json_parse_ignores_unknown_attributes )
{
    std::string jsonWithUnknownAttributes(
        "{"
        "   \"unknown1\"       : \"111\","
        "   \"unknown2\"       : \"stuff\""
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass");

    JSON json(cm);
    BOOST_CHECK_NO_THROW(json.parse(jsonWithUnknownAttributes, myClass));
}

BOOST_AUTO_TEST_CASE( json_parse_character_attribute )
{
    std::string jsonWithCharacterAttribute(
        "{"
        "   \"myValue\"           : \"a\""
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", tCharacter::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithCharacterAttribute, myClass);
    BOOST_CHECK_EQUAL(myObject->get("myValue")->asCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE(json_parse_as_stream)
{
    std::string jsonWithCharacterAttribute(
        "{"
        "   \"myValue\"           : \"a\""
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", tCharacter::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(std::stringstream(jsonWithCharacterAttribute), myClass);
    BOOST_CHECK_EQUAL(myObject->get("myValue")->asCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE( json_parse_integer_attribute )
{
    std::string jsonWithIntegerAttribute(
        "{"
        "   \"myValue\"           : -99"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", tInteger::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithIntegerAttribute, myClass);
    BOOST_CHECK_EQUAL(myObject->get("myValue")->asInteger(), -99);
}

BOOST_AUTO_TEST_CASE(json_parse_float_attribute)
{
    std::string jsonWithFloatAttribute(
        "{"
        "   \"myValue\"           : 3.14"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", tFloat::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithFloatAttribute, myClass);
    //std::cout << myObject->get("myValue")->asFloat() << std::endl;
    BOOST_CHECK(myObject->get("myValue")->asFloat() - 3.14 < 0.001);
}

BOOST_AUTO_TEST_CASE( json_parse_string_attribute )
{
    std::string jsonWithStringAttribute(
        "{"
        "   \"myValue\"           : \"mystr\""
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", tString::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithStringAttribute, myClass);
    BOOST_CHECK_EQUAL(myObject->get("myValue")->asString(), "mystr");
}

BOOST_AUTO_TEST_CASE( json_parse_boolean_attribute )
{
    std::string jsonWithBooleanAttribute(
        "{"
        "   \"myValue\"           : false"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", tBoolean::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithBooleanAttribute, myClass);
    BOOST_CHECK_EQUAL(myObject->get("myValue")->asBoolean(), false);
}

BOOST_AUTO_TEST_CASE( json_parse_null_attribute )
{
    std::string jsonWithNullAttribute(
        "{"
        "   \"myValue\"       : null"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", tNull::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithNullAttribute, myClass);
    BOOST_CHECK(myObject->get("myValue")->equals(tNull::value()));
}

BOOST_AUTO_TEST_CASE( json_parse_multiple_primitive_attributes )
{
    std::string testJsonObject(
        "{"
        "   \"myInt\"        : -99,"
        "   \"myFloat\"      : 3.14,"
        "   \"myStr\"        : \"test\","
        "   \"myChar\"       : \"a\","
        "   \"myBool\"       : true,"
        "   \"myNull\"       : null"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass")
                                  .addAttribute("myInt", tInteger::instance())
                                  .addAttribute("myFloat", tFloat::instance())
                                  .addAttribute("myStr", tString::instance())
                                  .addAttribute("myChar", tCharacter::instance())
                                  .addAttribute("myBool", tBoolean::instance())
                                  .addAttribute("myNull", tNull::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(testJsonObject, myClass);
    BOOST_CHECK(myObject->get("myInt")->asInteger() == -99);
    BOOST_CHECK(myObject->get("myFloat")->asFloat() == 3.14);
    BOOST_CHECK(myObject->get("myStr")->asString() == "test");
    BOOST_CHECK(myObject->get("myChar")->asCharacter() == 'a');
    BOOST_CHECK(myObject->get("myBool")->asBoolean() == true);
    BOOST_CHECK(myObject->get("myNull")->equals(tNull::value()));
}

BOOST_AUTO_TEST_CASE( json_parse_object_attribute )
{
    std::string jsonWithObjectAttribute(
        "{"
        "   \"myValue\"       : \"MyClass2\""
        "}");

    ClassModel cm;
    Class & myClass2 = cm.createClass("MyClass2");
    Class & myClass = cm.createClass("MyClass").addAttribute("myValue", myClass2);

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithObjectAttribute, myClass);
    BOOST_CHECK(myObject->get("myValue")->type == myClass2);
}

BOOST_AUTO_TEST_CASE( json_parse_empty_array_attribute )
{
    std::string jsonWithEmptyArrayAttribute(
        "{"
        "   \"myArray\"       : []"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myArray", tArray<tInteger>::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithEmptyArrayAttribute, myClass);
    BOOST_CHECK(myObject->get("myArray")->type.equals(tArray<tInteger>::instance()));
}

BOOST_AUTO_TEST_CASE( json_parse_char_array_attribute )
{
    std::string jsonWithCharacterArrayAttribute(
        "{"
        "   \"myArray\"       : [\"d\",\"a\",\"z\"]"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myArray", tArray<tCharacter>::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithCharacterArrayAttribute, myClass);
    std::shared_ptr<Object> * arr = myObject->get("myArray")->asArray();
    BOOST_CHECK_EQUAL('d', arr[0]->asCharacter());
    BOOST_CHECK_EQUAL('a', arr[1]->asCharacter());
    BOOST_CHECK_EQUAL('z', arr[2]->asCharacter());    
}

BOOST_AUTO_TEST_CASE( json_parse_int_array_attribute )
{
    std::string jsonWithIntegerArrayAttribute(
        "{"
        "   \"myArray\"       : [7,1,9]"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myArray", tArray<tInteger>::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithIntegerArrayAttribute, myClass);
    std::shared_ptr<Object> * arr = myObject->get("myArray")->asArray();
    BOOST_CHECK_EQUAL(7, arr[0]->asInteger());
    BOOST_CHECK_EQUAL(1, arr[1]->asInteger());
    BOOST_CHECK_EQUAL(9, arr[2]->asInteger()); 
}

BOOST_AUTO_TEST_CASE(json_parse_float_array_attribute)
{
    std::string jsonWithFloatArrayAttribute(
        "{"
        "   \"myArray\"       : [1.1,2.2,3.3]"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myArray", tArray<tFloat>::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithFloatArrayAttribute, myClass);
    std::shared_ptr<Object> * arr = myObject->get("myArray")->asArray();
    BOOST_CHECK_EQUAL(1.1, arr[0]->asFloat());
    BOOST_CHECK_EQUAL(2.2, arr[1]->asFloat());
    BOOST_CHECK_EQUAL(3.3, arr[2]->asFloat());
}

BOOST_AUTO_TEST_CASE( json_parse_string_array_attribute )
{
    std::string jsonWithStringArrayAttribute(
        "{"
        "   \"myArray\"       : [\"this\",\"is\",\"cool\"]"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myArray", tArray<tString>::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithStringArrayAttribute, myClass);
    std::shared_ptr<Object> * array = myObject->get("myArray")->asArray();
    BOOST_CHECK_EQUAL("this", array[0]->asString());
    BOOST_CHECK_EQUAL("is", array[1]->asString());
    BOOST_CHECK_EQUAL("cool", array[2]->asString());
}

BOOST_AUTO_TEST_CASE( json_parse_boolean_array_attribute )
{
    std::string jsonWithBooleanArrayAttribute(
        "{"
        "   \"myArray\"       : [true,false,false]"
        "}");

    ClassModel cm;
    Class & myClass = cm.createClass("MyClass").addAttribute("myArray", tArray<tBoolean>::instance());

    JSON json(cm);
    std::shared_ptr<Object> myObject = json.parse(jsonWithBooleanArrayAttribute, myClass);
    std::shared_ptr<Object> * arr = myObject->get("myArray")->asArray();
    BOOST_CHECK_EQUAL(true, arr[0]->asBoolean());
    BOOST_CHECK_EQUAL(false, arr[1]->asBoolean());
    BOOST_CHECK_EQUAL(false, arr[2]->asBoolean());
}

BOOST_AUTO_TEST_CASE( json_parse_object_array_attribute )
{
    std::string testJsonObject(
        "{"
        "   \"myArray\"       : [{}, {}]"
        "}");

    ClassModel cm;
    Class & myClass2 = cm.createClass("MyClass2");
    Class & myClass = cm.createClass("MyClass").addAttribute("myArray", tObjectArray::instance(myClass2));

    JSON json(cm);

    std::shared_ptr<Object> object = json.parse(testJsonObject, myClass);
    std::shared_ptr<Object> attrib = object->get("myArray");

    BOOST_CHECK_EQUAL(attrib->getObjectArrayLength(), 2);
    BOOST_CHECK(tObjectArray::instance(myClass2) == attrib->type);
    BOOST_CHECK(myClass2 == attrib->asObjectArray()[0]->type);
    BOOST_CHECK(myClass2 == attrib->asObjectArray()[1]->type);
}

BOOST_AUTO_TEST_CASE( json_parse_object_with_embedded_object )
{
    std::string testJsonObject(
        "{"
        "   \"embeddedObject\": { \"myArray\" : [{}, {}] }"
        "}");

    ClassModel cm;
    Class & myClass3 = cm.createClass("MyClass3");
    Class & myClass2 = cm.createClass("MyClass2").addAttribute("myArray", tObjectArray::instance(myClass3));
    Class & myClass = cm.createClass("MyClass").addAttribute("embeddedObject", myClass2);
    
    JSON json(cm);    
    std::shared_ptr<Object> embeddedObject = json.parse(testJsonObject, myClass)->get("embeddedObject");
    std::shared_ptr<Object> attrib = embeddedObject->get("myArray");

    BOOST_CHECK(myClass3 == attrib->asObjectArray()[0]->type);
    BOOST_CHECK(myClass3 == attrib->asObjectArray()[1]->type);
}

BOOST_AUTO_TEST_CASE( json_parse_object_with_embedded_object_with_missing_attribute_fails )
{
    std::string testJsonObject(
        "{"
        "   \"embeddedObject\": {}"
        "}");

    ClassModel cm;
    Class & myClass3 = cm.createClass("MyClass3");
    Class & myClass2 = cm.createClass("MyClass2").addAttribute("myArray", tObjectArray::instance(myClass3));
    Class & myClass = cm.createClass("MyClass").addAttribute("embeddedObject", myClass2);

    JSON json(cm);    
    BOOST_CHECK_THROW(json.parse(testJsonObject, myClass, false), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(json_parse_object_with_default_values)
{
    ClassModel cm;
    Class & c1 = cm.createClass("MyClass");
    Class & c2 = cm.createClass("MyClass2");
    c2.addAttribute("attr1", tInteger::instance());
    c2.addAttribute("attr2", tString::instance());
    c1.addAttribute("attr1", c2);
    c1.addAttribute("attr2", tCharacter::instance());

    std::shared_ptr<Object> obj1 = std::make_shared<Object>(c1);
    std::shared_ptr<Object> obj2 = obj1->get("attr1"); // lazy instantiate a defaults for all attribs
    obj2->get("attr1");
    obj2->get("attr2");
    obj1->get("attr2");

    JSON json(cm);
    std::string result = json.stringify(*obj1, c1);
}

BOOST_AUTO_TEST_CASE(json_parse_object_decoding_equals_encoding)
{
    ClassModel cm;
    Class & c1 = cm.createClass("MyClass");
    Class & c2 = cm.createClass("MyClass2");
    c2.addAttribute("attr1", tInteger::instance());
    c2.addAttribute("attr2", tFloat::instance());
    c2.addAttribute("attr3", tString::instance());
    c1.addAttribute("attr1", c2);
    c1.addAttribute("attr2", tCharacter::instance());

    std::shared_ptr<Object> obj1 = std::make_shared<Object>(c1);
    std::shared_ptr<Object> obj2 = obj1->get("attr1"); // lazy instantiate a defaults for all attribs
    obj2->set("attr1", tInteger::value(5));
    obj2->set("attr2", tFloat ::value(3.14));
    obj2->set("attr3", tString::value("hello"));
    obj1->set("attr2", tCharacter::value('-'));

    JSON json(cm);
    std::string result1 = json.stringify(*obj1, c1);
    std::shared_ptr<Object> obj3 = json.parse(result1, c1);
    std::string result2 = json.stringify(*obj3, c1);
    BOOST_CHECK_EQUAL(result1, result2);

    BOOST_CHECK(obj3->type == c1);
    BOOST_CHECK(obj3->get("attr1")->type == c2);
    BOOST_CHECK(obj3->get("attr1")->get("attr1")->asInteger() == 5);
    BOOST_CHECK(obj3->get("attr1")->get("attr2")->asFloat() == 3.14);
    BOOST_CHECK(obj3->get("attr1")->get("attr3")->asString() == "hello");
    BOOST_CHECK(obj3->get("attr2")->asCharacter() == '-');
}