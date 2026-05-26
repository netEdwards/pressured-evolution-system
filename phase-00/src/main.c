#include <stdio.h>
#include <stdlib.h>




typedef struct {
    double x;
    double y;
} vector2;

typedef struct {
    double mass;
    vector2 position;
    double velocity;
} object;

int main(void) {
    //create the object
    object ball = {
        20.00,
        {0, 10},
        0.0
    };


    object* ballPtr = &ball;
    double acceleration = -9.81;
    double dt = 0.1;
    double time = 0.0;

    while (ball.position.y > 0.0){
        printf("t=%6.2f s | y=%8.3f m | v=%8.3f m/s\n",
               time, ball.position.y, ball.velocity);

        ball.velocity += acceleration * dt;
        ball.position.y += ball.velocity * dt;
        time += dt;
    }

    printf("Object hit the ground at t=%.2f seconds.\n", time);
    printf("Impact velocity: %.2f m/s.\n", ball.velocity);
}
