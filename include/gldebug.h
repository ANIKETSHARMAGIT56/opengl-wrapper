#pragma once
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLDebug(x) GLClearErrors();\
                    x;\
                    ASSERT(GLCheckError())

void GLClearErrors();
bool GLCheckError();
