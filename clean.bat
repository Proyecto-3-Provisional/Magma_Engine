:: Borrar ficheros intermedios de nuestra solución
rmdir /Q /S temporary

:: Borrar directorios de salida de librerías ('proyectos' de los que depende Magma) de nuestra solución
rmdir /Q /S libraries

:: Borrar ejecutable del programa y otros ficheros de los que depende
cd executables
del *.exe
del *.pdb
del *.dll
del *.cfg
cd ..

:: Borrar compliación de Ogre (~4 GB)
echo =-==-= Borrando compilaciones de dependencias... =-==-=
echo =-==-= Por favor ESPERA unos instantes mientras la operación se completa... =-==-=
rmdir /Q /S dependencies\ogre\builds\x64
echo =-==-= Compilaciones de dependencias borradas =-==-=

:: NOTAS :: :: :: :: :: :: :: ::
::
:: Borrado de un directorio no vacío por teminal de Windows 11:
:: C:\> Remove-Item -Recurse .\temporary\
::
:: Borrado de un directorio no vacío por teminal de desarrollador de VS:
:: C:\> rmdir /Q /S temporary
:: Ayuda acerca de esto:
:: C:\> rmdir /?
::
:: Otra ayuda:
:: https://pureinfotech.com/delete-folders-subfolders-command-windows-10/
::
