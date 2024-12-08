#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>

#define BUILD_FAILED -1
#define BUILD_OK 0


static unsigned int g_active_program_id = INVALID_PROGRAM_ID;

unsigned int Shader_GetActiveProgramId() {
    return g_active_program_id;
}

static int Shader_CompileResult(unsigned int shader_id, GLenum shader_type) {
    int success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        fprintf(stderr, "%s Shader Compilation Error! Error: %s\n", shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);
        return BUILD_FAILED;
    }
    return BUILD_OK;
}

static int Shader_LinkResult(unsigned int program_id) {
    int success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program_id, 512, NULL, infoLog);
        fprintf(stderr, "Shader Program Link Error! Error: %s\n", infoLog);
        return BUILD_FAILED;
    }
    return BUILD_OK;
}


static unsigned int Shader_Compile(GLenum shader_type, const char* shader_source) {
    unsigned int shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_source, NULL);
    glCompileShader(shader_id);

    if (Shader_CompileResult(shader_id, shader_type) == BUILD_FAILED) return INVALID_SHADER_ID;

    return shader_id;
}


void Shader_CreateProgram(ShaderProgram* program) {
    if (!program) return;
    program->program_id = INVALID_PROGRAM_ID;
    program->vShader_id = INVALID_SHADER_ID;
    program->fShader_id = INVALID_SHADER_ID;
    program->gShader_id = INVALID_SHADER_ID;
}

void Shader_AddShader(ShaderProgram* program, GLenum shader_type, const char* shader_source_path) {
    if (!program || !shader_source_path) return;
    //if (program->program_id == INVALID_PROGRAM_ID) return;
    
    FILE* source_file = fopen(shader_source_path, "rb");
    if (!source_file) {
        perror("Error opening shader file");
        fprintf(stderr, "Cant Read Shader Source File\n");
        return;
    }

    fseek(source_file, 0, SEEK_END);
    long len = ftell(source_file);
    fseek(source_file, 0, SEEK_SET);

    char* source_buffer = malloc(len + 1);
    if (!source_buffer) {
        fclose(source_file);
        return;
    }

    fread(source_buffer, 1, len, source_file);
    source_buffer[len] = '\0';
    fclose(source_file);
    
    if (shader_type == GL_VERTEX_SHADER) program->vShader_id = Shader_Compile(shader_type, source_buffer);
    else if (shader_type == GL_FRAGMENT_SHADER) program->fShader_id = Shader_Compile(shader_type, source_buffer);

    free(source_buffer);
}

void Shader_LinkProgram(ShaderProgram* program) {
    if (!program) return;
    if (program->vShader_id == INVALID_SHADER_ID || 
    program->fShader_id == INVALID_SHADER_ID) return;

    program->program_id = glCreateProgram();
    glAttachShader(program->program_id, program->vShader_id);
	glAttachShader(program->program_id, program->fShader_id);
	glLinkProgram(program->program_id);

    if (Shader_LinkResult(program->program_id) == BUILD_FAILED) return;

    glDeleteShader(program->vShader_id);
    glDeleteShader(program->fShader_id);
    program->vShader_id = INVALID_SHADER_ID;
    program->fShader_id = INVALID_SHADER_ID;
}


void Shader_UseProgram(ShaderProgram* program) {
    if (!program) return;
    if (program->program_id == g_active_program_id || program->program_id == INVALID_PROGRAM_ID) return;
    glUseProgram(program->program_id);
    g_active_program_id = program->program_id;
}

int Shader_LocateUniform(ShaderProgram* program, const char* uniform_name) {
    if (!program || !uniform_name) return INVALID_UNIFORM_LOCATION;
    return glGetUniformLocation(program->program_id, uniform_name);
}

void Shader_DestroyProgram(ShaderProgram* program) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    glDeleteProgram(program->program_id);
    program->program_id = INVALID_PROGRAM_ID;
}


void Shader_SetFloat(ShaderProgram* program, const char* uniform_name, float value) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    Shader_UseProgram(program);
    glUniform1f(Shader_LocateUniform(program, uniform_name), value);
}

void Shader_SetDouble(ShaderProgram* program, const char* uniform_name, double value) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    Shader_UseProgram(program);
    glUniform1d(Shader_LocateUniform(program, uniform_name), value);
}


void Shader_SetInt(ShaderProgram* program, const char* uniform_name, int value) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    Shader_UseProgram(program);
    glUniform1i(Shader_LocateUniform(program, uniform_name), value);
}

void Shader_SetBool(ShaderProgram* program, const char* uniform_name, bool value) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    Shader_UseProgram(program);
    glUniform1i(Shader_LocateUniform(program, uniform_name), value ? 1 : 0);
}



void Shader_SetVec3(ShaderProgram* program, const char* uniform_name, vec3 value ) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    Shader_UseProgram(program);
	glUniform3fv(Shader_LocateUniform(program, uniform_name), 1, &value[0]);
}

void Shader_SetVec4(ShaderProgram* program, const char* uniform_name, vec4 value) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    Shader_UseProgram(program);
	glUniform4fv(Shader_LocateUniform(program, uniform_name), 1, &value[0]);
}

void Shader_SetMat4(ShaderProgram* program, const char* uniform_name, mat4 value) {
    if (!program) return;
    if (program->program_id == INVALID_PROGRAM_ID) return;
    Shader_UseProgram(program);
	glUniformMatrix4fv(Shader_LocateUniform(program, uniform_name), 1, GL_FALSE, &value[0][0]);
}
