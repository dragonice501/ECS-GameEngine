#pragma once

#include "Engine.h"
#include "GraphicsManager.h"
#include "AssetManager.h"

#include "ECS.h"
#include "Components.h"
#include "Events.h"

#include <SDL.h>
#include <algorithm>
#include <imgui.h>
#include <imgui_sdl.h>

class RenderSystem : public System
{
public:
	RenderSystem()
	{
		RequireComponent<SpriteComponent>();
		RequireComponent<TransformComponent>();
	}

	void Draw()
	{
		std::vector<Entity>& entities = GetSystemEntities();
		std::sort(entities.begin(), entities.end(), [](Entity& a, Entity& b)
			{
				const auto& spriteA = a.GetComponent<SpriteComponent>();
				const auto& spriteB = b.GetComponent<SpriteComponent>();

				return spriteA.zIndex < spriteB.zIndex;
			});

		SDL_Rect& camera = GraphicsManager::GetCamera();

		for (auto entity : GetSystemEntities())
		{
			const auto& sprite = entity.GetComponent<SpriteComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();

			SDL_Rect dstRect =
			{
				transform.position.x - (sprite.isFixed ? 0 : camera.x),
				transform.position.y - (sprite.isFixed ? 0 : camera.y),
				sprite.width * transform.scale.x,
				sprite.height * transform.scale.y
			};

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			SDL_RenderCopyEx(GraphicsManager::GetRenderer(), AssetManager::GetTexture(sprite.assetId), &sprite.srcRect, &dstRect, transform.rotation, NULL, flip);
		}
	}
};

class RenderGUISystem : public System
{
public:
	RenderGUISystem() {}

	void Draw()
	{
		ImGui::NewFrame();

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_AlwaysAutoResize;
		if (ImGui::Begin("Window"), NULL, flags);
		{
			ImGui::Text("This is text");
		}
		ImGui::End();

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
	}
};

class RenderLineSystem : public System
{
public:
	RenderLineSystem()
	{
		RequireComponent<LineComponent>();
	}

	void Draw()
	{
		for (auto entity : GetSystemEntities())
		{
			const auto& line = entity.GetComponent<LineComponent>();
			
			GraphicsManager::DrawLine(
				static_cast<int>(line.p1.x),
				static_cast<int>(line.p1.y),
				static_cast<int>(line.p2.x),
				static_cast<int>(line.p2.y),
				0xFFFFFF00);
		}
	}
};

class RenderParticleSystem : public System
{
public:
	RenderParticleSystem()
	{
		RequireComponent<TransformComponent>();
	}

	void Draw()
	{
		for (auto entity : GetSystemEntities())
		{
			const auto& transform = entity.GetComponent<TransformComponent>();

			//GraphicsManager::DrawPixel(static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), 0xFFFF0000);
			GraphicsManager::DrawFillCircle(static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), 2, 0xFFFF0000);
		}
	}
};

class RenderTextSystem : public System
{
public:
	RenderTextSystem()
	{
		RequireComponent<TextLabelComponent>();
	}

	void Draw()
	{
		SDL_Rect camera = GraphicsManager::GetCamera();

		for (auto entity : GetSystemEntities())
		{
			const auto text = entity.GetComponent<TextLabelComponent>();

			SDL_Surface* surface = TTF_RenderText_Blended(AssetManager::GetFont(text.assetId), text.text.c_str(), text.color);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);

			int textWidth = 0;
			int textHeight = 0;

			SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

			GraphicsManager::DrawTexture(
				text.position.x - camera.x,
				text.position.y - camera.y,
				textWidth,
				textHeight,
				0.0f,
				texture);

			SDL_DestroyTexture(texture);
			SDL_FreeSurface(surface);
		}
	}
};
