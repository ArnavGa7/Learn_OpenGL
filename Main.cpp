#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Texture.h"
#include "Camera.h"
#include "Object.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderClass.h"
#include "Cube.h"
#include "Model.h"
#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>




// Main function of the Main File(C++)
int main(){
	// Window
	int window_witdh = 1920;
	int window_height = 1080;
	Window window(window_witdh, window_height, "First Person Shooter");
	Camera camera;
	
	camera.Postion = glm::vec3(0.0f, 0.0f, 2.0f);

	glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Load Glad
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0,0, window_witdh, window_height);
	glEnable(GL_DEPTH_TEST);

	// Create the Object + the Light Sorce
	Model Katana("Model/Katana/model.obj");
	Object light_sorce1(CubeVertices, CubeVerticesSize, CubeIndiecs, CubeIndiecsSize, "light.vert", "light.frag");


	Texture diffuse("Texture's/container2.png");
	Texture specular("Texture's/container2_specular.png");

	// Set The Position and the scale of the Light Sorce and the color for the cube
	Shader shader("default.vert", "default.frag");

	light_sorce1.Position = glm::vec3(0.7f, 0.2f, -30.0f);
	light_sorce1.Color = glm::vec3(1.0f,1.0f, 1.0f);
	light_sorce1.Scale = glm::vec3(0.5f);





	// While Loop
	while (!window.WindowShouldClose()) {

	
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double xpos, ypos;
		glfwGetCursorPos(window.window, &xpos, &ypos);

		// Runs the game in 60 FPS(I hope so)
		float currentTime = (float)glfwGetTime();
		camera.deltaTime = currentTime - camera.LastTime;
		camera.LastTime = currentTime;

		// Keybourd + the mosude Movements functions
		camera.ProssecInput(window.window);
		camera.Mouse_CallBack(window.window, xpos, ypos);

		// Set the settings for The View Matrix(Camera Matrix) and add a Model Matrix
	

		glm::mat4 view = glm::lookAt(camera.Postion, camera.Postion + camera.Forward, camera.Up);
		// Set the settings for the Projeection Matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(window_witdh / (float)window_height), 0.1f, 100.0f);

		
	
		// Bind Texture
		diffuse.Bind(GL_TEXTURE0);
		specular.Bind(GL_TEXTURE1);
		Katana.Draw(shader, view, projection);

		light_sorce1.Draw(view, projection, light_sorce1.Color, light_sorce1.Position,camera.Postion);
	
	
		// The Swap Buffer
		window.SwapBuffers();
		// The PollEevnts
		window.PollEvents();
	}


	// Return 0 of the Int main Function
	return 0;
}