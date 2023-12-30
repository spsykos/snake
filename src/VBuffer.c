#include "VBuffer.h"

void GenerateVBO(unsigned int *m_RendererID, float data[], unsigned int size) {
    glGenBuffers(1, m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, *m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void DeleteVBO(unsigned int *m_RendererID) {
    glDeleteBuffers(1, m_RendererID);
}

void BindVBO(unsigned int *m_RendererID) {
    glBindBuffer(GL_ARRAY_BUFFER, *m_RendererID);
}

void UnbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
