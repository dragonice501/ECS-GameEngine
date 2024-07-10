#pragma once

#include "AARectangle.h"
#include "Curve.h"
#include "Rectangle.h"
#include "Vec2.h"

#include <SDL.h>
#include <stdint.h>
#include <vector>
#include <string>

class GraphicsManager
{
public:
    enum TextHorizontalAlignment
    {
        HA_LEFT,
        HA_CENTER,
        HA_RIGHT,
    };

    enum TextVerticalAlignment
    {
        VA_TOP,
        VA_CENTER,
        VA_BOTTOM,
    };

private:
    static size_t mWindowWidth;
    static size_t mWindowHeight;
    static size_t mScreenWidth;
    static size_t mScreenHeight;

    static uint32_t* mColorBuffer;
    static SDL_Texture* mColorBufferTexture;
    static SDL_Window* mWindow;
    static SDL_Renderer* mRenderer;

    static SDL_Rect mCamera;

    static Vec2 mScreenOffset;
    static float mScreenZoom;

    static size_t mClipAARectSize;
    static size_t mSubdivisionSize;

private:
    GraphicsManager() {}
    ~GraphicsManager() {}

    static void SwapInt(int& a, int& b);
    static void SwapFloat(float& a, float& b);
    static void SwapVec2(Vec2& a, Vec2& b);

    static void DisplayBresenhamCircle(const int xc, const int yc, const int x0, const int y0, const uint32_t color, const bool lockToScreen = true);
    static bool AARectInsideScreen(const AARectangle& rect);
    static void ClipAARectAgainstScreen(AARectangle& rect);

public:
    static bool OpenWindow();
    static void CloseWindow();

    inline static SDL_Renderer* GetRenderer() { return mRenderer; }

    inline static size_t WindowWidth() { return mWindowWidth; }
    inline static size_t WindowHeight() { return mWindowHeight; }
    inline static size_t ScreenWidth() { return mScreenWidth; }
    inline static size_t ScreenHeight() { return mScreenHeight; }

    inline static SDL_Rect& GetCamera() { return mCamera; }

    static void AdjustScreenOffset(const Vec2& offset);
    static void ResetScreenOffset();

    static void ScrollZoom(const int& scroll);

    static bool CircleOffScreen(const int& x, const int& y, const float& radius);

    static void ClearScreen(const uint32_t& color);
    static void RenderColorBuffer();
    static void PresentRender();

    static void DrawPixel(const int x, const int y, const uint32_t color);
    static void DrawLine(const int x0, const int y0, const int x1, const int y1, const uint32_t color, const bool lockToScreen = true);
    static void DrawGrid(const int gridWidth, const int gridHeight, const uint32_t color);

    static void DrawCurve(const Curve& curve, const uint32_t color);

    static void DrawAARect(const int x, const int y, const int width, const int height, const uint32_t color);
    static void DrawAARect(const AARectangle& rect, const uint32_t color);
    static void DrawFillAARect(const int x, const int y, const int width, const int height, const uint32_t color);
    static void DrawFillAARect(const AARectangle& rect, const uint32_t color);
    static void DrawRect(const Rectangle& rect, const uint32_t color);
    static void DrawFillRect(const Rectangle& rect, const uint32_t color);

    static void DrawCircle(const int x, const int y, const int radius, const float angle, const uint32_t color, const bool lockToScreen = true);
    static void DrawFillCircle(const int x, const int y, const int radius, const uint32_t color);
    static void DrawFillCircleTessellated(const int x, const int y, const int radius, const float zoomLevel, const uint32_t color);

    static void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

    static void DrawPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen = true);
    static void DrawFillPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen = true);
    static void DrawTexture(const int x, const int y, const int width, const int height, const float rotation, SDL_Texture* texture);

    static void DrawChar(const int x, const int y, const char character, const uint32_t color, const bool lockToScreen = true);
    static void DrawString(
        const int x,
        const int y,
        const char* string,
        const TextHorizontalAlignment horizontalAlignment = HA_LEFT,
        const TextVerticalAlignment verticalAlignement = VA_TOP,
        const uint32_t color = 0xFFFF0000,
        const bool lockToScreen = true);

    static void DrawSpriteRect(SDL_Texture* texture, SDL_Rect& srcRect, SDL_Rect& dstRect);
};