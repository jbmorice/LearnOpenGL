#version 330 core
in vec3 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D mainTexture;

void main()
{
//  FragColor = vec4(texCoord.x, texCoord.y, 0.0f, 1.0f);
  FragColor = texture(mainTexture, texCoord);
}
