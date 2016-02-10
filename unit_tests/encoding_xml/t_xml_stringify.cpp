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
#include "webo/encoding_xml/XML.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;
using namespace webo::encoding_xml;


BOOST_AUTO_TEST_CASE( xml_stringify ) {
     std::string simpleXmlExample(
         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
         "<A attr1=\"a\">"
         "    <B>"
         "        <id>1</id>"
         "    </B>"
         "    blah blah"
         "    <B>"
         "        <id>2</id>"
         "    </B>"
         "</A>");

    ClassModel cm;

    Class & classB = 
        cm.createClass("B")
        .addAttribute("@id", tInteger::instance());

    Class & classA = 
        cm.createClass("A")
        .addAttribute("#attr1", tString::instance())
        .addAttribute("node1", classB)
        .addAttribute("node2", tString::instance())
        .addAttribute("node3", classB);

    // allocate the objects   
    std::shared_ptr<Object> b1 = std::make_shared<Object>(classB);    
    std::shared_ptr<Object> b2 = std::make_shared<Object>(classB);
    std::shared_ptr<Object> a = std::make_shared<Object>(classA); 
    
    // set the values
    a->set("#attr1", tString::value("a"));
    a->set("node1", b1);
    b1->set("@id", tInteger::value(1));
    a->set("node2", tString::value("blah blah"));
    a->set("node3", b2);
    b2->set("@id", tInteger::value(2));

    XML xml(cm);
    //std::cout << xml.stringify(*a, classA) << std::endl;
    BOOST_CHECK_EQUAL(xml.stringify(*a, classA),
        "<A attr1=\"a\">\n   <B>\n      <id>1</id>\n   </B>\n   blah blah\n   <B>\n      <id>2</id>\n   </B>\n</A>");
}