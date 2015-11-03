
uniform sampler2D texture;
//uniform float time;
//uniform float xx;

uniform vec2 mouse;

void main() {
  vec2 resolution = vec2(800.0, 800.0);
  vec2 position = mouse/resolution;

  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

  vec4 ambientColor = vec4(0.15, 0.15, 0.30, 1.0);

  float min = -0.05;
  float max = 0.25 ;//+ 0.01*sin(length(position)*100);
  float distance = distance(gl_FragCoord.xy/resolution, position);
  float value = 1.0 - smoothstep(min, max, distance);

//  float intensity = 0.9;
//  vec4 ambient = mix(pixel, ambientColor, intensity);
  vec3 ambient = pixel.rgb * vec3(0.3, 0.3, 0.7) * 0.5;
//  vec4 ambient = pixel + vec4(0.2,0.2,0.2,1);
//  vec3 ambient = (pixel.rgb + vec3(0,0,0))/2.0;
//  vec3 ambient = pixel.rgb * 3;
//  vec3 ambient = mix(pixel.rgb, vec3(1,1,1), 0.1);
  
  vec3 lightColor = vec3(1.0,1.0,0.3) * 2;
  vec3 light = lightColor * clamp(value, 0.0, 1.0);
  vec3 intensity = ambient + light;
  vec3 final = pixel.rgb * intensity;
//  vec3 final = mix(ambient, mix(pixel,lightColor,0.5), clamp(value, 0.0, 1.0));

  gl_FragColor = vec4(final,1.0);
}