/*
 * (C) Copyright 2015  Arnel I Periquet.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 */

#pragma once

#include "webo/modeling/datatype/DataType.h"
#include "webo/modeling/datatype/tCharacter.h"
#include "webo/modeling/datatype/tInteger.h"
#include "webo/modeling/datatype/tFloat.h"
#include "webo/modeling/datatype/tString.h"
#include "webo/modeling/datatype/tNull.h"
#include "webo/modeling/datatype/tBoolean.h"
#include "webo/modeling/datatype/tVoid.h"
#include "webo/modeling/datatype/tArray.h"
#include "webo/modeling/datatype/tObjectArray.h"


#define CHARACTER_TYPE                 webo::modeling::datatype::tCharacter::instance()
#define INTEGER_TYPE                   webo::modeling::datatype::tInteger::instance()
#define FLOAT_TYPE                     webo::modeling::datatype::tFloat::instance()
#define STRING_TYPE                    webo::modeling::datatype::tString::instance()
#define NULL_TYPE                      webo::modeling::datatype::tNull::instance()
#define BOOLEAN_TYPE                   webo::modeling::datatype::tBoolean::instance()
#define VOID_TYPE                      webo::modeling::datatype::tVoid::instance()
#define ARRAY_OF(TYPE)                 webo::modeling::datatype::tArray<TYPE>::instance()
#define OBJECT_ARRAY                   webo::modeling::datatype::tObjectArray::instance()
