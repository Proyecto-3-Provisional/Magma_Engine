// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <cassert>
#include <cstdint>
#include <limits>

#include <EC/mpl.h>

namespace magma_engine
{
	//Struct para el grupo "general", no se debe usar en los grupos definidos por el usuario
	struct _grp_GENERAL;


	//ver ecs_defs para las listas de componentes, grupos...
#if __has_include("ec_defs.h")
#include <EC/ec_defs.h>
#endif

#ifndef _CMPS_LIST_
#define _ext_CMPS_LIST_
#else
#define _ext_CMPS_LIST_ _CMPS_LIST_
#endif

#ifndef _GRPS_LIST_
#define _ext_GRPS_LIST_ _grp_GENERAL
#else
#define _ext_GRPS_LIST_ _grp_GENERAL,_GRPS_LIST_
#endif

	namespace ec {
		struct Component;
		class Entity;
		class EntityManager;

		//listas para grupos y componentes
		using CmpsList = mpl::TypeList<_ext_CMPS_LIST_>;
		using GrpsList = mpl::TypeList<_grp_GENERAL, _ext_GRPS_LIST_>;


		//escoge un uInt con tamaño apropiado para guardar las distintas IDs
		using cmpId_type = mpl::numeric_type<CmpsList::size>::type;
		using grpId_type = mpl::numeric_type<GrpsList::size>::type;


		template<typename T>
		constexpr cmpId_type cmpId = (grpId_type)mpl::IndexOf<T, CmpsList>();

		template<typename T>
		constexpr grpId_type grpId = (grpId_type)mpl::IndexOf<T, GrpsList>();

		constexpr cmpId_type maxComponentId = CmpsList::size;
		constexpr grpId_type maxGroupId = GrpsList::size;
	}
}


