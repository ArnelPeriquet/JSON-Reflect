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


BOOST_AUTO_TEST_CASE(tobject_array_empty_array)
{
    Class myClass("MyClass");
    std::shared_ptr<Object> arr = tObjectArray::value(myClass);

    BOOST_CHECK(arr->type == tObjectArray::instance(myClass));
}

BOOST_AUTO_TEST_CASE(tobject_array_uninitialized_array)
{
    Class myClass("MyClass");
    std::shared_ptr<Object> arr = tObjectArray::value(myClass, 3);

    BOOST_CHECK(arr->getObjectArrayLength() == 3);
}

BOOST_AUTO_TEST_CASE(tobject_array_uninitialized_array_has_objects_with_default_values)
{
    Class myClass("MyClass");
    myClass.addAttribute("attr1", tString::instance());
    myClass.addAttribute("attr2", tInteger::instance());
    myClass.addAttribute("attr3", tFloat::instance());
    myClass.addAttribute("attr4", tCharacter::instance());
    myClass.addAttribute("attr5", tBoolean::instance());
    std::shared_ptr<Object> array = tObjectArray::value(myClass, 3);

    BOOST_CHECK(array->getObjectArrayLength() == 3);
    BOOST_CHECK_EQUAL(array->asObjectArray(myClass)[0]->get("attr1")->asString(), "");
    BOOST_CHECK_EQUAL(array->asObjectArray(myClass)[0]->get("attr2")->asInteger(), 0);
    BOOST_CHECK_EQUAL(array->asObjectArray(myClass)[0]->get("attr3")->asFloat(), 0.0);
    BOOST_CHECK_EQUAL(array->asObjectArray(myClass)[0]->get("attr4")->asCharacter(), 0);
    BOOST_CHECK_EQUAL(array->asObjectArray(myClass)[0]->get("attr5")->asBoolean(), false);
}

BOOST_AUTO_TEST_CASE(tobjectarray_loop)
{
    Class myClass("MyClass");
    std::shared_ptr<Object> arr = tObjectArray::value(myClass, 3);
    std::shared_ptr<Object> * nativeArr = arr->asObjectArray(myClass);

    for (size_t i = 0; i<arr->getObjectArrayLength(); i++) {        
        BOOST_CHECK(nativeArr[i]->type == myClass);
    }
}

BOOST_AUTO_TEST_CASE(tobjectarray_has_tobjectarray_type_name)
{
    Class myClass("MyClass");
    Type & arrType = tObjectArray::instance(myClass);
    BOOST_CHECK_EQUAL(arrType.name, "tObjectArray<MyClass>");
}
