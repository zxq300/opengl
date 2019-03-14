#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirectionLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4//点光源的个数

in vec3 FragPosition;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPosition;
uniform DirectionLight directionLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];//多个点光源
uniform SpotLight spotLight;
uniform Material material;

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDirection = normalize(viewPosition - FragPosition);
	vec3 result = CalcDirectionLight(directionLight, norm, viewDirection);
	int i = 0;
	for(i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], norm, FragPosition, viewDirection);
	}
	result += CalcSpotLight(spotLight, norm, FragPosition, viewDirection);
	color = vec4(result, 1.0);
}

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-light.direction);
	float diff = max(dot(normal, lightDirection), 0.0);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	vec3 diffuseTexture = vec3(texture(material.diffuse, TexCoords));
	vec3 specularTexture = vec3(texture(material.specular, TexCoords));
	vec3 emissionTexture = vec3(texture(material.emission, TexCoords));

	vec3 ambient = light.ambient * diffuseTexture;
	vec3 diffuse = light.diffuse * diff * diffuseTexture;
	vec3 specular = light.specular * spec * specularTexture;
	vec3 emission = emissionTexture;

	vec3 result = ambient + diffuse + specular + emission;

	return result;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - fragPosition);
	float diff = max(dot(normal, lightDirection), 0.0);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	float distance = length(light.position - fragPosition);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 diffuseTexture = vec3(texture(material.diffuse, TexCoords));
	vec3 specularTexture = vec3(texture(material.specular, TexCoords));
	vec3 emissionTexture = vec3(texture(material.emission, TexCoords));

	vec3 ambient = light.ambient * diffuseTexture;
	vec3 diffuse = light.diffuse * diff * diffuseTexture;
	vec3 specular = light.specular * spec * specularTexture;
	vec3 emission = emissionTexture;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular + emission;

	return result;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - fragPosition);
	float diff = max(dot(normal, lightDirection), 0.0);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	float distance = length(light.position - fragPosition);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 diffuseTexture = vec3(texture(material.diffuse, TexCoords));
	vec3 specularTexture = vec3(texture(material.specular, TexCoords));
	vec3 emissionTexture = vec3(texture(material.emission, TexCoords));

	vec3 ambient = light.ambient * diffuseTexture;
	vec3 diffuse = light.diffuse * diff * diffuseTexture;
	vec3 specular = light.specular * spec * specularTexture;
	vec3 emission = emissionTexture;

	ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    vec3 result = ambient + diffuse + specular + emission;

    return result;
}