#include <stdio.h>
#include <stdlib.h>
#include <math.h>




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
    vector2 net_force;
    int physics_on;
} object;

float SIM_G = 0.1; // overly simplified for now. Real value would never show anything meaningful at this point.
float epsilon = 0.01;

void write_telemetry_header(FILE *file){
    fprintf(file, "time,id,x,y,vx,vy,ax,ay,fx,fy\n");
}

void write_telemetry_row(FILE *file, double time, object *obj){
    fprintf(
        file,
        "%.4f,%s,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
        time,
        obj->id,
        obj->position.x,
        obj->position.y,
        obj->velocity.x,
        obj->velocity.y,
        obj->acceleration.x,
        obj->acceleration.y,
        obj->net_force.x,
        obj->net_force.y
    );
}

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
        {"A", 20.00, {1,10}, {0.0, 0.0}, {0,0}, {0,0}, 1},
        {"B", 10.00, {2,20}, {0.0, 0.0}, {0,0}, {0,0}, 1},
        {"C", 11.00, {-1,50}, {10.0, 10.0}, {0,0}, {0,0}, 1}
    };

    int n_balls = sizeof(balls) / sizeof(balls[0]);

    FILE *telemetry = fopen("telemetry.csv", "w");

    if (telemetry == NULL) {
        printf("Error: could not open telemetry.csv for writing.\n");
        return 1;
    }

    write_telemetry_header(telemetry);
    

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



    /*
    --Use state variables from prev or init iteration.
    --Calculate all forces (net forces) for each ball.
    --Apply forces to vectors and lastly position.
    --Update any state in place with calculations or replace.

    Gravity Equation for objects with mass near other objects :
    F = G (m1*m2) / (r*r )

    */

    while (time <= time_end){



        // Calculate all forces
        for (int i = 0; i < n_balls; i++){
            object *ball = &balls[i];

            force_g.x = ball->mass * acceleration_g.x;
            force_g.y = ball->mass * acceleration_g.y;

            net_force.x = force_g.x + f_air_resistance.x;
            net_force.y = force_g.y + f_air_resistance.y;

            ball->net_force = net_force;

            for (int j = 0; j < n_balls; j++){

                object *compare_ball = &balls[j];
                if (compare_ball->id == ball->id){
                    continue;
                }
                double dx = compare_ball->position.x - ball->position.x;
                double dy = compare_ball->position.y - ball->position.y;

                double distance_squared = dx*dx + dy*dy;
                double soft_dist_sqr = distance_squared + (epsilon*epsilon);
                double distance;
                if (distance_squared != 0) distance = sqrt(soft_dist_sqr);


                double mass_product = compare_ball->mass * ball->mass;
                double force_magnitude = SIM_G * (mass_product / soft_dist_sqr);
                vector2 vector_dir = {
                    dx / distance,
                    dy / distance
                };

                vector2 force_vector = {
                    vector_dir.x * force_magnitude,//x
                    vector_dir.y * force_magnitude //y
                };

                ball->net_force.x += force_vector.x;
                ball->net_force.y += force_vector.y;
            }

            ball->acceleration.x = ball->net_force.x / ball->mass;
            ball->acceleration.y = ball->net_force.y / ball->mass;

            ball->velocity.x += ball->acceleration.x * dt;
            ball->velocity.y += ball->acceleration.y * dt;

            ball->position.x += ball->velocity.x * dt;
            ball->position.y += ball->velocity.y * dt;

            //ground collision
            if(ball->position.y < 0)
            {
                ball->position.y = 0;
                ball->velocity.y = 0;
            }

            //add to telemetry file:
            write_telemetry_row(telemetry, time, ball);
        }
        
        time += dt;
    }

    

    
}


/*

Old loop

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

*/