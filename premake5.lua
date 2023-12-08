workspace "darkspore_server"
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

    defines {
      "NDEBUG"
    }

include "darkspore_server"