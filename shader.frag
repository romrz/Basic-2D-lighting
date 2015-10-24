uniform sampler2D texture;

uniform float time;
//uniform vec2 position;

void main() {
  vec2 mouse = vec2(500, 400);
  vec2 pos = mouse/vec2(800, 600);

  float x = time/800.0;

  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

  vec4 ambientColor = vec4(0.5, 0.5, 1.0, 1.0);

  vec3 ambient = ambientColor.rgb *ambientColor.a;

  float value = smoothstep(x-0.3, x+0.3, gl_FragCoord.xy/vec2(800, 600));
  vec3 intensity = ambient + vec3(value);

  
  vec4 final = mix(vec4(0.0, 0.0, 0.0, 1.0), pixel, clamp(1.0-value, 0.1, 1.0));
  //vec3 final = gl_Color.rgb * pixel.rgb * intensity;

  gl_FragColor = final;
}