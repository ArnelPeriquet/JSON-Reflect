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

#ifdef MODELING_EXPORTS
#define MODELING_API __declspec(dllexport)
#else
#define MODELING_API __declspec(dllimport)
#endif