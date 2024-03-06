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
						for (auto& model : engine.models)
							model.Rotate(10.f, 1.f, 0.f, 0.f);
						// engine.models[0].Rotate(10.f, 1.f, 0.f, 0.f);
						break;
					case GLFW_KEY_S:
						for (auto& model : engine.models)
							model.Rotate(10.f, -1.f, 0.f, 0.f);
						// engine.models[0].Rotate(10.f, -1.f, 0.f, 0.f);
						break;
					case GLFW_KEY_A:
						for (auto& model : engine.models)
							model.Rotate(10.f, 0.f, 1.f, 0.f);
						// engine.models[0].Rotate(10.f, 0.f, 1.f, 0.f);
						break;
					case GLFW_KEY_D:
						for (auto& model : engine.models)
							model.Rotate(10.f, 0.f, -1.f, 0.f);
						// engine.models[0].Rotate(10.f, 0.f, -1.f, 0.f);
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

					// Make arrows translate the model
					case GLFW_KEY_UP:
						for (auto& model : engine.models)
							model.Translate(0.f, 0.1f, 0.f);
						break;
					case GLFW_KEY_DOWN:
						for (auto& model : engine.models)
							model.Translate(0.f, -0.1f, 0.f);
						break;
					case GLFW_KEY_LEFT:
						for (auto& model : engine.models)
							model.Translate(-0.1f, 0.f, 0.f);
						break;
					case GLFW_KEY_RIGHT:
						for (auto& model : engine.models)
							model.Translate(0.1f, 0.f, 0.f);
						break;
				}
			}
		}

		static void	scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
			// Zoom in
			if (yoffset > 0) {
				for (auto& model : engine.models)
					model.Scale(1.1f);
			}
			// Zoom out
			else {
				for (auto& model : engine.models)
					model.Scale(0.9f);
			}
		}

		static void	dropCallback(GLFWwindow* window, int count, const char* paths[]) {
			for (int i = 0; i < count; i++) {
				const char* path = paths[i];
				
				cout << "Dropped file: " << path << endl;

				for (auto& model : engine.models) {
					if (model.texture.loadTexture(path))
						model.setVertices(TEXTURE_MODE);
				}
			}
		}
};
