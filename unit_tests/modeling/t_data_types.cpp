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


BOOST_AUTO_TEST_CASE( tinteger_create_object )
{
    BOOST_CHECK_EQUAL(tInteger::value(15)->asInteger(), 15);
}

BOOST_AUTO_TEST_CASE( tfloat_create_object )
{
    BOOST_CHECK_EQUAL(tFloat::value(3.14)->asFloat (), 3.14);
}

BOOST_AUTO_TEST_CASE( tstring_create_object )
{
    BOOST_CHECK_EQUAL(tString::value("hello")->asString(), "hello");
}

BOOST_AUTO_TEST_CASE( tchar_create_object )
{
    BOOST_CHECK_EQUAL(tCharacter::value('a')->asCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE( tnull_create_object )
{
    BOOST_CHECK(tNull::value()->type.equals(tNull::instance()));
}

BOOST_AUTO_TEST_CASE( tboolean_create_object )
{
    BOOST_CHECK_EQUAL(tBoolean::value(false)->asBoolean(), false);
}


