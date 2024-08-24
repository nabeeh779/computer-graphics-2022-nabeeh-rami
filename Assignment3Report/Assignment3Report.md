# Assignment 3:
### 1) before this part,We used this function to render the obj, and now we render the obj using OpenGL, this feature create identifier for an opengl texture and vertex array, also create a buffer to save our statistics and all of the  information we want for drawing. Briefly this function Attend to us all the things that we will need to render in OPENGL, (the buffers, VAO,…) and maps the pixels to the texture coordinates.
void Renderer::InitOpenGLRendering():

## Vertex shader:
~~~    				
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;
void main()
{
	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec3(model * vec4(pos, 1.0f));
	fragNormal = mat3(model) * normal;
	gl_Position = projection * view *  model * vec4(pos, 1.0f);
}
~~~

##  Fragment shade:
~~~
#version 330 core
struct Material
{
	sampler2D textureMap;
	// You can add more fields here...
	// Such as:
	//	1. diffuse/specular relections constants
	//	2. specular alpha constant
	//	3. Anything else you find relevant
};
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
// The final color of the fragment (pixel)
out vec4 frag_color;
void main()
{
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
	frag_color = vec4(0.5,0.5,0.5,1);
}
~~~

## 4. fragment shader:
~~~
 #version 330 core
struct Material
{
	sampler2D textureMap;
};
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
out vec4 frag_color;
void main()
{
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
	frag_color = vec4(0.5,0.5,0.5,1);
}
~~~

### 5. render:

void Renderer::Render( Scene& scene)
{
	int cameraCount = scene.GetCameraCount();
	if (cameraCount > 0)
	{
		int modelCount = scene.GetModelCount();
		const Camera& camera = scene.GetActiveCamera();
		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
		{	
			std::shared_ptr<MeshModel> currentModel = scene.GetModel(currentModelIndex);
			colorShader.use();
			colorShader.setUniform("model", currentModel->Get_transmatrix());
			colorShader.setUniform("view", camera.Get_Lookat() * camera.Get_Invtransmatrix());
			colorShader.setUniform("projection", camera.GetProjectionTransformation());
			colorShader.setUniform("material.textureMap", 0);

mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(currentModel->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
			glBindVertexArray(0);
			colorShader.setUniform("color", glm::vec3(0, 0, 0));
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBindVertexArray(currentModel->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
			glBindVertexArray(0);
		}
	}
}

### 6)Implement Phong shading :

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/SC1.png)

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/SC2.png)

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/SC3.png)

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/SC4.png)

### 7. Implement texture: 
#### cylinder texture:
![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/Cylindrical.png)
#### plane texture:
![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/teapot.JPG)


### Toon shading:
##### right of the model and closer than the model:

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/toonemapping1.jpeg)
##### edge of the model with 10 different layers of intensity.

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A3/toonemapping2.jpeg)

