#version 330

uniform sampler2D texture; //texture to change

void main() {
  vec2 coords = gl_TexCoord[0].xy;
  vec3 normalColor = texture2D(texture, coords).rgb; //original color

  gl_FragColor = vec4(normalColor.r, normalColor.g, normalColor.b, 1);
}