#version 150

in vec4 vColor;
out vec4 fColor;

in vec3 position;
in vec3 newNormal;

uniform vec3 lightPos;
uniform vec4 lightCol;

vec3 Ka;
vec3 Kd;
vec3 Ks;
vec3 lightIntensity = vec3(0.5, 0.5, 0.5);
float shininess = 2;

vec3 ads()
{
    // surface normal
    vec3 n = normalize(newNormal);

    // light source direction
    vec3 s = normalize(lightPos - position);

    // view direction
    vec3 v = normalize(-position);

    // reflection direction
    vec3 r = reflect(-s, n);

    return lightIntensity * vec3(vColor) * (Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(r,v), 0.0), shininess));
}

void main()
{
    Ka = vec3(vColor); // Ambient reflectivity
    Kd = vec3(vColor); // Diffuse reflectivity
    Ks = vec3(vColor); // Specular reflectivity

    //vec3 La = vec3(lightCol);
    //vec3 Ld = vec3(lightCol);
    //vec3 Ls = vec3(1.0, 1.0, 1.0);

    fColor = vec4(ads(), 1.0) * lightCol;
}
