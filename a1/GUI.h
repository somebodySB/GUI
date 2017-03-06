#pragma once

#define UNABLE -1


#include "stdafx.h"

struct COLORREF
{
	float R;
	float G;
	float B;
	COLORREF()
	{
		R = G = B = 0;
	}
	COLORREF(float red, float green, float blue)
	{
		R = red;
		G = green;
		B = blue;
	}
};

struct GuiRectParam;

typedef struct GuiContext *LPGuiContext;

void StartFrame(LPGuiContext gc);

void EndFrame(LPGuiContext gc);

bool Button(GLFWwindow* window, int id, int x, int y, int w, int h, COLORREF color);

void Render();

void Gui_MouseButton(GLFWwindow*, int button, int action, int /*mods*/);

void Gui_Init(GLFWwindow* window);