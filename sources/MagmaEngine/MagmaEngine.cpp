// MagmaEngine.cpp : Define las funciones exportadas del archivo DLL.
//

#include "pch.h"
#include "framework.h"
#include "MagmaEngine.h"

CMagmaEngine* CMagmaEngine::_instance = nullptr;

// Ejemplo de variable exportada
MAGMAENGINE_API int nMagmaEngine=0;

// Ejemplo de función exportada.
MAGMAENGINE_API int fnMagmaEngine(void)
{
    return 0;
}

// Constructor de clase exportada.
CMagmaEngine::CMagmaEngine()
{
    return;
}

bool CMagmaEngine::Init()
{
    if (_instance == nullptr)
    {
        _instance = new CMagmaEngine();

        // Aqui deberiamos de meter las instancias de todos los proyectos

        return true;
    }
    


    return false;
}

bool CMagmaEngine::ShutDown()
{

}

void CMagmaEngine::run()
{

}

