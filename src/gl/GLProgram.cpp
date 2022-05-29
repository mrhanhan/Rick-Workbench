//
// Created by rick on 2022/5/24.
//

#include <glad/glad.hpp>
#include <iostream>
#include "GLProgram.h"

namespace rick::core::gl {

    GLProgram::GLProgram(GLIdentifier identifier) : GLUnit(identifier) {

    }

    void GLProgram::attach_shader(GLShader *shader) {
        glAttachShader(this->identifier, shader->identifier);
    }

    bool GLProgram::link() {
        glLinkProgram(this->identifier);
        int success;
        char infoLog[512];
        glGetProgramiv(this->identifier, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->identifier, 512, NULL, infoLog);
            std::cout << "Program Link Error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    GLProgram::~GLProgram() {
        glDeleteProgram(this->identifier);
    }

}