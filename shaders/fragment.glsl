#version 330 core
in vec3 vertexResult;

out vec4 FragColor;

void main() {
  FragColor = vec4(vertexResult, 1.0);
}
