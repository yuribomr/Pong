#include "raylib.h"
#include "raymath.h"
#include "iostream"
#include "cmath"
#include <string.h>
#include <sstream>
#include <iomanip>


#define FPS 240
#define WIDTH 1280
#define HEIGHT 720
#define MARGIN 10
#define g 9.81*50

std::string floatToString(float n, int p){
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(p) << n;
	return stream.str();
}

class Particle{
	public:
		Vector2 position, velocity, acceleration;
		double mass, radius_size;

		Particle(Vector2 p, Vector2 v, double m, double r){
			position.x = p.x;
			position.y = p.y;
			velocity.x = v.x;
			velocity.y = v.y;
			mass = m;
			radius_size = r;
			acceleration.x = 0.0f;
			acceleration.y = 0.0f;
		}

		void update(double dt){
			double v_x = velocity.x;
			double v_y = velocity.y;
			if(position.x + radius_size >= WIDTH/2 || position.x - radius_size <= -WIDTH/2) velocity.x = v_x*(-1.0f);
			if(position.y + radius_size >= HEIGHT/2 || position.y - radius_size <= -HEIGHT/2) velocity.y = v_y*(-1.0f);
			velocity.x += acceleration.x*dt;
			velocity.y += acceleration.y*dt;
			position.x += velocity.x*dt;
			position.y += velocity.y*dt;
		}

		void applyGravity(){
			acceleration.y = g;
		}

		void DrawParticle(Color color){
			DrawCircleV(position, radius_size, color);
		}

};

class Table{
	public:
		Vector2 position_left, position_right;
		float size;
		Color color;
		Table(Vector2 p, float s, Color c){
			position_left.x = p.x;
			position_left.y = p.y;
			position_right.x = p.x;
			position_right.y = p.y;
			size = s;
			color = c;
		}

		void update(){
			position_left.x = GetMouseX() - WIDTH/2 - size;
			position_left.y = GetMouseY() - HEIGHT/2;
			position_right.x = GetMouseX() - WIDTH/2 + size;
			position_right.y = position_left.y;
		}

		void DrawTable(){
			DrawLineEx(position_left, position_right, 2.0f, color);
		}


		void checkCollision(Particle &p, float dt){
			float distance = pow(position_left.x - p.position.x, 2) + pow(position_left.y - p.position.y, 2) - pow(position_left.x - p.position.x, 2);
			
			if(sqrt(distance) <= p.radius_size + 0.2f && (p.position.x >= position_left.x && p.position.x <= position_right.x)){
				float v_y = p.velocity.y;
				p.velocity.y = (-1.0f)*v_y;
				p.update(dt);
			}
			//Task: Colisão lateral
		}
};

class Info{
	public:
		Vector2 position, size;
		Info(Vector2 p, Vector2 s){
			position.x = p.x;
			position.y = p.y;
			size.x = s.x;
			size.y = s.y;
		}
		
		void DrawInfo(Particle &p){
			std::string particle_p = floatToString(p.position.x, 2) + "     |      " + floatToString(p.position.y, 2);
			std::string particle_v = floatToString(p.velocity.x, 2) + "     |      " + floatToString(p.velocity.y, 2);


			DrawRectangleV(position, size, RAYWHITE);
			DrawText(particle_p.c_str(), position.x + MARGIN, position.y + MARGIN, 16,BLACK);
			DrawText(particle_v.c_str(), position.x + MARGIN, position.y + MARGIN + 30.0f , 16,BLACK);
		}
	
};

void drawAxis(){
	DrawLineEx({-WIDTH/2,0.0f}, {WIDTH/2,0.0F}, 1 ,RAYWHITE);
	DrawLineEx({0.0F, -HEIGHT/2}, {0.0F, HEIGHT/2},1 , RAYWHITE);
}

int main(){
	Camera2D camera = {0};
	camera.target = (Vector2){0, 0};
	camera.offset = (Vector2){WIDTH/2, HEIGHT/2};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	InitWindow(WIDTH, HEIGHT, "SIMULATOR");
	SetTargetFPS(FPS);

	Particle p1({200.0f, -100.0f}, {-100.0f, 50.0f}, 50.0f, 10.0f);
	p1.applyGravity();

	Info info1({-WIDTH/2 + MARGIN, -HEIGHT/2 + MARGIN}, {200.0f, 100.0f});

	Table t1({0.0f, 0.0f}, 20.0f, RAYWHITE);
	while(!WindowShouldClose()){
		float dt = GetFrameTime();
			
		t1.update();
		t1.checkCollision(p1, dt);
		p1.update(dt);
		BeginDrawing();
			ClearBackground(BLACK);
			BeginMode2D(camera);
				DrawFPS(WIDTH/2, -HEIGHT/2);
				drawAxis();
				p1.DrawParticle(RAYWHITE);
				info1.DrawInfo(p1);
				t1.DrawTable();
			EndMode2D();
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
