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
	// Se a textura n�o for nula, ent�o a cor do material � a cor da textura.
	//diffuseColor = texture(cubeMap, textureVector).rgb;
	// Sen�o
	diffuseColor = material.diffuse;

	// C�lculo da componente emissiva do material.
	vec4 emissive = vec4(material.emissive, 1.0);

	// Luz Ambiente Global
	vec4 ambient;

	// C�lculo do efeito da ilumina��o no fragmento.
	vec4 light[4];
	vec4 ambientTmp;
	// Contribui��o da fonte de luz ambiente
	ambient = calcAmbientLight(ambientLight);
	// Contribui��o da fonte de luz direcional
	ambient += ambientTmp;
	// Contribui��o da fonte de luz c�nica
	ambient += ambientTmp;

	// C�lculo da cor final do fragmento.
	// Com CubeMap
	//fColor = emissive + (ambient/4) + light[0] + light[1] + light[2] + light[3];
	// Com cor de fragmento
	fColor = emissive + (ambient/4);
}

vec4 calcAmbientLight(AmbientLight light) {
	// C�lculo da contribui��o da fonte de luz ambiente global, para a cor do objeto.
	vec4 ambient = vec4(material.ambient * light.ambient, 1.0);
	return ambient;
}