#version 410 core
layout (location = 0) in vec4 vertex_position;
uniform float x_dir;
uniform float y_dir;
uniform mat4 u_MVP;
void main() {
    gl_Position = u_MVP * vec4(vertex_position.x + x_dir, vertex_position.y + y_dir, 0.0, 1.0);
};