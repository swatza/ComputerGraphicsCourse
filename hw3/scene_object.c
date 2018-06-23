struct cow_object{
	//We need information to draw the object (MESH) (polygons, triangles, etc...)
	//Information about where the object is (location and orientation)
	//Information about the mesh collider 

	//Object Name 
	char *object_name;
	//Object identifier
	int object_identifier
	//Object type (Cow, Aircraft, Groundplane, Fence)
	struct cow_skeleton skeleton;
}