-- premake5.lua
workspace "Puly Engine"
   configurations { "Debug", "Release" }
   platforms { "Win64" }

   filter { "platforms:Win64" }
    system "Windows"
    architecture "x64"

project "Puly"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs { "include", "src/imgui" }
   libdirs { "vendor" }
   links { "opengl32", "glew32s", "glfw3", "spdlogd", "soil2-debug", "glm_static", "nfd_d" }

   files { "**.h", "**.cpp" }

   filter "configurations:Debug"
      defines { "PL_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "PL_RELEASE" }
      optimize "On"
