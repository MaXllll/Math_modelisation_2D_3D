

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ESGIShader.h"

#include <vector>


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 1200, HEIGHT = 800;

//Grid dimensions
const GLuint GRID_W = 10, GRID_H = 10;


EsgiShader basicShader;


// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);


	basicShader.LoadVertexShader("basic.vs"); // vs or vert
	basicShader.LoadFragmentShader("basic.fs");
	basicShader.Create();
	// Set up vertex data (and buffer(s)) and attribute pointers
	//GLfloat vertices[] = {
	//	-1.f, -1.f, 1.0f,		// 0
	//	1.f, -1.f, 1.0f,  		// 1	
	//	1.f, 1.f, 1.0f,			// 2
	//	-1.f, 1.f, 1.0f,		// 3	
	//	-1.f, -1.f, -1.0f,		// 4
	//	1.f, -1.f, -1.0f,		// 5
	//	1.f, 1.f, -1.0f,		// 6
	//	-1.f, 1.f, -1.0f		// 7
	//};

	//GLuint indices[] = {  // Note that we start from 0!
	//	0, 1, 2, // avant
	//	2, 3, 0,
	//	3, 2, 6, // haut
	//	6, 7, 3,
	//	7, 6, 5, // arriere
	//	5, 4, 7,
	//	1, 5, 6, // droite
	//	6, 2, 1,
	//	4, 0, 3, // gauche
	//	3, 7, 4,
	//	4, 5, 1, // bas
	//	1, 0, 4
	//};

	//GLfloat vertices[] = {
	//	1.f, 1.f, 0.0f,  // Top Right
	//	1.f, 0.5f, 0.0f,  // Bottom Right
	//	0.5f, 0.5f, 0.0f,  // Bottom Left
	//	0.5f, 1.f, 0.0f,   // Top Left
	//	1.f, 0.0f, 0.0f,  
	//	0.5f, 0.f, 0.0f,   
	//};
	//GLuint indices[] = {  // Note that we start from 0!
	//	0, 1, 3,   // First Triangle
	//	1, 2, 3,   // Second Triangle
	//	1, 4, 2,
	//	4, 5, 2
	//};

	GLfloat vertices[] = {
		0.f, 0.f, 0.0f,
		0.5f, 0.f, 0.0f,
		0.f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,

	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 2, 3, 1
	};

	std::vector<GLfloat> vertices2 = std::vector<GLfloat>();
	std::vector<GLuint> indices2 = std::vector<GLuint>();

	float incrementW = 0.3f;
	float incrementH = 0.3f;

	//float increment = GRID_H >= GRID_W?

	//float incrementW = 3.f / GRID_W;
	//float incrementH = 3.f / GRID_W;

	for (float i = 0.f; i <= GRID_W; i += 1.f)
	{
		for (float j = 0.f; j <= GRID_H; j += 1.f)
		{
			vertices2.push_back(j * incrementW);
			vertices2.push_back(i * incrementH);
			vertices2.push_back(0.f);
		}
	}

	for (float i = 0.f; i < GRID_W; i += 1.f)
	{
		for (float j = 0.f; j < GRID_H; j += 1.f)
		{
			if (j == 0.f)
			{
				//x2 cause Degenerate triangle
				indices2.push_back((GRID_H + 1) * i);
				indices2.push_back((GRID_H + 1) * i);

				indices2.push_back((GRID_H + 1) * (i + 1));
				indices2.push_back((GRID_H + 1) * i + 1);
			}
			else
			{
				indices2.push_back((GRID_H + 1) * (i + 1) + j);
				indices2.push_back((GRID_H + 1) * i + j + 1);
				
			}
			//End of the line
			if (j == GRID_H - 1)
			{
				//x2 cause Degenerate triangle
				indices2.push_back((GRID_H + 1) * (i + 1) + j + 1);
				indices2.push_back((GRID_H + 1) * (i + 1) + j + 1);
			}
		}
	}

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), &vertices2.front(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(float), &indices2.front(), GL_STATIC_DRAW);
	//glBufferDakta(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Unbind VAO

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate shader
		basicShader.Bind();

		// Create transformations
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		model = glm::rotate(model, /*(GLfloat)glfwGetTime() **/ 1.0f, glm::vec3(0.5f, 0.0f, 0.0f));  
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(basicShader.GetProgram(), "model");
		GLint viewLoc = glGetUniformLocation(basicShader.GetProgram(), "view");
		GLint projLoc = glGetUniformLocation(basicShader.GetProgram(), "projection");
		// Pass them to the shaders
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw container
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLE_STRIP, vertices2.size(), GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLE_STRIP, indices2.size(), GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

