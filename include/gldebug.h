#pragma once
#define ASSERT(x) if (!(x)) raise(SIGQUIT);
#define GLDebug(x) GLClearErrors();\
                    x;\
                    ASSERT(GLCheckError())

void GLClearErrors();
bool GLCheckError();
