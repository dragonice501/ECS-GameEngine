#pragma once

#include <SDL.h>
#include "../utils/Vec2.h"
#include "../Objects/Shapes/AARectangle.h"
#include "../Objects/Shapes/Rectangle.h"

#include <stdint.h>
#include <vector>
#include <string>

class GraphicsManager
{

public:
    enum TextHorizontalAlignment
    {
        Left,
        Center,
        Right,
    };

    enum TextVerticalAlignment
    {
        Top,
        Middle,
        Bottom,
    };

private:
    static int windowWidth;
    static int windowHeight;
    static int screenWidth;
    static int screenHeight;

    static uint32_t* colorBuffer;
    static SDL_Texture* colorBufferTexture;
    static SDL_Window* window;
    static SDL_Renderer* renderer;

    static SDL_Rect camera;

    static Vec2 screenOffset;
    static float screenZoom;

public:
    static bool OpenWindow();
    static void CloseWindow();

    static int WindowWidth();
    static int WindowHeight();
    static int ScreenWidth();
    static int ScreenHeight();

    static SDL_Renderer* Renderer() { return renderer; }
    static SDL_Rect& Camera() { return camera; }

    static void AdjustScreenOffset(const Vec2& offset);
    static void ResetScreenOffset();

    static void ScrollZoom(const int& scroll);

    static bool CircleOffScreen(const int& x, const int& y, const float& radius);

    static void ClearScreen(const uint32_t& color);
    static void PresentRender();

    static void DrawPixel(const int x, const int y, const uint32_t color);
    static void DrawLine(const int x0, const int y0, const int x1, const int y1, const uint32_t color, const bool lockToScreen = true);
    static void DrawGrid(const uint32_t color);

    static void DrawAARect(const int x, const int y, const int width, const int height, const uint32_t color);
    static void DrawAARect(const AARectangle& rect, const uint32_t color);
    static void DrawFillAARect(const int x, const int y, const int width, const int height, const uint32_t color);
    static void DrawRect(const Rectangle& rect, const uint32_t color);
    static void DrawFillRect(const Rectangle& rect, const uint32_t color);

    static void DrawCircle(const int x, const int y, const int radius, const float angle, const uint32_t color, const bool lockToScreen = true);
    static void DrawFillCircle(const int x, const int y, const int radius, const uint32_t color);

    static void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

    static void DrawPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen = true);
    static void DrawFillPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen = true);
    static void DrawTexture(const int x, const int y, const int width, const int height, const float rotation, SDL_Texture* texture);

    static void DrawChar(const int x, const int y, const char character, const uint32_t color, const bool lockToScreen = true);
    static void DrawString(
        const int x,
        const int y,
        const char* string,
        const TextHorizontalAlignment horizontalAlignment = Left,
        const TextVerticalAlignment verticalAlignement = Top,
        const uint32_t color = 0xFFFF0000,
        const bool lockToScreen = true);


private:
    static void SwapInt(int& a, int& b);
    static void SwapFloat(float& a, float& b);
    static void SwapVec2(Vec2& a, Vec2& b);
    static void FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
    static void FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

    static void DisplayBresenhamCircle(const int xc, const int yc, const int x0, const int y0, const uint32_t color, const bool lockToScreen = true);
};