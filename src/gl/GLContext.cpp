//
// Created by rick on 2022/5/21.
//

#include "GLContext.h"
#include <glad/glad.hpp>
#include <iostream>

namespace rick::core::gl {

    /**
     * 创建GL 程序
     * @return  GLProgram
     */
    GLProgram* create_program() {
        return new GLProgram(glCreateProgram());
    }
    /**
     * 创建渲染器
     * @param type 渲染器类型
     * @param source 渲染器源代码
     * @param size 代码长度
     * @return 返回创建渲染器后的渲染器ID
     */
    GLShader* create_shader(ShaderEnum type, RICK_GL_SOURCE_TEXT source, const int size) {
        // 创建GL 渲染器
        GLIdentifier shader_id = glCreateShader(type == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
        // 设置 渲染器代码
        glShaderSource(shader_id, size, source, NULL);
        return new GLShader(shader_id);
    }
    /**
     * 使用程序
     * @param program GLProgram
     */
    void use_program(const GLProgram& program) {
        glUseProgram(program.identifier);
    }

}