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
 * @defgroup analysis_module Analysis module
 *
 * @brief This module contains analysis routines.
 */

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
 * @defgroup control_module Control module
 *
 * @brief This module contains controller implementations and synthesis
 * routines.
 */

/**
 * @defgroup core_module Core module
 *
 * @brief This module contains core functionality used throughout
 * @a Lodestar.
 */

/**
 * @defgroup examples_module Examples module
 *
 * @brief This module includes examples for @a Lodestar features.
 */

/**
 * @defgroup filter_module Filter module
 *
 * @brief This module contains filtering functionality used throughout
 * @a Lodestar.
 */

/**
 * @defgroup io_module I/O module
 *
 * @brief This module contains bindings and interface with foreign functions and
 * protocols.
 */

/**
 * @defgroup primitives_module Primitives module
 *
 * @brief This module contains mathematical primitives used throughout
 * @a Lodestar.
 */

/**
 * @defgroup symbolic_module Symbolic module
 *
 * @brief This module contains symbolic mathematics functionality used mainly
 * during preprocessing in @a Lodestar.
 */

/**
 * @defgroup synthesis_module Synthesis module
 *
 * @brief This module contains low-level synthesis (optimization, etc.) routines
 * used throughout @a Lodestar.
 */

/**
 * @defgroup systems_module Systems module
 *
 * @brief This module contains definitions for (dynamic) systems used in
 * @a Lodestar.
 */

/**
 * @defgroup time_module Time module
 *
 * @brief This module contains timing capabilities used in @a Lodestar.
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
 * @namespace ls::analysis
 * @brief Analysis routines and implementations.
 * @ingroup analysis_module
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

/**
 * @namespace ls::control
 * @brief Controller synthesis routines and implementations.
 * @ingroup control_module
 */

/**
 * @namespace ls::core
 * @brief Core functionality.
 * @ingroup core_module
 */

/**
 * @namespace ls::filter
 * @brief Signal filtering functionality.
 * @ingroup filter_module
 */

/**
 * @namespace ls::io
 * @brief I/O and foreign interfacing functionality.
 * @ingroup io_module
 */

/**
 * @namespace ls::primitives
 * @brief Primitive mathematics functionality.
 * @ingroup primitives_module
 */

/**
 * @namespace ls::symbolic
 * @brief Symbolic mathematics functionality.
 * @ingroup symbolic_module
 */

/**
 * @namespace ls::synthesis
 * @brief Low-level synthesis functionality.
 * @ingroup synthesis_module
 */

/**
 * @namespace ls::systems
 * @brief Dynamic system definitions.
 * @ingroup systems_module
 */

/**
 * @namespace ls::time
 * @brief Timing and timekeeping functionality.
 * @ingroup time_module
 */

#endif //LODESTAR_LS_HPP
