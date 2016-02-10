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
#include "webo/encoding/ClassStore.h"
#include <fstream>

namespace {
    
    void mkDirIfNotExists(const std::string & path) {        
        // windows
        std::string winpath = path;
        std::replace(winpath.begin(), winpath.end(), '/', '\\');
        system(std::string("if not exist \"" + winpath + "\" mkdir " + winpath).c_str());

        // linux Korn shell
        //system(std::string("if [[!- e " + path + "]]; then mkdir " + path).c_str());
    }

    void mkDirs(const std::string & path) {
        size_t index = path.find_first_of("/");        

        if (index != std::string::npos) {
            bool stop = false;

            while (!stop) {
                mkDirIfNotExists(path.substr(0, index));
                int incr = path.substr(index + 1).find_first_of("/");

                if (incr != std::string::npos) {
                    index += incr + 1;
                } else {
                    mkDirIfNotExists(path);
                    stop = true;
                }
            }
        }
    }

}

namespace webo {

    namespace encoding {

        ClassStore::ClassStore(std::string rootDir) : mRootDir(rootDir) {
            if (!mRootDir.empty() && mRootDir.find("/") != mRootDir.length() - 1 && mRootDir.find("\\") != mRootDir.length() - 1)
                mRootDir += "/";

            std::replace(mRootDir.begin(), mRootDir.end(), '\\', '/');
        }

        void ClassStore::store(const std::string & name, const std::string & content, const std::string & package) {
            std::string filePath = mRootDir + package;
            std::replace(filePath.begin(), filePath.end(), '.', '/');
            mkDirs(filePath);

            filePath.append("/" + name);
            std::ofstream ofs(filePath, std::ofstream::out);
            ofs << content;
            ofs.close();
        }

        std::string ClassStore::retrieve(const std::string & name, const std::string & package) {
            std::string filePath = mRootDir + package;
            std::replace(filePath.begin(), filePath.end(), '.', '/');

            filePath.append("/" + name);
            std::ostringstream oss;
            std::ifstream ifs(filePath, std::ifstream::in);

            if (ifs.is_open()) {
                bool first = true;

                while (ifs.good()) {
                    std::string line;
                    getline(ifs, line);

                    if (first)
                        first = false;
                    else
                        oss << "\n";

                    oss << line;
                }
            } else {
                throw std::runtime_error("unable to open file: " + filePath);
            }

            ifs.close();

            return oss.str();
        }

    }

}
