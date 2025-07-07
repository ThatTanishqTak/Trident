#version 430 core

in vec3 v_FragPos;
in vec3 v_Normal;
in vec4 v_Color;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform vec3 u_LightColor;
uniform float u_LightIntensity;
uniform vec3 u_LightDirection;
uniform int u_LightType;
uniform float u_CutOff;
uniform float u_OuterCutOff;

out vec4 FragColor;

void main()
{
    // Configurable properties
    vec3 ambientColor = vec3(0.1);
    vec3 lightColor   = u_LightColor * u_LightIntensity;
    float shininess   = 64.0;
    float specStrength = 0.6;

    // Normalize inputs
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = u_LightType == 0 ? normalize(-u_LightDirection) : normalize(u_LightPos - v_FragPos);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    // Components
    vec3 ambient  = ambientColor * lightColor;
    float diff    = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = diff * lightColor;
    float spec    = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specStrength * spec * lightColor;

    float attenuation = 1.0;
    if (u_LightType != 0)
    {
        float distance = length(u_LightPos - v_FragPos);
        attenuation = 1.0 / (distance * distance);
    }
    if (u_LightType == 2)
    {
        float theta = dot(lightDir, normalize(-u_LightDirection));
        float epsilon = cos(radians(u_CutOff)) - cos(radians(u_OuterCutOff));
        float intensity = clamp((theta - cos(radians(u_OuterCutOff))) / epsilon, 0.0, 1.0);
        attenuation *= intensity;
    }

    vec3 lighting = (ambient + diffuse + specular) * attenuation * v_Color.rgb;
    FragColor = vec4(lighting, v_Color.a);
}