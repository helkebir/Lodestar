//
// Created by Hamza El-Kebir on 12/26/21.
//

#ifndef LODESTAR_LS_HPP
#define LODESTAR_LS_HPP

/**
 * @file ls.hpp
 * @brief Global @a Lodestar documentation definitions.
 */

/**
 * @mainpage Overview
 *
 * Lodestar is a general-purpose lightweight real-time control library written
 * in standard C++11.
 */

//-----------------------------------------------------------
// GROUPS
//-----------------------------------------------------------

/**
 * @defgroup aux_module Aux module
 *
 * @brief This module contains core auxiliary functionality used throughout
 * @a Lodestar.
 */

/**
 * @defgroup blocks_module Blocks module
 *
 * @brief This module deals with functional block features in @a Lodestar.
 *
 * Functionality includes a standard library of blocks, execution order
 * computations, simplifying operations, algebraic loop resolution, and more.
 */

/**
 * @defgroup examples_module Examples module
 *
 * @brief This module includes examples for @a Lodestar features.
 */

//-----------------------------------------------------------
// DIRECTORIES
//-----------------------------------------------------------

/**
 * @dir src
 * @brief @a Lodestar source directory.
 */

/**
 * @dir src/analysis
 * @brief Common analysis routines.
 */

/**
 * @dir src/aux
 * @brief Common auxiliary routines.
 */

/**
 * @dir src/blocks
 * @brief Functional blocks.
 */

/**
 * @dir src/blocks/aux
 * @brief Standard functional blocks auxiliary routines.
 */

/**
 * @dir src/blocks/std
 * @brief Standard functional blocks.
 */

/**
 * @dir src/blocks/std/geometry
 * @brief Standard functional blocks (geometry-focus).
 */

/**
 * @dir src/blocks/std/systems
 * @brief Standard functional blocks (systems-focus).
 */

/**
 * @dir src/control
 * @brief Controller synthesis routines.
 */

/**
 * @dir src/core
 * @brief Common core routines.
 */

/**
 * @dir src/data
 * @brief Data manipulation routines.
 */

/**
 * @dir src/filter
 * @brief Signal filtering routines.
 */

/**
 * @dir src/io
 * @brief I/O interface routines.
 */

/**
 * @dir src/primitive
 * @brief Primitive math routines.
 */

/**
 * @dir src/symbolic
 * @brief Symbolic math routines.
 */

/**
 * @dir src/synthesis
 * @brief General synthesis routines.
 */

/**
 * @dir src/systems
 * @brief System manipulation routines.
 */

/**
 * @dir src/time
 * @brief Time-keeping routines.
 */

//-----------------------------------------------------------
// NAMESPACES
//-----------------------------------------------------------

/**
 * @namespace ls
 * @brief Main Lodestar code.
 */

/**
 * @namespace ls::aux
 * @brief Auxiliary functionality.
 * @ingroup aux_module
 */

/**
 * @namespace ls::blocks
 * @brief Main functional block definitions.
 * @ingroup blocks_module
 */

/**
 * @namespace ls::blocks::std
 * @brief Standard functional block library.
 * @ingroup blocks_module
 */

#endif //LODESTAR_LS_HPP
