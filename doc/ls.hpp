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

//-----------------------------------------------------------
// DIRECTORIES
//-----------------------------------------------------------

/**
 * @dir src
 * @brief @a Lodestar source directory.
 */

/**
 * @dir src/aux
 * @brief Auxiliary functionality directory.
 */

/**
 * @dir src/blocks
 * @brief Functional blocks directory.
 */

/**
 * @dir src/blocks/aux
 * @brief Standard functional blocks auxiliary functionality directory.
 */

/**
 * @dir src/blocks/std
 * @brief Standard functional blocks directory.
 */

/**
 * @dir src/blocks/std/geometry
 * @brief Standard functional blocks (geometry-focus) directory.
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
