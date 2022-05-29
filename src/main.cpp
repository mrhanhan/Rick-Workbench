#include "glad/glad.hpp"
#include <GLFW/glfw3.h>
#include "utils/file_utils.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <iostream>
#include "game/Game.h"
#include "gl/GLContext.h"

float x = 0;
float y = 0;
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
         .0f, .5f, .0f,  1.0f, .0f, .0f,
         .5f, -.5f, .0f, .0f, .0f, 1.0f,
         -.5f, -.5f, .0f, .0f, 1.0f, .0f,
    };
    rick::core::gl::use_program(*program);
    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    glBindVertexArray(0);
    // 关闭Bind
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // render
        // ------
        glViewport(0 ,0 , 1920, 1080);
        glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        procesInput(window);
        rick::core::gl::use_program(*program);
        vertexes[1] = y;
        vertexes[0] = x;
        vertexes[3] += 0.0001f;
        if (vertexes[3] > 1.0f) vertexes[3] = .0f;
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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
    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);
    x = -(1.0f - (dx * 2 / 1920));
    y = 1.0f - (dy * 2 / 1080);
}
