uniform sampler2D texture;

uniform float time;

void main() {
  vec2 mouse = vec2(500, 400);
  vec2 pos = mouse/vec2(800, 600);

  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

  vec4 ambientColor = vec4(0.5, 0.5, 1.0, 1.0);

  vec3 ambient = ambientColor.rgb * abs(sin(time*0.1))*ambientColor.a;

  float value = step(0.5, gl_FragCoord.xy/vec2(800, 600));
  vec3 intensity = ambient + vec3(value);

  vec3 final = gl_Color.rgb * pixel.rgb * intensity;

  gl_FragColor = vec4(final, pixel.a);
}