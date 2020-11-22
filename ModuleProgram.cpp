#include "ModuleProgram.h"
#include "GL/glew.h"

bool ModuleProgram::Init()
{
	program = CreateProgram("fragment.glsl", "shader.glsl");
	return true;
}

static unsigned CreateProgram(const char* fragmentShaderFilename, const char* vertexShaderFilename)
{
	unsigned fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);
	unsigned vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename);
	
	unsigned programID = glCreateProgram();
	glAttachShader(programID, fragmentShader);
	glAttachShader(programID, vertexShader);
	glLinkProgram(programID);
	int res = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(programID, len, &written, info);
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	return programID;
}

bool ModuleProgram::CleanUp()
{
	glDeleteProgram(program);

	return true;
}

static char* ReadShaderFile(const char* filename)
{
	char* data = nullptr;
	FILE* shader = fopen(filename, "rb");
	if (shader)
	{
		fseek(shader, 0, SEEK_END);
		int size = ftell(shader);
		rewind(shader);
		data = (char*)malloc(size + 1);
		fread(data, 1, size, shader);
		data[size] = 0;
		fclose(shader);
	}
	return data;
}

static unsigned CreateShader(unsigned shaderType, const char* filename)
{
	char* shader = ReadShaderFile(filename);
	unsigned shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shader, 0);
	glCompileShader(shaderID);
	int res = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shaderID, len, &written, info);
			LOG("Log info: %s", info);
			free(info);
		}
	}
	free(shader);
	return shaderID;
}