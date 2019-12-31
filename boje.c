#include "funkcije.h"
	
	/* 
	Pravi listu pocetnih boja. U 'ostalo' kopiramo boje iz 'bojeOstalo' da bi 
		mogli da koristimo manje boja nego sto imamo dostupno. 
		
		U ostalo[][1] cuvamo R, ostalo[][2] G, ostalo[][3] B.
		Zatim  inicijalizujemo 'ostaloUsed' na 1 posto ni jedna boja nije 
		iskoriscena, pa	idemo kroz sve segmente staze i gledamo da li je ta 
		prepreka vec izabrana.
		Postavljamo random boju iz rgb-a pa za ostale prepreke na random 
		biramo prepreku i boju iz liste	'ostalo' i postavljamo prepreku na tu 
		boju, pa postavljamo 'ostaloUsed' na 0 kada se ta boja iskoristi da
		se ne koristi opet.
	 */
	
void pocetneBoje(){
	int i, j;
	int r, rRgb, rPrepreka;
	
	GLfloat *ostalo[brBoja];
	ostalo[brBoja] = malloc(sizeof(float) * brBoja);
	
	for(int i=0; i<brBoja; i++){  // pravi listu pocetnih boja
		ostalo[i] = malloc(sizeof(float) * 3);
		
		ostalo[i][0] = bojeOstalo[i][0];
		ostalo[i][1] = bojeOstalo[i][1];
		ostalo[i][2] = bojeOstalo[i][2];
	}

	int *ostaloUsed = malloc(sizeof(int) * brBoja);
	
	for(i=0; i<brStaza; i++){ // za svaku stazu
		
		rRgb = rand() % 3;		// random boja od R G B
		rPrepreka = rand() % 3;	// random prepreka za R G B
		
		for(int k=0; k<brBoja; k++){ ostaloUsed[k] = 1;}

		for(j=0; j<3; j++){ // za svaku prepreku
			int whileContinue = 1;
			
			if(j == rPrepreka){
				listaBoja[i].pBoja[j][0] = bojeRgb[rRgb][0];
				listaBoja[i].pBoja[j][1] = bojeRgb[rRgb][1];
				listaBoja[i].pBoja[j][2] = bojeRgb[rRgb][2];
			} else {
				while(whileContinue){ // bira jedinstvenu boju
					r = rand() % brBoja;
					if(ostaloUsed[r] == 1){
			
						listaBoja[i].pBoja[j][0] = ostalo[r][0];
						listaBoja[i].pBoja[j][1] = ostalo[r][1];
						listaBoja[i].pBoja[j][2] = ostalo[r][2];
				
						ostaloUsed[r] = 0;
						whileContinue = 0;
					}
				}
			}
		}
	}
}

/*posto transliramo stazu sve vreme umesto lopte moramo da shiftujemo boje */

void shift(){
	int i, j;
	int r, rRgb, rPrepreka;
	
	rRgb = rand() % 3;		// random boja od R G B
	rPrepreka = rand() % 3;	// random prepreka za R G B
	
	GLfloat *ostalo[brBoja];
	ostalo[brBoja] = malloc(sizeof(float) * brBoja);
	
	for(int i=0; i<brBoja; i++){
		ostalo[i] = malloc(sizeof(float) * 3);
		
		ostalo[i][0] = bojeOstalo[i][0];
		ostalo[i][1] = bojeOstalo[i][1];
		ostalo[i][2] = bojeOstalo[i][2];
	}

	for(i=0; i<brStaza-1; i++){
		for(j=0; j<3; j++){
			listaBoja[i].pBoja[j][0] = listaBoja[i+1].pBoja[j][0];
			listaBoja[i].pBoja[j][1] = listaBoja[i+1].pBoja[j][1];
			listaBoja[i].pBoja[j][2] = listaBoja[i+1].pBoja[j][2];
		}
	}
	
	int *ostaloUsed = malloc(sizeof(int) * brBoja);
	for(int k=0; k<brBoja; k++){ ostaloUsed[k] = 1;}
	
	for(j=0; j<3; j++){ // br prepreka
	
		int whileContinue = 1;
		if(j == rPrepreka){
				listaBoja[i].pBoja[j][0] = bojeRgb[rRgb][0];
				listaBoja[i].pBoja[j][1] = bojeRgb[rRgb][1];
				listaBoja[i].pBoja[j][2] = bojeRgb[rRgb][2];
		} else {
			while(whileContinue){
			
				r = rand() % brBoja;
				if(ostaloUsed[r] == 1){
				
					listaBoja[brStaza-1].pBoja[j][0] = ostalo[r][0];
					listaBoja[brStaza-1].pBoja[j][1] = ostalo[r][1];
					listaBoja[brStaza-1].pBoja[j][2] = ostalo[r][2];
			
					ostaloUsed[r] = 0;
					whileContinue = 0;
				}
			}
		}

	}
	
	//deo pomeranja za boost-ove
	//pomeramo prvih brStaza-1 za 1 unapred
	for(int i=0; i<brStaza-1; i++) {
		boost_position[i] = boost_position[i+1];
	}
	//pa postavljamo na poslednje mesto novu vrednost
	int rand_boost_spawn = rand() % 10;
	if(rand_boost_spawn < boost_spawn_chance) {
		int rand_lane = rand() % 3;
		boost_position[brStaza-1] = rand_lane;
	} else {
		boost_position[brStaza-1] = -1;
	}
	
}















