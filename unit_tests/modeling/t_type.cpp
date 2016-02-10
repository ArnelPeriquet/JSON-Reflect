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
#include "webo/modeling/Type.h"

using namespace webo::modeling;


BOOST_AUTO_TEST_CASE(type_equals_for_different_type_names_fails)
{
    Type myType1("myName1", "myPackage");
    Type myType2("myName2", "myPackage");

    BOOST_CHECK(!myType1.equals(myType2));
    BOOST_CHECK(myType1 != myType2);
}

BOOST_AUTO_TEST_CASE(type_equals_for_same_type_names_but_different_packages_fails)
{
    Type myType1("myName", "myPackage1");
    Type myType2("myName", "myPackage2");

    BOOST_CHECK(!myType1.equals(myType2));
    BOOST_CHECK(myType1 != myType2);
}

BOOST_AUTO_TEST_CASE(type_equals_for_different_type_names_and_different_packages_fails)
{
    Type myType1("myName1", "myPackage1");
    Type myType2("myName2", "myPackage2");

    BOOST_CHECK(!myType1.equals(myType2));
    BOOST_CHECK(myType1 != myType2);
}

BOOST_AUTO_TEST_CASE(type_equals_by_same_object_succeeds)
{
    Type myType("myName", "myPackage");

    BOOST_CHECK(myType.equals(myType));
    BOOST_CHECK(myType == myType);
}

BOOST_AUTO_TEST_CASE(type_equals_by_same_name_and_package_succeeds)
{
    Type myType1("myName", "myPackage");
    Type myType2("myName", "myPackage");

    BOOST_CHECK(myType1.equals(myType2));
    BOOST_CHECK(myType1 == myType2);
}

BOOST_AUTO_TEST_CASE(type_package_sets_default_namespace_if_one_is_not_provided)
{
    Type myType("myName");

    BOOST_CHECK(myType.nameSpace == Type::DEFAULT_NAME_SPACE);
}