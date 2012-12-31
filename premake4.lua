-- this is a premake4 script
-- see http://industriousone.com/premake

solution "mcomm"
	language "C++"
	configurations { "debug", "release" }

	configuration "debug"
		targetdir "build/debug"
		flags "Symbols"
		defines "DEBUG"

	configuration "release"
		targetdir "build/release"
		defines { "RELEASE", "NDEBUG" }

	configuration "linux or macosx"
		defines { "UNIX" }

	project "mcomm"
		kind "ConsoleApp"
		files { "./src/**.h", "./src/**.cc", "./src/**.cpp" }
		includedirs { "./src", "./src/3rdparty/include" }
		buildoptions { "-std=c++0x" }
		links { "sfml-system", "sfml-window", "sfml-graphics", "boost_iostreams" }
