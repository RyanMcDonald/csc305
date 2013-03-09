#version 150

in vec4 vColor;
out vec4 fColor;

in vec3 position;
in vec3 lightDirection;
in vec3 viewDirection;
in vec4 texCoord;

uniform vec3 lightPos; // Light position in eye coords
uniform vec4 lightCol;

uniform sampler2D colormap;
uniform sampler2D bumpmap;

vec3 Ka;
vec3 Kd;
vec3 Ks;
vec3 lightIntensity = vec3(0.5, 0.5, 0.5);
float shininess = 2.0;
vec3 textureColor;

vec3 ads(vec3 norm, vec3 diffR)
{
    // reflection direction
    vec3 r = reflect(-lightDirection, norm);

    vec3 ambient = lightIntensity * Ka;

    float sDotN = max( dot(lightDirection, norm), 0.0);

    vec3 diffuse = lightIntensity * diffR * sDotN;

    vec3 specular = vec3(0.0);
    if (sDotN > 0.0)
        specular = lightIntensity * Ks * pow( max( dot(r, viewDirection), 0.0 ), shininess);

    return ambient + diffuse + specular;
}

void main()
{
    vec4 normal = texture(bumpmap, texCoord.xy);

    vec4 texColor = texture(colormap, texCoord.xy);
    Ka = vec3(texColor); // Ambient reflectivity
    Ks = vec3(texColor); // Specular reflectivity

    //fColor = vec4(ambient + diffuse, 1.0) * lightCol * texture(colormap, texCoord.xy) + vec4(specular, 1.0);
    fColor = vec4(ads(normal.xyz, texColor.rgb), 1.0);
}
