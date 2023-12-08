workspace "darkspore_server"
  configurations {
    "Debug",
    "Release"
  }

  platforms {
    "x64"
  }

  filter "platforms:x64"
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