#version 400

in vec3 vPosition;
in vec2 vUV;
in vec3 vNormal;

in vec3 csEyeDirection;
in vec3 csLightDirection;
in vec3 tsEyeDirection;
in vec3 tsLightDirection;

out vec3 out_Color;

uniform sampler2D txDiffuse;
uniform sampler2D txNormal;
uniform sampler2D txSpecular;

uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform float uLightPower;

uniform vec3 uMaterialDiffuse;
uniform vec3 uMaterialAmbient;
uniform vec3 uMaterialSpecular;

void main(void){

	//Calculate material colors from textures and specular map
	vec3 mDiffuseColor = uMaterialDiffuse * texture(txDiffuse, vUV).rgb;
	vec3 mAmbientColor = uMaterialAmbient * mDiffuseColor;
	vec3 mSpecularColor = uMaterialSpecular * texture(txSpecular, vUV).rgb;

	//Calculate tangent space normal from normal map
	vec3 tsNormal = normalize(texture(txNormal, vec2(vUV.x,-vUV.y)).rgb * 2.0 - 1.0);
	
	//Calculate distance from light to vertex position
	float distance = length(uLightPos - vPosition);

	//Calculate angle between normal and light direction
	vec3 n = tsNormal;
	vec3 l = normalize(tsLightDirection);
	float cosTheta = clamp(dot(n, l), 0, 1);

	//Calculate angle between eye direction and reflection
	vec3 e = normalize(tsEyeDirection);
	vec3 r = reflect(-l, n);
	float cosAlpha = clamp(dot(e, r), 0, 1);

	//Set vertex color
	out_Color = 
		//Add ambient color
		mAmbientColor +
		//Calculate diffuse color
		mDiffuseColor * uLightColor * uLightPower * cosTheta / (distance*distance) +
		//Calculate specular color
		mSpecularColor * uLightColor * uLightPower * pow(cosAlpha,5) / (distance*distance);
}