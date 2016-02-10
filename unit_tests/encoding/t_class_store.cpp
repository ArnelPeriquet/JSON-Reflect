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
#include "webo/encoding/ClassStore.h"

using namespace webo::encoding;


BOOST_AUTO_TEST_CASE(class_store_store_and_retrieve_from_relative_path)
{
    system("if exist this rmdir /S /Q this");

    ClassStore cs;
    cs.store("stuf.txt", "content\nmore content", "this.that.other");
    std::string result = cs.retrieve("stuf.txt", "this.that.other");
    BOOST_CHECK_EQUAL("content\nmore content", result);

    system("if exist this rmdir /S /Q this");
}

BOOST_AUTO_TEST_CASE(class_store_store_and_retrieve_from_specified_path_linux_separator)
{
    system("if exist c:\\this rmdir /S /Q c:\\this");

    ClassStore cs("c:/");
    cs.store("stuf.txt", "content\nmore content", "this.that.other");
    std::string result = cs.retrieve("stuf.txt", "this.that.other");
    BOOST_CHECK_EQUAL("content\nmore content", result);

    system("if exist c:\\this rmdir /S /Q c:\\this");
}

BOOST_AUTO_TEST_CASE(class_store_store_and_retrieve_from_specified_path_win_separator)
{
    system("if exist c:\\this rmdir /S /Q c:\\this");

    ClassStore cs("c:\\");
    cs.store("stuf.txt", "content\nmore content", "this.that.other");
    std::string result = cs.retrieve("stuf.txt", "this.that.other");
    BOOST_CHECK_EQUAL("content\nmore content", result);

    system("if exist c:\\this rmdir /S /Q c:\\this");
}

BOOST_AUTO_TEST_CASE(class_store_store_and_retrieve_from_specified_path_no_separtor)
{
    system("if exist c:\\this rmdir /S /Q c:\\this");

    ClassStore cs("c:");
    cs.store("stuf.txt", "content\nmore content", "this.that.other");
    std::string result = cs.retrieve("stuf.txt", "this.that.other");
    BOOST_CHECK_EQUAL("content\nmore content", result);

    system("if exist c:\\this rmdir /S /Q c:\\this");
}