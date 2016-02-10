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

#include <string>
#include "webo/modeling/Type.h"

namespace webo {

    namespace encoding {

        class ENCODING_API ClassStore {
        public:
            ClassStore(std::string rootDir = "");
            virtual std::string retrieve(const std::string & name, const std::string & package = modeling::Type::DEFAULT_NAME_SPACE);
            virtual void store(const std::string & name, const std::string & content, const std::string & package = modeling::Type::DEFAULT_NAME_SPACE);

        private:
            std::string mRootDir;
        };

    }

}
