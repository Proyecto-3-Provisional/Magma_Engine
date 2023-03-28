:: utilidad -> https://stackoverflow.com/questions/3827567/how-to-get-the-path-of-the-batch-script-in-windows
set dir_raiz=%~dp0

set dir_fuentes_ogre=%dir_raiz%dependencies\ogre\sources\ogre-13.6.1
set dir_sol_config_ogre=%dir_raiz%dependencies\ogre\builds\x64

set dir_fuentes_bullet=%dir_raiz%\dependencies\bullet\sources
set dir_sol_config_bullet=%dir_raiz%\dependencies\bullet\builds

set dir_fuentes_mixer=%dir_raiz%dependencies\sdl_mixer\sources
set dir_sol_config_mixer=%dir_raiz%dependencies\sdl_mixer\builds

set dir_fuentes_lua=%dir_raiz%dependencies\lua\sources
set dir_sol_config_lua=%dir_raiz%dependencies\lua\builds


:: PREPARAR LAS DEPENDENCIAS ::
:: Guía inicial -> https://ogrecave.github.io/ogre/api/latest/building-ogre.html

:: Situarse junto al ejecutable de cmake
cd .\dependencies\cmake\bin

:: OGRE DEBUG
:: Configurar fuentes para la plataforma
:: valor por defecto CMAKE_CONFIGURATION_TYPES="Debug;Release;MinSizeRel;RelWithDebInfo"
.\cmake.exe -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -DOGRE_PLUGIN_DIR=%dir_raiz%executables -DOGRE_BUILD_COMPONENT_BITES=off -DOGRE_BUILD_COMPONENT_BULLET=off -DOGRE_BUILD_COMPONENT_TERRAIN=off -DOGRE_BUILD_COMPONENT_VOLUME=off -DOGRE_BUILD_MSVC_MP=on -DOGRE_BUILD_MSVC_ZM=off -DOGRE_BUILD_RENDERSYSTEM_D3D9=off -DOGRE_BUILD_RENDERSYSTEM_D3D11=off -DOGRE_BUILD_RENDERSYSTEM_GL=on -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=off -DOGRE_BUILD_RENDERSYSTEM_GLES2=off -DOGRE_BUILD_RENDERSYSTEM_TINY=off -DOGRE_BUILD_RENDERSYSTEM_VULKAN=off -DOGRE_INSTALL_DOCS=off -DOGRE_INSTALL_PDB=off -DOGRE_INSTALL_CMAKE=off -DOGRE_INSTALL_VSPROPS=off -DOGRE_BUILD_SAMPLES=off -DOGRE_INSTALL_SAMPLES=off -DOGRE_BUILD_TOOLS=off -DOGRE_STATIC=off -DOGRE_PROFILING=off -DOGRE_BUILD_PLUGIN_ASSIMP=off -DOGRE_BUILD_PLUGIN_BSP=off -DOGRE_BUILD_PLUGIN_OCTREE=off -DOGRE_BUILD_PLUGIN_DOT_SCENE=off -DOGRE_BUILD_PLUGIN_PCZ=off -DOGRE_BUILD_PLUGIN_STBI=on -DOGRE_BUILD_COMPONENT_PYTHON=off -DOGRE_BUILD_COMPONENT_JAVA=off -DOGRE_BUILD_COMPONENT_CSHARP=off -S %dir_fuentes_ogre% -B %dir_sol_config_ogre%
:: Compilar solución fuente generada
.\cmake.exe --build %dir_sol_config_ogre% --config Debug
:: "Instalar" OGRE -> dir. "sdk"
.\cmake.exe --build %dir_sol_config_ogre% --config Debug --target install

:: OGRE RELEASE
:: Configurar fuentes para la plataforma
.\cmake.exe -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -DOGRE_PLUGIN_DIR=%dir_raiz%executables -DOGRE_BUILD_COMPONENT_BITES=off -DOGRE_BUILD_COMPONENT_BULLET=off -DOGRE_BUILD_COMPONENT_TERRAIN=off -DOGRE_BUILD_COMPONENT_VOLUME=off -DOGRE_BUILD_MSVC_MP=on -DOGRE_BUILD_MSVC_ZM=off -DOGRE_BUILD_RENDERSYSTEM_D3D9=off -DOGRE_BUILD_RENDERSYSTEM_D3D11=off -DOGRE_BUILD_RENDERSYSTEM_GL=on -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=off -DOGRE_BUILD_RENDERSYSTEM_GLES2=off -DOGRE_BUILD_RENDERSYSTEM_TINY=off -DOGRE_BUILD_RENDERSYSTEM_VULKAN=off -DOGRE_INSTALL_DOCS=off -DOGRE_INSTALL_PDB=off -DOGRE_INSTALL_CMAKE=off -DOGRE_INSTALL_VSPROPS=off -DOGRE_BUILD_SAMPLES=off -DOGRE_INSTALL_SAMPLES=off -DOGRE_BUILD_TOOLS=off -DOGRE_STATIC=off -DOGRE_PROFILING=off -DOGRE_BUILD_PLUGIN_ASSIMP=off -DOGRE_BUILD_PLUGIN_BSP=off -DOGRE_BUILD_PLUGIN_OCTREE=off -DOGRE_BUILD_PLUGIN_DOT_SCENE=off -DOGRE_BUILD_PLUGIN_PCZ=off -DOGRE_BUILD_PLUGIN_STBI=on -DOGRE_BUILD_COMPONENT_PYTHON=off -DOGRE_BUILD_COMPONENT_JAVA=off -DOGRE_BUILD_COMPONENT_CSHARP=off -S %dir_fuentes_ogre% -B %dir_sol_config_ogre%
:: Compilar solución fuente generada
.\cmake.exe --build %dir_sol_config_ogre% --config Release
:: "Instalar" OGRE -> dir. "sdk"
.\cmake.exe --build %dir_sol_config_ogre% --config Release --target install

:: BULLET DEBUG Y RELEASE
.\cmake.exe -DBUILD_BULLET3=on -DBUILD_BULLET2_DEMOS=off -DBUILD_BULLET_ROBOTICS_EXTRA=off -DBUILD_BULLET_ROBOTICS_GUI_EXTRA=off -DBUILD_CLSOCKET=off -DBUILD_CONVEX_DECOMPOSITION_EXTRA=off -DBUILD_CPU_DEMOS=off -DBUILD_ENET=off -DBUILD_EXTRAS=off -DBUILD_GIMPACTUTILS_EXTRA=off -DBUILD_HACD_EXTRA=off -DBUILD_INVERSE_DYNAMIC_EXTRA=off -DBUILD_OBJ2SDF_EXTRA=off -DBUILD_OPENGL3_DEMOS=off -DBUILD_SERIALIZE_EXTRA=off -DBUILD_UNIT_TESTS=off -DENABLE_VHACD=off -DUSE_MSVC_RUNTIME_LIBRARY_DLL=on -S %dir_fuentes_bullet% -B %dir_sol_config_bullet% 

.\cmake.exe --build %dir_sol_config_bullet% --config Debug

.\cmake.exe --build %dir_sol_config_bullet% --config Release

:: LUABRIDGE DEBUG Y RELEASE
.\cmake.exe %dir_fuentes_lua% -B %dir_sol_config_lua%

.\cmake.exe --build %dir_sol_config_lua% --config Debug

.\cmake.exe --build %dir_sol_config_lua% --config Release

:: Volver a la raíz
cd %dir_raiz%

:: Alguna de las dependencias de OGRE también la usaremos nosotros directamente en Magma, y además la queremos tanto en Debug como en Release...
:: Por algún motivo después de llegar a este punto, no se regenera la build interna de SDL para Ogre con la nueva configuración, y solo queda la antigua.
:: Compilamos SDL manualmente aparte para obtener la .dll que nos falta
cd .\dependencies\ogre\builds\x64\SDL2-build
msbuild SDL2.sln -p:Configuration=Release -noLogo -verbosity:minimal -maxCpuCount
cd %dir_raiz%
copy .\dependencies\ogre\builds\x64\SDL2-build\Release\SDL2.dll .\dependencies\ogre\builds\x64\sdk\bin
:: También pasa con zlib...
cd .\dependencies\ogre\builds\x64\zlib-1.2.13
msbuild zlib.sln -p:Configuration=Release -noLogo -verbosity:minimal -maxCpuCount
cd %dir_raiz%
copy .\dependencies\ogre\builds\x64\zlib-1.2.13\Release\zlib.dll .\dependencies\ogre\builds\x64\sdk\bin

cd .\dependencies\cmake\bin

:: SDL_MIXER DEBUG Y RELEASE
:: Configurar fuentes para la plataforma
.\cmake.exe  -DSDL2_DIR="../../ogre/builds/x64/SDL2-build/CMakeFiles" -DSDL2_LIBRARY="../../ogre/builds/x64/SDL2-build/Release/SDL2.lib" -DSDL2_INCLUDE_DIR="../../ogre/builds/x64/SDL2-build/include" -DCMAKE_POSITION_INDEPENDENT_CODE=on -DINSTALL_CMAKE_PACKAGE_MODULE=off -DSDL2MIXER_CMD=off -DSDL2MIXER_DEPS_SHARED=on -DSDL2MIXER_FLAC=off -DSDL2MIXER_INSTALL=on -DSDL2MIXER_MIDI=off -DSDL2MIXER_MOD=off -DSDL2MIXER_MP3=on -DSDL2MIXER_DRMP3=on -DSDL2MIXER_MP3_MPG123=off -DSDL2MIXER_OPUS=off -DSDL2MIXER_SAMPLES=off -DSDL2MIXER_SAMPLES_INSTALL=off -DSDL2MIXER_VENDORED=off -DSDL2MIXER_VORBIS=STB -DSDL2MIXER_WAVE=on -S %dir_fuentes_mixer% -B %dir_sol_config_mixer%
:: Compilar solución fuente generada

copy ..\..\ogre\builds\x64\SDL2-build\include-config-debug\SDL_config.h ..\..\ogre\builds\x64\SDL2-build\include

.\cmake.exe --build %dir_sol_config_mixer% --config Debug

del ..\..\ogre\builds\x64\SDL2-build\include\SDL_config.h
copy ..\..\ogre\builds\x64\SDL2-build\include-config-release\SDL_config.h ..\..\ogre\builds\x64\SDL2-build\include

.\cmake.exe --build %dir_sol_config_mixer% --config Release 
cd %dir_raiz%

:: Copia de ficheros necesarios al dir. de salida
mkdir executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreMain.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreMain_d.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreOverlay.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreOverlay_d.dll .\executables
copy .\dependencies\ogre\builds\x64\SDL2-build\Release\SDL2.dll .\executables
copy .\dependencies\ogre\builds\x64\SDL2-build\Debug\SDL2d.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\plugins.cfg .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\RenderSystem_GL.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\RenderSystem_GL_d.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\Plugin_ParticleFX.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\Plugin_ParticleFX_d.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\Codec_STBI.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\Codec_STBI_d.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\zlib.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\zlibd.dll .\executables
copy .\dependencies\sdl_mixer\builds\Debug\SDL2_mixerd.dll .\executables
copy .\dependencies\sdl_mixer\builds\Release\SDL2_mixer.dll .\executables

:: COMPILAR LA SOLUCIÓN DEL MOTOR ::
:: niveles de verborrea: q[uiet], m[inimal], n[ormal], d[etailed], diag[nostic]
msbuild .\Magma.sln -p:Configuration=Debug -noLogo -verbosity:minimal -maxCpuCount
msbuild .\Magma.sln -p:Configuration=Release -noLogo -verbosity:minimal -maxCpuCount


echo ========-----========__Fin_del_Script__========-----========
