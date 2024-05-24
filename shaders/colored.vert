#version 440 core

uniform mat4 View;
uniform mat4 ModelView;		// View * Model
uniform mat3 NormalMatrix;

layout(location = 0) in vec3 vPosition;			// Coordenadas locais do v�rtice
layout(location = 1) in vec3 vColors;			// Cores do v�rtice
layout(location = 3) in vec3 vNormal;			// Normal do v�rtice

out vec3 vPositionEyeSpace;
out vec3 vNormalEyeSpace;
out vec3 textureVector;

uniform mat4 MVP;

void main()
{ 
	// Posi��o do v�rtice em coordenadas do olho.
	vPositionEyeSpace = (ModelView * vec4(vPosition, 1.0)).xyz;

	// Transformar a normal do v�rtice.
	vNormalEyeSpace = normalize(NormalMatrix * vNormal);

	// Posi��o final do v�rtice (em coordenadas de clip)
	gl_Position = MVP * vec4(vPosition, 1.0f);
}
