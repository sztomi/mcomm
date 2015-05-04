#pragma once

#include "precompiled.h"

namespace sf
{
	class Texture;
}

namespace mcomm
{

class TextureManager
{
public:
	static TextureManager& instance()
	{
		static TextureManager inst;
		return inst;
	}

	void addTexture(const std::string& fileName, const std::string& id);
	std::shared_ptr<sf::Texture> texture(const std::string& id);

private:
	TextureManager();

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	std::string m_workingDir;
};

}
