#include <GL/freeglut.h>

#include "ClothSimulator.h"

ClothSimulator::ClothSimulator() {
	clothMesh = NULL;
	nV = nE = nT = nB = 0;
}

ClothSimulator::ClothSimulator(TriangularMesh* clmesh) :clothMesh(clmesh) {
	initWithClothMesh(clmesh);
}

ClothSimulator::~ClothSimulator() {

}

void ClothSimulator::toggleFixedConstraint(int index) {
	list<int>::iterator itr = fixedConstraintVertices.begin();
	for (; itr != fixedConstraintVertices.end(); itr++) {
		if (*itr < index)
			continue;
		else if (*itr > index) {
			fixedConstraintVertices.insert(itr, index);
			return;
		}
		else if (index == *itr) {
			fixedConstraintVertices.erase(itr);
			return;
		}
	}

	fixedConstraintVertices.push_back(index);
}

void ClothSimulator::addCollider(TriangularMesh* tm) {
	colliders.push_back(tm);
}

void ClothSimulator::drawMesh() {
	glPushMatrix();

	// Material setting (pearl)
	float mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	float mat_ambient[] = { 0.25, 0.20725, 0.20725, 0.922 };
	float mat_diffuse[] = { 1.0, 0.829, 0.829, 0.922 };
	float mat_specular[] = { 0.296648, 0.296648, 0.296648, 0.922 };
	float mat_shininess[] = { 11.264 };

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nT; i++) {
		//glColor3f(0, 1, 0);
		glVertex3f(pos[triangles[i][0]][0], pos[triangles[i][0]][1], pos[triangles[i][0]][2]);
		glVertex3f(pos[triangles[i][1]][0], pos[triangles[i][1]][1], pos[triangles[i][1]][2]);
		glVertex3f(pos[triangles[i][2]][0], pos[triangles[i][2]][1], pos[triangles[i][2]][2]);
	}
	glEnd();

	glPopMatrix();
}

void ClothSimulator::drawVertices() {
	glPushMatrix();

	glDisable(GL_LIGHTING);

	// vertices
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glColor3f(1, 0.3, 0.3);
	for (int i = 0; i < nV; i++)
		glVertex3f(pos[i][0], pos[i][1], pos[i][2]);
	glEnd();

	// edges
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(0.5, 0, 0);
	for (int i = 0; i < nE; i++) {
		glVertex3f(pos[edges[i][0]][0], pos[edges[i][0]][1], pos[edges[i][0]][2]);
		glVertex3f(pos[edges[i][1]][0], pos[edges[i][1]][1], pos[edges[i][1]][2]);
	}
	glEnd();
	//glEnable(GL_LIGHTING);

	glPopMatrix();
}

void ClothSimulator::drawBVH() {
	// argument meaning (1: root, 2: children of root, ...)
	for (auto col : CCD_colliders)
		if(col.getBVH() != NULL)
			col.visualizeBVH(3);
}

void ClothSimulator::initPBD() {	
	for (int i = 0; i < nV; i++) { //initialize velocity
		vel[i][0] = 0.0; vel[i][1] = 20.0; vel[i][2] = 0.0;
	}
}

void ClothSimulator::updatePBD() {
	Parameter& param = Parameter::getInstance(); //parameter instance 积己

	for (int i = 0; i < nV; i++) { //舅绊府硫 Line (5), (7) 利侩
		vel[i][1] += param.getTimestep() * param.getGravity();
		pred_pos[i] += vel[i] * param.getTimestep();
	}
}

void ClothSimulator::initRestAngles() {
	
}

void ClothSimulator::initRestLenghtsOfBending() {
	
}

void ClothSimulator::calForce() {
	
}

void ClothSimulator::calDistanceConstraint() {
	
}

void ClothSimulator::calBendingConstraint() {
	
}
