#include <stdio.h>
#include <time.h>
#include "/Anant/US_FUNCTIONS/hwfunctions.h"
#include <stdlib.h>
#include <errno.h>

#define send_hk_t(f) NULL //do nothing

int main()
{
    FILE *f = fopen("/home/smr/Anant/Transmit/downlink_hk.txt", "a");
    if(f==NULL)
    {
        perror("Error");
        exit(0);
    }

	//initialization of the three sensors
	init_magnetometer();
	init_gy521();
	init_gy80();

    time_t curt;
    curt = time(NULL);
    char* finalstr = (char*) malloc(50); 
    //fseek(f, 0, SEEK_END);
    sprintf(finalstr, "Time: %s\n", ctime(&curt));fputs(finalstr, f);
    sprintf(finalstr, "Bx: %d\n", get_Bx());fputs(finalstr, f);
    sprintf(finalstr, "By: %d\n", get_By());fputs(finalstr, f);
    sprintf(finalstr, "Bz: %d\n", get_Bz());fputs(finalstr, f);
    sprintf(finalstr, "S1: %d\n", get_S1());fputs(finalstr, f);
    sprintf(finalstr, "S2: %d\n", get_S2());fputs(finalstr, f);
    sprintf(finalstr, "S3: %d\n", get_S3());fputs(finalstr, f);
    sprintf(finalstr, "S4: %d\n", get_S4());fputs(finalstr, f);
    sprintf(finalstr, "S5: %d\n", get_S5());fputs(finalstr, f);
    sprintf(finalstr, "Wx: %d\n", get_Wx());fputs(finalstr, f);
    sprintf(finalstr, "Wy: %d\n", get_Wy());fputs(finalstr, f);
    sprintf(finalstr, "Wz: %d\n", get_Wz());fputs(finalstr, f);
    sprintf(finalstr, "Ax: %d\n", get_Ax());fputs(finalstr, f);
    sprintf(finalstr, "Ay: %d\n", get_Ay());fputs(finalstr, f);
    sprintf(finalstr, "Az: %d *end of block*\n\n", get_Az());fputs(finalstr, f);
    FILE *f1 = send_hk_t(f);
	fclose(f);
	
	//closing the three sensors
	clear_magnetometer();
	clear_gy521();
	clear_gy80();
    
}
