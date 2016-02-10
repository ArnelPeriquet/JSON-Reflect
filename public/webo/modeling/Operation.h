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

#include <vector>
#include <map>
#include <memory>

namespace webo {

    namespace modeling {

        class Invoker;
        class Type;
        class Class;
        class Object;


        class MODELING_API Operation {
        public:
            static std::string composeSignature(std::string name, Type & returnType, std::map<std::string, Type *> parameters);

            Operation(std::string name, Type & returnType, std::map<std::string, Type *> parameters);

            std::string getSignature() const;

            std::vector<std::string> & getParameterNames();
            Type * getParameterType(std::string name);

            void bind(Invoker & implementation);            
            std::shared_ptr<Object> invoke(std::map<std::string, std::shared_ptr<Object>> & arguments, bool allowMissingArguments = true) const;
            std::shared_ptr<Object> invoke(std::vector<std::shared_ptr<Object>> & arguments, bool allowMissingArguments = true) const;

            std::string name;

        protected:
            void verifyArguments(std::map<std::string, std::shared_ptr<Object>> & arguments, bool allowMissingArguments) const;
            void verifyArguments(std::vector<std::shared_ptr<Object>> & arguments, bool allowMissingArguments) const;

            Type &                          mReturnType;
            std::vector<std::string>        mParameterNames;
            std::map<std::string, Type *>   mParameters;
            Invoker *                       mImplementation; // not owned, do not destroy
        };

    }

}
