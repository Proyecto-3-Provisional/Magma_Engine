:: utilidad -> https://stackoverflow.com/questions/3827567/how-to-get-the-path-of-the-batch-script-in-windows
set dir_raiz=%~dp0

set dir_fuentes=%dir_raiz%dependencies\ogre\sources\ogre-13.6.1
set dir_sol_config=%dir_raiz%dependencies\ogre\builds\x64

:: PREPARAR LAS DEPENDENCIAS
:: Situarse junto al ejecutable
cd .\dependencies\cmake\bin
:: Configurar fuentes para la plataforma
:: valor por defecto -DCMAKE_CONFIGURATION_TYPES="Debug;Release;MinSizeRel;RelWithDebInfo"
.\cmake.exe -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -DOGRE_BUILD_COMPONENT_BITES=off -DOGRE_BUILD_COMPONENT_BULLET=on -DOGRE_BUILD_MSVC_MP=on -DOGRE_BUILD_MSVC_ZM=off -DOGRE_BUILD_RENDERSYSTEM_D3D9=off -DOGRE_BUILD_RENDERSYSTEM_D3D11=off -DOGRE_BUILD_RENDERSYSTEM_GL=on -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=off -DOGRE_BUILD_RENDERSYSTEM_GLES2=off -DOGRE_BUILD_RENDERSYSTEM_TINY=off -DOGRE_BUILD_RENDERSYSTEM_VULKAN=off -DOGRE_INSTALL_DOCS=off -DOGRE_INSTALL_PDB=on -DOGRE_BUILD_SAMPLES=off -DOGRE_BUILD_TOOLS=off -DOGRE_STATIC=off -DOGRE_PROFILING=off -S %dir_fuentes% -B %dir_sol_config%
:: Compilar solución fuente generada
.\cmake.exe --build %dir_sol_config% --config Release
:: Compilar solución fuente generada: "instalar" OGRE -> dir. "sdk"
.\cmake.exe --build %dir_sol_config% --config Release --target install
:: Volver a la raíz
cd ..\..\..
:: Copia de ficheros necesarios al dir. de salida
mkdir executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreMain.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\OgreOverlay.dll .\executables
copy .\dependencies\ogre\builds\x64\sdk\bin\plugins.cfg .\executables
copy .\dependencies\ogre\builds\x64\SDL2-build\Release\SDL2.dll .\executables


:: COMPILAR LA SOLUCIÓN DEL MOTOR
:: niveles de verborrea: q[uiet], m[inimal], n[ormal], d[etailed], diag[nostic].
msbuild .\Magma.sln -p:Configuration=Release -noLogo -verbosity:minimal -maxCpuCount

echo ========-----========__Fin_del_Script__========-----========
