/*
 * (C) Copyright 2015  Arnel I Periquet.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 */

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma warning (disable : 4251)

#include "webo/modeling/modeling_dll.h"
#include "webo/encoding_xml/encoding_xml_dll.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdarg.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <boost/optional.hpp>
#include <boost/any.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using namespace boost::property_tree;

// BOOST header dependency, but no library dependency.
