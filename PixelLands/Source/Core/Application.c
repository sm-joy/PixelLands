#include "Application.h"
#include "../Event/Event.h" // IWYU pragma: export
#include "../Utility/Color.h"
#include "../Graphics/Shader.h"
#include "../World/Cube.h"
#include <CGLM/call.h>
#include <stdio.h>
#include "../Graphics/Texture.h"

static bool run = true;
static bool wireframe_mode = false;
static ShaderProgram basic;

float fov = 45.0f;  // Typical Minecraft FOV
float aspect_ratio = 16.0f / 9.0f;  // Widescreen aspect ratio
float near_plane = 0.05f;  // Very close near plane for detailed rendering
float far_plane = 1000.0f;  // Large draw distance typical in Minecraft
Cube test;

Texture tex;


void setWireframeMode(Event* event) {
	KeyEvent* key_event = (KeyEvent*)event;
	if (key_event->key_code != KEY_V) return;

 	if (!wireframe_mode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		wireframe_mode = true;
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		wireframe_mode = false;
	}
}

static void onWindowClose(Event* event) {
	run = false;
}

void ApplicationInit(Application* app) {
	CreateWindow(&app->window, "Pixel Lands", 1280, 720);
	CreateRenderer(&app->renderer);
	Clock_Create(&app->clock);
	InitEventSystem();

	Color bg_color = Colori(15, 119, 125, 255);
	SetRenderClearColor(&bg_color);

	BindEventHandler(EVENT_WINDOW_CLOSE, onWindowClose);
	BindEventHandler(EVENT_KEY_PRESS, setWireframeMode);

	Shader_CreateProgram(&basic);
	Shader_AddShader(&basic, GL_VERTEX_SHADER, 	 "C:\\Users\\zihad\\Development\\C\\PixelLands\\PixelLands\\Assets\\basic.vs");
	Shader_AddShader(&basic, GL_FRAGMENT_SHADER, "C:\\Users\\zihad\\Development\\C\\PixelLands\\PixelLands\\Assets\\basic.fs");
	Shader_LinkProgram(&basic);

	mat4 projection;
	glmc_mat4_identity(projection);
	glmc_perspective(glm_rad(fov), aspect_ratio, near_plane, far_plane, projection);
	Shader_SetMat4(&basic, "projection", projection);

	mat4 view;
	glmc_mat4_identity(view);
	glmc_translate(view, (vec3){0.0f, 0.0f, -10.0f});
	Shader_SetMat4(&basic, "view", view);

	Cube_Create(&test, (vec3){0.0f, 0.0f, 0.0f});

	Texture_Load(&tex, "C:\\Users\\zihad\\Development\\C\\PixelLands\\PixelLands\\Assets\\Textures\\grass_block.jpeg");
	Shader_UseProgram(&basic);
	Shader_SetInt(&basic, "texture1", 0);
}


static void ApplicationRenderFrame(Application *app) {
	Cube_Rotate(&test, glm_rad(40), Y_AXIS);
	Shader_SetMat4(&basic, "model", test.model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.texture_id);
	Cube_Render(&test);
}

void ApplicationRun(Application* app) {
	while (run) {
		Clock_Tick(&app->clock);
		//printf("\rFPS: %lf  Delta Time: %lf Elapsed Time: %f, GLFW Time: %f", app->clock.fps, app->clock.delta_time, Clock_GetElapsedTime(&app->clock));
		
		ClearRender(&app->renderer);
		ApplicationRenderFrame(app);
		UpdateWindow(&app->window);
	}
}

void ApplicationShutdown(Application* app) {
	TerminateWindow(&app->window);
	ShutdownEventSystem();
	Texture_Destroy(&tex);
}




