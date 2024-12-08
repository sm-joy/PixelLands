#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>
#include <CGLM/call.h>
#include <stdbool.h>

#define INVALID_SHADER_ID 0
#define INVALID_PROGRAM_ID 0
#define INVALID_UNIFORM_LOCATION -1

typedef struct ShaderProgram {
    unsigned int program_id;
    unsigned int vShader_id;
    unsigned int fShader_id;
    unsigned int gShader_id;
} ShaderProgram;

void Shader_CreateProgram(ShaderProgram* program);
void Shader_AddShader(ShaderProgram* program, GLenum shader_type, const char* shader_source_path);
void Shader_LinkProgram(ShaderProgram* program);
void Shader_DestroyProgram(ShaderProgram* program);

void Shader_UseProgram(ShaderProgram* program);
int Shader_LocateUniform(ShaderProgram* program, const char* uniform_name);
unsigned int Shader_GetActiveProgramId();

void Shader_SetFloat(ShaderProgram* program, const char* uniform_name, float value);
void Shader_SetDouble(ShaderProgram* program, const char* uniform_name, double value);
void Shader_SetInt(ShaderProgram* program, const char* uniform_name, int value);
void Shader_SetBool(ShaderProgram* program, const char* uniform_name, bool value);
void Shader_SetVec3(ShaderProgram* program, const char* uniform_name, vec3 value );
void Shader_SetVec4(ShaderProgram* program, const char* uniform_name, vec4 value);
void Shader_SetMat4(ShaderProgram* program, const char* uniform_name, mat4 value);


#endif // SHADER_H