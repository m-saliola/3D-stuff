#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "vertex.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "index_buffer.h"
#include "shader.h"
#include "material.h"
#include "model.h"
#include "texture.h"
#include "camera.h"
#include "batcher.h"
#include "renderer.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

/* 
TODO LIST:
    - Allow per-model translation using model matrices
    - Optimize batching by only updating buffers if geometry has been modified
    - Optimize rendering by only binding buffers if not bound
    - Optimize materials by using uniform buffers
    - Improve error handling
*/

Camera cam(glm::vec3(0, 0, 5), glm::vec3(-90.0f, 0.0f, 0.0f), 45.0f, 1.0f, 0.01f, 100.0f);

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

    cam.Rotate(glm::vec3(xoffset * sensitivity, yoffset * sensitivity, 0.0f));
}

void resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    cam = Camera(cam.GetPosition(), cam.GetRotation(), cam.GetFov(), static_cast<float>(width) / static_cast<float>(height), cam.GetNearPlane(), cam.GetFarPlane());
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(960, 960, "Window", NULL, NULL);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowSizeCallback(window, resize_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);  

    glEnable(GL_DEPTH_TEST);

    {
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 10000.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5.0f));

        Material color("assets/materials/color.material");
        color.Bind();
        
        Renderer renderer;
        Batcher batcher;

        Model sphere(batcher, "assets/models/cube.model");
        batcher.AddModel(sphere);

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
                batcher.Draw(renderer, model, cam.GetViewMatrix(), cam.GetProjectionMatrix());
            }

            {
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

            if (cam.GetRotation().y > 85.0f) cam.SetRotation(glm::vec3(cam.GetRotation().x, 89.9f, cam.GetRotation().z));
            else if (cam.GetRotation().y < -85.0f) cam.SetRotation(glm::vec3(cam.GetRotation().x, -89.9f, cam.GetRotation().z));

            static bool escPressed = false;
            static unsigned int mode = GLFW_CURSOR_DISABLED;
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                if (!escPressed) {
                    escPressed = true;
                    mode = (mode == GLFW_CURSOR_DISABLED) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
                    glfwSetInputMode(window, GLFW_CURSOR, mode);
                }
            } else {
                escPressed = false;
            }
        }

        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}