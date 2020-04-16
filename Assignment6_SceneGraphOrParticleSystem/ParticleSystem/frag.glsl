#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
// And our normal
in vec3 norm;
// And our fragment position for lighting
in vec3 fragPos;

// We always define a fragment color that we output.
out vec4 fragColor;

// Define our light(s)
struct PointLight {
    vec3 color;
    vec3 position;
    
    float ambientIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {
    vec3 color;
    vec3 direction;
    
    float ambientIntensity;
    float specularIntensity;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


// Maintain our uniforms.
uniform sampler2D tex;              // our primary texture
uniform mat4 view;                  // we need the view matrix for highlights
uniform PointLight pointLights[3];  // Our lights

vec3 CalcLights(PointLight light, vec3 normal, vec3 fragPos, bool isSpecular)
{ 
    vec3 obj;
    obj = vec3(1, 1, 1);

    //stores the final texture color
    vec3 diffColor;
    diffColor = texture(tex, texCoords).rgb;

    if (!isSpecular)
    {
        obj = diffColor;
    }

    // computes ambient lighitng
    light.ambient = light.ambientIntensity * diffColor;

    // computes diffuse lighting
    vec3 lightDir = normalize(light.position - fragPos);
    float diffImpact = max(dot(normal, lightDir), 0.0);
    light.diffuse = diffImpact * light.color;

    //computes specular lighting
    vec3 viewPos = vec3(0.0,0.0,0.0);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    light.specular = light.specularIntensity * spec * light.color;

    vec3 Lighting = light.diffuse + light.ambient + light.specular;
    
    return obj * Lighting;
    
}   

void main() {
  vec3 N = normalize(norm);

  //loop for multiple lights
  vec3 lights = vec3(0.0);

  // do the same for all lights
  lights += CalcLights(pointLights[0], N, fragPos, false);
  //lights += CalcLights(pointLights[1], N, fragPos, false);
 // lights += CalcLights(pointLights[2], N, fragPos, false);

  	

  fragColor = vec4(lights, 1.0);
  
}