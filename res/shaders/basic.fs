#version 410 core

out vec4 FragColor;

/* in vec2 TexCoord; */

/* uniform struct Material { */
/*     sampler2D diffuse0; */
/*     sampler2D specular0; */
/* } material; */

uniform vec3 color;

void main() {
    FragColor = vec4(color, 1.0f);
    /* FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); */
    /* FragColor = texture(material.diffuse0, TexCoord); */
}

