//这是一种状态机的实现方式，通过定义不同的状态，来实现不同的功能

typedef struct
{
	int start_time;
	int end_time;

	enum
	{
		EMS_PULSE_INIT,
		EMS_PULSE_UPDATE,
		EMS_RING_INIT,
		EMS_RING_UPDATE,
		EPT_RF_INIT,
		EMS_RF_UPDATE,
	} status;
} xNURESE_T;

typedef struct
{
	int start_time;
	int end_time;

	enum
	{
		EMS_FACE_INIT,
		EMS_FACE_UPDATE_UP,
		EMS_FACE_STABLE,
		EMS_FACE_UPDATE_DOWN,
		EMS_FACE_IDLE,
	} status;
} xFACE_T;

const xFACE_T xFACE[] =
	{
		{0, 0, EMS_FACE_INIT},
		{1, 400, EMS_FACE_UPDATE_UP},
		{401, 600, EMS_FACE_STABLE},
		{601, 800, EMS_FACE_UPDATE_DOWN}
		
};

const xNURESE_T xNURESE[] =
	{
		{0, 0, EMS_PULSE_INIT},
		{1, 499, EMS_PULSE_UPDATE},

		{500, 500, EMS_RING_INIT},
		{501, 749, EMS_RING_UPDATE},

		{750, 750, EPT_RF_INIT},
		{751, 999, EMS_RF_UPDATE},
};



void nurse_update(unsigned int timer)
{
	for (int i = 0; i < sizeof(xNURESE) / sizeof(xNURESE[0]); i++)
	{
		if (timer >= xNURESE[i].start_time && timer <= xNURESE[i].end_time)
		{
	
			switch (xNURESE[i].status)
			{
			case EMS_PULSE_INIT:
			
				break;
			case EMS_PULSE_UPDATE:
		;
				break;
			case EMS_RING_INIT:
			
				break;
			case EMS_RING_UPDATE:
			
				break;
			case EPT_RF_INIT:
			
				break;
			case EMS_RF_UPDATE:

				break;
			}
			break;
		}
	}
}

void face_update(unsigned int timer)
{

	for (int i = 0; i < sizeof(xFACE) / sizeof(xFACE[0]); i++)
	{
		if (timer >= xFACE[i].start_time && timer <= xFACE[i].end_time)
		{

			switch (xFACE[i].status)
			{
			case EMS_FACE_INIT:

				break;
			case EMS_FACE_UPDATE_UP:

				break;
	
			case EMS_FACE_STABLE:

				break;
			case EMS_FACE_UPDATE_DOWN:

				break;
			case EMS_FACE_IDLE:

				break;
			}
			break;
		}
	}
}


