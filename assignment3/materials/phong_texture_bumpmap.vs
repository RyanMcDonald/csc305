#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;

uniform mat3 normalMatrix;

uniform vec3 lightPos;
uniform vec4 lightCol;

in vec3 vertex;
in vec4 color;
in vec3 normal;
in vec4 texcoord0;

out vec4 vColor;

out vec3 position;

out vec4 texCoord;
out vec3 lightDirection;
out vec3 viewDirection;

void main()
{
        // Transform normal and tangent to eye space
        vec3 norm = normalize(normalMatrix * normal);

        // Approximate the tangent vector
        vec4 vertexTangent;
        vec3 c1 = cross(norm, vec3(0.0, 0.0, 1.0));
        vec3 c2 = cross(norm, vec3(0.0, 1.0, 0.0));
        if (length(c1) > length(c2))
        {
            vertexTangent = vec4(c1, 1.0);
        }
        else
        {
            vertexTangent = vec4(c2, 1.0);
        }

        vec3 tang = normalize(normalMatrix * vec3(vertexTangent));

        // Compute the binormal
        vec3 binormal = normalize( cross( norm, tang ) ) * vertexTangent.w;

        // Create the matrix that transforms to tangent space
        mat3 toObjectLocal = mat3(
            tang.x, binormal.x, norm.x,
            tang.y, binormal.y, norm.y,
            tang.z, binormal.z, norm.z );

        // Get the position in eye coordinates
        position = vec3(modelMatrix * vec4(vertex, 1.0));

        // Transform light direction and view direction to tangent space
        lightDirection = normalize(toObjectLocal * (lightPos.xyz - position));
        viewDirection = toObjectLocal * normalize(-position);

        // Pass along the texture coordinate
        texCoord = texcoord0;

        gl_Position = projectionMatrix * viewMatrix * vec4(vertex, 1.0);
}
