#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D textureSampler;

uniform Material material;

uniform vec3 cameraPosition;

uniform vec3 ambientLightColor;

uniform vec3 directionalLightPosition;
uniform vec3 directionalLightColor;

void main()
{
    vec3 ambientLight = material.ambient * ambientLightColor;
    
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(directionalLightPosition - FragPos);
    float difference = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = (difference * material.diffuse) * directionalLightColor;
    
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = (material.specular * spec) * directionalLightColor;
    
    vec3 textureColor = texture(textureSampler, TexCoord).rgb;
    float textureAlpha = texture(textureSampler, TexCoord).a;
    
    FragColor = vec4((ambientLight + diffuseLight + specularLight) * textureColor, textureAlpha);
}
