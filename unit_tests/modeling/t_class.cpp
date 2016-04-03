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
#include "webo/modeling/Class.h"
#include "webo/modeling/datatype/DataTypes.h"
#include <webo/modeling/ModelExceptions.h>

using namespace webo::modeling;
using namespace webo::modeling::datatype;


BOOST_AUTO_TEST_CASE(class_add_void_attribute_fails)
{
    Class myClass("MyClass");
    BOOST_CHECK_THROW(myClass.addAttribute("name", tVoid::instance()), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( class_add_primitive_attributes )
{    
    Class myClass("MyClass");
    BOOST_CHECK(myClass.addAttribute("name", tString::instance()).getAttributeType("name") == tString::instance());
    BOOST_CHECK(myClass.addAttribute("age", tInteger::instance()).getAttributeType("age") == tInteger::instance());
    BOOST_CHECK(myClass.addAttribute("size", tCharacter::instance()).getAttributeType("size") == tCharacter::instance());
}

BOOST_AUTO_TEST_CASE( class_add_object_attribute )
{    
    Class myClass("MyClass");
    Class attrClass("MyClassB");
    BOOST_CHECK(myClass.addAttribute("my_attr", attrClass).getAttributeType("my_attr") == attrClass);
}

BOOST_AUTO_TEST_CASE( class_adding_same_attribute_twice_fails )
{    
    Class myClass("MyClass");
    myClass.addAttribute("my_attr", tString::instance());
    BOOST_CHECK_THROW(myClass.addAttribute("my_attr", tString::instance()), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( class_has_attribute_fails_when_missing )
{
    Class myClass("MyClass");
    BOOST_CHECK(!myClass.hasAttribute("my_attr"));
}

BOOST_AUTO_TEST_CASE(class_has_attribute_succeeds_when_present )
{
    Class myClass("MyClass");
    myClass.addAttribute("my_attr", tString::instance());
    BOOST_CHECK(myClass.hasAttribute("my_attr"));
}

BOOST_AUTO_TEST_CASE( class_get_attribute_type_for_missing_attribute_fails )
{
    Class myClass("MyClass");
    BOOST_CHECK_THROW(myClass.getAttributeType("my_attr"), UnknownAttributeException);
}

BOOST_AUTO_TEST_CASE( class_get_attribute_type_succeeds )
{
    Class myClass("MyClass");
    myClass.addAttribute("my_attr", tString::instance());
    BOOST_CHECK_EQUAL(myClass.getAttributeType("my_attr").name, tString::instance().name);
}

BOOST_AUTO_TEST_CASE( class_get_attribute_names ) 
{
    Class myClass("MyClass");
    myClass.addAttribute("my_attr1", tString::instance());
    myClass.addAttribute("my_attr2", tInteger::instance());
    
    std::vector<std::string> & vNames = myClass.getAttributeNames();
    std::vector<std::string>::iterator vIt = vNames.begin();
    BOOST_CHECK_EQUAL(*vIt, "my_attr1");
    ++vIt;
    BOOST_CHECK_EQUAL(*vIt, "my_attr2");
}