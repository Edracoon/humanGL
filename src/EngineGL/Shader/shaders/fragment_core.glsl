#version 330 core
out vec4 FragColor;
in vec3 ourColor; 
in vec2 TexCoord;

uniform bool	  tex;
uniform sampler2D ourTexture;

void main() {
	if (tex) {
    	FragColor = texture(ourTexture, TexCoord);
	} else {
    	FragColor = vec4(ourColor, 1.0);
	}
}