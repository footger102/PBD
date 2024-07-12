#include <iostream>
using namespace std;

#include "Parameter.h"

Parameter* Parameter::instance = NULL; //싱글턴 패턴

Parameter::Parameter() {
	initParameters();
}

Parameter::~Parameter() {

}

Parameter& Parameter::getInstance() {
	if (instance == NULL)
		instance = new Parameter();

	return *instance;
}

void Parameter::initParameters() {
	timeStep = 0.01;
	mass = 0.00001;
	gravity = -98.0; //980에서 98.0으로 수정
	stretch = 1;
	bending = 1;
	iteration = 20;
}

double Parameter::getTimestep() {
	return timeStep;
}

double Parameter::getMass() {
	return mass;
}

double Parameter::getGravity() {
	return gravity;
}

double Parameter::getStretchStiffness() {
	return stretch;
}

double Parameter::getBendingStiffness() {
	return bending;
}

int Parameter::getIteration() {
	return iteration;
}