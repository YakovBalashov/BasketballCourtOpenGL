#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float shininess;
};

struct Sun {
     vec3 direction;
     vec3 color;
  
     float ambientIntensity;
     float diffuseIntensity;
     float specularIntensity;
};

struct PointLight {
    vec3 position;
    vec3 color;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;
};

struct FlashLight {
    vec3 position;
    vec3 direction;
    vec3 color;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
    
    float cutOff;
    
    int state;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D textureSampler;
uniform Material material;
uniform vec3 cameraPosition;

uniform Sun sun;
uniform PointLight pointLight;
uniform FlashLight flashLight;

vec3 calculateFlashLight(vec3 norm, vec3 fragPos) {
    vec3 lightDir = normalize(flashLight.position - fragPos);
    float theta = dot(lightDir, normalize(-flashLight.direction));
    
    if (theta < flashLight.cutOff) {
        return vec3(0.0);
    }
    
    vec3 ambient = (material.ambient * flashLight.ambientIntensity) * flashLight.color;

    vec3 flashLightDir = normalize(-flashLight.direction);
    float flashDot = max(dot(norm, flashLightDir), 0.0);
    vec3 directionl = (flashDot * flashLight.diffuseIntensity * material.diffuse) * flashLight.color;

    vec3 viewDir = normalize(cameraPosition - fragPos);
    vec3 reflectDir = reflect(-flashLightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (material.specular * flashLight.specularIntensity * spec) * flashLight.color;
    
    return ambient + directionl + specular;
}

vec3 calculateSunLight(vec3 normal, vec3 fragPos) {
    vec3 ambientSunLight = (material.ambient * sun.ambientIntensity) * sun.color;
    
    vec3 sunDir = normalize(sun.direction);
    float sunDot = max(dot(normal, sunDir), 0.0);
    vec3 directionalSunLight = (sunDot * sun.diffuseIntensity * material.diffuse) * sun.color;
    
    vec3 viewDir = normalize(cameraPosition - fragPos);
    vec3 reflectDir = reflect(-sunDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularSunLight = (material.specular * sun.specularIntensity * spec) * sun.color;
    
    vec3 sunLight = ambientSunLight + directionalSunLight + specularSunLight;
    return sunLight;
}

vec3 calculatePointLight(vec3 normal, vec3 fragPos) {
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
    
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float lightDot = max(dot(normal, lightDir), 0.0);
    vec3 directionalPointLight = (lightDot * pointLight.diffuseIntensity * material.diffuse * attenuation) * pointLight.color;
    
    vec3 ambientPointLight = (material.ambient * pointLight.ambientIntensity) * pointLight.color;
    vec3 viewDir = normalize(cameraPosition - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularPointLight = (material.specular * pointLight.specularIntensity * spec * attenuation) * pointLight.color;
    
    vec3 pointLight = ambientPointLight + directionalPointLight + specularPointLight;
    return pointLight;
}

void main()
{
    vec3 sunLight = calculateSunLight(Normal, FragPos);
    
    vec3 pointLight = calculatePointLight(Normal, FragPos);
    
    vec3 flashLight = calculateFlashLight(Normal, FragPos);
    
    vec3 textureColor = texture(textureSampler, TexCoord).rgb;
    float textureAlpha = texture(textureSampler, TexCoord).a;

    FragColor = vec4((sunLight + pointLight + flashLight) * textureColor, textureAlpha);
}


