#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

struct Vec2 {
	float x;
	float y;
};

Vec2 transform_vector_2x2(Vec2 v, float m[2][2]) {
	float tx = (v.x * m[0][0]) + (v.y * m[0][1]);
	float ty = (v.x * m[1][0]) + (v.y * m[1][1]);

	return { tx, ty };
}

void multiply_matrixes(float m1[2][2], float m2[2][2], float result[2][2]) {
    result[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0];
    result[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1];
    result[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0];
    result[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1];
}

constexpr int kScreenWidth  { 640 };
constexpr int kScreenHeight { 480 };

int main(int argc, char* argv[]) {
    
    bool init_success = true;
    if (!SDL_Init(SDL_INIT_VIDEO)) 
    {
        SDL_Log("SDL could not initialize! Error: %s\n", SDL_GetError());
        init_success = false;
    }

    Vec2 v1 = { 1, 1 };

    float mLeft90[2][2] = {
        {0, -1},
        {1, 0}
    };

    float mSheer[2][2] = {
        {1,  0},
        {0,  2}
    };

    float mLeftSheer[2][2];
    multiply_matrixes(mLeft90, mSheer, mLeftSheer);

    Vec2 transformed = transform_vector_2x2(v1, mLeft90);
    Vec2 transformed2 = transform_vector_2x2(transformed, mSheer);
    Vec2 transformed3 = transform_vector_2x2(v1, mLeftSheer);

    printf("Original vector:     [%f, %f]\n", v1.x, v1.y);
    printf("Transformed1 vector: [%f, %f]\n", transformed.x, transformed.y);
    printf("Transformed2 vector: [%f, %f]\n", transformed2.x, transformed2.y);
    printf("Transformed3 vector: [%f, %f]\n", transformed3.x, transformed3.y);

    return 0;
}