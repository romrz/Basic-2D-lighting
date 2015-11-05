uniform sampler2D texture;
uniform float time;

uniform vec2 mouse;

void main() {
  vec2 resolution = vec2(800.0, 800.0);
  vec2 position = mouse/resolution;

  float min = -0.05;
  float max = 0.25 + 0.01*sin(length(position)*100);
  float distance = distance(gl_FragCoord.xy/resolution, position);
  float value = 1.0 - smoothstep(min, max, distance);
  
  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

  vec3 ambientColor = vec3(0.3, 0.3, 0.7);
  float ambientIntensity = 0.5;
  vec3 ambient = pixel.rgb * ambientColor * ambientIntensity;
  
  vec3 lightColor = vec3(1,0.8,0.2);
  float lightIntensity = 1.5;
  vec3 light = lightColor * lightIntensity * clamp(value, 0.0, 1.0);
  
  vec3 intensity = ambient + light;
  vec3 final = pixel.rgb * intensity;

  gl_FragColor = vec4(final,1.0);
}