# Pressured Evolution System (PES)

Pressured Evolution System is a long-term systems engineering project built around one idea:

> A system should evolve because real engineering pressure forces it to evolve.

Instead of starting with the “best” language, framework, architecture, or abstraction, PES begins with a minimal implementation and lets complexity create pressure. That pressure is then documented and used to justify the next evolution of the system.

The first domain for PES is physical simulation.

Phase 00 begins with a small C-based gravity and physics simulation. The current goal is not to build a perfect physics engine. The goal is to build a system from first principles, observe where the implementation starts to break down, and use those breakdowns to motivate better numerical methods, better architecture, better tooling, and eventually better runtime/language choices.

---

## Project Thesis

Most software projects hide the reason behind their tools.

A system might use C++, Rust, Python, Kubernetes, GPU acceleration, a database, a message bus, or a visualization layer — but the decision is often presented as a starting assumption instead of an earned engineering conclusion.

PES is an attempt to make those decisions visible.

The project asks:

* What can be built with the simplest viable tool?
* When does the current implementation become hard to reason about?
* When does readability become a real constraint?
* When does numerical error become visible?
* When does the simulation need better integrators?
* When does single-file C stop being enough?
* When does the system need modules, tests, telemetry, visualization, or parallelism?
* When does the pressure justify evolving to a new architecture or language?

PES is not just a simulation project. It is a record of engineering pressure.

---

## Current Phase: Phase 00 — C Physics Simulation

Phase 00 starts in C because C exposes the structure of the system directly.

There are no classes hiding state.
There is no framework organizing the architecture.
There is no engine abstracting physics away.
There is no runtime protecting the developer from poor structure.

That makes C a good starting point for learning how simulation state, memory, numerical integration, and system architecture actually behave.

The current implementation models objects with:

* mass
* position
* velocity
* acceleration
* net force
* physics state flags

The simulation currently supports:

* evolving object state through time
* multiple objects in the same simulation
* force-based acceleration
* simplified air resistance
* gravitational interaction between simulated objects
* Euler integration as the initial numerical method
* basic vector math using 2D vectors

---

## Current Implementation Goals

Phase 00 is being developed through small implementation milestones.

### Implementation 1 — Single Object State Evolution

Goal:

> Can one object be numerically evolved through time?

This milestone establishes the most basic simulation loop:

1. compute acceleration
2. update velocity
3. update position
4. advance time

### Implementation 2 — Multiple Objects

Goal:

> Can multiple independent objects be evolved through time?

This adds arrays of objects and begins creating pressure around iteration, object state management, readability, and output formatting.

### Implementation 3 — Different Initial Conditions

Goal:

> Can different objects begin with different positions, velocities, and masses?

This introduces variation into the simulation and makes it easier to observe differences in state evolution.

### Implementation 4 — Force-Based Motion

Goal:

> Can objects move because of forces instead of hardcoded acceleration?

This shifts the simulation toward a more general physics model:

```txt
F = m * a
a = F / m
```

### Implementation 5 — Object-to-Object Gravity

Goal:

> Can objects gravitationally interact with each other?

This introduces pairwise force calculation:

```txt
F = G * (m1 * m2) / r^2
```

The force direction is calculated from the vector between objects, and force is accumulated into each object’s net force.

### Implementation 6 — Numerical Pressure

Goal:

> Does Euler integration begin to fail under orbital or multi-body dynamics?

This is the first major expected pressure point.

Euler integration is simple and useful for learning, but it accumulates error. As the simulation moves toward orbital setups and more sensitive interactions, the numerical limitations should become visible.

That pressure will motivate improved integration methods such as:

* semi-implicit Euler
* Verlet integration
* Runge-Kutta methods
* RK4 comparison experiments

---

## Why Euler First?

Euler integration is intentionally simple.

It is not the best long-term integration method, but it is the right first method because it makes state evolution obvious.

The basic idea:

```txt
velocity += acceleration * dt
position += velocity * dt
```

Starting with Euler allows the project to expose numerical error naturally instead of skipping directly to a better method without understanding why it is needed.

When Euler begins producing unstable or unrealistic behavior, that failure becomes evidence for the next evolution of the simulation.

---

## What This Project Is Not

PES is not currently a production physics engine.

It is not claiming high physical accuracy.
It is not optimized for performance yet.
It is not pretending to be an aerospace-grade simulator in its current form.

The current implementation is intentionally early and intentionally minimal.

The value of the project is in the staged development process:

1. build the simplest version
2. observe the pressure
3. document the limitation
4. evolve the system
5. repeat

---

## What This Project Is Becoming

PES is intended to evolve into a larger simulation and systems-engineering portfolio project.

Near-term evolution will focus on turning the current single-file C simulation into a more structured simulation system.

Planned improvements include:

* modular C architecture
* dedicated vector math utilities
* force calculation modules
* integrator modules
* CSV telemetry output
* deterministic validation tests
* improved terminal output
* Python-based visualization/replay tools
* orbital injection experiments
* Euler vs. RK4 comparison
* energy drift measurement
* simulation state logging
* subsystem-style telemetry messages
* hardware-adjacent HIL experiments

---

## Target Architecture Direction

The current implementation is intentionally simple, but the project is expected to evolve toward a structure like:

```txt
pressured-evolution-system/
  README.md
  Makefile
  src/
    main.c
    vector.c
    object.c
    forces.c
    integrator.c
    simulation.c
    telemetry.c
  include/
    vector.h
    object.h
    forces.h
    integrator.h
    simulation.h
    telemetry.h
  docs/
    phase-00.md
    pressure-log.md
    roadmap.md
    message-schema.md
    test-plan.md
  tests/
    test_vector.c
    test_forces.c
    test_integrator.c
  tools/
    plot_telemetry.py
```

This structure is not the starting point. It is the direction the project will evolve toward as pressure justifies it.

---

## Pressure Log

PES tracks pressure points as first-class project artifacts.

A pressure point is a moment where the current implementation becomes limiting.

Examples:

| Pressure                       | Cause                                | Possible Evolution                              |
| ------------------------------ | ------------------------------------ | ----------------------------------------------- |
| Hard to read `main.c`          | too much logic in one file           | split into modules                              |
| Messy vector math              | repeated manual x/y operations       | create vector utility functions                 |
| Output is unreadable           | raw terminal printing does not scale | telemetry logs and visualization                |
| Euler drift                    | numerical error accumulates          | compare improved integrators                    |
| Pairwise gravity scales poorly | O(n²) force calculation              | spatial partitioning or approximation           |
| Hard to validate behavior      | no tests or expected outputs         | deterministic test cases                        |
| No interface between systems   | simulation is monolithic             | message schema and telemetry bus                |
| CPU bottlenecks                | large object counts                  | parallelism, GPU, or optimized language/runtime |

The pressure log is the core of the project. It explains why the system evolves.

---

## Long-Term Phase Roadmap

### Phase 00 — Minimal C Simulation

Start with a simple C implementation of physical state evolution.

Focus:

* C fundamentals
* structs
* pointers
* arrays
* numerical integration
* force accumulation
* simulation loops

### Phase 01 — Structured C Simulation Engine

Refactor the initial simulation into modular C components.

Focus:

* headers and source separation
* build system
* testable modules
* telemetry output
* deterministic validation

### Phase 02 — Numerical Methods and Validation

Compare integration methods and measure simulation error.

Focus:

* Euler vs. semi-implicit Euler vs. RK4
* orbital dynamics
* energy drift
* validation tests
* plotting and replay

### Phase 03 — Simulation Telemetry and Tooling

Turn the simulation into a system that emits structured state data.

Focus:

* CSV logs
* message schemas
* state replay
* visualization
* external analysis tools

### Phase 04 — Hardware-Adjacent / HIL Experiments

Introduce a small hardware or embedded endpoint.

Focus:

* serial communication
* microcontroller integration
* command/telemetry loops
* hardware-in-the-loop style testing
* simple physical indicators driven by simulation state

### Phase 05 — Higher-Level Architecture Evolution

Evaluate when C becomes too slow or too costly to extend safely.

Possible directions:

* C++ for stronger architecture and object modeling
* Rust for memory safety and systems reliability
* Python for analysis and tooling
* GPU acceleration for large-scale simulation
* distributed simulation components

The goal is not to jump to these tools early. The goal is to earn them.

---

## Current Build

If using the current root-level `main.c` layout:

```bash
gcc main.c -lm -o pes
./pes
```

If using the included `Makefile`:

```bash
make
make run
```

Clean build artifacts:

```bash
make clean
```

---

## Current Status

PES is currently in Phase 00.

The current implementation is a basic C physics simulation with multi-object state evolution and simplified gravitational interaction.

The immediate next steps are:

1. clean up the repository structure
2. add a reliable build process
3. document the current implementation
4. add telemetry output
5. split the simulation into modules
6. add validation tests
7. begin orbital dynamics experiments

---

## Why This Matters To Me

I am building PES to strengthen my foundations in systems programming, numerical integration, simulation architecture, and engineering decision-making.

Long term, I want to work on systems where software interacts with the physical world: aerospace software, mission systems, hardware-in-the-loop testing, simulation tools, robotics, infrastructure, and high-performance engineering systems.

PES is my attempt to build toward that future from first principles.

The project begins with a falling object.

It evolves from there.
