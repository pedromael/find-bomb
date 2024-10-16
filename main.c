#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 800
#define HEIGTH 600
#define N_BOMBAS 3 
#define VELOCIDADE 10
#define P_INCIAL 20
#define MAX_SIZE_BLOCK 8

typedef struct {
    int x,y,size;
    int jogador;
} tentativa;

typedef struct{
    int x,y;
    int size;
} bomba;

int numeroDeTentativas = 0;
int jogadorSelecionado;
int jogadorInicial;
int pontosJogador[2] = {P_INCIAL, P_INCIAL};
tentativa *tentativas;
bomba *bombas;

int ganhou(tentativa *c){
    for (size_t i = 0; i < N_BOMBAS; i++)
    {
        bool colisaoHorizontal = (c->x < bombas[i].x + bombas[i].size) && (c->x + c->size > bombas[i].x);
        bool colisaoVertical = (c->y < bombas[i].y + bombas[i].size) && (c->y + c->size > bombas[i].y);
        
        if (colisaoHorizontal && colisaoVertical)
            return 1;
        
    }
    return 0;
}

int perdeu(){
    if (jogadorInicial == jogadorSelecionado)
    {
        for (size_t i = 0; i < 2; i++)
            if (pontosJogador[i] < 1)
                return i+1;
    }
    return 0;
}

void desenhar(int x, int y, int size, SDL_Renderer *render){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = size;
    rect.w = size;
    SDL_RenderDrawRect(render,&rect);
}

void aplicar(int *lugarSelecionado) {
    ++numeroDeTentativas;
    tentativas[numeroDeTentativas-1].x = lugarSelecionado[0];
    tentativas[numeroDeTentativas-1].y = lugarSelecionado[1];
    tentativas[numeroDeTentativas-1].size = lugarSelecionado[2]*20;
    tentativas[numeroDeTentativas-1].jogador = jogadorSelecionado;

    pontosJogador[jogadorSelecionado-1] -= lugarSelecionado[2];

    if(jogadorSelecionado == 2) jogadorSelecionado--;
    else jogadorSelecionado++;
}

int main()
{
    srand(time(NULL));
    SDL_Init;
    SDL_Window* janela = SDL_CreateWindow("Find Bomb", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    jogadorSelecionado = rand() % 2 == 0 ? 2 : 1 ;
    jogadorInicial = jogadorSelecionado;
    tentativas = malloc(100 * sizeof(tentativa));
    bombas = malloc(N_BOMBAS * sizeof(tentativa));
    int lugarSelecionado[3] = {0,0,1}; //0 e X, 1 e Y e 2 a area
    int x,y,s;

    for (size_t i = 0; i < N_BOMBAS; i++)
    {
        bombas[i].size = (rand() % 9) + 4;
        bombas[i].x = rand() % (WIDTH - bombas[i].size);
        bombas[i].y = rand() % (HEIGTH - bombas[i].size);
    }
    

    int rodando = 1;
    while (rodando)
    {
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
                rodando = 0;
            else if (evento.type == SDL_KEYDOWN)
            {
                switch (evento.key.keysym.sym)
                {
                    case SDLK_w:
                        if((lugarSelecionado[1] - VELOCIDADE) < 0){
                            if((lugarSelecionado[1] - 2) >= 0){
                                lugarSelecionado[1] -= 2;
                            }
                        }else{
                            lugarSelecionado[1] -= VELOCIDADE;
                        }
                        break;
                    case SDLK_s:
                        if((lugarSelecionado[1] + VELOCIDADE + lugarSelecionado[2] * 20) > HEIGTH){
                            if((lugarSelecionado[1] + 2 + lugarSelecionado[2] * 20) <= HEIGTH)
                                lugarSelecionado[1] += 2;
                        }else
                            lugarSelecionado[1] += VELOCIDADE;
                        break;
                    case SDLK_a:
                        if((lugarSelecionado[0] - VELOCIDADE) < 0){
                            if((lugarSelecionado[0] - 2) >= 0){
                                lugarSelecionado[0] -= 2;
                            }
                        }else{
                            lugarSelecionado[0] -= VELOCIDADE;
                        }
                        break;
                    case SDLK_d:
                        if((lugarSelecionado[0] + VELOCIDADE + lugarSelecionado[2] * 20) > WIDTH){
                            if((lugarSelecionado[0] + 2 + lugarSelecionado[2] * 20) <= WIDTH)
                            lugarSelecionado[0] += 2;
                        }else
                            lugarSelecionado[0] += VELOCIDADE;
                        break;
                    case SDLK_UP:
                        if (lugarSelecionado[2] <= MAX_SIZE_BLOCK && pontosJogador[jogadorSelecionado-1] > lugarSelecionado[2])
                            lugarSelecionado[2] += 1;
                        break;
                    case SDLK_DOWN:
                        if (lugarSelecionado[2] > 1)
                            lugarSelecionado[2] -= 1;
                        break;
                    case SDLK_SPACE:
                        aplicar(lugarSelecionado);
                        lugarSelecionado[2] = 1;
                        break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(render,0,0,0,255);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render,255,255,255,255);

        x = lugarSelecionado[0];
        y = lugarSelecionado[1];
        s = lugarSelecionado[2];

        int xFinal = x + s * 20;
        int yFinal = y + s * 20;

        // Desenhando as linhas do retângulo
        SDL_RenderDrawLine(render, x, y, xFinal, y);            // Canto superior esquerdo para canto superior direito
        SDL_RenderDrawLine(render, x, yFinal, xFinal, yFinal);  // Canto inferior esquerdo para canto inferior direito
        SDL_RenderDrawLine(render, x, y, x, yFinal);            // Canto superior esquerdo para canto inferior esquerdo
        SDL_RenderDrawLine(render, xFinal, y, xFinal, yFinal);  // Canto superior direito  para canto inferior direito

        SDL_SetRenderDrawColor(render,0,255,0,255);
        for (int i = 0; i < numeroDeTentativas; i++)
            desenhar(tentativas[i].x, tentativas[i].y, tentativas[i].size, render);

        if (ganhou(&tentativas[numeroDeTentativas-1]) || perdeu())
        {
            SDL_SetRenderDrawColor(render,255,0,0,255);
            for (size_t i = 0; i < N_BOMBAS; i++)
                desenhar(bombas[i].x,bombas[i].y,bombas[i].size, render);
            
            SDL_RenderPresent(render);

            if (perdeu() && !ganhou(&tentativas[numeroDeTentativas-1])){
                printf("jogador %d perdeu por falta de pontos \n", perdeu());
                printf("Prima tecla ESPACO para reiniciar o jogo\n");
                printf("----------------------------------------\n");
            }else{
                printf("bomba encontrada, jogador %d ganhou.\n", tentativas[numeroDeTentativas-1].jogador);
                printf("Prima tecla ESPACO para reiniciar o jogo\n");
                printf("----------------------------------------\n");
            }

            int pause = 1;
            while (pause)
            {
                while (SDL_PollEvent(&evento))
                {
                    if (evento.type == SDL_QUIT)
                        return 0;
                    else if(evento.type == SDL_KEYDOWN){
                        switch (evento.key.keysym.sym){
                            case SDLK_SPACE:
                                numeroDeTentativas = 0;
                                jogadorSelecionado = rand() % 2 == 0 ? 2 : 1 ;
                                jogadorInicial = jogadorSelecionado;
                                pontosJogador[0] = P_INCIAL;
                                pontosJogador[1] = P_INCIAL;
                                pause = 0;
                                break;
                            
                            default:
                                break;
                        }
                    }
                }
            }
        }else
            SDL_RenderPresent(render);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}
