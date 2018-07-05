void drawSkyBox(unsigned int face1, unsigned int face2, unsigned int face3, unsigned int face4, unsigned int face5, unsigned int face6){
	glColor3f(1.0,0.0,1.0);
	double Skybox_size = 500;
	double distance_to_skybox = 250;
	//Draw Four Side Planes and texture
	glPushMatrix();
	glTranslated(Skybox_size,0,distance_to_skybox);
	glRotated(90,0.0,1.0,0.0);
	glScaled(Skybox_size,Skybox_size,0);
	drawPlanewTexture(face1);
glPopMatrix();

glPushMatrix();
	glTranslated(-Skybox_size,0,distance_to_skybox);
	glRotated(90,0.0,1.0,0.0);
	glScaled(Skybox_size,Skybox_size,0);
	drawPlanewTexture(face2);
glPopMatrix();

glPushMatrix();
	glTranslated(0,Skybox_size,distance_to_skybox);
	glRotated(90,1.0,0.0,0.0);
	glScaled(Skybox_size,Skybox_size,0);
	drawPlanewTexture(face3);
glPopMatrix();

	glPushMatrix();
	glTranslated(0,-Skybox_size,distance_to_skybox);
	glRotated(90,1.0,0.0,0.0);
	glScaled(Skybox_size,Skybox_size,0);
	drawPlanewTexture(face4);
	glPopMatrix();

	//Top
	glPushMatrix();
	glTranslated(0,0,Skybox_size);
	glScaled(Skybox_size,Skybox_size,0);
	drawPlanewTexture(face5);
	glPopMatrix();
	
	//Bottom
	glScaled(Skybox_size,Skybox_size,0);
	drawPlanewTexture(face6);
}