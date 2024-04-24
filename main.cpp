/*******************************************************************************************
 *
 *   raylib [core] example - Basic window (adapted for HTML5 platform)
 *
 *   This example is prepared to compile for PLATFORM_WEB and PLATFORM_DESKTOP
 *   As you will notice, code structure is slightly different to the other
 *examples... To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB
 *at beginning
 *
 *   This example has been created using raylib 1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/
// #define PLATFORM_WEB
#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;
class Ball {
public:
  Ball();
  ~Ball();

  Vector2 getPosition();
  Vector2 getSpeed();
  float getRadius();
  Color getColor();
  void updatePosition();
  void switchGravityOnOff();

private:
  Vector2 position_;
  Vector2 speed_;
  float radius_;
  float g_;
  Color color_;
};

Ball::Ball() {
  position_ = {float(screenWidth) / 2, float(screenHeight) / 2};
  speed_ = {2, 2};
  radius_ = 20;
  g_ = 9.81 / 60;
  color_ = RED;
}
Vector2 Ball::getPosition() { return position_; }
Vector2 Ball::getSpeed() { return speed_; }
float Ball::getRadius() { return radius_; }
Color Ball::getColor() { return color_; }
void Ball::updatePosition() {
  speed_.y = speed_.y + g_;
  position_.x += speed_.x;
  position_.y += speed_.y;
  speed_.y = speed_.y + g_;
  if (position_.y + radius_ >= screenHeight && speed_.y > 0) {
    speed_.y = -(speed_.y * 0.99);
  }
  if (position_.x + radius_ >= screenWidth || position_.x - radius_ <= 0) {
    speed_.x = -speed_.x * 0.99;
  }
}
void Ball::switchGravityOnOff() {
  if (g_ > 0)
    g_ = 0;
  else
    g_ = 9.81;
}

Ball::~Ball() {}
//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(Ball ball); // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(screenWidth, screenHeight, "Ball");
  Ball ball;

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    if (IsKeyDown(KEY_G))
      ball.switchGravityOnOff();
    ball.updatePosition();
    UpdateDrawFrame(ball);
  }
#endif

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(Ball ball) {
  // Update
  //----------------------------------------------------------------------------------
  // TODO: Update your variables here
  //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Congrats! You created your first window!", 190, 300, 20, LIGHTGRAY);
  DrawCircle(ball.getPosition().x, ball.getPosition().y, ball.getRadius(),
             ball.getColor());

  EndDrawing();
  //----------------------------------------------------------------------------------
}
