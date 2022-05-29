//
// Created by rick on 2022/5/24.
//

#ifndef WORKBENCH_GLSHADER_H
#define WORKBENCH_GLSHADER_H

#include "GLUnit.h"

namespace rick::core::gl {

    enum ShaderEnum {
        /**
         * 顶点渲染器
         */
        VERTEX,
        /**
         * 片段渲染器
         */
        FRAGMENT
    };

    /**
     * 渲染器， 顶点渲染器、片段渲染器
     */
    class GLShader : public GLUnit {
    public:
        /**
         * GL 渲染器
         * @param identifier
         */
        explicit GLShader(GLIdentifier identifier);
        /**
         * 编译渲染器
         * @return
         */
        bool compile();
        /**
         * 删除渲染器
         */
        ~GLShader();

    };
}


#endif //WORKBENCH_GLSHADER_H
