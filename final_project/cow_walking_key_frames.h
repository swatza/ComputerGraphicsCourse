//Set all the cow key frames

//---- Walking ----
struct cow_frame** walking_frames;
int number_of_walking_frames = 12; //6*2

//------ Shim Sham Steps ------

//------ Cross Overs ------

//------ Tacky Anne's ------

//Break Step

//Boogie Forward

//Boogie Back

//Shorty George

void createWalkingFrames(){
	walking_frames = (struct cow_frame**)malloc(sizeof(struct* cow_frame) * number_of_walking_frames);
	walking_frame_0.LeftLeg.ULX = 0;
	walking_frame_0.LeftLeg.ULY = -30;
	walking_frame_0.LeftLeg.LLX = 0;
	walking_frame_0.LeftLeg.LLY = 30;

	walking_frame_0.RightLeg.ULX = 0;
	walking_frame_0.RightLeg.ULY = 0;
	walking_frame_0.RightLeg.LLX = 0;
	walking_frame_0.RightLeg.LLY = 0;

	walking_frame_0.RightArm = walking_frame_0.LeftLeg;
	walking_frame_0.LeftArm = walking_frame_0.RightLeg;

	walking_frame_1.LeftLeg.ULX = 0;
	walking_frame_1.LeftLeg.ULY = -40;
	walking_frame_1.LeftLeg.LLX = 0;
	walking_frame_1.LeftLeg.LLY = 0;

	walking_frame_1.RightLeg.ULX = 0;
	walking_frame_1.RightLeg.ULY = 0;
	walking_frame_1.RightLeg.LLX = 0;
	walking_frame_1.RightLeg.LLY = 0;

	walking_frame_1.RightArm = walking_frame_1.LeftLeg;
	walking_frame_1.LeftArm = walking_frame_1.RightLeg;

	walking_frame_2.LeftLeg.ULX = 0;
	walking_frame_2.LeftLeg.ULY = -30;
	walking_frame_2.LeftLeg.LLX = 0;
	walking_frame_2.LeftLeg.LLY = -15;

	walking_frame_2.RightLeg.ULX = 0;
	walking_frame_2.RightLeg.ULY = 15;
	walking_frame_2.RightLeg.LLX = 0;
	walking_frame_2.RightLeg.LLY = 0;

	walking_frame_2.RightArm = walking_frame_2.LeftLeg;
	walking_frame_2.LeftArm = walking_frame_2.RightLeg;

	walking_frame_3.LeftLeg.ULX = 0;
	walking_frame_3.LeftLeg.ULY = -10;
	walking_frame_3.LeftLeg.LLX = 0;
	walking_frame_3.LeftLeg.LLY = 0;

	walking_frame_3.RightLeg.ULX = 0;
	walking_frame_3.RightLeg.ULY = 30;
	walking_frame_3.RightLeg.LLX = 0;
	walking_frame_3.RightLeg.LLY = 15;

	walking_frame_3.RightArm = walking_frame_3.LeftLeg;
	walking_frame_3.LeftArm = walking_frame_3.RightLeg;

	walking_frame_4.LeftLeg.ULX = 0;
	walking_frame_4.LeftLeg.ULY = 0;
	walking_frame_4.LeftLeg.LLX = 0;
	walking_frame_4.LeftLeg.LLY = 0;

	walking_frame_4.RightLeg.ULX = 0;
	walking_frame_4.RightLeg.ULY = 35;
	walking_frame_4.RightLeg.LLX = 0;
	walking_frame_4.RightLeg.LLY = 25;

	walking_frame_4.RightArm = walking_frame_4.LeftLeg;
	walking_frame_4.LeftArm = walking_frame_4.RightLeg;

	walking_frame_5.LeftLeg.ULX = 0;
	walking_frame_5.LeftLeg.ULY = 0;
	walking_frame_5.LeftLeg.LLX = 0;
	walking_frame_5.LeftLeg.LLY = 0;

	walking_frame_5.RightLeg.ULX = 0;
	walking_frame_5.RightLeg.ULY = -20;
	walking_frame_5.RightLeg.LLX = 0;
	walking_frame_5.RightLeg.LLY = 45;

	walking_frame_5.RightArm = walking_frame_5.LeftLeg;
	walking_frame_5.LeftArm = walking_frame_5.RightLeg;

	//Beginning Repeat on other leg
	walking_frame_6.RightLeg = walking_frame_0.LeftLeg;
	walking_frame_7.RightLeg = walking_frame_1.LeftLeg;
	walking_frame_8.RightLeg = walking_frame_2.LeftLeg;
	walking_frame_9.RightLeg = walking_frame_3.LeftLeg;
	walking_frame_10.RightLeg = walking_frame_4.LeftLeg;
	walking_frame_11.RightLeg = walking_frame_5.LeftLeg;

	walking_frame_6.Leftleg = walking_frame_0.RightLeg;
	walking_frame_7.Leftleg = walking_frame_1.RightLeg;
	walking_frame_8.Leftleg = walking_frame_2.RightLeg;
	walking_frame_9.Leftleg = walking_frame_3.RightLeg;
	walking_frame_10.Leftleg = walking_frame_4.RightLeg;
	walking_frame_11.Leftleg = walking_frame_5.RightLeg;

	walking_frame_6.RightArm = walking_frame_6.LeftLeg;
	walking_frame_6.LeftArm = walking_frame_6.RightLeg;
	walking_frame_7.RightArm = walking_frame_7.LeftLeg;
	walking_frame_7.LeftArm = walking_frame_7.RightLeg;
	walking_frame_8.RightArm = walking_frame_8.LeftLeg;
	walking_frame_8.LeftArm = walking_frame_8.RightLeg;
	walking_frame_9.RightArm = walking_frame_9.LeftLeg;
	walking_frame_9.LeftArm = walking_frame_9.RightLeg;
	walking_frame_10.RightArm = walking_frame_10.LeftLeg;
	walking_frame_10.LeftArm = walking_frame_10.RightLeg;
	walking_frame_11.RightArm = walking_frame_11.LeftLeg;
	walking_frame_11.LeftArm = walking_frame_11.RightLeg;

	//Hand to the memory thing
	for (int i =0; i < number_of_walking_frames; i++){
		struct cow_frame *my_cow_frame_ptr = (struct cow_frame*)malloc(sizeof(struct cow_frame));
		if(i==0)
			*my_cow_frame_ptr = walking_frame_0;
		else if(i==1)
			*my_cow_frame_ptr = walking_frame_1;
		else if(i==2)
			*my_cow_frame_ptr = walking_frame_2;
		else if(i==3)
			*my_cow_frame_ptr = walking_frame_3;
		else if(i==4)
			*my_cow_frame_ptr = walking_frame_4;
		else if(i==5)
			*my_cow_frame_ptr = walking_frame_5;
		else if(i==6)
			*my_cow_frame_ptr = walking_frame_6;
		else if(i==7)
			*my_cow_frame_ptr = walking_frame_7;
		else if(i==8)
			*my_cow_frame_ptr = walking_frame_8;
		else if(i==9)
			*my_cow_frame_ptr = walking_frame_9;
		else if(i==10)
			*my_cow_frame_ptr = walking_frame_10;
		else if(i==1)
			*my_cow_frame_ptr = walking_frame_11;
		walking_frames[i] = my_cow_frame_ptr;
	}
}


