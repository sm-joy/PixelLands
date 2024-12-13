#include "Application.h"
#include "../Event/Event.h" // IWYU pragma: export
#include "../Utility/Color.h"
#include "../Graphics/Shader.h"
#include "../World/Cube.h"
#include <CGLM/call.h>
#include <stdio.h>

static bool run = true;
static bool wireframe_mode = false;
static ShaderProgram basic;

float fov = 70.0f; 
float aspect_ratio = 800.0f / 600.0f; 
float near_plane = 0.05f;
float far_plane = 1000.0f;
Cube test;


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
	CreateWindow(&app->window, "Pixel Lands", 800, 600);
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
	glmc_translate(view, (vec3){0.0f, 0.0f, -5.0f});
	Shader_SetMat4(&basic, "view", view);

	Cube_Create(&test, (vec3){0.0f, 0.0f, 0.0f});
	Cube_AddTexture(&test, FACE_SIDE, "C:\\Users\\zihad\\Development\\C\\PixelLands\\PixelLands\\Assets\\Textures\\grass_block_side.png");
	Cube_AddTexture(&test, FACE_TOP, "C:\\Users\\zihad\\Development\\C\\PixelLands\\PixelLands\\Assets\\Textures\\grass_block_top.png");
	Cube_AddTexture(&test, FACE_BOTTOM, "C:\\Users\\zihad\\Development\\C\\PixelLands\\PixelLands\\Assets\\Textures\\grass_block_bottom.png");
	Shader_SetInt(&basic, "texture1", 0);
}


static void ApplicationRenderFrame(Application *app) {
	vec3 axis;
	glmc_vec3_add(X_AXIS, Y_AXIS, axis);
	Cube_Rotate(&test, glm_rad(10), axis);
	Shader_SetMat4(&basic, "model", test.model);

	glActiveTexture(GL_TEXTURE0);
	Cube_Render(&test);
}

void ApplicationRun(Application* app) {
	while (run) {
		
		Clock_Tick(&app->clock);
		printf("\rFPS: %lf  Delta Time: %lf Elapsed Time: %f", app->clock.fps, app->clock.delta_time, Clock_GetElapsedTime(&app->clock));
		
		ClearRender(&app->renderer);
		ApplicationRenderFrame(app);
		UpdateWindow(&app->window);
	}
}

void ApplicationShutdown(Application* app) {
	TerminateWindow(&app->window);
	ShutdownEventSystem();
	Cube_Destroy(&test);
}




