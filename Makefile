CXX = clang++
CC = clang
CPPFLAGS = -Iinclude -Idependencies_GL_GLFW/include -Idependencies_GL_GLFW/ImGui -I/opt/homebrew/include -I/opt/homebrew/opt/glfw/include
CXXFLAGS = -std=c++17 -MMD -MP
CFLAGS = -MMD -MP
LDFLAGS = -L/opt/homebrew/opt/glfw/lib
LDLIBS = -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
IMGUI = dependencies_GL_GLFW/ImGui
SOURCES = $(wildcard src/*.cpp) $(IMGUI)/imgui.cpp $(IMGUI)/imgui_draw.cpp $(IMGUI)/imgui_tables.cpp $(IMGUI)/imgui_widgets.cpp $(IMGUI)/imgui_impl_glfw.cpp $(IMGUI)/imgui_impl_opengl3.cpp
OBJECTS = $(patsubst %.cpp,build/%.o,$(SOURCES)) build/dependencies_GL_GLFW/glad.o

.PHONY: all run
all: app
app: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
run: app
	./app
-include $(OBJECTS:.o=.d)
