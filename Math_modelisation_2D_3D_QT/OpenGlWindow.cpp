#define GLEW_STATIC
#include <GL/glew.h>
#include "OpenGlWindow.h"

#include <iostream>

// SOIL
#include <SOIL.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ESGIShader.h"

#include <vector>
#include "Point.h"

//Qt
#include <QtWidgets\qapplication.h>

const GLuint GRID_W = 5, GRID_H = 5;

std::vector<std::vector<Point>> controlPoints = std::vector<std::vector<Point>>();
std::vector<std::vector<float>> bsplineC = std::vector<std::vector<float>>();

int currentSpline = -1;

std::vector<std::vector<float>> controlP = std::vector<std::vector<float>>();

EsgiShader basicShader;

//GLuint VBO, VAO, VBO_spline, VAO_spline;

std::vector<GLuint> VAOsP = std::vector<GLuint>();
std::vector<GLuint> VBOsP = std::vector<GLuint>();

std::vector<GLuint> VAOsS = std::vector<GLuint>();
std::vector<GLuint> VBOsS = std::vector<GLuint>();

OpenGlWindow::OpenGlWindow(Model* model)
{
	this->model = model;
}

void OpenGlWindow::knot(int n, int c, int x[])
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

void OpenGlWindow::basis(int c, float t, int npts, int x[], float n[])
{
	int nplusc;
	int i, k;
	float d, e;
	float temp[1000];

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

void OpenGlWindow::bspline(int npts, int k, int p1, int current)
{
	int i, j, icount, jcount;
	int i1;
	int x[1000];		/* allows for 20 data points with basis function of order 5 */
	int nplusc;

	float step;
	float t;
	float nbasis[1000];
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
			float pointC = 0.;

			for (i = 1; i <= npts; i++){ /* Do local matrix multiplication */
				temp = nbasis[i] * controlP[current][jcount];
				pointC = pointC + temp;
				jcount = jcount + 3;
			}
			bsplineC[current].push_back(pointC);
			//bsplineC.push_back(pointC);
		}
		/*
		printf("icount, p %d %f %f %f \n",icount,p[icount+1],p[icount+2],p[icount+3]);
		*/
		icount = icount + 3;
		t = t + step;
	}
}

void OpenGlWindow::calculateBSpline(int i)
{
	bsplineC[i].clear();

	int npts, k, p1;

	npts = controlPoints[i].size();
	k = model->degree;     /* second order, change to 4 to get fourth order */
	p1 = model->pas;   /* eleven points on curve */

	bspline(npts, k, p1, i);
}

//void initializeGridBuffer() {
//	GLuint VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), &vertices2.front(), GL_STATIC_DRAW);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(float), &indices2.front(), GL_STATIC_DRAW);
//	//glBufferDakta(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
//
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
//
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(0); // Unbind VAO
//}

void convertPointToFloat(int current){
	controlP[current].clear();
	controlP[current].push_back(0.0);
	for (int i = 0; i < controlPoints[current].size(); i++)
	{
		controlP[current].push_back(controlPoints[current][i].x_);
		controlP[current].push_back(controlPoints[current][i].y_);
		controlP[current].push_back(controlPoints[current][i].z_);
	}
}

void OpenGlWindow::initializeGL()
{
	newBSpline();

	for (int i = 0; i < 100; i++)
	{
		VAOsP.push_back(GLuint());
		VBOsP.push_back(GLuint());
		VAOsS.push_back(GLuint());
		VBOsS.push_back(GLuint());
	}

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, this->width(), this->height());

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

	glEnable(GL_PROGRAM_POINT_SIZE);

}

void OpenGlWindow::paintGL()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate shader
	basicShader.Bind();

	// Create transformations
	//glm::mat4 model;
	//glm::mat4 view;
	//glm::mat4 projection;
	//model = glm::rotate(model, /*(GLfloat)glfwGetTime() **/ 0.f, glm::vec3(0.5f, 0.0f, 0.0f));
	//view = glm::translate(view, glm::vec3(-1.0f, -1.0f, -5.0f));
	//projection = glm::perspective(45.0f, (GLfloat)this->width() / (GLfloat)this->height(), 0.1f, 100.0f);
	//// Get their uniform location
	//GLint modelLoc = glGetUniformLocation(basicShader.GetProgram(), "model");
	//GLint viewLoc = glGetUniformLocation(basicShader.GetProgram(), "view");
	//GLint projLoc = glGetUniformLocation(basicShader.GetProgram(), "projection");
	//// Pass them to the shaders
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	for (int i = 0; i < bsplineC.size(); i++){

		convertPointToFloat(i);

		if (controlP[i].size() > 3){
			calculateBSpline(i);
			controlP[i].erase(controlP[i].begin());
			glGenVertexArrays(i + 1, &VAOsP[i]);
			glGenBuffers(i + 1, &VBOsP[i]);
			glBindVertexArray(VAOsP[i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBOsP[i]);
			glBufferData(GL_ARRAY_BUFFER, controlP[i].size() * sizeof(float), &controlP[i].front(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
		}

		if (bsplineC[i].size() > 0){
			glGenVertexArrays(i + 1, &VAOsS[i]);
			glGenBuffers(i + 1, &VBOsS[i]);
			glBindVertexArray(VAOsS[i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBOsS[i]);
			glBufferData(GL_ARRAY_BUFFER, bsplineC[i].size() * sizeof(float), &bsplineC[i].front(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
		}


		if (controlP[i].size() > 0){
			glBindVertexArray(VAOsP[i]);
			glDrawArrays(GL_POINTS, 0, controlP[i].size() / 3);
			glBindVertexArray(0);
		}

		if (bsplineC[i].size() > 0){
			glBindVertexArray(VAOsS[i]);
			glDrawArrays(GL_LINE_STRIP, 0, bsplineC[i].size() - this->model->pas * 2);
			glBindVertexArray(0);
		}
	}

}

double convertViewportToOpenGLCoordinate(double x)
{
	return (x * 2) - 1;
}

void OpenGlWindow::mousePressEvent(QMouseEvent * event)
{
	double xpos, ypos;

	xpos = convertViewportToOpenGLCoordinate(event->x() / (double)this->width());
	ypos = -convertViewportToOpenGLCoordinate(event->y() / (double)this->height());

	controlPoints[currentSpline].push_back(Point(xpos, ypos, 0.f));
	this->update();
}

void OpenGlWindow::newBSpline()
{
	currentSpline++;
	controlP.push_back(std::vector<float>());
	controlPoints.push_back(std::vector<Point>());
	bsplineC.push_back(std::vector<float>());
}