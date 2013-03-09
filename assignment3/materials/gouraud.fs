#version 150

in vec4 vColor;
out vec4 fColor;

in vec3 lightIntensity;

void main()
{
   //fColor = vColor;
   fColor = vec4(lightIntensity, 1.0);
}
