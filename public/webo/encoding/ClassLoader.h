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

#include "webo/modeling/ClassModel.h"
#include "webo/encoding/ClassStore.h"
#include <string>

namespace webo {

    namespace modeling {
        
        class Class;
        class Type;

    }

    namespace encoding {
        class JSON;

        class ENCODING_API ClassLoader : public modeling::ClassModel {
        public:
            ClassLoader(const std::string & rootPath, ClassStore * store = nullptr);
            virtual ~ClassLoader();

            virtual modeling::Class & getClass(std::string name, std::string nameSpace = modeling::Type::DEFAULT_NAME_SPACE);

        private:
            ClassStore * mClassStore;

            JSON * json;
            ClassStore * mStore;
            const std::string mRootPath;
        };

    }

}

