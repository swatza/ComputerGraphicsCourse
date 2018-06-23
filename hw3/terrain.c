
//includes

//Global variables??
double* x_positions;
double* y_positions;
double* z_positions;


void getHeightData(double* x, double* y, int size){
	//open a file
	FILE *fp;
	char *filename = "test.txt"; //name of the file in the folder that holds the terrain information
	fp = fopen(filename,"r");
	//check to see if we got anything
	if(fp == NULL){
		fprintf(stderr,"Can't open input file\n");
		//Do we want to exit or return? 
		exit(1);
	}
	//loop through the x and y coordinates
	int i; int j;
	//double output_buffer[size]; //should be nxm = size (MALLOC THIS ACTUALLY)
	z_positions = malloc(sizeof(double)*size);
	for (i=0;i<size;i++){
		//Get the location in the file
		long int byteLocation = calculateByteFromXY(x[i],y[i]);
		//seek to that location
		fseek(fp,byteLocation,SEEK_SET); //where 0 should be the location 
		//grab the bytes
		fread(&z_positions[i], sizeof(double), 1, fp); //read one double and put it into the buffer at that spot
	}
	
	//close file
	fclose(fp);
	
}

/*
* Function that receives the lat,lon,alt of a point and the lat,lon,alt of the center and converts to flat earth approximation using WGS84
* Returns X,Y
*/
double* LLA2FLAT(double* lla, double* center_lla){
	//Copy code from python/matlab to do this 
}

double* FLAT2LLA(double* ENU, double* center_lla){
	//Copy code from python/matlab to do this 
}

long int calculateByteFromXY(double x, double y){
	//Function that knows the arrangement/setup of the file
}

//Do this before many other operations with glut
void getTerrainMeshData(){
	//Center LLA of region 
	double center_lla[3];
	center_lla[0] = 0; //lattitude 
	center_lla[1] = 0; //longitude
	center_lla[2] = 0; //reference alt 0
	//Region of interest (How many kilometers)
	double north = 1000;
	double south = 1000;
	double east = 1000;
	double west = 1000;
	double map_resolution = 1; //if in the US we can get 1m maps 
	//calculate number of points/cells 
	double size = (north+south)/map_resolution * (east+west)/map_resolution;
	
	//Is the DEM going to be lat/lon or is it going to be flat? idk 
	x_positions = malloc(sizeof(double)*size);
	y_positions = malloc(sizeof(double)*size);
	
	//Get all the values for the x and y
	int i; int j; int counter = 0;
	//Loop from xmin to xmax; ymin to ymax
	for (i=-west; i < east; i+= map_resolution){
		for (j=-south; j < north; j+= map_resolution){
			//Assign all the positions
			x_positions[counter] = i;
			y_positions[counter] = j;
		}
	}
	
	//Get the height and store into the global variable
	getHeightData(x_positions,y_positions,size);
}