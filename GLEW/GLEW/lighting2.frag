 #version 330 core
 struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 color;

in vec3 Normal;
in vec3 FragPosition;

uniform vec3 viewPosition;

uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPosition);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = material.specular * diff * light.diffuse;

    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.specular;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}