#version 330 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D mainTexture;
uniform sampler2D secondaryTexture;

void main()
{
  // FragColor = vec4(texCoord.x, texCoord.y, 0.0f, 1.0f);
  // FragColor = texture(mainTexture, texCoord) * vec4(vertexColor, 1.0f);
  FragColor = mix(texture(mainTexture, texCoord), texture(secondaryTexture, texCoord), 0.2f);
}
