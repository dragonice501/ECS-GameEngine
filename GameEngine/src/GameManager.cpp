#include "GameManager.h"

#include "AssetManager.h"
#include "Components.h"

#include "Logger.h"

#include <fstream>

void GameManager::LoadLevel(size_t numLevel, std::unique_ptr<Registry>& registry, sol::state& lua)
{
	std::string path = SDL_GetBasePath();
	path += "assets\\scripts\\level" + std::to_string(numLevel) + ".lua";
	sol::load_result script = lua.load_file(path);
	
	if (!script.valid())
	{
		sol::error err = script;
		Logger::Error(err.what());
		return;
	}

	lua.script_file(path);

	sol::table level = lua["Level"];

	sol::table assets = level["assets"];
	int i = 0;
	while (true)
	{
		sol::optional<sol::table> hasAsset = assets[i];
		if (hasAsset == sol::nullopt) break;

		sol::table asset = assets[i];

		std::string assetType = asset["type"];
		if (assetType == "texture")
		{
			AssetManager::AddTexture(asset["id"], asset["file"]);
		}
		else if (assetType == "font")
		{
			AssetManager::AddTexture(asset["id"], asset["file"]);
		}

		i++;
	}

	sol::table map = level["tilemap"];
	std::string mapName = map["map_file"];
	std::string mapTextureAssetId = map["texture_asset_id"];

	int mapNumRows = map["num_rows"];
	int mapNumCols = map["num_cols"];
	int tileSize = map["tile_size"];
	double mapScale = map["scale"];

	std::fstream mapFile;
    std::string mapFilePath = SDL_GetBasePath();
    mapFilePath += "assets\\tilemaps\\" + mapName;
	mapFile.open(mapFilePath);
	for (int y = 0; y < mapNumRows; y++)
	{
		for (int x = 0; x < mapNumCols; x++)
		{
			char ch;
			mapFile.get(ch);
			int srcRectY = std::atoi(&ch) * tileSize;
			mapFile.get(ch);
			int srcRectX = std::atoi(&ch) * tileSize;
			mapFile.ignore();

			Entity tile = registry->CreateEntity();
			tile.AddComponent<TransformComponent>(Vec2(x * (mapScale * tileSize), y * (mapScale * tileSize)), Vec2(mapScale, mapScale), 0.0);
			tile.AddComponent<SpriteComponent>(mapTextureAssetId, 0, tileSize, tileSize, srcRectX, srcRectY);
		}
	}
	mapFile.close();

    sol::table entities = level["entities"];
    i = 0;
    while (true)
    {
        sol::optional<sol::table> hasEntity = entities[i];
        if (hasEntity == sol::nullopt) break;

        sol::table entity = entities[i];

        Entity newEntity = registry->CreateEntity();

        sol::optional<std::string> tag = entity["tag"];
        if (tag != sol::nullopt)
        {
            newEntity.Tag(entity["tag"]);
        }

        sol::optional<std::string> group = entity["group"];
        if (group != sol::nullopt)
        {
            newEntity.Group(entity["group"]);
        }

        sol::optional<sol::table> animation = entity["components"]["animation"];
        if (animation != sol::nullopt)
        {
            newEntity.AddComponent<AnimationComponent>(
                entity["components"]["animation"]["num_frames"].get_or(1),
                entity["components"]["animation"]["speed_rate"].get_or(1));
        }

        sol::optional<sol::table> collider = entity["components"]["boxcollider"];
        if (collider != sol::nullopt)
        {
            newEntity.AddComponent<BoxCollider2DComponent>(
                entity["components"]["boxcollider"]["width"],
                entity["components"]["boxcollider"]["height"],
                Vec2(
                    entity["components"]["boxcollider"]["offset"]["x"].get_or(0),
                    entity["components"]["boxcollider"]["offset"]["y"].get_or(0)));
        }

        sol::optional<sol::table> cameraFollow = entity["components"]["camera_follow"];
        if (cameraFollow != sol::nullopt)
        {
            newEntity.AddComponent<CameraFollowComponent>();
        }

        sol::optional<sol::table> health = entity["components"]["health"];
        if (health != sol::nullopt)
        {
            newEntity.AddComponent<HealthComponent>(
                static_cast<int>(entity["components"]["health"]["health_percentage"].get_or(100)));
        }

        sol::optional<sol::table> keyboardControlled = entity["components"]["keyboard_controller"];
        if (keyboardControlled != sol::nullopt)
        {
            newEntity.AddComponent<KeyboardControlComponent>(
                Vec2(
                    entity["components"]["keyboard_controller"]["up_velocity"]["x"],
                    entity["components"]["keyboard_controller"]["up_velocity"]["y"]),
                Vec2(
                    entity["components"]["keyboard_controller"]["down_velocity"]["x"],
                    entity["components"]["keyboard_controller"]["down_velocity"]["y"]),
                Vec2(
                    entity["components"]["keyboard_controller"]["right_velocity"]["x"],
                    entity["components"]["keyboard_controller"]["right_velocity"]["y"]),
                Vec2(
                    entity["components"]["keyboard_controller"]["left_velocity"]["x"],
                    entity["components"]["keyboard_controller"]["left_velocity"]["y"]));
        }

        sol::optional<sol::table> projectileEmitter = entity["components"]["projectile_emitter"];
        if (projectileEmitter != sol::nullopt)
        {
            newEntity.AddComponent<ProjectileEmitterComponent>(
                Vec2(
                    entity["components"]["projectile_emitter"]["projectile_velocity"]["x"],
                    entity["components"]["projectile_emitter"]["projectile_velocity"]["y"]),
                static_cast<int>(entity["components"]["projectile_emitter"]["repeat_frequency"].get_or(1)),
                static_cast<int>(entity["components"]["projectile_emitter"]["projectile_duration"].get_or(10)),
                static_cast<int>(entity["components"]["projectile_emitter"]["hit_percentage_damage"].get_or(10)),
                entity["components"]["projectile_emitter"]["friendly"].get_or(false));
        }

        sol::optional<sol::table> rigidbody = entity["components"]["rigidbody"];
        if (rigidbody != sol::nullopt)
        {
            newEntity.AddComponent<RigidbodyComponent>(
                Vec2(
                    entity["components"]["rigidbody"]["velocity"]["x"].get_or(0.0),
                    entity["components"]["rigidbody"]["velocity"]["y"].get_or(0.0)));
        }

        sol::optional<sol::table> script = entity["components"]["onUpdateScript"];
        if (script != sol::nullopt)
        {
            sol::function func = entity["components"]["onUpdateScript"][0];
            newEntity.AddComponent<ScriptComponent>(func);
        }

        sol::optional<sol::table> sprite = entity["components"]["sprite"];
        if (sprite != sol::nullopt)
        {
            newEntity.AddComponent<SpriteComponent>(
                entity["components"]["sprite"]["texture_asset_id"],
                entity["components"]["sprite"]["z_index"].get_or(1),
                entity["components"]["sprite"]["width"],
                entity["components"]["sprite"]["height"],
                entity["components"]["sprite"]["src_rect_x"].get_or(0),
                entity["components"]["sprite"]["src_rect_y"].get_or(0),
                entity["components"]["sprite"]["fixed"].get_or(false));
        }

        sol::optional<sol::table> hasComponents = entity["components"];
        if (hasComponents != sol::nullopt)
        {
            sol::optional<sol::table> transform = entity["components"]["transform"];
            if (transform != sol::nullopt)
            {
                newEntity.AddComponent<TransformComponent>(
                    Vec2(
                        entity["components"]["transform"]["position"]["x"],
                        entity["components"]["transform"]["position"]["y"]),
                    Vec2(
                        entity["components"]["transform"]["scale"]["x"].get_or(1.0),
                        entity["components"]["transform"]["scale"]["y"].get_or(1.0)),
                    entity["components"]["transform"]["rotation"].get_or(0.0));
            } 
        }
        i++;
    }
}
