-- this is a premake5 script
-- see http://industriousone.com/premake

solution "mcomm"
    language "C++"
	kind "ConsoleApp"

    buildoptions { "-std=c++14" }
    configurations { "debug", "release" }

    links {
        "sfml-system",
        "sfml-window",
        "sfml-graphics",
        "boost_iostreams",
        "boost_python3",
        "glog",
        "python3.4m",
        "Box2D",
        "camp",
    }

    includedirs {
        "./src",
        "./src/3rdparty/include",
        "/usr/include/python3.4m",
    }

    libdirs {
        "./src/3rdparty/lib"
    }

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
        files {
            "./src/**.h",
            "./src/**.cc",
            "./src/**.cpp",
            "./generated/generated.cc",
        }
        pchheader "precompiled.h"

    project "test"
        kind "ConsoleApp"
        files {
            "./src/3rdparty/src/jsonxx.cc",
            "./src/simulation/components/transformcomponent.cc",
            "./src/simulation/components/textcomponent.cc",
            "./src/simulation/component.cc",
            "./src/simulation/entity.cc",
            "./src/simulation/components/spritecomponent.cc",
            "./src/media/texturemanager.cc",
            "./src/3rdparty/**.cc",
            "./src/3rdparty/**.h",
            "./src/simulation/factories.cc",
            "./test/**.cc", "./test/**.h"
        }

        includedirs { "./test/include" }
        links "gtest"
