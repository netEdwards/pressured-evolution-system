# Small Gravity and Physics Simulation
Here I will build a very basic and simple physics simulator, starting with simple gravity and building to multi-body systems and more on top as we go. 
I plan to start super simple by using Euler's numerical integration technique, which uses the slope or the rate of change to predict some value in the future.
We should encounter some margin of error as we continue to make more components of the objects in the simulation dynamic. 

## Implementations

### First Implementatin
`main.c` will contiain a non abstract implementation of simple physics and mathematics to simulate an object falling. I have created a new type for our object:
```c
typedef struct{
    double mass;
    vector2 position;
    vector2 velocity;
}object;
```
This will be the foundation of our updatable object in time. The vector2 type is just another struct with two doubles (x & y) inside. Which will make things more structured in the future. 

#### Known Issues

Currently there are no known issues with this implementation of *just* simulating one object falling toward earth (using earths gravitational acceleration). We have no other bodies and sense acceleration stays constant and our dt is rather small, the margin of error is extrememly small. 

#### Summary
This first implementation was to achieve one goal: "Can I numerically evolve state through time?". No abstracted integrator, just raw attempt. We have done it, so first implementation was successful. No pressure to do anything yet either, due to the simplicity of our first few implementations we will most likely not even feel pressure to abstract yet. It will come in time though. 

Euler's integration methods will most likely stay in use until we begin to see larger margins of error or fuzzy/chaotic results. Maybe in the future, if we do orbit simulation or something similar, we will begin to see odd behavior with Euler's integration method which will call for an evolutin to Rk4 or something in between.

---

### Second Implementation

