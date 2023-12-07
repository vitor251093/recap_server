workspace "DarkSporeServer"
  project "DarkSporeServer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "darkspore_server/build/%{cfg.buildcfg}"
    files {
      "darkspore_server/source/**.h",
      "darkspore_server/source/**.cpp"
    }
    includedirs {
      "darkspore_server/source",
      "darkspore_server/libs/raknet-3.902-mod/Source",
      "darkspore_server/libs/sol2",
      "darkspore_server/libs/LuaJIT/include",
      "darkspore_server/libs/glm",
      "darkspore_server/libs/lodepng",
      "darkspore_server/libs/cpp-base64",
      "darkspore_server/libs/pugixml-1.9/include",
      "darkspore_server/libs/rapidjson-1.1.0/include",
      "darkspore_server/libs/openssl-1.1.1b/include",
      "darkspore_server/libs/boost_1_73_0
    }
    libdirs {
      "darkspore_server/libs/LuaJIT/lib64",
      "darkspore_server/libs/raknet-3.902-mod/Lib",
      "darkspore_server/libs/pugixml-1.9/lib",
      "darkspore_server/libs/openssl-1.1.1b/lib",
      "darkspore_server/libs/boost_1_73_0/stage/lib"
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
      "NDEBUG",
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
    
    configurations {
      "Debug",
      "Release"
    }

    platforms {
      "Win32",
      "x64"
    }

    filter "platform:Win32"
      system "Windows"
      architecture "x86"

    filter "platform:x64"
      system "Windows"
      architecture "x86_64"

    filter "configurations:Debug"
      runtime "Debug"
      symbols "On"
      optimize "Off"
    
    filter "configurations:Release"
      runtime "Release"
      symbols "Off"
      optimize "On"

    filter {}