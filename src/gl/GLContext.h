//
// Created by rick on 2022/5/21.
//

#ifndef WORKBENCH_GLCONTEXT_H
#define WORKBENCH_GLCONTEXT_H
#define RICK_GL_SOURCE_TEXT const char * const *
#include "GLShader.h"
#include "GLProgram.h"
#include "GLBuffer.h"
namespace rick::core::gl {
    /**
     * 创建GL 程序
     * @return
     */
    GLProgram* create_program();

    /**
     * 创建渲染器
     * @param type 渲染器类型
     * @param source 渲染器源代码
     * @param size 代码长度
     * @return 返回创建渲染器后的渲染器ID
     */
    GLShader* create_shader(ShaderEnum type, RICK_GL_SOURCE_TEXT source, int size);
    /**
     * 使用程序
     * @param program GLProgram
     */
    void use_program(const GLProgram& program);


    GLBuffer* create_buffer();
}
#endif //WORKBENCH_GLCONTEXT_H
