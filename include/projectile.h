#pragma once
namespace sim{
struct Point {
		double x;
		double y;
		//Overloading operators
		Point& operator= (Point pt) {
			x = pt.x;
			y = pt.y;
			return *this;
		}
		Point& operator+ (Point pt) {
			x += pt.x;
			y += pt.y;
			return *this;
		}
		Point& operator* (Point pt) {
			x *= pt.x;
			y *= pt.y;
			return *this;
		}
		Point& operator/ (Point pt) {
			x /= pt.x;
			y /= pt.y;
			return *this;
		}

	};
}
	class Projectile
	{
	public:
		//Constructor and Destructor
		Projectile(Point location, double angle);
		~Projectile();

		//Setters
		void setVelocity(double v);
		void setMass(double m);
        void updateCurrentLoc(Point newLoc);

		//Getters
		double getVelocity();
		double getMass();
		double getInitialAngle();
        Point getCurrentLoc();
        Point getStartLoc();

		//Constants
        Point startLoc;
		const double gravity = 9.81;

	private:
		int currentState = 0;
		double velocity;
		double mass;
		double initAngle;
        Point currentLoc;
    };

