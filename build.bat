:: utilidad -> https://stackoverflow.com/questions/3827567/how-to-get-the-path-of-the-batch-script-in-windows
set dir_raiz=%~dp0

set dir_fuentes=%dir_raiz%dependencies\ogre\sources\ogre-13.6.1
set dir_sol_config=%dir_raiz%dependencies\ogre\builds\x64


:: PREPARAR LAS DEPENDENCIAS ::

:: Situarse junto al ejecutable de cmake
cd .\dependencies\cmake\bin

:: OGRE DEBUG
:: Configurar fuentes para la plataforma
:: valor por defecto CMAKE_CONFIGURATION_TYPES="Debug;Release;MinSizeRel;RelWithDebInfo"
.\cmake.exe -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -DOGRE_BUILD_COMPONENT_BITES=off -DOGRE_BUILD_COMPONENT_BULLET=on -DOGRE_BUILD_COMPONENT_TERRAIN=off -DOGRE_BUILD_COMPONENT_VOLUME=off -DOGRE_BUILD_MSVC_MP=on -DOGRE_BUILD_MSVC_ZM=off -DOGRE_BUILD_RENDERSYSTEM_D3D9=off -DOGRE_BUILD_RENDERSYSTEM_D3D11=off -DOGRE_BUILD_RENDERSYSTEM_GL=on -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=off -DOGRE_BUILD_RENDERSYSTEM_GLES2=off -DOGRE_BUILD_RENDERSYSTEM_TINY=off -DOGRE_BUILD_RENDERSYSTEM_VULKAN=off -DOGRE_INSTALL_DOCS=off -DOGRE_INSTALL_PDB=off -DOGRE_INSTALL_CMAKE=off -DOGRE_INSTALL_VSPROPS=off -DOGRE_BUILD_SAMPLES=off -DOGRE_INSTALL_SAMPLES=off -DOGRE_BUILD_TOOLS=off -DOGRE_STATIC=off -DOGRE_PROFILING=off -DOGRE_BUILD_PLUGIN_ASSIMP=off -DOGRE_BUILD_PLUGIN_BSP=off -DOGRE_BUILD_PLUGIN_OCTREE=off -DOGRE_BUILD_PLUGIN_DOT_SCENE=off -DOGRE_BUILD_PLUGIN_PCZ=off -DOGRE_BUILD_COMPONENT_PYTHON=off -DOGRE_BUILD_COMPONENT_JAVA=off -DOGRE_BUILD_COMPONENT_CSHARP=off -S %dir_fuentes% -B %dir_sol_config%
:: Compilar solución fuente generada
.\cmake.exe --build %dir_sol_config% --config Debug
:: "Instalar" OGRE -> dir. "sdk"
.\cmake.exe --build %dir_sol_config% --config Debug --target install

:: OGRE RELEASE
:: Configurar fuentes para la plataforma
.\cmake.exe -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -DOGRE_BUILD_COMPONENT_BITES=off -DOGRE_BUILD_COMPONENT_BULLET=on -DOGRE_BUILD_COMPONENT_TERRAIN=off -DOGRE_BUILD_COMPONENT_VOLUME=off -DOGRE_BUILD_MSVC_MP=on -DOGRE_BUILD_MSVC_ZM=off -DOGRE_BUILD_RENDERSYSTEM_D3D9=off -DOGRE_BUILD_RENDERSYSTEM_D3D11=off -DOGRE_BUILD_RENDERSYSTEM_GL=on -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=off -DOGRE_BUILD_RENDERSYSTEM_GLES2=off -DOGRE_BUILD_RENDERSYSTEM_TINY=off -DOGRE_BUILD_RENDERSYSTEM_VULKAN=off -DOGRE_INSTALL_DOCS=off -DOGRE_INSTALL_PDB=off -DOGRE_INSTALL_CMAKE=off -DOGRE_INSTALL_VSPROPS=off -DOGRE_BUILD_SAMPLES=off -DOGRE_INSTALL_SAMPLES=off -DOGRE_BUILD_TOOLS=off -DOGRE_STATIC=off -DOGRE_PROFILING=off -DOGRE_BUILD_PLUGIN_ASSIMP=off -DOGRE_BUILD_PLUGIN_BSP=off -DOGRE_BUILD_PLUGIN_OCTREE=off -DOGRE_BUILD_PLUGIN_DOT_SCENE=off -DOGRE_BUILD_PLUGIN_PCZ=off -DOGRE_BUILD_COMPONENT_PYTHON=off -DOGRE_BUILD_COMPONENT_JAVA=off -DOGRE_BUILD_COMPONENT_CSHARP=off -S %dir_fuentes% -B %dir_sol_config%
:: Compilar solución fuente generada
.\cmake.exe --build %dir_sol_config% --config Release
:: "Instalar" OGRE -> dir. "sdk"
.\cmake.exe --build %dir_sol_config% --config Release --target install

:: Volver a la raíz
cd ..\..\..

:: Una de las dependencias de OGRE también la usaremos nosotros directamente en Magma, y además la queremos tanto en Debug como en Release...
:: Por algún motivo después de llegar a este punto, no se regenera la build interna de SDL para Ogre con la nueva configuración, y solo queda la antigua.
:: Compilamos SDL manualmente aparte para obtener la .dll que nos falta
cd .\dependencies\ogre\builds\x64\SDL2-build
msbuild SDL2.sln -p:Configuration=Release -noLogo -verbosity:normal -maxCpuCount
cd %dir_raiz%
copy .\dependencies\ogre\builds\x64\SDL2-build\Release\SDL2.dll .\dependencies\ogre\builds\x64\sdk\bin

:: Copia de ficheros necesarios al dir. de salida
mkdir executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreMain.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreMain_d.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreOverlay.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreOverlay_d.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\plugins.cfg .\executables
copy .\dependencies\ogre\builds\x64\SDL2-build\Release\SDL2.dll .\executables
copy .\dependencies\ogre\builds\x64\SDL2-build\Debug\SDL2d.dll .\executables


:: COMPILAR LA SOLUCIÓN DEL MOTOR
:: niveles de verborrea: q[uiet], m[inimal], n[ormal], d[etailed], diag[nostic].
msbuild .\Magma.sln -p:Configuration=Debug -noLogo -verbosity:minimal -maxCpuCount
msbuild .\Magma.sln -p:Configuration=Release -noLogo -verbosity:minimal -maxCpuCount

echo ========-----========__Fin_del_Script__========-----========
