#include "funkcije.h"
int *boost_position;

// inicijalizujemo vrednosti boostera za brStaza-1 segmenata
void pocetni_boost() {
	boost_position = malloc(sizeof(int) * brStaza);
	for(int i=0; i<brStaza; i++) {
		// rand vrednost izmedju 1 i 10 koju koristimo za % pojavljivanja (0%-100%, 10%)
		int rand_boost_spawn = rand() % 10;
		
		if(rand_boost_spawn < boost_spawn_chance) {
			// ako se pojavi, biramo random lane
			int rand_lane = rand() % 3;
			boost_position[i] = rand_lane;
		} else {
			// inace nije inicijalizovano
			boost_position[i] = -1;
		}
	}
}

void spawn_boost(int rBoostLane){
	//ako treba da postoji u toj stazi
	if(rBoostLane != -1){
		//transliramo u lane, centralni je default
		if(rBoostLane == 2){
			glTranslatef(-wStaza/laneOffset, 0, 0);
		} else if(rBoostLane == 0){
			glTranslatef(+wStaza/laneOffset, 0, 0);
		}
	
		glTranslatef(0, 0.4, -lStaza/2);
		glRotatef(-animation_parameter*90, 0, 1, 0);
			//iscrtavanje objekta boost
			boost();
		glRotatef(animation_parameter*90, 0, 1, 0);
		glTranslatef(0, -0.4, lStaza/2);
	
		// vracanje translacije
		if(rBoostLane == 2){
			glTranslatef(+wStaza/laneOffset, 0, 0);
		} else if(rBoostLane == 0){
			glTranslatef(-wStaza/laneOffset, 0, 0);
		}

	}   
}

