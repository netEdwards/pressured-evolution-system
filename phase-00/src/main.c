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
    int physics_on;
} object;


void initialize_ball_physics(object* balls, int n_balls) {
    /*
    void function - sets `physics_on` value for each object in the array to 1.

    params:
    - object* balls: the array of object balls with the `physics_on` attr.
    - int n_balls: *read only* value used to iterate over balls.
    */

    for (int i = 0; i < n_balls; i++){

        balls[i].physics_on = 1;
    }

}


int main(void) {
    //create the object

    object balls[] = {
        {20.00, {0,10}, 0.0},
        {10.00, {0,20}, 0.0},
        {11.00, {0,50}, 10.0}
    };

    int n_balls = sizeof(balls) / sizeof(balls[0]);

    initialize_ball_physics(balls, n_balls);

    double acceleration = -9.81;
    double dt = 0.1;
    double time = 0.0;
    double time_start = 0.0;
    double time_end = 10.0;
    object fastest_ball;
    int fastest_ball_set = 0;

    while (time <= time_end){
        for (int i = 0; i < n_balls; i++)
        {   
            object *ball = &balls[i];

            if (ball->physics_on == 0) {
                continue;
            };

            printf("Ball: %d | t=%6.2f | y=%8.3f | v=%8.3f m/s\n", i+1, time, ball->position.y, ball->velocity);
            ball->velocity += acceleration * dt;
            ball->position.y += ball->velocity * dt;

            if (ball->position.y <= 0){
                if (!fastest_ball_set) {
                    fastest_ball_set = 1;
                    fastest_ball = *ball;
                }
                printf("Ball [%d] has hit the ground at, t=%6.2f s \n", i+1, time);
                ball->physics_on = 0;
            }
        }
        
        time += dt;
    }

    printf("All balls are on the ground, the first ball to have impact was: Ball with Mass = %8.2f \n", fastest_ball.mass);

    
}


