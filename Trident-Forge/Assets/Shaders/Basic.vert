#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_ViewProjection;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec4 v_Color;

void main()
{
    vec4 worldPosition = u_Model * vec4(a_Position, 1.0);
    v_FragPos = worldPosition.xyz;

    // Use normal matrix for correct normal transformation
    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    v_Normal = normalize(normalMatrix * a_Normal);

    v_Color = a_Color;

    gl_Position = u_ViewProjection * worldPosition;
}