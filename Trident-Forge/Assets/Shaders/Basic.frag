#version 430 core

in vec3 v_FragPos;
in vec3 v_Normal;
in vec4 v_Color;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

out vec4 FragColor;

void main()
{
    // Configurable properties
    vec3 ambientColor = vec3(0.1);
    vec3 lightColor   = vec3(1.0);
    float shininess   = 64.0;
    float specStrength = 0.6;

    // Normalize inputs
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    // Components
    vec3 ambient  = ambientColor * lightColor;
    float diff    = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = diff * lightColor;
    float spec    = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specStrength * spec * lightColor;

    vec3 lighting = (ambient + diffuse + specular) * v_Color.rgb;
    FragColor = vec4(lighting, v_Color.a);
}