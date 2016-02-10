#include <stdafx.h>
#include "boost/test/unit_test.hpp"
#include "webo/encoding/ClassLoader.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;
using namespace webo::encoding;


BOOST_AUTO_TEST_CASE(class_loader_load_from_root)
{
    system("if exist c:\\default rmdir /S /Q c:\\default");

    ClassStore cs("c:/");
    cs.store("NoAttribClass", "{ \"NoAttribClass\" : {} }");

    ClassLoader cl("c:/");
    BOOST_CHECK_NO_THROW(cl.getClass("NoAttribClass"));

    system("if exist c:\\default rmdir /S /Q c:\\default");
}

BOOST_AUTO_TEST_CASE(class_loader_load_from_package)
{
    system("if exist c:\\test rmdir /S /Q c:\\test");

    ClassStore cs("c:/test");
    cs.store("NoAttribClass", "{ \"this.that.other.NoAttribClass\" : {} }", "this.that.other");

    ClassLoader cl("c:/test");
    BOOST_CHECK_NO_THROW(cl.getClass("NoAttribClass", "this.that.other"));

    system("if exist c:\\test rmdir /S /Q c:\\test");
}

BOOST_AUTO_TEST_CASE(class_loader_load_class_with_attributes)
{
    system("if exist c:\\test rmdir /S /Q c:\\test");

    ClassStore cs("c:/test");
    cs.store("MyClass", "{ \"this.that.other.MyClass\" : { \"attr1\" : \"tString\" } }", "this.that.other");

    ClassLoader cl("c:/test");
    Class & c = cl.getClass("MyClass", "this.that.other");
    Object o(c);

    BOOST_CHECK_NO_THROW(o.set("attr1", tString::value("test")));
    BOOST_CHECK(o.get("attr1")->asString() == "test");

    system("if exist c:\\test rmdir /S /Q c:\\test");
}
