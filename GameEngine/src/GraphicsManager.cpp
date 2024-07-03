#include "GraphicsManager.h"

#include "Constants.h"
#include "Font.h"

#include <iostream>

size_t GraphicsManager::mWindowWidth = 0;
size_t GraphicsManager::mWindowHeight = 0;
size_t GraphicsManager::mScreenWidth = 0;
size_t GraphicsManager::mScreenHeight = 0;

uint32_t* GraphicsManager::mColorBuffer = nullptr;
SDL_Texture* GraphicsManager::mColorBufferTexture = nullptr;
SDL_Window* GraphicsManager::mWindow = nullptr;
SDL_Renderer* GraphicsManager::mRenderer = nullptr;

SDL_Rect GraphicsManager::mCamera;

Vec2 GraphicsManager::mScreenOffset = { 0.0f, 0.0f };
float GraphicsManager::mScreenZoom = 1.0f;

size_t GraphicsManager::mSubdivisionSize = 10;

bool GraphicsManager::OpenWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    mWindowWidth = display_mode.w;
    mWindowHeight = display_mode.h;
    mWindowWidth = 1280;
    mWindowHeight = 720;

    mScreenWidth = mWindowWidth * SCREEN_SCALE;
    mScreenHeight = mWindowHeight * SCREEN_SCALE;

    mWindow = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, SDL_WINDOW_BORDERLESS);
    if (!mWindow)
    {
        std::cerr << "Error creating SDL window" << std::endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return false;
    }

    mColorBuffer = new uint32_t[mScreenWidth * mScreenHeight];
    mColorBufferTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, mScreenWidth, mScreenHeight);

    mCamera.x = 0;
    mCamera.y = 0;
    mCamera.w = mWindowWidth;
    mCamera.h = mWindowHeight;

    return true;
}

void GraphicsManager::CloseWindow(void)
{
    if(mColorBuffer) delete[] mColorBuffer;
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void GraphicsManager::AdjustScreenOffset(const Vec2& offset)
{
    mScreenOffset.x += offset.x;
    mScreenOffset.y += offset.y;
}

void GraphicsManager::ResetScreenOffset()
{
    mScreenOffset = { 0.0f, 0.0f };
}

void GraphicsManager::ScrollZoom(const int& scroll)
{
    mScreenZoom += static_cast<float>(scroll) * 0.25f;
}

bool GraphicsManager::CircleOffScreen(const int& x, const int& y, const float& radius)
{
    return
        x + radius + mScreenOffset.x < 0 ||
        x - radius + mScreenOffset.x > mScreenWidth ||
        y + radius + mScreenOffset.y < 0 ||
        y - radius + mScreenOffset.y > mScreenHeight;

}

void GraphicsManager::ClearScreen(const uint32_t& color)
{
    for (int i = 0; i < mScreenWidth * mScreenHeight; i++)
    {
        mColorBuffer[i] = color;
    }

    SDL_RenderClear(mRenderer);
}

void GraphicsManager::PresentRender()
{
    SDL_UpdateTexture(mColorBufferTexture, nullptr, mColorBuffer, sizeof(uint32_t) * mScreenWidth);
    SDL_RenderCopy(mRenderer, mColorBufferTexture, nullptr, nullptr);

    SDL_RenderPresent(mRenderer);
}

void GraphicsManager::DrawPixel(const int x, const int y, const uint32_t color)
{
    if (x < 0 || x >= mScreenWidth || y < 0 || y >= mScreenHeight) return;

    mColorBuffer[x + y * mScreenWidth] = color;
}

void GraphicsManager::DrawLine(const int x0, const int y0, const int x1, const int y1, const uint32_t color, const bool lockToScreen)
{
    float x = x0;
    float y = y0;
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

    int steps = abs(deltaX) > abs(deltaY) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float)steps;
    float yIncrement = deltaY / (float)steps;

    for (int i = 0; i < steps; i++)
    {
        if(lockToScreen)
            DrawPixel(static_cast<int>(x), static_cast<int>(y), color);
        else
            DrawPixel(static_cast<int>(x + mScreenOffset.x), static_cast<int>(y + mScreenOffset.y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

void GraphicsManager::DrawGrid(const int gridWidth, const int gridHeight, const uint32_t color)
{
    for (int y = 0; y < mScreenHeight; y++)
    {
        for (int x = 0; x < mScreenWidth; x++)
        {
            if (x % gridWidth == 0 || y % gridHeight == 0)
                DrawPixel(x, y, color);
        }
    }
}

void GraphicsManager::DrawCurve(const Curve& curve, const uint32_t color)
{
    Vec2 start = curve.start;
    Vec2 end;

    //DrawPixel(start.x, start.y, color);

    for (int i = 1; i < 11; i++)
    {
        end = start + curve.normal * curve.length * 0.1f;
        end.RotateAroundPoint(start, curve.degree * 0.1f * i);

        //DrawPixel(end.x, end.y, color);
        
        DrawLine(start.x, start.y, end.x, end.y, color);

        start = end;
    }
}

void GraphicsManager::DrawAARect(const int x, const int y, const int width, const int height, const uint32_t color)
{
    DrawPixel(x + width / 2, y + height / 2, color);

    for (int i = x; i < x + width; i++)
        mColorBuffer[i + y * mScreenWidth] = color;

    for (int i = y; i < y + height; i++)
        mColorBuffer[x + i * mScreenWidth] = color;

    for (int i = y; i < y + height + 1; i++)
        mColorBuffer[(x + width) + i * mScreenWidth] = color;

    for (int i = x; i < x + width + 1; i++)
        mColorBuffer[i + (y + height) * mScreenWidth] = color;
}

void GraphicsManager::DrawAARect(const AARectangle& rect, const uint32_t color)
{
    int x = rect.topLeft.x;
    int y = rect.topLeft.y;
    int width = rect.bottomRight.x - rect.topLeft.x;
    int height = rect.bottomRight.y - rect.topLeft.y;

    for (int i = x; i < x + width; i++)
        mColorBuffer[i + y * mScreenWidth] = color;

    for (int i = y; i < y + height; i++)
        mColorBuffer[x + i * mScreenWidth] = color;

    for (int i = y; i < y + height + 1; i++)
        mColorBuffer[(x + width) + i * mScreenWidth] = color;

    for (int i = x; i < x + width + 1; i++)
        mColorBuffer[i + (y + height) * mScreenWidth] = color;
}

void GraphicsManager::DrawFillAARect(const int x, const int y, const int width, const int height, const uint32_t color)
{
    for (int i = y; i < y + height; i++)
    {
        for (int j = x; j < x + width; j++)
        {
            DrawPixel(j, i, color);
        }
    }
}

void GraphicsManager::DrawFillAARect(const AARectangle& rect, const uint32_t color)
{
    for (int i = rect.topLeft.y; i < rect.bottomRight.y; i++)
    {
        for (int j =  rect.topLeft.x; j < rect.bottomRight.x; j++)
        {
            DrawPixel(j, i, color);
        }
    }
}

void GraphicsManager::DrawRect(const Rectangle& rect, const uint32_t color)
{
    DrawPixel(rect.center.x, rect.center.y, color);
    DrawLine(rect.p0.x, rect.p0.y, rect.p1.x, rect.p1.y, color);
    DrawLine(rect.p1.x, rect.p1.y, rect.p2.x, rect.p2.y, color);
    DrawLine(rect.p2.x, rect.p2.y, rect.p3.x, rect.p3.y, color);
    DrawLine(rect.p3.x, rect.p3.y, rect.p0.x, rect.p0.y, color);
}

void GraphicsManager::DrawFillRect(const Rectangle& rect, const uint32_t color)
{
    DrawFillTriangle(rect.p0.x, rect.p0.y, rect.p1.x, rect.p1.y, rect.p2.x, rect.p2.y, 0xFFFFFF00);
    DrawFillTriangle(rect.p0.x, rect.p0.y, rect.p2.x, rect.p2.y, rect.p3.x, rect.p3.y, 0xFFFFFF00);
}

void GraphicsManager::DrawCircle(const int x, const int y, const int radius, const float angle, const uint32_t color, const bool lockToScreen)
{
    if (CircleOffScreen(x, y, radius)) return;

    int x0 = 0;
    int y0 = radius;
    int p0 = 3 - (2 * radius);

    DisplayBresenhamCircle(x, y, x0, y0, color, lockToScreen);

    while (y0 >= x0)
    {
        x0++;

        if (p0 > 0)
        {
            y0--;
            p0 += 4 * (x0 - y0) + 10;
        }
        else
        {
            p0 += 4 * x0 + 6;
        }

        DisplayBresenhamCircle(x, y, x0, y0, color, lockToScreen);
    }

    //DrawLine(x, y, x + cos(angle) * radius, y + sin(angle) * radius, color, lockToScreen);
}

void GraphicsManager::DrawFillCircle(const int x, const int y, const int radius, const uint32_t color)
{
    if (CircleOffScreen(x, y, radius)) return;
    int pRadius = radius;
    int topLeftX = x - pRadius;
    int topLeftY = y - pRadius;

    for (int i = topLeftY; i < topLeftY + pRadius + 1; i++)
    {
        for (int j = topLeftX; j < topLeftX + pRadius + 1; j++)
        {
            Vec2 point = { static_cast<float>(x - j), static_cast<float>(y - i) };

            if (point.MagnitudeSquared() < pRadius * pRadius)
            {
                DrawPixel(j + mScreenOffset.x, i + mScreenOffset.y, color);

                DrawPixel(j + mScreenOffset.x + (x - j) * 2, i + mScreenOffset.y, color);
                DrawPixel(j + mScreenOffset.x, i + mScreenOffset.y + (y - i) * 2, color);
                DrawPixel(j + mScreenOffset.x + (x - j) * 2, i + mScreenOffset.y + (y - i) * 2, color);
            }
        }
    }
}

void GraphicsManager::DrawFillCircleTessellated(const int x, const int y, const int radius, const float zoomLevel, const uint32_t color)
{
    if (radius <= 0) return;

    size_t upperTen = radius / mSubdivisionSize;
    if (radius % mSubdivisionSize > 0) upperTen++;

    size_t subdivisions = upperTen * 2;
    float topX = x - upperTen * mSubdivisionSize;
    float topY = y - upperTen * mSubdivisionSize;
    float squareDistance = radius * radius;
    AARectangle rect;

    for (size_t i = 0; i < subdivisions; i++)
    {
        for (size_t j = 0; j < subdivisions; j++)
        {
            rect = AARectangle(topX + j * mSubdivisionSize, topY + i * mSubdivisionSize, mSubdivisionSize, mSubdivisionSize);
            if (!AARectInsideScreen(rect))
            {
                continue;
            }

            ClipAARectAgainstScreen(rect);

            for (float k = rect.topLeft.y; k < rect.bottomRight.y; k++)
            {
                for (float l = rect.topLeft.x; l < rect.bottomRight.x; l++)
                {
                    float xDistance = l - x;
                    xDistance *= xDistance;

                    float yDistance = k - y;
                    yDistance *= yDistance;

                    if (xDistance + yDistance > squareDistance) continue;

                    DrawPixel(l, k, 0xff0000ff);
                }
            }

            DrawAARect(rect, 0xffffffff);
        }
    }
}

void GraphicsManager::DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    if (y0 > y1)
    {
        SwapInt(y0, y1);
        SwapInt(x0, x1);
    }
    if (y1 > y2)
    {
        SwapInt(y1, y2);
        SwapInt(x1, x2);
    }
    if (y0 > y1)
    {
        SwapInt(y0, y1);
        SwapInt(x0, x1);
    }

    float slope1 = 0.0f;
    float slope2 = 0.0f;

    if (y1 - y0 != 0) slope1 = static_cast<float>(x1 - x0) / abs(y1 - y0);
    if (y2 - y0 != 0) slope2 = static_cast<float>(x2 - x0) / abs(y2 - y0);

    if (y1 - y0 != 0)
    {
        for (int y = y0; y <= y1; y++)
        {
            int xStart = x1 + (y - y1) * slope1;
            int xEnd = x0 + (y - y0) * slope2;

            if (xEnd < xStart)
            {
                SwapInt(xEnd, xStart);
            }

            for (int x = xStart; x < xEnd; x++)
            {
                DrawPixel(x, y, color);
            }
        }
    }

    slope1 = 0.0f;

    if (y2 - y1 != 0) slope1 = static_cast<float>(x2 - x1) / abs(y2 - y1);

    if (y2 - y1 != 0)
    {
        for (int y = y1; y <= y2; y++)
        {
            int xStart = x1 + (y - y1) * slope1;
            int xEnd = x0 + (y - y0) * slope2;

            if (xEnd < xStart)
            {
                SwapInt(xEnd, xStart);
            }

            for (int x = xStart; x < xEnd; x++)
            {
                DrawPixel(x, y, color);
            }
        }
    }
}

void GraphicsManager::DrawPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen)
{
    Vec2 current = vertices[0];
    Vec2 previous = vertices[vertices.size() - 1];

    DrawLine(previous.x, previous.y, current.x, current.y, 0xFFFFFFFF, lockToScreen);

    for (int i = 1; i < vertices.size(); i++)
    {
        previous = current;
        current = vertices[i];
        DrawLine(previous.x, previous.y, current.x, current.y, color, lockToScreen);
    }
}

void GraphicsManager::DrawFillPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen)
{
    
}

void GraphicsManager::DrawTexture(const int x, const int y, const int width, const int height, const float rotation, SDL_Texture* texture)
{
    SDL_Rect dstRect = {x - (width / 2), y - (height / 2), width, height};
    float rotationDeg = rotation * 57.2958;
    SDL_RenderCopyEx(mRenderer, texture, nullptr, &dstRect, rotationDeg, nullptr, SDL_FLIP_NONE);
}

void GraphicsManager::DrawChar(const int x, const int y, const char character, const uint32_t color, const bool lockToScreen)
{
    for (int j = 0; j < Font::fontHeight; j++)
    {
        for (int k = 0; k < Font::fontWidth; k++)
        {
            if (character == ' ') continue;

            if (Font::fontMap[character][k + j * Font::fontWidth])
            {
                int yOffset = 0;

                if (character == 'g' || character == 'j' || character == 'p' || character == 'q' || character == 'y') yOffset = 2;

                if(lockToScreen)
                    DrawPixel(x + k, y + j + yOffset, color);
                else
                    DrawPixel(x + k + mScreenOffset.x, y + j + yOffset + mScreenOffset.y, color);
            }
        }
    }
}

void GraphicsManager::DrawString(
    const int x,
    const int y,
    const char* string,
    const TextHorizontalAlignment horizontalAlignment,
    const TextVerticalAlignment verticalAlignement,
    const uint32_t color,
    const bool lockToScreen)
{
    int i = 0;

    int xPos;
    int yPos;
    switch (horizontalAlignment)
    {
        case HA_LEFT:
        {
            xPos = x;
            break;
        }
        case HA_CENTER:
        {
            xPos = x - (Font::GetStringFontLength(string) / 2);
            break;
        }
        case HA_RIGHT:
        {
            xPos = x - Font::GetStringFontLength(string);
            break;
        }
    }

    switch (verticalAlignement)
    {
        case VA_TOP:
        {
            yPos = y;
            break;
        }
        case VA_CENTER:
        {
            yPos = y - Font::fontHeight / 2;
            break;
        }
        case VA_BOTTOM:
        {
            yPos = y - Font::fontHeight;
            break;
        }
    }

    while (string[i] != '\0')
    {
        DrawChar(xPos, yPos, string[i], color, lockToScreen);
        i++;
        xPos += Font::fontWidth + Font::fontSpacing;
    }
}

void GraphicsManager::DrawSpriteRect(SDL_Texture* texture, SDL_Rect& srcRect, SDL_Rect& dstRect)
{
}

void GraphicsManager::SwapFloat(float& a, float& b)
{
    float temp = a;
    a = b;
    b = temp;
}

void GraphicsManager::SwapVec2(Vec2& a, Vec2& b)
{
    Vec2 temp = a;
    a = b;
    b = temp;
}

void GraphicsManager::SwapInt(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void GraphicsManager::DisplayBresenhamCircle(const int xc, const int yc, const int x0, const int y0, const uint32_t color, const bool lockToScreen)
{
    if (lockToScreen)
    {
        DrawPixel(xc + x0, yc + y0, color);
        DrawPixel(xc - x0, yc + y0, color);
        DrawPixel(xc + x0, yc - y0, color);
        DrawPixel(xc - x0, yc - y0, color);
        DrawPixel(xc + y0, yc + x0, color);
        DrawPixel(xc - y0, yc + x0, color);
        DrawPixel(xc + y0, yc - x0, color);
        DrawPixel(xc - y0, yc - x0, color);
    }
    else
    {
        DrawPixel(xc + x0 + mScreenOffset.x, yc + y0 + mScreenOffset.y, color);
        DrawPixel(xc - x0 + mScreenOffset.x, yc + y0 + mScreenOffset.y, color);
        DrawPixel(xc + x0 + mScreenOffset.x, yc - y0 + mScreenOffset.y, color);
        DrawPixel(xc - x0 + mScreenOffset.x, yc - y0 + mScreenOffset.y, color);
        DrawPixel(xc + y0 + mScreenOffset.x, yc + x0 + mScreenOffset.y, color);
        DrawPixel(xc - y0 + mScreenOffset.x, yc + x0 + mScreenOffset.y, color);
        DrawPixel(xc + y0 + mScreenOffset.x, yc - x0 + mScreenOffset.y, color);
        DrawPixel(xc - y0 + mScreenOffset.x, yc - x0 + mScreenOffset.y, color);
    }
}

bool GraphicsManager::AARectInsideScreen(const AARectangle& rect)
{
    if (rect.topLeft.x > mScreenWidth ||
        rect.topLeft.y > mScreenHeight ||
        rect.bottomRight.x < 0 ||
        rect.bottomRight.y < 0)
        return false;

    return true;
}

void GraphicsManager::ClipAARectAgainstScreen(AARectangle& rect)
{
    if (rect.topLeft.x < 0) rect.topLeft.x = 0;
    if (rect.topLeft.y < 0) rect.topLeft.y = 0;
    if (rect.bottomRight.x > mScreenWidth) rect.bottomRight.x = mScreenWidth;
    if (rect.bottomRight.y > mScreenHeight) rect.bottomRight.y = mScreenHeight;
}
