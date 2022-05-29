//
// Created by rick on 2022/5/24.
//

#include "GLUnit.h"
#include <iostream>

namespace rick::core::gl {


    GLUnit::GLUnit(GLIdentifier glIdentifier) : identifier(glIdentifier) {
        std::cout << "ID: " << glIdentifier << std::endl;
    }

    GLUnit::~GLUnit() {
        std::cout << "Delete: " << this->identifier << std::endl;
    }
}