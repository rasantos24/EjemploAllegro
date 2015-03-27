#include <allegro.h>
#include "inicia.h"
#include "disparos.h"

#define ANCHO 600
#define ALTO  375

struct NAVE
{
     int x,y;
     int nDisp;
     int maxDisp;
     int tick;

     BITMAP* imgNave;
     BITMAP* imgBala;

     void inicia(char* rutaNave , char* rutaBala);
     bool temporizador();
     void pinta(BITMAP* buffer);
     void mueve();
};

void NAVE::inicia(char* rutaNave , char* rutaBala)
{
     x = ANCHO/2; y = ALTO -50;
     nDisp = 0; maxDisp = 5;
     imgNave = load_bitmap(rutaNave,NULL);
     imgBala = load_bitmap(rutaBala,NULL);
     tick = 0;

}

bool NAVE::temporizador()
{
    tick++;
    if(tick == 5)
    {
        tick = 0;
        return true;
    }
    return false;
}

void NAVE::pinta(BITMAP* buffer)
{
    masked_blit(imgNave,buffer,0,0,x,y,30,20);
}

void NAVE::mueve()
{
    if(key[KEY_A] && x>=1) x -= 5;
    if(key[KEY_D] && x<=565) x += 5;
//    if(key[KEY_W] && y>=1) y -= 5;
//    if(key[KEY_S] && y<=353) y += 5;
}

int main()
{

    inicia_allegro(ANCHO,ALTO); // fuciones del include inicia.h
	inicia_audio(70,70);        //

    BITMAP *buffer = create_bitmap(ANCHO, ALTO);

    NAVE N;
    N.inicia("Recursos/nave.bmp" , "Recursos/Bala2.bmp");
    Balas disparos[N.maxDisp];

    while(!key[KEY_ESC])
    {
        clear_to_color(buffer,0x000000);
        N.pinta(buffer);
        N.mueve();

        if(key[KEY_SPACE] && N.temporizador())
        crear_bala(N.nDisp , N.maxDisp , disparos , N.x , N.y, -8);

        pintar_bala(N.nDisp , N.maxDisp , disparos , buffer , N.imgBala);
        elimina_bala(N.nDisp , N.maxDisp , disparos , ANCHO , ALTO);

        blit(buffer, screen , 0,0 ,0,0 ,ANCHO, ALTO);
        rest(20);
    }

	return 0;
}

END_OF_MAIN();

