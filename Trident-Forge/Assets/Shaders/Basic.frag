#version 430 core

in vec3 v_FragPos;
in vec3 v_Normal;
in vec4 v_Color;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

out vec4 FragColor;

void main()
{
    // Properties
    vec3 ambientColor = vec3(0.1);
    vec3 lightColor = vec3(1.0);

    // Ambient
    vec3 ambient = ambientColor * lightColor;

    // Diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 finalColor = (ambient + diffuse + specular) * v_Color.rgb;

    FragColor = vec4(finalColor, v_Color.a);
}