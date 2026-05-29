#include <stdio.h>
#include <stdlib.h>




typedef struct {
    double x;
    double y;
} vector2;

typedef struct {
    char* id;
    double mass;
    vector2 position;
    vector2 velocity;
    vector2 acceleration;
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
        {"ball_1", 20.00, {0,10}, {0.0, 0.0}},
        {"ball_2", 10.00, {0,20}, {0.0, 0.0}},
        {"ball_3", 11.00, {0,50}, {10.0, 10.0}}
    };

    int n_balls = sizeof(balls) / sizeof(balls[0]);

    initialize_ball_physics(balls, n_balls);

    

    vector2 acceleration_g = {0, -9.81};
    double dt = 0.1;
    double time = 0.0;
    double time_start = 0.0;
    double time_end = 10.0;
    object fastest_ball;
    int fastest_ball_set = 0;
    vector2 force_g;
    vector2 f_air_resistance = {12, -3};
    vector2 net_force;

    while (time <= time_end){
        for (int i = 0; i < n_balls; i++)
        {   
            object *ball = &balls[i];

            if (ball->physics_on == 0) {
                continue;
            };

            printf("Ball: %s | t=%6.2f | x=%2.3f, y=%2.3f | v: (%2.3f ,%2.3f) m/s\n", ball->id, time, ball->position.x, ball->position.y, ball->velocity.x,  ball->velocity.y);
            
            force_g.x = ball->mass * acceleration_g.x;
            force_g.y = ball->mass * acceleration_g.y;

            

            net_force.x = force_g.x + f_air_resistance.x;
            net_force.y = force_g.y + f_air_resistance.y;

            ball->acceleration.x = net_force.x / ball->mass;
            ball->acceleration.y = net_force.y / ball->mass;            

            ball->velocity.x += ball->acceleration.x * dt;
            ball->velocity.y += ball->acceleration.y * dt;

            ball->position.x += ball->velocity.x * dt;
            ball->position.y += ball->velocity.y * dt;

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

    

    
}


