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
#include "webo/encoding/ClassLoader.h"
#include "webo/modeling/ModelExceptions.h"
#include "webo/encoding/JSON.h"

using namespace webo::encoding;
using namespace webo::modeling;

namespace webo {

    namespace encoding {

        ClassLoader::ClassLoader(const std::string & rootPath, ClassStore * store) 
            : mRootPath(rootPath) {  
            mClassStore = new ClassStore(rootPath);
            json = new JSON(*this);
            mStore = store ? store : mClassStore;           
        }

        ClassLoader::~ClassLoader() {
            if (mClassStore)
                delete mClassStore;

            if (json)
                delete json;
        }

        Class & ClassLoader::getClass(std::string name, std::string nameSpace) {
            try {
                return ClassModel::getClass(name, nameSpace);
            }
            catch (ClassNotFoundException &) {
                std::string schema = mStore->retrieve(name, nameSpace);
                json->parseSchema(schema);
                return ClassModel::getClass(name, nameSpace);
            }
        }

    }

}
