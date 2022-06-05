#include "glad/glad.hpp"
#include <GLFW/glfw3.h>
#include "utils/file_utils.hpp"
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <iostream>
#include "game/Game.h"
#include "gl/GLContext.h"

float x = 0;
float y = 0;
float angle = 0;
void procesInput(GLFWwindow *pWwindow);

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

int main() {
    GLFWwindow* window;

    auto a = glm::vec2(1.0f ,1.0f);
    std::cout << a.x << std::endl;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    auto g = rick::core::Game();
    g.start();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // glfwGetProcAddress
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /* */
    FILE_TEXT fs, * vs;

    read_all("E:\\Rick\\Workbench\\glsl\\test.fragment.glsl", &fs);
    read_all("E:\\Rick\\Workbench\\glsl\\test.vertx.glsl", &vs);
    auto program = rick::core::gl::create_program();
    auto v_shader = rick::core::gl::create_shader(rick::core::gl::VERTEX, &vs, 1);
    auto f_shader = rick::core::gl::create_shader(rick::core::gl::FRAGMENT, &fs, 1);

    if (v_shader->compile()) {
        program->attach_shader(v_shader);
        delete v_shader;
    }

    if (f_shader->compile()) {
        program->attach_shader(f_shader);
        delete f_shader;
    }
    if (program->link()) {

    }
    free(fs);
    free(vs);

    float vertexes[] = {
            -.5f, -.5f, .5f,  1.0f, .0f, .0f,
         .5f, -.5f, .5f, .0f, 1.f, 0.0f,
         .5f, .5f, .5f, .0f, .0f, 1.0f,
         -.5f, .5f, .5f, 1.0f, 1.0f, .0f,

            -.5f, -.5f, -.5f,  1.0f, .0f, .0f,
            .5f, -.5f, -.5f, .0f, 1.f, 0.0f,
            .5f, .5f, -.5f, .0f, .0f, 1.0f,
            -.5f, .5f, -.5f, 1.0f, 1.0f, .0f,
    };
    unsigned int indices[] = {
            // 第一个面 前面
            0, 1, 2, 2, 3, 0,
            // 第二个面 背面
            4, 5, 6, 6, 7, 4,
            // 第三个面 左面
            0, 3, 4,  4, 3, 7,
            // 第四个面 右面
            1, 2, 5,  5, 2, 6,
            // 第五个面 上面
            3, 2, 6, 6, 7, 3,
            // 第六个面 下面
            0, 1, 5, 5, 4, 0,

    };
    glPolygonMode(GL_FRONT, GL_LINE);
    glEnable(GL_CULL_FACE);
    rick::core::gl::use_program(*program);
    GLuint vbo, vao, ebo;
    // glm::mat4 view = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate<float>(model, glm::radians<float>(225.0f), glm::vec3(1, 1, 0));

    program->setUniformMatrix("model", model);
    program->setUniformMatrix("view", view);
    program->setUniformMatrix("projection", projection);
//    program->setUniformMatrix("model", glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f));
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 关闭Bind
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glm::vec3 route = {1, 1, 1};
    /* Loop until the user closes the window */
    float angel = 0;
    while (!glfwWindowShouldClose(window))
    {
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // render
        // ------
        glViewport(0 ,0 , 1920, 1080);
        glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        procesInput(window);
        angel ++;
        rick::core::gl::use_program(*program);
        program->setUniformMatrix("model", model);
        program->setUniformMatrix("view", view);
        program->setUniformMatrix("projection", projection);
        auto m = view;
        int p = 0;
        printf("[%f] [%f] [%f] [%f]\n", m[p][0], m[p][1], m[p][2], m[p][3]);
        p++;
        printf("[%f] [%f] [%f] [%f]\n", m[p][0], m[p][1], m[p][2], m[p][3]);
        p++;
        printf("[%f] [%f] [%f] [%f]\n", m[p][0], m[p][1], m[p][2], m[p][3]);
        p++;
        printf("[%f] [%f] [%f] [%f]\n", m[p][0], m[p][1], m[p][2], m[p][3]);
        printf("---------------------------------------------------------------\n");
        glBindVertexArray(vao);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//        glDrawArrays(GL_POINTS, 0, 8);
        // Index
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        /* Render here */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void procesInput(GLFWwindow * window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_KEY_SPACE)
        angle += 0.01f;

    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);
    x = (dx / 1920 * 2);
    y = (dy / 1080 * 2);
    if (dx > 1920 / 2) {
        dx = -dx;
    }
    if (dy > 1080 / 2) {
        dy = -dy;
    }

}
