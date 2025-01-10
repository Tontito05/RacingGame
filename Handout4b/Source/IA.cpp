#include "IA.h"

void IA::MoveAlwaysForward() {
	// Get the current angle of the body
	float angle = body->body->GetAngle();

	// Calculate the forward direction vector
	b2Vec2 forwardVec(cos(angle), sin(angle));

	// Set the body's velocity in the forward direction
	b2Vec2 velocity = speed * forwardVec;
	body->body->SetLinearVelocity(velocity);
}

void IA::Pattern()
{
	if (waypointsIndex < waypoints.size()-1) {
		
		// Waypoint direction
		b2Vec2 currentPosition = body->body->GetPosition();
		b2Vec2 diff;
		diff.x = (PIXEL_TO_METERS(waypoints[waypointsIndex].x)*SCALE - currentPosition.x);
		diff.y = (PIXEL_TO_METERS(waypoints[waypointsIndex].y)*SCALE - currentPosition.y);

		float distance = diff.Length();
		if (distance > 0) {
			b2Vec2 direction = diff;
			direction.Normalize();
			
			float desiredAngle = atan2(direction.y, direction.x);
			body->body->SetTransform(currentPosition, desiredAngle);

			MoveAlwaysForward();
		}

		if (distance < 0.1f) {
			waypointsIndex++;
			
			cout << "Waypoint: " << waypointsIndex << " x: " << waypoints[waypointsIndex].x << " y: " << waypoints[waypointsIndex].y << endl;
			
			cout << "Waypoint: " << waypointsIndex << " x: " << PIXEL_TO_METERS(waypoints[waypointsIndex].x) << " y: " << PIXEL_TO_METERS(waypoints[waypointsIndex].y) << endl;
		}
	}
	else {
		std::cout << "Waypoints completed." << std::endl;
		
		SetXvelocity(0);
		SetYvelocity(0);
	}


}