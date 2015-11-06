uniform sampler2D texture;
uniform vec2 resolution;
uniform vec2 mouse;
uniform vec2 time;

uniform vec4 ambientData;
uniform vec4 lightData;
uniform vec2 lightSize;

void main() {
  vec2 position = mouse/resolution.xx;

  float maxDistance = lightSize + 0.015*sin(time.x);
  float distance = distance(gl_FragCoord.xy/resolution.xx, position);
  float value = 1.0 - smoothstep(-0.2, maxDistance, distance);
  
  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

  vec3 ambient = pixel.rgb * ambientData.rgb * ambientData.a;
  vec3 light = lightData.rgb * lightData.a * clamp(value, 0.0, 1.0);
  
  vec3 intensity = ambient + light;
  vec3 final = pixel.rgb * intensity;

  gl_FragColor = vec4(final, 1.0);
}