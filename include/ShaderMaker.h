// ============================================================================
// ShaderMaker.h - GUIDA DIDATTICA
// Dichiarazioni di utilita per lettura, compilazione e collegamento degli shader GLSL.
// ============================================================================

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderMaker
{
    // PUBLIC: servizi statici per costruire il programma shader.
    public:
		// Compila e collega vertex shader e fragment shader.
		static GLuint createProgram(char* vertexfilename, char *fragmentfilename);
		// Legge il testo GLSL dal file; il chiamante gestisce la memoria restituita.
		static char* readShaderSource(const char* shaderFile);
	
    // PRIVATE: impedisce di creare istanze di ShaderMaker.
    private:
		ShaderMaker() { }	
};