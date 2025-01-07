#include "IA.h"

bool IA::CheckGear()
{
	b2Vec2 vel = body->GetVelocity();

	//Check the gear in each moment, and set diferent variables to the car, so that each gear ist equilibrated
	switch (GearChange)
	{
	case 0:
		Acceleration = { 3,3 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.05;
		EndDriftLerp = 0.2;

		break;
	case 1:

		Acceleration = { 5,5 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.04;
		EndDriftLerp = 0.1;

		jumpaScale = 0.015;
		airTime = 0.6;

		break;

	case 2:

		Acceleration = { 10 ,10 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.02;
		EndDriftLerp = 0.05;

		jumpaScale = 0.02;
		airTime = 0.7;

		break;

	case 3:
		Acceleration = { 15,15 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.02;
		EndDriftLerp = 0.03;
		jumpaScale = 0.025;
		airTime = 0.8;

		break;

	default:
		break;
	}

	//Naw chack if the player should or not change the gear
	if (GearChange < 3 && vel.Length() > GetMaxVel().Length() * 0.8)
	{
		return true;
	}
	if (vel.Length() < GetMaxVel().Length())
	{
		return false;
	}

}
void IA::GearBack()
{
	b2Vec2 vel = body->GetVelocity();
	//Set the gears back if nessessary
	if (GearChange != 0 && vel.Length() < Gears[GearChange - 1].Length() * 0.3)
	{
		GearChange--;
	}
}
b2Vec2 IA::GetMaxVel()
{
	//get the maximum velocity that the car can reach in each gear
	b2Vec2 MaxVel = Gears[GearChange];
	MaxVel += GetFriction(MaxVel);
	return MaxVel;
}

Vector2 IA::GetPosition() {
	int x, y;
	body->GetPhysicPosition(x, y);
	return Vector2{ (float)x, (float)y };
}

void IA::Pattern()
{
	/*if (waypointsIndex < waypoints.size())
	{
		b2Vec2 diff = waypoints[waypointsIndex] - body->body->GetPosition();
		transform.right = diff;
		transform.Translate(Vector3.right * speed * Time.deltaTime);

		if (diff.magnitude < .1f) {
			waypointsIndex++;
		}
	}
	else {
		Destroy(gameObject);
	}*/

	if (waypointsIndex < waypoints.size()) {
		// Calcular la dirección hacia el siguiente waypoint
		b2Vec2 currentPosition = body->body->GetPosition();
		b2Vec2 diff = waypoints[waypointsIndex] - currentPosition;

		// Normalize
		float distance = diff.Length();
		if (distance > 0) {
			b2Vec2 direction = diff;
			direction.Normalize();

			// Move
			/*b2Vec2 velocity = direction;
			velocity *= 2.0f;
			body->body->SetLinearVelocity(velocity);*/
			Rotate(0);
			MoveForward();
			Update();
		}

		// Verificar si hemos alcanzado el waypoint actual
		if (distance < 0.1f) {
			waypointsIndex++;
		}
	}
	else {
		// Destruir el cuerpo si hemos terminado (simulando Destroy en Unity)
		std::cout << "Waypoints completados. Destruyendo objeto." << std::endl;
		/*body->body->GetWorld()->DestroyBody(body->body);*/
	}


}

//void Update(b2Body* body, std::vector<b2Vec2>& waypoints, int& waypointsIndex, float speed, float deltaTime) {
//	if (waypointsIndex < waypoints.size()) {
//		// Calcular la dirección hacia el siguiente waypoint
//		b2Vec2 currentPosition = body->GetPosition();
//		b2Vec2 diff = waypoints[waypointsIndex] - currentPosition;
//
//		// Normalizar la dirección
//		float distance = diff.Length();
//		if (distance > 0) {
//			b2Vec2 direction = diff;
//			direction.Normalize();
//
//			// Mover el cuerpo en la dirección hacia el waypoint
//			b2Vec2 velocity = direction * speed;
//			body->SetLinearVelocity(velocity);
//		}
//
//		// Verificar si hemos alcanzado el waypoint actual
//		if (distance < 0.1f) {
//			waypointsIndex++;
//		}
//	}
//	else {
//		// Destruir el cuerpo si hemos terminado (simulando Destroy en Unity)
//		std::cout << "Waypoints completados. Destruyendo objeto." << std::endl;
//		body->GetWorld()->DestroyBody(body);
//	}
//}
