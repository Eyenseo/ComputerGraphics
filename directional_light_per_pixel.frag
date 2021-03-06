#version 120
varying vec4 diffuse, ambient;
varying vec3 normal, halfVector;
void main() {
  vec3 n, halfV, lightDir;
  float NdotL, NdotHV;
  lightDir = vec3(gl_LightSource[2].position);

  vec4 color = ambient;
  n = normalize(normal);
  NdotL = max(dot(n, lightDir), 0.0);

  if(NdotL > 0.0) {
    color += diffuse * NdotL;
    halfV = normalize(halfVector);
    NdotHV = max(dot(n, halfV), 0.0);
    color += gl_FrontMaterial.specular * gl_LightSource[2].specular * pow(NdotHV, gl_FrontMaterial.shininess);
  }
  gl_FragColor = color;
}
