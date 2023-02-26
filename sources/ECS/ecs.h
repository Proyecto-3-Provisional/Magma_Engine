// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cassert>
#include <cstdint>
#include <limits>

#include "mpl.h"

// A struct for the general group, should not be used in the user
// defined groups
//
struct _grp_GENERAL;

// You should define a file ../game/ecs_defs.h with the list of your
// components, groups, and handlers. See ecs_defs_example.h for an
// example file
//
#if __has_include("ecs_defs.h")
#include "ecs_defs.h"
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

namespace ecs {

	struct Component;
	class Entity;
	class EntityManager;

	// TypeLists for components, systems, groups and handlers
	//
	using CmpsList = mpl::TypeList<_ext_CMPS_LIST_>;
	using GrpsList = mpl::TypeList<_grp_GENERAL, _ext_GRPS_LIST_>;


	// Automatically choose an unsigned integer type large enough to hold
	// corresponding IDs
	//
	using cmpId_type = mpl::numeric_type<CmpsList::size>::type;
	using grpId_type = mpl::numeric_type<GrpsList::size>::type;


	template<typename T>
	constexpr cmpId_type cmpId = mpl::IndexOf<T, CmpsList>();

	template<typename T>
	constexpr grpId_type grpId = mpl::IndexOf<T, GrpsList>();

	constexpr cmpId_type maxComponentId = CmpsList::size;
	constexpr grpId_type maxGroupId = GrpsList::size;
} // end of namespace

