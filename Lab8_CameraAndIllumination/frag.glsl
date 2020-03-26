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
uniform DirLight dirLight;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{ 

    vec3 lightDir = normalize(light.position - fragPos);
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(0, texCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(0, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(1, texCoords));
    
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}   

void main() {
  vec3 N = normalize(norm);
  
  vec3 diffuseColor = texture(tex, texCoords).rgb;

  //ambient light
  vec3 ambient = pointLights[0].ambientIntensity * pointLights[1].color;

  //diffuse light
  vec3 lightDir = normalize(pointLights[0].position - fragPos);
  float diffImpact = max(dot(norm, lightDir), 0.0);
  vec3 diffuseLight = diffImpact * pointLights[0].color;

  //Specular Lighting
  vec3 viewPos = vec3(0.0,0.0,0.0);
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, N);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = pointLights[0].specularIntensity * spec * pointLights[0].color;

  vec3 lighting = diffuseLight + ambient + specular;

  //loop for multiple lights
  vec3 output = vec3(0.0);

  // do the same for all point lights
  for(int i = 0; i < 3; i++)
  {
      output += CalcPointLight(pointLights[i], N, fragPos, viewDir);
  }
  	

  fragColor = vec4(output, 1.0);
  
}