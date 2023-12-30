#ifndef VBUFFER_H
#define VBUFFER_H

#include <glad/glad.h>

typedef struct VertexBufffer {
    unsigned int m_RendererID;
} VertexBuffer;

void GenerateVBO(unsigned int *m_RendererID, float data[], unsigned int size);
void DeleteVBO(unsigned int *m_RendererID);
void BindVBO(unsigned int *m_RendererID);
void UnbindVBO();

#endif //VBUFFER_H