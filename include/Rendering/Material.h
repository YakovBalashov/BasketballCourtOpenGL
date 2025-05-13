/**
* \file Material.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Material class that represents the material properties of a 3D object.
 */

#pragma once

#include "pgr.h"

struct Material {
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float shininess;

    Material() : ambientColor(1.0f), diffuseColor(1.0f), specularColor(0.5f), shininess(32.0f) {}
    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
        : ambientColor(ambient), diffuseColor(diffuse), specularColor(specular), shininess(shininess) {}
};

