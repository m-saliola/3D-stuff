all:
	g++ src/main.cpp \
	src/renderer.cpp \
	src/batcher.cpp \
	src/vertex_buffer.cpp \
	src/index_buffer.cpp \
	src/vertex_array.cpp \
	src/vertex_buffer_layout.cpp \
	src/shader.cpp \
	src/material.cpp \
	src/model.cpp \
	src/texture.cpp \
	src/camera.cpp \
	src/glad.c \
	src/vendor/stb_image/stb_image.cpp \
	src/vendor/imgui/imgui_demo.cpp \
	src/vendor/imgui/imgui_draw.cpp \
	src/vendor/imgui/imgui_impl_glfw_gl3.cpp \
	src/vendor/imgui/imgui.cpp \
	-Iinclude -Llib -lglfw3 -lopengl32 -lgdi32 \
	-static-libstdc++ -static-libgcc \
	-o main.exe