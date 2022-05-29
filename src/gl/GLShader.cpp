//
// Created by rick on 2022/5/24.
//

#include "GLShader.h"
#include <glad/glad.hpp>
#include <iostream>

namespace rick::core::gl {


    GLShader::GLShader(GLIdentifier identifier) : GLUnit(identifier) {

    }

    bool GLShader::compile() {
        // 编译
        glCompileShader(this->identifier);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(this->identifier, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(this->identifier, 512, NULL, infoLog);
            std::cout << "Shader Error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    GLShader::~GLShader() {
        glDeleteShader(this->identifier);
    }
}