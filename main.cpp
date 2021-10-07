#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "image.h"

float posx = 0;
float posy = 0;
float posz = 0;

float viewx = 0;
float viewy = 0;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
			case GLFW_KEY_W:
				posx += 0.1f;
				break;
			case GLFW_KEY_S:
				posx -= 0.1f;
				break;
			case GLFW_KEY_A:
				posz -= 0.1f;
				break;
			case GLFW_KEY_D:
				posz += 0.1f;
				break;
			case GLFW_KEY_R:
				posy -= 0.1f;
				break;
			case GLFW_KEY_F:
				posy += 0.1f;
				break;
			case GLFW_KEY_UP:
				viewy += 0.1f;
				break;
			case GLFW_KEY_DOWN:
				viewy -= 0.1f;
				break;
			case GLFW_KEY_LEFT:
				viewx += 0.1f;
				break;
			case GLFW_KEY_RIGHT:
				viewx -= 0.1f;
				break;
		}
	}
}

static void sizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	glfwInit();

	/* create window */
	GLFWwindow* window = glfwCreateWindow(640, 480, "MEngine", NULL, NULL);
	if (!window) {
		std::cout << "ERROR: failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetFramebufferSizeCallback(window, sizeCallback);

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1);

	/* create shaders */
	GLuint vShader = createShaderFromFile(GL_VERTEX_SHADER, "shaders/shader1.vert");
	GLuint fShader = createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/shader1.frag");

	const GLuint shaderList[] = {vShader, fShader};
	GLuint shaderProgram = createShaderProgram(shaderList, 2);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	/* temporoary triangle stuff */
	/*
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f
	};
	*/
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL); //position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //texture
	glEnableVertexAttribArray(1);

	GLuint texture = createTextureFromBMP("obama.bmp", GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

	glEnable(GL_DEPTH_TEST);

	/* main loop */
	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		/* draw background color */
		glClearColor(0.0f, 0.2f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);

		glm::vec3 cameraDirection(
			cos(viewy) * sin(viewx),
			sin(viewy),
			cos(viewx) * cos(viewy)
		);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		glm::vec3 pos = glm::vec3(posx, posy, posz);

		model = glm::rotate(model, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(posx, posy, posz));
		view = glm::lookAt(pos, pos + cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		unsigned int modelL = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewL = glGetUniformLocation(shaderProgram, "view");

		glUniformMatrix4fv(modelL, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewL, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "proj"), 1, GL_FALSE, &proj[0][0]);

		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3((float)i, (float)i, -1 * (float)i));
			model = glm::rotate(model, (float)glfwGetTime() * 3, glm::vec3(0.0f, 1.0f, 0.0f));

			unsigned int modelL = glGetUniformLocation(shaderProgram, "model");
			unsigned int viewL = glGetUniformLocation(shaderProgram, "view");

			glUniformMatrix4fv(modelL, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewL, 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "proj"), 1, GL_FALSE, &proj[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/* draw triangle */
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/* this code should go last */
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}