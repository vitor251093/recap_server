project "darkspore_server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"
    targetdir "build/%{cfg.buildcfg}"
    files {
      "source/**.h",
      "source/**.cpp"
    }
    includedirs {
      "source",
      "libs/raknet-3.902-mod/Source",
      "libs/sol2",
      "libs/LuaJIT/include",
      "libs/glm",
      "libs/lodepng",
      "libs/cpp-base64",
      "libs/pugixml-1.9/include",
      "libs/rapidjson-1.1.0/include",
      "libs/openssl-1.1.1b/include",
      "libs/boost_1_73_0"
    }
    libdirs {
      "libs/LuaJIT/lib64",
      "libs/raknet-3.902-mod/Lib",
      "libs/pugixml-1.9/lib",
      "libs/openssl-1.1.1b/lib",
      "libs/boost_1_73_0/stage/lib"
    }
    links {
      "libssl.lib",
      "libcrypto.lib",
      "pugixml.lib",
      "RakNetDLL.lib",
      "lua51.lib"
    }
    defines {
      "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
      "_WIN32_WINNT=0x0601",
      "_CRT_SECURE_NO_WARNINGS",
      "WIN32_LEAN_AND_MEAN",
      "NOMINMAX",
      "BOOST_NETWORK_ENABLE_HTTPS",
      "BOOST_ASIO_DISABLE_CONCEPTS",
      "RAPIDJSON_HAS_STDSTRING",
      "SOL_STRINGS_ARE_NUMBERS=1",
      "SOL_SAFE_FUNCTION=1",
      "SOL_LUAJIT=1",
      "SOL_EXCEPTIONS_SAFE_PROPAGATION=1"
    }
