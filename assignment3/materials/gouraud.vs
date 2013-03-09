#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;

in vec3 vertex;
in vec4 color;
in vec3 normal;
in vec4 texcoord0;

out vec4 vColor;

out vec3 lightIntensity;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec4 lightCol;

// Phone Shading Model:
// Ia + Id + Is
// Ia = La * Ka
// Id = Ld * Kd * (s dot n)
// Is = Ls * Ks(r dot v)^f
// r = -s + 2(s dot n) * n
// f = value chosen between 1 and 200
void main()
{
	vec4 position = modelMatrix * vec4(vertex, 1.0);
        //gl_Position = projectionMatrix * viewMatrix * position;

        vColor = color;

        vec3 Ka = vec3(color);
        vec3 Kd = vec3(color);
        vec3 Ks = vec3(color);
        vec3 La = vec3(lightCol);
        vec3 Ld = vec3(lightCol);
        vec3 Ls = vec3(1.0, 1.0, 1.0);
        float shininess = 2.0;

        vec3 tnorm = normalize( normalMatrix * normal );

        // Direction towards the light source
        vec3 s = normalize(vec3(vec4(lightPos, 1.0) - position));

        // viewing direction
        vec3 v = normalize(vec3(-position.xyz));

        vec3 r = reflect( -s, tnorm );

        vec3 ambient = La * Ka;

        float sDotN = max( dot(s, tnorm), 0.0);
        vec3 diffuse = Ld * Kd * sDotN;

        vec3 spec = vec3(0.0);

        //if (sDotN > 0.0)
            spec = Ls * Ks * pow( max( dot(r, v), 0.0), shininess );

        lightIntensity = ambient + diffuse + spec;

        // Convert position to clip coordinates and pass along
        gl_Position = projectionMatrix * viewMatrix * position;

}
