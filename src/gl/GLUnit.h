//
// Created by rick on 2022/5/24.
//

#ifndef WORKBENCH_GLUNIT_H
#define WORKBENCH_GLUNIT_H


namespace rick::core::gl {
    typedef unsigned int GLIdentifier;
    /**
     * Gl单元
     */
    class GLUnit {
    public:
        explicit GLUnit(GLIdentifier identifier);
        /**
         * GL 标识符
         */
        const GLIdentifier identifier;
        /**
         * 虚构函数
         */
        ~GLUnit();

    };
}


#endif //WORKBENCH_GLUNIT_H
