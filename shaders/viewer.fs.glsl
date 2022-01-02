#version 330 core

in vec2 texCoord;

out vec4 color;

uniform int texType;
uniform sampler2D renderedTex;
uniform int mK;

uniform float cameraFar;
uniform float cameraNear;

float readDepth(ivec2 iPos){
	float z, f = cameraFar, n = cameraNear;
	z = texelFetch(renderedTex, iPos, 0).r;
	return (2.0 * n) / (f + n - z * (f - n));
}

void main() {
	switch(texType){
		case 0: case 1: case 6:/* MAIN, Color, Pixel Blur */
			color = texture(renderedTex, texCoord) ;
			break;
		case 2: /* DEPTH */
			float z = readDepth(ivec2(gl_FragCoord.xy));
			color = vec4(z,z,z,1.0);
			break;
		case 3: /* VELOCITY */
			vec3 vecVel = texture(renderedTex, texCoord).xyz;
			if(length(vecVel) == 0)
				color = vec4(0,0,0,0);
			else
				color = vec4(vecVel / 50 + vec3(0.5), 1.0);
			break;

		case 4: case 5: /* TILEMAX AND NEIGHBORMAX */
			ivec2 iPos = ivec2(gl_FragCoord.xy);
			vec3 vecNM = texelFetch(renderedTex, (iPos / mK), 0).rgb;

			if(length(vecNM) == 0)
				color = vec4(0,0,0,0);
			else
				color = vec4(vecNM / 50 + vec3(0.5), 0.5);
			break;

	}
};