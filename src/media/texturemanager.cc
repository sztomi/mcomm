#include "precompiled.h"

#include "texturemanager.h"

#ifdef BOOST_OS_LINUX
	#include <unistd.h>
#else
	#include <direct.h>
	#define getcwd _getcwd
#endif

namespace mcomm
{

TextureManager::TextureManager()
{
	char path[1024];
	getcwd(path, sizeof(path));
	m_workingDir = path;
}

void TextureManager::addTexture(const std::string& fileName, const std::string& id)
{
	auto tex = std::make_shared<sf::Texture>();
	auto fullFileName = boost::str(boost::format("%1%/%2%")
									% m_workingDir
									% fileName);
	tex->loadFromFile(fileName);
	m_textures[id] = tex;
}

std::shared_ptr<sf::Texture> TextureManager::texture(const std::string& id)
{
	return m_textures[id];
}

}
