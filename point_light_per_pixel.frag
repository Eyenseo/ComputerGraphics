#version 120
varying vec4 diffuse, ambientGlobal, ambient, ecPos;
varying vec3 normal, halfVector;

void main() {
  vec3 n, halfV, viewV, lightDir;
  float NdotL, NdotHV;
  vec4 color = ambientGlobal;
  float att, dist;

  n = normalize(normal);
  lightDir = vec3(gl_LightSource[0].position - ecPos);
  dist = length(lightDir);
  NdotL = max(dot(n, normalize(lightDir)), 0.0);

  if(NdotL > 0.0) {
    att = 1.0 / (gl_LightSource[0].constantAttenuation + gl_LightSource[0].linearAttenuation * dist + gl_LightSource[0].quadraticAttenuation * dist * dist);
    color += att * (diffuse * NdotL + ambient);
    halfV = normalize(halfVector);
    NdotHV = max(dot(n, halfV), 0.0);
    color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV, gl_FrontMaterial.shininess);
  }
  gl_FragColor = color;
}
