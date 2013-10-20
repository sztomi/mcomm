-- this is a premake4 script
-- see http://industriousone.com/premake

solution "mcomm"
    language "C++"
    includedirs { "./src", "./src/3rdparty/include", "./src/3rdparty/include/lua" }
    libdirs { "./src/3rdparty/lib" }
    links 
    {
        "sfml-system",
        "sfml-window",
        "sfml-graphics",
        "boost_iostreams",
        "glog",
        "lua"
    }
    buildoptions { "-std=c++11" }

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

    project "test"
        kind "ConsoleApp"
        files 
        { 
            "./src/3rdparty/src/jsonxx.cc",
            "./src/simulation/components/transformcomponent.cc",
            "./src/simulation/components/textcomponent.cc",
            "./src/simulation/component.cc",
            "./src/simulation/entity.cc",
            --"./src/simulation/components/spritecomponent.cc",
            "./src/media/texturemanager.cc",
            "./src/3rdparty/**.cc",
            "./src/3rdparty/**.h",
            "./src/simulation/factories.cc",
            "./test/**.cc", "./test/**.h" 
        }

        includedirs { "./test/include" }
        libdirs { "./test/lib" }
        links "gtest"
