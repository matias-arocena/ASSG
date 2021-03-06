#include "juego.h"

Juego::Juego(const char* titulo, int x, int y){
	pantalla=SDL_CreateWindow(titulo,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,x,y,SDL_WINDOW_SHOWN);
	render=SDL_CreateRenderer(pantalla,-1,SDL_RENDERER_PRESENTVSYNC);
	running=false;
	puntos=0;
	espacio = new Espacio(render);
	nave = new Nave(render,pantalla,"Others/nave.png");
	for(int i=0;i<5;i++) enemigo[i]=new Enemigo(render,pantalla,"Others/enemigo.png");
}

Juego::~Juego(){
	//enemigo=NULL;
	delete espacio;
	delete nave;
//	enemigos.clear();
	for(int i=0;i<5;i++) delete enemigo[i];
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(pantalla);
}

void Juego::ejecutar(){
	running=true;
	while(running){
		renderizar();
		eventos();
		actualizar();
	}
}

void Juego::renderizar(){
	SDL_RenderClear(render);

	espacio->renderizar();
	nave->renderizar();
/*
   for(unsigned int i=0;i<enemigos.size();i++){
		enemigos[i].renderizar();
	}
*/
	for(int i=0;i<5;i++){
		enemigo[i]->renderizar();
	}
	SDL_RenderPresent(render);
}

void Juego::eventos(){
	SDL_PollEvent(&evento);
	SDL_Scancode sc;

	switch(evento.type){
	case SDL_QUIT:
		running=false;
		break;
	case SDL_KEYDOWN:
		sc = evento.key.keysym.scancode;
		if (sc==SDL_SCANCODE_A || sc==SDL_SCANCODE_LEFT){
			nave->moverIzquierda();
		}
		else if(sc==SDL_SCANCODE_D || sc==SDL_SCANCODE_RIGHT){
			nave->moverDerecha();
		}

		if(sc==SDL_SCANCODE_SPACE){
			nave->disparar(5);
		}
		break;
	case SDL_KEYUP:
		nave->detener();
		break;

	}
}

void Juego::actualizar(){
	for(int i=0;i<=5;i++){
		nave->bala[i]->colision(enemigo[0]);
		nave->bala[i]->colision(enemigo[1]);
		nave->bala[i]->colision(enemigo[2]);
		nave->bala[i]->colision(enemigo[3]);
		nave->bala[i]->colision(enemigo[4]);
	}
	nave->actualizar();
	for(int i=0;i<5;i++) enemigo[i]->actualizar();
	/*
	for(unsigned int i=0; i<enemigos.size();i++){
		enemigos[i].actualizar();
	}
	*/
}



