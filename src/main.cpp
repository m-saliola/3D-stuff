#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "index_buffer.h"
#include "shader.h"
#include "material.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

Camera cam(glm::vec3(0, 0, 5), glm::vec3(-90.0f, 0.0f, 0.0f));

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static bool firstMouse = true;
    static double lastX = 0.0f, lastY = 0.0f;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam.Rotate(glm::vec3(xoffset, yoffset, 0.0f));
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(960, 960, "Window", NULL, NULL);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    float positions[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        4, 5, 6,
        6, 7, 4,

        0, 1, 2,
        2, 3, 0,

        0, 4, 7,
        7, 3, 0,

        1, 5, 6,
        6, 2, 1,

        0, 1, 5,
        5, 4, 0,

        3, 2, 6,
        6, 7, 3
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 36);
    ib.Bind();

    cam;

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 10000.0f); // glm::ortho(0.0f, 960.0f, 0.0f, 960.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5.0f));

    // Shader s("assets/shaders/basic.shader");
    // s.Bind();

    // Texture t("assets/textures/circle.png");
    // t.Bind(0);

    // s.SetUniform<1, int>("u_Texture", 0);

    Material color("assets/materials/color.material");
    color.Bind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    glm::vec3 translation(0, 0, 0);
    glm::vec3 rotation = glm::normalize(glm::vec3(1.0f, 2.0f, 1.0f));

    glm::vec3 campos = cam.GetPosition();
    glm::vec3 camrot = cam.GetRotation();
    
    float r = 0;
    float increment = 0.01f;
    float f;

    while (!glfwWindowShouldClose(window)) {
        renderer.ClearColor(0.45f, 0.55f, 0.6f, 1.0f);
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        {
            glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1.0f), translation), glm::radians((float)glfwGetTime() * 20.0f), rotation);
            // cam.SetPosition(campos);
            // cam.SetRotation(camrot);
            glm::mat4 mvp = cam.GetProjectionMatrix() * cam.GetViewMatrix() * model;
            color.GetShader().SetUniform<1, glm::mat4>("u_MVP", mvp);

            renderer.Draw(va, ib, color.GetShader());
        }

        {
            ImGui::SliderFloat3("Translation", &translation.x, -3.0f, 3.0f);
            ImGui::SliderFloat3("Position", &campos.x, -5.0f, 5.0f);
            ImGui::SliderFloat3("Rotation", &camrot.x, -180.0f, 180.0f);
            ImGui::Text("FPS: %d (%.3fms)", (int)ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        if (r > 1 || r < 0) increment = -increment;
        r += increment;

        glfwPollEvents();

        glm::vec3 moveVector(0.0f);

        glm::vec3 forward = cam.GetForward();
        forward.y = 0.0f;
        if (glm::length(forward) > 0.0f)
            forward = glm::normalize(forward);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            moveVector += forward;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            moveVector -= cam.GetRight();
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            moveVector -= forward;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            moveVector += cam.GetRight();

        if (glm::length(moveVector) > 0.0f) {
            moveVector = glm::normalize(moveVector) * 0.025f;
            cam.Translate(moveVector);
        }

        cam.Translate(moveVector);

        if (cam.GetRotation().y > 89.9f) cam.SetRotation(glm::vec3(cam.GetRotation().x, 89.9f, cam.GetRotation().z));
        else if (cam.GetRotation().y < -89.9f) cam.SetRotation(glm::vec3(cam.GetRotation().x, -89.9f, cam.GetRotation().z));
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}