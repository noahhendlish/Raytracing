#version 150

in  vec4 vPosition;
in  vec3 vNormal;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat3 NormalMatrix;

out vec4 pos;
out vec4 N;


void main()
{
  
  // Transform vertex normal into eye coordinates
  N = vec4(normalize(NormalMatrix*vec3(vNormal)), 0.0);
    // N = NormalMatrix*vec4(vNormal, 0.0); N.w = 0.0;
    // N = normalize(N);
  
  // Transform vertex position into eye coordinates
  pos = ModelView * vPosition;
  gl_Position = Projection * pos;


}
