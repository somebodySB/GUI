#include "stdafx.h"

//struct COLORREF
//{
//	float R;
//	float G;
//	float B;
//	COLORREF()
//	{
//		R = G = B = 0;
//	}
//};

struct GuiRectParam
{
	int x;
	int y;
	int w;
	int h;
	COLORREF color;
};
typedef std::vector<GuiRectParam> GuiRectList;

struct GuiContext
{
	int MouseX;
	int MouseY;
	bool MouseDown;

	int HoveredID;
	int ActiveID;

	GuiRectList grl;

	GuiContext()
	{
		MouseX = 0;
		MouseY = 0;
		MouseDown = false;
		HoveredID = NULL;
		ActiveID = NULL;
	}
	void AddRect(int x, int y, int w, int h, COLORREF color)
	{
		GuiRectParam grp;
		grp.x = x;
		grp.y = y;
		grp.w = w;
		grp.h = h;
		grp.color = color;
		grl.push_back(grp);
	}

};
static GuiContext GC;
static GuiContext* gc=&GC;
bool IsInRect(GLFWwindow* window,int x, int y, int w, int h)
{
	double Mouse_x;
	double Mouse_y;
	glfwGetCursorPos(window, &Mouse_x, &Mouse_y);
	if (Mouse_x >= x&&Mouse_x <= x + w&&Mouse_y >= y&&Mouse_y <= y + h)
		return true;
	else
		return false;
}
bool Button(GLFWwindow* window,int id,int x, int y, int w, int h, COLORREF color)
{
	if (IsInRect(window, x, y, w, h))
	{
		gc->HoveredID = id;
		if (gc->ActiveID == NULL&&gc->MouseDown)
			gc->ActiveID = id;
	}
		gc->AddRect(x, y, w, h, color);

		if (gc->MouseDown&&
			gc->HoveredID == id&&
			gc->ActiveID == id)
			return true;
		else
			return false;
	
	
}

void StartFrame(LPGuiContext gc)
{
	gc->HoveredID = 0;
}

void EndFrame(LPGuiContext gc)
{
	if (!gc->MouseDown)
		gc->HoveredID = NULL;
	else
	{
		if (gc->HoveredID == NULL)
			gc->HoveredID = UNABLE;
	}
}

void Render()
{
	if (!gc->grl.empty())
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 480, 320, 0, -1.0f, 1.0f);

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(gc->grl[0].color.R, gc->grl[0].color.G, gc->grl[0].color.B);
		glBegin(GL_POLYGON);
		glVertex2f(gc->grl[0].x, gc->grl[0].y);
		glVertex2f(gc->grl[0].x + gc->grl[0].w, gc->grl[0].y);
		glVertex2f(gc->grl[0].x + gc->grl[0].w, gc->grl[0].y + gc->grl[0].h);
		glVertex2f(gc->grl[0].x, gc->grl[0].y + gc->grl[0].h);
		glEnd();
		gc->grl.pop_back();
	}
}

void Gui_MouseButton(GLFWwindow*, int button, int action, int /*mods*/)
{
	if (action)
		gc->MouseDown = true;
	else
		gc->MouseDown = false;
}

void Gui_Init(GLFWwindow* window)
{
	glfwSetMouseButtonCallback(window, Gui_MouseButton);

}