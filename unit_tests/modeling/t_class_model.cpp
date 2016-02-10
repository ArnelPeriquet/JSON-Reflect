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
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/Class.h"
#include <webo/modeling/ModelExceptions.h>

using namespace webo::modeling;


BOOST_AUTO_TEST_CASE( class_model_create_type ) 
{
    ClassModel cm;
    BOOST_CHECK_NO_THROW(cm.createClass("Employee"));
}

BOOST_AUTO_TEST_CASE( class_model_adding_same_type_name_twice_fails )
{    
    ClassModel cm;
    cm.createClass("Employee");
    BOOST_CHECK_THROW(cm.createClass("Employee"), NameCollisionException);
}

BOOST_AUTO_TEST_CASE( class_model_get_missing_type_fails )
{
    ClassModel cm;
    BOOST_CHECK_THROW(cm.getClass("Employee"), ClassNotFoundException);
}

BOOST_AUTO_TEST_CASE( class_model_get_added_type_exists )
{
    ClassModel cm;    
    Class & myClass = cm.createClass("Employee"); // use default namespace to add

    BOOST_CHECK(cm.hasClass("Employee")); // use default namespace to retrieve
    BOOST_CHECK_NO_THROW(cm.hasClass(myClass.name, myClass.nameSpace));
}

BOOST_AUTO_TEST_CASE( class_model_get_added_type_succeeds )
{
    ClassModel cm;    
    Class & myClass = cm.createClass("Employee"); // use default namespace to add

    BOOST_CHECK_NO_THROW(cm.getClass("Employee")); // use default namespace to retrieve
    BOOST_CHECK_NO_THROW(cm.getClass(myClass.name, myClass.nameSpace));
}