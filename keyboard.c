#include "funkcije.h"


void on_keyboard(unsigned char key, int x, int y){

	switch (key){
		case 27:
		    // zavrsava se program na ESC
			exit(0);
			break;
		
		/* namestamo kontrole, za 'd' proveravamo da li se nalazimo u desnom
			delu staze. Ako ne, loptu transliramo(menjamo koordinate za lane) 
			udesno za sirinu staze/laneOffset. Isto i za levo */
		
		case 'd':
		case 'D':
			if(laneCoord != 0 - wStaza/laneOffset){
				laneCoord = laneCoord - wStaza/laneOffset;
				lane += 1;
		    }
		    break;
		    
		case 'a':
		case 'A':
			if(laneCoord != 0 + wStaza/laneOffset){
				laneCoord = laneCoord + wStaza/laneOffset;
				lane -= 1;
		    }
		    break;
		    
		//menjamo boju lopte: 'j' - crvena,'k' - zelena, 'l' - plava 
		    
		case 'j':			
		case 'J':
			loptaR = 1.0, loptaG = 0.0, loptaB = 0.0;		
			break;
			
		case 'k':
		case 'K':
			loptaR = 0.0, loptaG = 1.0, loptaB = 0.0;
			break;
			
		case 'l':
		case 'L':
			loptaR = 0.0, loptaG = 0.0, loptaB = 1.0;
			break;
		
		// na reset stavljamo sve vrednosti na inicijalne
		case 'r':
		case 'R':
			running = 1;
			score = 0;
    		ballSpeed = 15;
			laneCoord = 0;
			lane = 1;
			scoreMulti = 1;
    		noObstacles = 0;
			animation_parameter = 0;
			animation_parameter2 = 0;
			glutTimerFunc(ballSpeed, on_timer, 0);
			pocetneBoje();
    		pocetni_boost();
    		boost_colected = 0;
			break;
	
		//pauziramo igru, svaku animaciju zasebno
		case 'p':
		case 'P':
			if(running){
				running = 0;
			} else {
				running = 1;
				glutTimerFunc(ballSpeed, on_timer, 0);
			}
			if(running2){
				running2 = 0;
			} else {
				running2 = 1;
				glutTimerFunc(ballSpeed, on_timer, 1);
			}
			break;
	}
}
