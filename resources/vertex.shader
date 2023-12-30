#version 410 core
layout (location = 0) in vec4 vertex_position;
uniform float x_dir;
uniform float y_dir;
void main() {
    gl_Position = vec4(vertex_position.x + x_dir, vertex_position.y + y_dir, 0.0, 1.0);
};