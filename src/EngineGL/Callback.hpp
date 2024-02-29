#include "Engine.hpp"

using namespace std;

class Callback {
	public:

		static void	framebufferSizeCallback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		static void	keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			
			if (action == GLFW_PRESS || action == GLFW_REPEAT) {
				// cout << "Key: " << key << endl;
				switch (key) {
					// Make WASD rotate the model
					case GLFW_KEY_W:
						engine.models[0].Rotate(10.f, 1.f, 0.f, 0.f);
						break;
					case GLFW_KEY_S:
						engine.models[0].Rotate(10.f, -1.f, 0.f, 0.f);
						break;
					case GLFW_KEY_A:
						engine.models[0].Rotate(10.f, 0.f, 1.f, 0.f);
						break;
					case GLFW_KEY_D:
						engine.models[0].Rotate(10.f, 0.f, -1.f, 0.f);
						break;
					case GLFW_KEY_E: // GLFW_KEY_1
						// default mode
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
						break;
					case GLFW_KEY_R: // GLFW_KEY_2
						// only edges mode
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						break;
					case GLFW_KEY_T: // GLFW_KEY_3
						// only vertices mode
						glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
						break;
					case GLFW_KEY_LEFT: // GLFW_KEY_4
						engine.models[0].setVertices(NO_COLOR_MODE);
						break;
					case GLFW_KEY_RIGHT: // GLFW_KEY_5
						engine.models[0].setVertices(RAND_COLOR_MODE);
						break;
					case GLFW_KEY_UP: // GLFW_KEY_6
						engine.models[0].setVertices(TEXTURE_MODE);
						break;
				}
			}
		}

		static void	scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
			// Zoom in
			if (yoffset > 0)
				engine.models[0].Scale(1.1f);
			// Zoom out
			else
				engine.models[0].Scale(0.9f);
		}

		static void	dropCallback(GLFWwindow* window, int count, const char* paths[]) {
			for (int i = 0; i < count; i++) {
				const char* path = paths[i];
				
				cout << "Dropped file: " << path << endl;

				if (engine.models[0].texture.loadTexture(path))
					engine.models[0].setVertices(TEXTURE_MODE);
			}
		}
};
