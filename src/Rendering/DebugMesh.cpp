#include "../../include/Rendering/DebugMesh.h"

void DebugMesh::Render()
{
    if (textureID != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    
    if (textureID != 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}