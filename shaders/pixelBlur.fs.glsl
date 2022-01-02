#version 330 core


out vec4 color;

uniform sampler2D TEX_C;
uniform sampler2D TEX_VL;

uniform int S;


void main() {
    vec2  pos                 = gl_FragCoord.xy;
    ivec2 iPos                = ivec2(pos);

    vec2 vX                   = texelFetch(TEX_VL, iPos, 0).xy;           /* Pixel Velocity */
    vec3 currentColor         = texelFetch(TEX_C, iPos, 0).rgb; /* Pixel Color */

    if (length(vX) < 0.005){
        color = vec4(currentColor, 1.0);
        return;
    }

    vec3 sum        = vec3(0);
    vec2 t          = vX / float(S);

    for (int i = 0; i < S; i++){
        vec2 Y   = floor(pos - t * i);
        ivec2 iY = ivec2(Y);

        vec3 cY  = texelFetch(TEX_C, iY, 0).rgb;
        sum += cY;
    }

    color = vec4(sum / S, 1.0);
};
