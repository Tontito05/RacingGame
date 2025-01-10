#pragma once
#include "Car.h"

class IA : public Car
{
public:
	//IA constructor
	IA(ModulePhysics* physics, int x, int y, int width, int height, Module* listener, Texture2D texture, Group type, int rank)
		: Car(physics, x, y, width, height, listener, texture, type)
	{

		//Set the waypoints
		switch (rank)
		{
		case 1:

			waypoints.push_back({ 200, 349 });
			waypoints.push_back({ 266, 348 });
			waypoints.push_back({ 322, 330 });
			waypoints.push_back({ 347, 300 });
			waypoints.push_back({ 343, 256 });
			waypoints.push_back({ 296, 211 });
			waypoints.push_back({ 252, 197 });
			waypoints.push_back({ 205, 176 });
			waypoints.push_back({ 167, 148 });
			waypoints.push_back({ 170, 113 });
			waypoints.push_back({ 233, 69 });
			waypoints.push_back({ 316, 60 });
			waypoints.push_back({ 432, 59 });
			waypoints.push_back({ 501, 91 });
			waypoints.push_back({ 562, 109 });
			waypoints.push_back({ 626, 90 });
			waypoints.push_back({ 709, 54 });
			waypoints.push_back({ 791, 47 });
			waypoints.push_back({ 877, 54 });
			waypoints.push_back({ 903, 89 });
			waypoints.push_back({ 892, 123 });
			waypoints.push_back({ 784, 164 });
			waypoints.push_back({ 751, 193 });
			waypoints.push_back({ 733, 249 });
			waypoints.push_back({ 710, 273 });
			waypoints.push_back({ 645, 272 });
			waypoints.push_back({ 590, 271 });
			waypoints.push_back({ 541, 300 });
			waypoints.push_back({ 535, 358 });
			waypoints.push_back({ 548, 416 });
			waypoints.push_back({ 520, 483 });
			waypoints.push_back({ 518, 495 });
			waypoints.push_back({ 522, 506 });
			waypoints.push_back({ 531, 521 });
			waypoints.push_back({ 529, 537 });
			waypoints.push_back({ 525, 553 });
			waypoints.push_back({ 524, 574 });
			waypoints.push_back({ 532, 585 });
			waypoints.push_back({ 545, 595 });
			waypoints.push_back({ 560, 602 });
			waypoints.push_back({ 580, 611 });
			waypoints.push_back({ 594, 630 });
			waypoints.push_back({ 607, 650 });
			waypoints.push_back({ 648, 678 });
			waypoints.push_back({ 732, 690 });
			waypoints.push_back({ 842, 671 });
			waypoints.push_back({ 861, 635 });
			waypoints.push_back({ 830, 585 });
			waypoints.push_back({ 798, 585 });
			waypoints.push_back({ 762, 578 });
			waypoints.push_back({ 732, 550 });
			waypoints.push_back({ 740, 506 });
			waypoints.push_back({ 784, 452 });
			waypoints.push_back({ 834, 418 });
			waypoints.push_back({ 887, 391 });
			waypoints.push_back({ 914, 386 });
			waypoints.push_back({ 931, 392 });
			waypoints.push_back({ 940, 403 });
			waypoints.push_back({ 943, 431 });
			waypoints.push_back({ 944, 451 });
			waypoints.push_back({ 952, 471 });
			waypoints.push_back({ 990, 483 });
			waypoints.push_back({ 1059, 503 });
			waypoints.push_back({ 1092, 525 });
			waypoints.push_back({ 1116, 547 });
			waypoints.push_back({ 1150, 585 });
			waypoints.push_back({ 1184, 621 });

			speed = 4;

			break;
		case 2:

			waypoints.push_back({ 200, 349 });
			waypoints.push_back({ 266, 348 });
			waypoints.push_back({ 322, 330 });
			waypoints.push_back({ 347, 300 });
			waypoints.push_back({ 343, 256 });
			waypoints.push_back({ 296, 211 });
			waypoints.push_back({ 252, 197 });
			waypoints.push_back({ 205, 176 });
			waypoints.push_back({ 167, 148 });
			waypoints.push_back({ 170, 113 });
			waypoints.push_back({ 233, 69 });
			waypoints.push_back({ 316, 60 });
			waypoints.push_back({ 432, 59 });
			waypoints.push_back({ 501, 91 });
			waypoints.push_back({ 562, 109 });
			waypoints.push_back({ 626, 90 });
			waypoints.push_back({ 709, 54 });
			waypoints.push_back({ 791, 47 });
			waypoints.push_back({ 877, 54 });
			waypoints.push_back({ 903, 89 });
			waypoints.push_back({ 892, 123 });
			waypoints.push_back({ 784, 164 });
			waypoints.push_back({ 751, 193 });
			waypoints.push_back({ 733, 249 });
			waypoints.push_back({ 710, 273 });
			waypoints.push_back({ 645, 272 });
			waypoints.push_back({ 590, 271 });
			waypoints.push_back({ 541, 300 });
			waypoints.push_back({ 535, 358 });
			waypoints.push_back({ 548, 416 });
			waypoints.push_back({ 520, 483 });
			waypoints.push_back({ 452, 527 });
			waypoints.push_back({ 342, 544 });
			waypoints.push_back({ 217, 550 });
			waypoints.push_back({ 175, 576 });
			waypoints.push_back({ 171, 621 });
			waypoints.push_back({ 206, 657 });
			waypoints.push_back({ 283, 685 });
			waypoints.push_back({ 358, 695 });
			waypoints.push_back({ 408, 692 });
			waypoints.push_back({ 445, 647 });
			waypoints.push_back({ 531, 635 });
			waypoints.push_back({ 607, 650 });
			waypoints.push_back({ 648, 678 });
			waypoints.push_back({ 732, 690 });
			waypoints.push_back({ 842, 671 });
			waypoints.push_back({ 861, 635 });
			waypoints.push_back({ 830, 585 });
			waypoints.push_back({ 798, 585 });
			waypoints.push_back({ 762, 578 });
			waypoints.push_back({ 732, 550 });
			waypoints.push_back({ 740, 506 });
			waypoints.push_back({ 784, 452 });
			waypoints.push_back({ 834, 418 });
			waypoints.push_back({ 887, 391 });
			waypoints.push_back({ 914, 386 });
			waypoints.push_back({ 931, 392 });
			waypoints.push_back({ 940, 403 });
			waypoints.push_back({ 943, 431 });
			waypoints.push_back({ 944, 451 });
			waypoints.push_back({ 952, 471 });
			waypoints.push_back({ 990, 483 });
			waypoints.push_back({ 1059, 503 });
			waypoints.push_back({ 1092, 525 });
			waypoints.push_back({ 1116, 547 });
			waypoints.push_back({ 1150, 585 });

			speed = 3;

			break;
		case 3:

			waypoints.push_back({ 200, 349 });
			waypoints.push_back({ 266, 348 });
			waypoints.push_back({ 322, 330 });
			waypoints.push_back({ 347, 300 });
			waypoints.push_back({ 343, 256 });
			waypoints.push_back({ 296, 211 });
			waypoints.push_back({ 252, 197 });
			waypoints.push_back({ 205, 176 });
			waypoints.push_back({ 167, 148 });
			waypoints.push_back({ 170, 113 });
			waypoints.push_back({ 233, 69 });
			waypoints.push_back({ 316, 60 });
			waypoints.push_back({ 432, 59 });
			waypoints.push_back({ 501, 91 });
			waypoints.push_back({ 562, 109 });
			waypoints.push_back({ 626, 90 });
			waypoints.push_back({ 709, 54 });
			waypoints.push_back({ 791, 47 });
			waypoints.push_back({ 877, 54 });
			waypoints.push_back({ 903, 89 });
			waypoints.push_back({ 892, 123 });
			waypoints.push_back({ 784, 164 });
			waypoints.push_back({ 751, 193 });
			waypoints.push_back({ 733, 249 });
			waypoints.push_back({ 710, 273 });
			waypoints.push_back({ 645, 272 });
			waypoints.push_back({ 590, 271 });
			waypoints.push_back({ 541, 300 });
			waypoints.push_back({ 535, 358 });
			waypoints.push_back({ 548, 416 });
			waypoints.push_back({ 520, 483 });
			waypoints.push_back({ 452, 527 });
			waypoints.push_back({ 342, 544 });
			waypoints.push_back({ 217, 550 });
			waypoints.push_back({ 175, 576 });
			waypoints.push_back({ 171, 621 });
			waypoints.push_back({ 206, 657 });
			waypoints.push_back({ 283, 685 });
			waypoints.push_back({ 358, 695 });
			waypoints.push_back({ 408, 692 });
			waypoints.push_back({ 445, 647 });
			waypoints.push_back({ 531, 635 });
			waypoints.push_back({ 607, 650 });
			waypoints.push_back({ 648, 678 });
			waypoints.push_back({ 732, 690 });
			waypoints.push_back({ 842, 671 });
			waypoints.push_back({ 861, 635 });
			waypoints.push_back({ 830, 585 });
			waypoints.push_back({ 768, 583 });
			waypoints.push_back({ 733, 555 });
			waypoints.push_back({ 737, 506 });
			waypoints.push_back({ 785, 450 });
			waypoints.push_back({ 865, 403 });
			waypoints.push_back({ 961, 376 });
			waypoints.push_back({ 986, 335 });
			waypoints.push_back({ 968, 301 });
			waypoints.push_back({ 932, 301 });
			waypoints.push_back({ 907, 328 });
			waypoints.push_back({ 920, 371 });
			waypoints.push_back({ 938, 410 });
			waypoints.push_back({ 947, 457 });
			waypoints.push_back({ 970, 480 });
			waypoints.push_back({ 1010, 491 });
			waypoints.push_back({ 1065, 507 });
			waypoints.push_back({ 1116, 547 });
			waypoints.push_back({ 1150, 585 });

			speed = 2;
			break;
		default:
			break;
		}


	}

	//IA functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Pattern to follow the finish line and the road
	void Pattern();

	// Always forward
	void MoveAlwaysForward();

	int waypointsIndex = 0;
	std::vector<b2Vec2> waypoints;

	float speed;

private:

};
