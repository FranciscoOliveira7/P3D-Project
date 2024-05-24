#version 440 core

uniform mat4 View;
uniform mat4 ModelView;		// View * Model

//uniform samplerCube cubeMap;

// Estrutura da fonte de luz ambiente global
struct AmbientLight {
	vec3 ambient;	// Componente de luz ambiente global
};

uniform AmbientLight ambientLight; // Fonte de luz ambiente global

struct Material{
	vec3 emissive;
	vec3 ambient;		// Ka
	vec3 diffuse;		// kd
	vec3 specular;		// ke
	float shininess;
};

uniform Material material;
vec3 diffuseColor;

in vec3 vPositionEyeSpace;
in vec3 vNormalEyeSpace;
in vec3 textureVector;

layout (location = 0) out vec4 fColor; // Cor final do fragmento

vec4 calcAmbientLight(AmbientLight light);

void main()
{
	// Cor do Material
	// Se a textura não for nula, então a cor do material é a cor da textura.
	//diffuseColor = texture(cubeMap, textureVector).rgb;
	// Senão
	diffuseColor = material.diffuse;

	// Cálculo da componente emissiva do material.
	vec4 emissive = vec4(material.emissive, 1.0);

	// Luz Ambiente Global
	vec4 ambient;

	// Cálculo do efeito da iluminação no fragmento.
	vec4 light[4];
	vec4 ambientTmp;
	// Contribuição da fonte de luz ambiente
	ambient = calcAmbientLight(ambientLight);
	// Contribuição da fonte de luz direcional
	ambient += ambientTmp;
	// Contribuição da fonte de luz cónica
	ambient += ambientTmp;

	// Cálculo da cor final do fragmento.
	// Com CubeMap
	//fColor = emissive + (ambient/4) + light[0] + light[1] + light[2] + light[3];
	// Com cor de fragmento
	fColor = emissive + (ambient/4);
}

vec4 calcAmbientLight(AmbientLight light) {
	// Cálculo da contribuição da fonte de luz ambiente global, para a cor do objeto.
	vec4 ambient = vec4(material.ambient * light.ambient, 1.0);
	return ambient;
}