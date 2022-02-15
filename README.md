# Lodestar

> An integrated real-time safety-critical control framework in C++.

## Description

_Lodestar_ is a lightweight C++11 framework for rapidly prototyping and deploying real-time control systems.
Traditionally, issues such as data dependencies, execution order, hardware interfacing, and networking have had to be
manually solved by developers; _Lodestar_ provides abstractions and automatic routines for resolving these common
problems, without obscuring functional relations. Using _Lodestar_, one is only responsible for specifying
_function blocks_ and their interconnections; _Lodestar_ takes care of the rest.

_Lodestar_ aims to be a framework that provides _directly executable code_, unlike most modeling and simulation-centric
toolboxes, which have not been tailored for use in real-time applications. At the same time, _Lodestar_ also allows for
_code generation_ when performance is particularly important. It comes built-in with many compile-time checks that cover
most common typos and bugs (i.e., matrix-vector dimensions mismatch, connecting inputs to inputs, etc.).

To this end, _Lodestar_ adopts a function block description of systems, where
each `Block` provides a _pure function_ (i.e., one that only alters its internal state). Each of these block may have
any number of inputs, parameters, and outputs. The resulting functional block diagrams can easily be extended with new
user-defined block types, without incurring overhead.

```
                           Parameters
           +-----------------------------------------+
Inputs --->| Block : f(Input, Parameters) -> Outputs |---> Outputs
           +-----------------------------------------+
```

### Features

- Automatic resolution of circular data-dependencies (algebraic loops).
- Transparent compile-time error checking, as well as run-time checks prior to executing code.
- Easy extensibility with a simple yet powerful `Block` API based on template metaprogramming.
- Clean C++ code generation with predetermined function execution order, as well as resolved data-dependencies.
- Zero-overhead abstraction using templated classes; it does not matter if you have a thousand inputs, or just one.
- Out-of-the-box networking support, with efficient serialization.
- Automatic direct encryption and decryption of messages for enhanced security using state-of-the-art elliptic curve algorithms.

## Getting Started

### Dependencies

* CMake
* A C++11-compliant compiler
* [GiNaC](https://ginac.de/) (optional, for resolving algebraic loops)
* [nng](https://nng.nanomsg.org/) (optional, for networking)

### Building

Simply clone the [repository](https://github.com/helkebir/Lodestar) and build using CMake.
If you just want to grab a static library, run `cmake ..` instead of a debug build.

```bash
git clone https://github.com/helkebir/Lodestar
cd Lodestar
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
sudo make install
```

You can find some demos in the `examples/` folder, as well as unit tests of different components in the `tests/` folder.

### Getting Started

Here's an example to get you started. We will be using `ConstantBlock`, `SumBlock`, and `GainBlock` objects to construct
a simple program.

```cpp
#include <Lodestar/blocks/std/ConstantBlock.hpp>
#include <Lodestar/blocks/std/SumBlock.hpp>
#include <Lodestar/blocks/std/GainBlock.hpp>

#include <Lodestar/blocks/BlockUtilities.hpp>
#include <Lodestar/blocks/aux/Executor.hpp>

using namespace ls::blocks;

/*
 *                (+)
 * +---+    +---+    +---+
 * | c |--->| g |--->| s |--->
 * +---+    +---+    +---+
 *                     ^ (-)
 * +----+              |
 * | c2 |--------------+
 * +----+
 */

int main()
{
    std::ConstantBlock<double> c{5}, c2{2};
    std::SumBlock<double, 2> s;
    std::GainBlock<double> g{0.5};
    
    s.setOperators(decltype(s)::Plus, decltype(s)::Minus);
    
    // We now establish the interconnections:
    connect(c.o<0>(), g.i<0>());
    connect(g.o<0>(), s.i<0>());
    connect(c2.o<0>(), s.i<1>());
    
    // We group all our blocks in a BlockPack object,
    // which contains all components of our system.
    BlockPack bp{c, c2, s, g};
    
    // We pass the BlockPack onto the Executor,
    // which will allow us to resolve the execution order,
    // providing a single trigger function for the entire system.
    aux::Executor ex{bp};
    ex.resolveExecutionOrder();

    // Triggering the entire system is as simple as
    // calling the trigger function of the executor.
    ex.trigger();
    
    // We obtain +5*0.5 -2 = 0.5  
    auto res = (s.o<0>().object == 0.5);
    
    return 0;
}
```

## Help

Documentation is still a work-in-progress; feel free to look around in the header files, and open an issue in the meantime!

## Authors

Hamza El-Kebir<br/>
[@helkebir](http://github.com/helkebir)

## Version History

_Pre-alpha_

## License

This project is licensed under the BSD3 License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

Inspiration was drawn from the following projects, old and new alike:
* Modelica, for its approach to [block definitions](https://specification.modelica.org/maint/3.5/class-predefined-types-and-declarations.html#S6.I1.i4.p1), syntax, as well as a number of [canonical blocks](https://doc.modelica.org/Modelica%204.0.0/Resources/helpDymola/Modelica_Blocks.html#Modelica.Blocks)
* [Esterel](https://en.wikipedia.org/wiki/Esterel) and [Lustre](https://en.wikipedia.org/wiki/Lustre_(programming_language)), for their approach to signal passing and handling, as well as functional block definitions.

The name _Lodestar_ is used to refer to a guiding or navigation star (such as Polaris), underscoring the goal of
_Lodestar_ to be a framework that reliably guides users to a stable solution to their control problems.