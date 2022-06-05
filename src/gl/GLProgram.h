//
// Created by rick on 2022/5/24.
//

#ifndef WORKBENCH_GLPROGRAM_H
#define WORKBENCH_GLPROGRAM_H
#include "GLUnit.h"
#include "GLShader.h"
#include <glm/glm.hpp>

namespace rick::core::gl {
    /**
     * GL程序
     */
    class GLProgram : public GLUnit {
    public:
        /**
         * GL 程序
         * @param identifier
         */
        explicit GLProgram(GLIdentifier identifier);
        /**
         * 将渲染器连接到程序中
         * @param shader
         */
        void attach_shader(GLShader* shader);
        /**
         * link 程序
         */
        bool link();

        /**
         * 删除渲染器
         */
        ~GLProgram();
        /**
         * 设置矩阵
         * @param mat  4x4 矩阵
         */
        void setUniformMatrix(const char* name, glm::mat4x4 mat);
    };
};


#endif //WORKBENCH_GLPROGRAM_H
