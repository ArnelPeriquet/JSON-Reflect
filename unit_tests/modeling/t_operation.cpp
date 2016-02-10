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
#include "webo/modeling/Modeling.h"
#include "webo/modeling/datatype/DataTypes.h"
#include "webo/modeling/Operation.h"
#include "webo/modeling/Invoker.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;


namespace {
    class MyFunctionWithNoParams : public Invoker {
    public:
        virtual std::shared_ptr<Object> invoke(std::map<std::string, std::shared_ptr<Object>> & arguments) {
            return tInteger::value(10);
        }
    };
    
    class MyFunctionWithParams : public Invoker {
    public:
        virtual std::shared_ptr<Object> invoke(std::map<std::string, std::shared_ptr<Object>> & arguments) {
            std::map<std::string, std::shared_ptr<Object>>::iterator it = arguments.begin();

            int arg1 = it->second->asInteger();  ++it;
            std::string arg2 = it->second->asString();

            std::ostringstream oss;
            oss << arg1;
            return tString::value(oss.str() + "-" + arg2);
        }
    };

    class MyFunctionWithObjectParams : public Invoker {
    public:
        virtual std::shared_ptr<Object> invoke(std::map<std::string, std::shared_ptr<Object>> & arguments) {
            std::map<std::string, std::shared_ptr<Object>>::iterator it = arguments.begin();

            Object & argObj1 = *it->second; ++it;
            webo::modeling::Object & argObj2 = *it->second;

            int arg1 = argObj1.get("attr1")->asInteger();
            std::string arg2 = argObj2.get("attr1")->asString();

            std::ostringstream oss;
            oss << arg1;
            return tString::value(oss.str() + "-" + arg2);
        }
    };
}

BOOST_AUTO_TEST_CASE(operation_invoke_with_no_parameters)
{
    MyFunctionWithNoParams myFunction;
    std::map<std::string, Type *> parameters;
    std::map<std::string, std::shared_ptr<Object>> arguments;
    ClassModel cm;
    
    Operation operation("myFunction", tInteger::instance(), parameters);
    operation.bind(myFunction);

    BOOST_CHECK_EQUAL(operation.invoke(arguments)->asInteger(), 10);
}

BOOST_AUTO_TEST_CASE(operation_invoke_with_parameters)
{
    MyFunctionWithParams myFunction;
    std::map<std::string, Type *> parameters;
    parameters["param1"] = &tInteger::instance();
    parameters["param2"] = &tString::instance();
    std::map<std::string, std::shared_ptr<Object>> arguments;
    arguments["param1"] = tInteger::value(15);
    arguments["param2"] = tString::value("hello");

    Operation operation("myFunction", tString::instance(), parameters);
    operation.bind(myFunction);

    BOOST_CHECK_EQUAL(operation.invoke(arguments)->asString(), "15-hello");
}

BOOST_AUTO_TEST_CASE(operation_invoke_with_object_parameters)
{
    Class class1("MyClass1");
    class1.addAttribute("attr1", tInteger::instance());
    Class class2("MyClass2");
    class2.addAttribute("attr1", tString::instance());
        
    std::map<std::string, Type *> parameters;
    parameters["param1"] = &class1;
    parameters["param2"] = &class2;
    
    Operation operation("myFunction", tString::instance(), parameters);
    MyFunctionWithObjectParams myFunction;
    operation.bind(myFunction);       

    std::map<std::string, std::shared_ptr<Object>> arguments;
    std::shared_ptr<Object> arg1 = std::make_shared<Object>(class1);
    arg1->set("attr1", tInteger::value(15));
    std::shared_ptr<Object> arg2 = std::make_shared<Object>(class2);
    arg2->set("attr1", tString::value("hello"));
    arguments["param1"] = arg1;
    arguments["param2"] = arg2;

    BOOST_CHECK_EQUAL(operation.invoke(arguments)->asString(), "15-hello");
}

BOOST_AUTO_TEST_CASE(operation_get_signature)
{
    Class class1("MyClass1");
    class1.addAttribute("attr1", tInteger::instance());
    Class class2("MyClass2");
    class2.addAttribute("attr1", tString::instance());

    std::map<std::string, Type *> parameters;
    parameters["param1"] = &class1;
    parameters["param2"] = &class2;

    Operation operation("myFunction", tVoid::instance(), parameters);
   
    //std::cout << operation.getSignature() << std::endl;
    BOOST_CHECK_EQUAL("tVoid myFunction(MyClass1 param1, MyClass2 param2)", operation.getSignature());
}

BOOST_AUTO_TEST_CASE(operation_disallow_missing_arguments_when_invoking_with_vector)
{
    std::map<std::string, Type *> parameters;
    parameters["param1"] = &tInteger::instance();
    parameters["param2"] = &tString::instance();

    Operation operation("myFunction", tVoid::instance(), parameters);

    std::vector<std::shared_ptr<Object>> args;
    args.push_back(tInteger::value(3));
    BOOST_CHECK_THROW(operation.invoke(args, false), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(operation_detect_mismatched_arguments_when_invoking_with_vector)
{
    std::map<std::string, Type *> parameters;
    parameters["param1"] = &tInteger::instance();
    parameters["param2"] = &tString::instance();

    Operation operation("myFunction", tVoid::instance(), parameters);

    std::vector<std::shared_ptr<Object>> args;
    args.push_back(tString::value("abc"));
    BOOST_CHECK_THROW(operation.invoke(args, false), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(operation_disallow_missing_arguments_when_invoking_with_map)
{
    std::map<std::string, Type *> parameters;
    parameters["param1"] = &tInteger::instance();
    parameters["param2"] = &tString::instance();

    Operation operation("myFunction", tVoid::instance(), parameters);

    std::map<std::string, std::shared_ptr<Object>> args;
    args["param2"] = tString::value("abc");
    BOOST_CHECK_THROW(operation.invoke(args, false), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(operation_detect_mismatched_arguments_when_invoking_with_map)
{
    std::map<std::string, Type *> parameters;
    parameters["param1"] = &tInteger::instance();
    parameters["param2"] = &tString::instance();

    Operation operation("myFunction", tVoid::instance(), parameters);

    std::map<std::string, std::shared_ptr<Object>> args;
    args["param1"] = tString::value("abc");
    BOOST_CHECK_THROW(operation.invoke(args, false), std::invalid_argument);
}