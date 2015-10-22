uniform sampler2D texture;

void main() {
  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
  vec4 ambient = vec4(12, 13, 69, 0.8);

  gl_FragColor = gl_Color * pixel * 0.5;
}