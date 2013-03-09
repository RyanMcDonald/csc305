#version 150

in vec4 vColor;
out vec4 fColor;

in vec3 position;
in vec3 newNormal;
in vec4 texCoord;

uniform vec3 lightPos; // Light position in eye coords
uniform vec4 lightCol;
uniform sampler2D brickTexture;

vec3 Ka;
vec3 Kd;
vec3 Ks;
vec3 lightIntensity = vec3(0.5, 0.5, 0.5);
float shininess = 2.0;

void ads(out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
    // surface normal
    vec3 n = normalize(newNormal);

    // light source direction
    vec3 s = normalize(lightPos - position);

    // view direction
    vec3 v = normalize(-position);

    // reflection direction
    vec3 r = reflect(-s, n);

    //return lightIntensity * vec3(vColor) * (Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(r,v), 0.0), shininess));

    ambient = lightIntensity * Ka;
    diffuse = lightIntensity * Kd * max(dot(s, n), 0.0);
    specular = lightIntensity * Ks * pow( max( dot(r, v), 0.0 ), shininess);
}

void main()
{
    vec3 ambient, diffuse, specular;

    vec4 texColor = texture( brickTexture, texCoord.xy );

    //Ka = vec3(vColor); // Ambient reflectivity
    //Kd = vec3(vColor); // Diffuse reflectivity
    //Ks = vec3(vColor); // Specular reflectivity
    Ka = vec3(texColor); // Ambient reflectivity
    Kd = vec3(texColor); // Diffuse reflectivity
    Ks = vec3(texColor); // Specular reflectivity

    ads(ambient, diffuse, specular);

    //fColor = vec4(ads(), 1.0) * lightCol;
    fColor = vec4(ambient + diffuse, 1.0) * lightCol * texColor + vec4(specular, 1.0);
}
