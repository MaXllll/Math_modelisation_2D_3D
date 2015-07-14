

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
const GLuint GRID_W = 5, GRID_H = 5;


EsgiShader basicShader;

void knot(int n, int c, int x[])
{
	int nplusc, nplus2, i;

	nplusc = n + c;
	nplus2 = n + 2;

	x[1] = 0;
	for (i = 2; i <= nplusc; i++){
		if ((i > c) && (i < nplus2))
			x[i] = x[i - 1] + 1;
		else
			x[i] = x[i - 1];
	}
}

void basis(int c, float t, int npts, int x[], float n[])
{
	int nplusc;
	int i, k;
	float d, e;
	float temp[36];

	nplusc = npts + c;

	/*		printf("knot vector is \n");
	for (i = 1; i <= nplusc; i++){
	printf(" %d %d \n", i,x[i]);
	}
	printf("t is %f \n", t);
	*/

	/* calculate the first order basis functions n[i][1]	*/

	for (i = 1; i <= nplusc - 1; i++){
		if ((t >= x[i]) && (t < x[i + 1]))
			temp[i] = 1;
		else
			temp[i] = 0;
	}

	/* calculate the higher order basis functions */

	for (k = 2; k <= c; k++){
		for (i = 1; i <= nplusc - k; i++){
			if (temp[i] != 0)    /* if the lower order basis function is zero skip the calculation */
				d = ((t - x[i])*temp[i]) / (x[i + k - 1] - x[i]);
			else
				d = 0;

			if (temp[i + 1] != 0)     /* if the lower order basis function is zero skip the calculation */
				e = ((x[i + k] - t)*temp[i + 1]) / (x[i + k] - x[i + 1]);
			else
				e = 0;

			temp[i] = d + e;
		}
	}

	if (t == (float)x[nplusc]){		/*    pick up last point	*/
		temp[npts] = 1;
	}

	/* put in n array	*/

	for (i = 1; i <= npts; i++) {
		n[i] = temp[i];
	}
}

void bspline(int npts, int k, int p1, float b[], float p[])
{
	int i, j, icount, jcount;
	int i1;
	int x[30];		/* allows for 20 data points with basis function of order 5 */
	int nplusc;

	float step;
	float t;
	float nbasis[20];
	float temp;


	nplusc = npts + k;

	/*  zero and redimension the knot vector and the basis array */

	for (i = 0; i <= npts; i++){
		nbasis[i] = 0.;
	}

	for (i = 0; i <= nplusc; i++){
		x[i] = 0.;
	}

	/* generate the uniform open knot vector */

	knot(npts, k, x);

	/*
	printf("The knot vector is ");
	for (i = 1; i <= nplusc; i++){
	printf(" %d ", x[i]);
	}
	printf("\n");
	*/

	icount = 0;

	/*    calculate the points on the bspline curve */

	t = 0;
	step = ((float)x[nplusc]) / ((float)(p1 - 1));

	for (i1 = 1; i1 <= p1; i1++){

		if ((float)x[nplusc] - t < 5e-6){
			t = (float)x[nplusc];
		}

		basis(k, t, npts, x, nbasis);      /* generate the basis function for this value of t */
		/*
		printf("t = %f \n",t);
		printf("nbasis = ");
		for (i = 1; i <= npts; i++){
		printf("%f  ",nbasis[i]);
		}
		printf("\n");
		*/
		for (j = 1; j <= 3; j++){      /* generate a point on the curve */
			jcount = j;
			p[icount + j] = 0.;

			for (i = 1; i <= npts; i++){ /* Do local matrix multiplication */
				temp = nbasis[i] * b[jcount];
				p[icount + j] = p[icount + j] + temp;
				/*
				printf("jcount,nbasis,b,nbasis*b,p = %d %f %f %f %f\n",jcount,nbasis[i],b[jcount],temp,p[icount+j]);
				*/
				jcount = jcount + 3;
			}
		}
		/*
		printf("icount, p %d %f %f %f \n",icount,p[icount+1],p[icount+2],p[icount+3]);
		*/
		icount = icount + 3;
		t = t + step;
	}
}

void initializeGridBuffer() {
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), &vertices2.front(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(float), &indices2.front(), GL_STATIC_DRAW);
	//glBufferDakta(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Unbind VAO
}

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


	int i;
	int npts, k, p1;

	float b[31];  /* allows for up to 10  control vertices */
	float p[103];  /* allows for up to 100 points on curve */

	npts = 4;
	k = 2;     /* second order, change to 4 to get fourth order */
	p1 = 11;   /* eleven points on curve */

	for (i = 1; i <= 3 * npts; i++){
		b[i] = 0.;
	}

	for (i = 1; i <= 3 * p1; i++){
		p[i] = 0.;
	}


	/*
	Define the control polygon, Ex. 3.4 in the z=1 plane because
	this is three dimensional routine. x=b[1], y=b[2], z=b[3], etc.
	*/
	//b[1] = 0;
	//b[2] = 0;
	//b[3] = 0;
	//b[4] = 0;
	//b[5] = 2;
	//b[6] = 0;
	//b[7] = 2;
	//b[8] = 2;
	//b[9] = 0;
	//b[10] = 0;
	//b[11] = 2;
	//b[12] = 0;

	bspline(npts, k, p1, b, p);

	printf("\nPolygon points\n\n");

	for (i = 1; i <= 3 * npts; i = i + 3){
		printf(" %f %f %f \n", b[i], b[i + 1], b[i + 2]);
	}

	printf("\nCurve points\n\n");

	for (i = 1; i <= 3 * p1; i = i + 3){
		printf(" %f %f %f \n", p[i], p[i + 1], p[i + 2]);
	}

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		0.0f, 0.5f, 0.0f,
		0.0f, 1.f, 0.0f  // Top   // Top 
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);	
	

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
		model = glm::rotate(model, /*(GLfloat)glfwGetTime() **/ 0.f, glm::vec3(0.5f, 0.0f, 0.0f));  
		view = glm::translate(view, glm::vec3(-1.0f, -1.0f, -5.0f));
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
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLE_STRIP, vertices2.size(), GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLE_STRIP, indices2.size(), GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 1, 10);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
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