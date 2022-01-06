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
 * @dir Lodestar
 * @brief @a Lodestar source directory.
 */

/**
 * @dir Lodestar/analysis
 * @brief Common analysis routines.
 */

/**
 * @dir Lodestar/aux
 * @brief Common auxiliary routines.
 */

/**
 * @dir Lodestar/blocks
 * @brief Functional blocks.
 */

/**
 * @dir Lodestar/blocks/aux
 * @brief Standard functional blocks auxiliary routines.
 */

/**
 * @dir Lodestar/blocks/std
 * @brief Standard functional blocks.
 */

/**
 * @dir Lodestar/blocks/std/geometry
 * @brief Standard functional blocks (geometry-focus).
 */

/**
 * @dir Lodestar/blocks/std/systems
 * @brief Standard functional blocks (systems-focus).
 */

/**
 * @dir Lodestar/control
 * @brief Controller synthesis routines.
 */

/**
 * @dir Lodestar/core
 * @brief Common core routines.
 */

/**
 * @dir Lodestar/data
 * @brief Data manipulation routines.
 */

/**
 * @dir Lodestar/filter
 * @brief Signal filtering routines.
 */

/**
 * @dir Lodestar/io
 * @brief I/O interface routines.
 */

/**
 * @dir Lodestar/primitive
 * @brief Primitive math routines.
 */

/**
 * @dir Lodestar/symbolic
 * @brief Symbolic math routines.
 */

/**
 * @dir Lodestar/synthesis
 * @brief General synthesis routines.
 */

/**
 * @dir Lodestar/systems
 * @brief System manipulation routines.
 */

/**
 * @dir Lodestar/time
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
