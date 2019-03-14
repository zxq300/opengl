 #version 330 core
 struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

out vec4 color;

in vec3 Normal;
in vec3 FragPosition;
in vec2 TexCoords;

uniform vec3 viewPosition;

uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDirection = normalize(light.position - FragPosition);//the drection from fragment to light
    vec3 emission = vec3(texture(material.emission, TexCoords));
    float theta = dot(lightDirection, normalize(-light.direction));
    vec3 result;
    if(theta <= light.outerCutOff)//cos
    {
        result = light.ambient * vec3(texture(material.diffuse, TexCoords)) + emission;
    }
    else if(theta > light.outerCutOff)
    {
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

        vec3 norm = normalize(Normal);
        
        vec3 lightDir = normalize(-light.direction);//the direction of light
        float diff = max(dot(norm, lightDirection), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

        vec3 viewDirection = normalize(viewPosition - FragPosition);
        vec3 reflectDirection = reflect(-lightDirection, norm);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
        vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoords));

        

        float distance = length(light.position - FragPosition);
        float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        //ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
        if(theta < light.cutOff)
        {
            float epsilon = light.cutOff - light.outerCutOff;
            float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
            diffuse *= intensity;
            specular *= intensity;
        }
        result = ambient + diffuse + specular + emission;
    }
    color = vec4(result, 1.0f);
}