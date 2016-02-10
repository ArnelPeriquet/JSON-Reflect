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
#include "webo/modeling/Operation.h"
#include "webo/modeling/Invoker.h"
#include "webo/modeling/Modeling.h"
#include "webo/modeling/datatype/tVoid.h"
#include "webo/modeling/datatype/tNull.h"

namespace webo {

    namespace modeling {

        std::string Operation::composeSignature(std::string name, Type & returnType, std::map<std::string, Type *> parameters) {
            std::string signature(returnType.name);
            signature.append(" ");
            signature.append(name);
            signature.append("(");

            for (std::pair<std::string, Type *> param : parameters) {
                signature.append(param.second->name);
                signature.append(" ");
                signature.append(param.first);
                signature.append(", ");
            }

            signature = signature.substr(0, signature.size() - 2);

            signature.append(")");
            return signature;
        }

        Operation::Operation(std::string name, modeling::Type & returnType, std::map<std::string, Type *> parameters)
            : name(name), mReturnType(returnType), mParameters(parameters), mImplementation(nullptr) {

            for (std::map<std::string, Type *>::iterator it = parameters.begin(); it != parameters.end(); ++it) {
                mParameterNames.push_back(it->first);
            }
        }

        std::string Operation::getSignature() const {
            return composeSignature(name, mReturnType, mParameters);
        }

        std::vector<std::string> & Operation::getParameterNames() {
            return mParameterNames;
        }

        Type * Operation::getParameterType(std::string name) {
            return mParameters[name];
        }

        void Operation::bind(Invoker & implementation) {
            mImplementation = &implementation;
        }

        std::shared_ptr<Object> Operation::invoke(std::map<std::string, std::shared_ptr<Object>> & arguments, bool allowMissingArguments) const {
            verifyArguments(arguments, allowMissingArguments);

            if (mReturnType == datatype::tVoid::instance()) {
                mImplementation->invoke(arguments);
                return datatype::tNull::value();
            } else {
                return mImplementation->invoke(arguments);
            }
        }

        std::shared_ptr<Object> Operation::invoke(std::vector<std::shared_ptr<Object>> & arguments, bool allowMissingArguments) const {
            verifyArguments(arguments, allowMissingArguments);

            if (mReturnType == datatype::tVoid::instance()) {
                mImplementation->invoke(arguments);
                return datatype::tNull::value();
            } else {
                return mImplementation->invoke(arguments);
            }
        }

        void Operation::verifyArguments(std::map<std::string, std::shared_ptr<Object>> & arguments, bool allowMissingArguments) const {
            for (std::pair<std::string, Type *> param : mParameters) {
                if (arguments.find(param.first) == arguments.end() && !allowMissingArguments)
                    throw std::invalid_argument("missing argument: " + param.first + " of type: " + param.second->name);

                Type & givenType = arguments[param.first]->type;

                if (*param.second != givenType)
                    throw std::invalid_argument("argument " + param.first + " of type " + givenType.name + " does not match expected type of " + param.second->name);
            }
        }

        void Operation::verifyArguments(std::vector<std::shared_ptr<Object>> & arguments, bool allowMissingArguments) const {
            size_t index = 0;

            for (std::pair<std::string, Type *> param : mParameters) {
                if (index < arguments.size()) {
                    Type & givenType = arguments[index]->type;

                    if (*param.second != givenType) {
                        std::ostringstream oss;
                        oss << index;
                        throw std::invalid_argument("arguments[" + oss.str() + "] of type " + givenType.name + " does not match expected type of " + param.second->name);
                    }
                } else {
                    if (!allowMissingArguments)
                        throw std::invalid_argument("missing argument: " + param.first + " of type: " + param.second->name);
                    else
                        break;
                }

                index++;
            }
        }
    }

}

