#include "Globals.h"


void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);

	logs.append(tmp_string2);
}

void logFPS(float deltaTime) {
	float FPS = 1000.0f / deltaTime;
	FPSIndex--;
	if (FPSIndex < 0) {
		FPSIndex = 99;
	}
	logsFPS[FPSIndex] = FPS;
	logsMiliseconds[FPSIndex] = deltaTime * 1000.0f;
}

std::string logs;
int FPSIndex = 99;
float logsFPS[100] = { 0 };
float logsMiliseconds[100] = { 0 };