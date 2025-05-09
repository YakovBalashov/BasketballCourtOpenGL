#include <Game/GameUtils.h>

float GameUtils::Repeat(float value, float max)
{
    return fmod(fmod(value, max) + max, max);
}

std::pair<std::vector<Vertex>, std::vector<GLuint>> GameUtils::GenerateGridLines(int divisionsX, int divisionsZ,
    float spacing, float yLevel)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint currentIndex = 0;

    float halfWidth = (divisionsX * spacing) / 2.0f;
    float halfDepth = (divisionsZ * spacing) / 2.0f;

    glm::vec3 defaultNormal = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec2 defaultTexCoords = glm::vec2(0.0f, 0.0f);

    for (int i = 0; i <= divisionsX; ++i) {
        float x = -halfWidth + (i * spacing);
        vertices.push_back({{x, yLevel, -halfDepth}, defaultNormal, defaultTexCoords});
        vertices.push_back({{x, yLevel,  halfDepth}, defaultNormal, defaultTexCoords});
        indices.push_back(currentIndex++);
        indices.push_back(currentIndex++);
    }

    for (int i = 0; i <= divisionsZ; ++i) {
        float z = -halfDepth + (i * spacing);
        vertices.push_back({{-halfWidth, yLevel, z}, defaultNormal, defaultTexCoords});
        vertices.push_back({{ halfWidth, yLevel, z}, defaultNormal, defaultTexCoords});
        indices.push_back(currentIndex++);
        indices.push_back(currentIndex++);
    }

    return {vertices, indices};
}
