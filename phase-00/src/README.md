# Small Gravity and Physics Simulation
Here I will build a very basic and simple physics simulator, starting with simple gravity and building to multi-body systems and more on top as we go. 
I plan to start super simple by using Euler's numerical integration technique, which uses the slope or the rate of change to predict some value in the future.
We should encounter some margin of error as we continue to make more components of the objects in the simulation dynamic. 

## Implementations

Implementation 1:
Can I evolve one object through time?

Implementation 2:
Can I evolve multiple objects through time?

Implementation 3:
Can objects have different initial conditions?

Implementation 4:
Can objects apply forces instead of hardcoded acceleration?

Implementation 5:
Can objects gravitationally interact with each other?

Implementation 6:
Does Euler start failing under orbital/multi-body dynamics?

### First Implementation
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

`main.c` has been modified evolve multiple objects through time the same updating rules. There was one small abstraction with the creation of the `initialize_ball_physics()` function. This was intended to improve readability of the `main()` function and make focusing on integration logic more clear. 

The variable `ball` no longer exists and has been changed to an array of `objects` called balls, where I intialized 3 different objects - with differing initial values. There was a slight miniature side objective here which was not only to attempt to evolve multiple states through time, but also see if we can't do a small observation of the state in real-time. 

#### The main changes
`main()` now inits three object types in an array called balls. We added a `physics_on` variable to - the object struct - be able to track when we do and don't want to integrate that specifc `object`. 

The loop was modified to now check and see if `physics_on` is 10(T), which skips calculations for that object in the array. Otherwise it calculates and prints the balls integration like normal. At the end of each loop we now also check if the balls y position is less than or equal to zero, if so we check if `fastest_ball` is set using a flag, and then set it if not (updating the flag). We also set the `physics_on` attr in that object to 0 marking it off for calculation later in the iterations. 

Finally, as we exit the loop we use the `fastest_ball` variable to display which ball with which identifying mass feel first. Which is an odd identifyer now that I think about because we do not integrate mass dynamically - or at all yet. 

#### Errors and issues
The first main issue I had was as I was teaching myself this code to write, it quickly became hard to see where I was in the code. Mainly due to everything being written in one `main()` function (also other factors like IDE color-theme, experience reading C and more) I wanted to make it easier seeing the logical progression code in `main()`. So I abstracted the thing I wanted "out of mind out of sight". Which was getting all `physics_on` flags set to 1. I already knew how to do it and it was a lightweight abstraction, so I compeleted the additon of `initialize_balls_physics()` function. Readability could still improve, but that is from my low level of C programming experiencen probably.

So far, I have gotten this implementation to function with minimal issues or none at all. Which is amazing, but also slightly expected for this basic level of implemenation change. 

#### Summary 
Successful second implementation. For phase-00 we will continue to keep this small steps in implementation with the implementations themselves becoming more complex as the small changes build complexity over time. Our goal was just to see if we could evolved multiple objects through time. Now that we know we can and have the code written, we already have the foundation for multiple object or variance in future simulations as we add things like mass or body interactions to our physics. Which would most like require some more abstraction, but we will see as we climb closer. 

### Third Implementation

We wil skip over the written third implementation and combine it with the fourth into the this third implementaiton. This is because testing for different initial values was sort of a symptom of creating the multi-object implementation. We had different values for each object and I changed them often while developing the implementation itself. So we already achieved that indirectly and blew through it. 

For this implementation I am writing/documenting before I begin coding. The goal for this is to change acceleration into a dynamic integration by calculating it from a force. From the beginning it will be a singular force and later we could add one or two more. We will also stick with the idea we are close to the earths surface using the -9.81 acceleration number still. 

A more refined definition of the goal here is, "Can each object compute its own acceleration from forced acting on it , rather than sharing one hardcoded acceleration value?". 

The implementation will stay non-abstract with minor to small abstractions for readability in `main.c`. Readability is still a pressure point in programming and development - while at this stage its very minor. 

#### Issues Encountered

The first one was after adding in just the math to calculate acceleration based on a force, by just changing how the objects acceleration is derived (from force), it seems that the velocity has been disrupted. Which is odd. I also changed the velocity from a double to vector2 type we defined in implementation 1. I will look into this. 
- Updated, I figured it out. It was just because I did not update the print values in the loop to print the specific axis of the velocity vector (y). 

After adding a new force, it is very hard to tell what is what and read my outputs. But from what I can tell, my math may be wrong in applying the force to each ball. For some reason the balls are starting at (0,0). Could be an issue with new attributes being added to the struct. I need to be more careful about adding attributes to the struct in the future for sure. After adjusting an issue with how I was printing the values each iteration to the terminal, I found that the force is mostly positive. Where they start at y=10 for example and in the next timestep they change to y=10.097. This is incorrect behavior. After further investigation, it seems I accidentally added a (-) infront of the mass in an expression to calculate the gravitational force... which I missed. Maybe I should abstract a new function soon. 

Another thing I forgot was to change assignment of velocity in the hardcoded creation of the balls to a vector2 assignment. It was still a double assignment which was messing with calculations - but no errors due to it. 

#### Whats New & New Realizations
I have changed the velocity attribute to be a vector2, added an `char id` attribute to identify balls easier (outside of loops), and also added a `vector2 acceleration` attribute to ensure we seperate acceleration constants from the objects now dynamic acceleration. Forces are caclulcated or defined outside the main simulation loop and then dynamically calculated per timestep based on their rates of change, sticking with that classic euler integration method. 

A new realization I had was related to the actual definition and initialization of the balls. We hardcoded the definition of the balls in the beginning of the function, but I abstracted the assignment of the `physics_on` value. It would be easier to just assign the initial value of it in the actual hardcoded declaration... so I may remove that abstraction.

#### Summary
I have now made it so that all balls now feel more than one force, simultaneously I also made it to where the balls experience a force on more than just the y axis, updating the code to properly use vectors where it is appropriate (for vel, accl, force). With that, I changed the print statements to be a bit more readable and reveal all parts of the ball now that we have more data to review from the integration - allowing us to see both the x & y axis for velocity and position. Which reveals some cool behavior. 

I was able to successfully dynamically integrate acceleration for this example, meaning object acceleration is no longer hardcoded and is now dependant on hardcoded force values or the hardcoded gravitational constant for being close to earths surface. This was fun! I enjoyed looking at how I could make sure the math was correct and also how to properly integrate everything together. Everything was right under the hood, but syntactically I had some issues here and there. After solving them I was able to see all the balls fall and be affected by a "wind" or "air resistance" force I added. 