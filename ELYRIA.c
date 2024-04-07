#include "sprites/sprites.h"
#include "Falas.h"
#include <conio.h> // Getch()
#include <stdio.h>
#include <string.h> // Strcpy() Memcpy()
#include <stdlib.h> // Rand() e Srand()
#include <windows.h> // System("cls") | Vapara() | 
#include <math.h> // Floor
#include <time.h> // TIME NULL e Tempo
#include <locale.h> // Caracteres Especiais

// STRUCTS
typedef struct {
    char nome[50];
    char desc[200];
    int atk;
    int hp;
    int esq;
    int def;
    int equipado;
    int elemento; 
    int key; // Se � um item chave ou n�o
    int tipo; // Arma, Armadura, Acess�rio
    }ITEM;

    typedef struct {
    char nome[50];
    int classe_id; // O que identifica a classe em s�
    char classe[20]; // Nome da classe
    int atk;
    int hp;
    int esq;
    int def;
    int nivel;
    char habs[2][20];
    char desc_habs[2][200];
    char sprite [18][18];
    }JOGADOR;

    typedef struct{ // HP, ATK, DEF, ESQ, BOSS, FRAQUEZA
    int hp;
    int atk;
    int def;
    int esq;
    int boss; // TRUE OU FALSE
    int fraqueza; //FRAQUEZA:  RAIO = 1 | GELO = 2 | FOGO = 3 | NULO = 0
    char nome[50];
    char sprite[18][18];
   }MONSTRO;

   typedef struct{ // sprite lim x, lim y, mons x, mons y, tam-lim, saida x , saida Y, inicio x, inicio y,  bloco inicial
      char sprite[40][60];
      int limites_de_x[200]; // Limites 
      int limites_de_y[200]; // Limites 
      int monstros_x[2];
      int monstros_y[2];
      int tam_lim; // Quantos Pontos "proibidos" Existem no Mapa
      int saida_x; // A linha da Saida
      int saida_y; // A coluna da Saida
      int inicio_x, inicio_y; // Linha e Coluna na qual o personagem come�a
      char bloco_inicial; // Cor do Bloco onde o Personagem come�a
   }MAPA; 



//  CORES:
#define N "\033[0m" // Neutro

#define A "\033[38;5;178m" // Amarelo
#define AC "\033[38;5;11m"  // Amarelo Claro
#define AE "\033[38;5;3m" // Amarelo Escuro
#define AZ "\033[38;5;4m" // Azul
#define AZC "\033[38;5;12m" // Azul Claro
#define AZE "\033[38;5;18m" // Azul Escuro
#define V "\033[38;5;2m" // Verde
#define VC "\033[38;5;10m" // Verde Claro
#define VE "\033[38;5;22m" // Verde Escuro
#define VR "\033[38;5;1m" // Vermelho
#define VRC "\033[38;5;9m" // Vermelho Claro
#define VRE "\033[38;5;88m" // Vermelho Escuro
#define VI "\033[38;5;5m" // Violeta
#define VIC "\033[38;5;13m" // Violeta Claro
#define VIE "\033[38;5;55m" // Violeta Escuro
#define L "\033[38;5;208m" // Laranja
#define LC "\033[38;5;214m" // Laranja Claro
#define LE "\033[38;5;166m" //  Laranja Escuro
#define B "\033[37m" // Branco
#define CZ "\033[38;5;7m" // Cinza
#define CZE "\033[38;5;8m" // Cinza Escuro 
#define R "\033[38;5;13m" // Rosa
#define RC "\033[38;5;218m" // Rosa Claro
#define RE "\033[38;5;162m" // Rosa Escuro
#define M "\033[38;5;94m" // Marrom
#define MC "\033[38;5;130m" // Marrom Claro (Meio alaranjado)
// Fundos Abaixo
#define FAC "\033[48;5;11m" // Fundo Amarelo Claro
#define FA "\033[48;5;178m" // Fundo Amarelo
#define FAE "\033[48;5;3m" // Fundo Amarelo Escuro
#define FAZC "\033[48;5;12m" // Fundo Azul Claro
#define FAZ "\033[48;5;4m" // Fundo Azul
#define FAZE "\033[48;5;18m" // Fundo Azul Escuro
#define FVC "\033[48;5;10m" // Fundo Verde Claro
#define FV "\033[48;5;2m" // Fundo Verde
#define FVE "\033[48;5;22m" // Fundo Verde Escuro
#define FVRC "\033[48;5;9m" // Fundo Vermelho Claro
#define FVR "\033[48;5;1m" // Fundo Vermelho
#define FVRE "\033[48;5;88m" // Fundo Vermelho Escuro
#define FVIC "\033[48;5;13m" // Fundo Violeta Claro
#define FVI "\033[48;5;5m" // Fundo Violeta
#define FVIE "\033[48;5;55m" // Fundo Violeta Escuro
#define FLC "\033[48;5;214m" // Fundo Laranja Claro
#define FL "\033[48;5;208m" // Fundo Laranja
#define FLE "\033[48;5;166m" // Fundo Laranja Escuro
#define FB "\033[48;5;15m" // Fundo Branco 
#define FCZ "\033[48;5;7m" // Fundo Cinza
#define FCZE "\033[48;5;242m" // Fundo Cinza Escuro 
#define FRC "\033[48;5;218m" // Fundo Rosa Claro
#define FR "\033[48;5;13m" // Fundo Rosa
#define FRE "\033[48;5;162m" // Fundo Rosa Escuro
#define FMC "\033[48;5;130m" // Fundo Marrom Claro (Meio alaranjado)
#define FM "\033[48;5;94m" // Fundo Marrom

/* GUIA DAS CORES
 A = Amarelo Claro
 B = Amarelo
 C = Amarelo Escuro
 D = Azul Claro
 E = Azul
 F = Azul Escuro
 G = Verde Claro
 H = Verde
 I = Verde Escuro
 J = Vermelho Claro
 K = Vermelho
 L = Vermelho Escuro
 M = Violeta Claro
 N = Violeta
 O = Violeta Escuro
 P = Laranja Claro
 Q = Laranja
 R = Laranja Escuro
 S = Branco 
 T = Cinza 
 U = Cinza Escuro 
 V = Rosa Claro 
 W = Rosa 
 X = Rosa Escuro 
 Y = Marrom Claro 
 Z = Marrom 
*/

// EQUIPAMENTO
#define ARMA 1 
#define PROT 2 //Prote��o
#define ACE 3 // Acess�rio
#define KEY 1 // Se ITEM CHAVE
#define NOT_KEY 0 
#define RAIO 1
#define GELO 2
#define FOGO 3
#define EQUIPED 1
#define NOT_EQUIPED 0
#define NULO 0

// MENU E OUTRAS DEFINI��ES
#define menu_elyria 1
#define sprite_vitoria 2
#define sprite_derrota 3
#define sprite_mapas 4
#define andar 5


#define cols_mapa 60
#define lins_mapa 40
int PJL= 18, PJC = 32+18; // Posi��o Jogador Linha & Posi��o Jogador Coluna (o 32 � o equivalente aos espa�os dados)


// TECLAS
#define Cima 119
#define Baixo 115
#define ENTER 13
#define ESC 27

// VALORES L�GICOS
#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

// VARI�VEIS GLOBAIS
int monstro_atual = 0;
int mapa_atual = 0;
int arma_atual = 0;
int numItens = 0;
int level_atual = 1;
char anterior;
int limite_menu = 14;
int jogo_iniciou = FALSE;
int pontuacao = 0;
int batalha = 0;
int final_bom = FALSE;
int hp_referencia = 0;
int hp_ref_monstro=0;

int aumento_hp =0;
int aumento_atk =0;
int aumento_def =0;
int aumento_esq =0;

char jogador_sprite_tras[18][18];

   // CRIA��O DE MONSTROS E ITENS
    // ITENS � DIFERENTE DE INVENT�RIO.
    // NOME | DESCRI��O | ATK | HP | ESQ | DEF | EQUIPADO | ELEMENTO | KEY | TIPO DO ITEM (ARMA = 1, ARMADURA (PROT) = 2, ACE = 3)
    ITEM itens[20] = {
        // GUERREIRO
        {"Claymore","Uma espada de Metal de Boa qualidade. � Perfurante e Resistente.", 10 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 3 /*DEF*/ , NOT_EQUIPED , RAIO , NOT_KEY, ARMA},
        {"Matadora de Drag�es","� uma espada antiga, mas muito confi�vel, � dito que sua lamina de mithril\n\tPerfurou o cora��o de v�rios drag�es.", 20 /*ATK*/, 5 /*HP*/, NULO/*ESQ*/, NULO /*DEF*/ , NOT_EQUIPED , FOGO , NOT_KEY, ARMA},
        {"Capacete de Ferro","Capacete feito de Ferro. Simples, mas resistente.", NULO /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 3 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"Armadura do Lobo","Armadura Negra, espinhosa e resistente, parece aumentar a for�a de quem a usa.", 3 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 8 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"Manoplas do Ca�ador","Manoplas de Couro e A�o, parecem conter algum tipo de feiti�o que melhora a precis�o.", 5 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 1 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        // MAGO
        {"Luva M�gica","Uma Luva leve com cristais adornados. Os cristais parecem facilitar o acumulo de mana.\n\tLan�ar feiti�os � certamente mais f�cil com ela.", 10 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, NULO /*DEF*/ , NOT_EQUIPED , RAIO , NOT_KEY, ARMA},
        {"Grim�rio 4 Trevos","Parece ser um Grim�rio que d� sorte ao seu usu�rio no lan�amento de m�gias e na esquiva.", 20 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 5 /*DEF*/ , NOT_EQUIPED , FOGO , NOT_KEY, ARMA},
        {"M�scara da Sorte","Parece trazer sorte a quem a usa.", 3 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 3 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"T�nica Revestida","T�nica de combate comumente usada por magos. � m�gicamente refor�ada.", NULO /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 10 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"Cal�ado Revestido","Cal�ados de combate comumente usado por magos. � m�gicamente refor�ado.", NULO /*ATK*/, 5 /*HP*/, NULO/*ESQ*/, 5 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        // VIGARISTA
        {"Adaga Venenosa","Infelizmente o veneno n�o parece ser muito forte.", 10 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, NULO /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, ARMA},
        {"Adaga de Mithril","Feita do Material mais resistente conhecido, al�m de ser muito leve.\n\tParece conter runas de m�gia de fogo.", 20 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 5 /*DEF*/ , NOT_EQUIPED , FOGO , NOT_KEY, ARMA},
        {"Botas do Passo Veloz","Essencial para qualquer a que se preze.", NULO /*ATK*/, NULO /*HP*/, 3 /*ESQ*/, 3 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"Coura�a Refor�ada","Coura�a de metal com refor�o m�gico.", NULO /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 8 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"Manopla do Javali","Vestes aparentemente simples, mas com not�vel energia espiritual que as torna muito mais resistentes.", NULO /*ATK*/, 5 /*HP*/, NULO/*ESQ*/, 5 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        // MONGE
        {"Soqueira Espinhosa","Uma Soqueira de Metal leve e resistente.", 10 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, NULO /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, ARMA},
        {"Bast�o do Rei Macaco","Um Bast�o de Madeira revestido de Mithril e com muita energia espiritual imbutida.", 20 /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 5 /*DEF*/ , NOT_EQUIPED , FOGO , NOT_KEY, ARMA},
        {"Botas da Agilidade","Botas com feiti�o de Agilidade.", NULO /*ATK*/, NULO /*HP*/, 3 /*ESQ*/, 3 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"Cintur�o da Resist�ncia","Cintur�o M�gico feito de Mithril.", NULO /*ATK*/, NULO /*HP*/, NULO/*ESQ*/, 10 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT},
        {"Vestes do Rei Macaco","Vestes aparentemente simples, mas com not�vel energia espiritual que as torna muito mais resistentes.", NULO /*ATK*/, 5 /*HP*/, NULO/*ESQ*/, 5 /*DEF*/ , NOT_EQUIPED , NULO , NOT_KEY, PROT}
        
        };

        ITEM acessorios[4]= {
            {"Anel da For�a","Aquele que o usa sente seus limites expandirem.",5,NULO,NULO,NULO,NOT_EQUIPED,NULO,NOT_KEY,ACE},
            {"Colar da Vitalidade","Aquele que o usa torna-se mais resistente.",NULO,5,NULO,NULO,NOT_EQUIPED,NULO,NOT_KEY,ACE},
            {"Pulseira do Discreto","Dificulta a rastreabilidade de quem o usa.",NULO,NULO,5,NULO,NOT_EQUIPED,NULO,NOT_KEY,ACE},
            {"Amuleto do Destemido","Prove uma �urea Protetora a quem o usa.",NULO,NULO,NULO,5,NOT_EQUIPED,NULO,NOT_KEY,ACE}
        };

        ITEM inventario[13];

        JOGADOR jogador = {"NULO",NULO,"NULO",NULO,NULO,NULO,NULO,NULO,{"NULO","NULO"},{"NULO","NULO"}, {" "}}; // Jogador Vazio.
        
        MONSTRO monstros[16] = {
            {50, 30, 7, 20, FALSE, FOGO, "ARANHA VENENOSA", {{""}}},
            {60, 30, 12, 20, FALSE, FOGO, "GOBLIN SEDENTO", {{""}}},
            {70, 35, 15, 32, FALSE, RAIO, "LIZARD", {{""}}},
            {80, 40, 20, 30, FALSE, FOGO, "OGRO", {{""}}},
            {150, 50, 35, 60, TRUE, FOGO,"LILITH, A RAINHA ARANHA", {{""}}}, // CHEF�O
            {150, 55, 30, 40,FALSE , GELO,"SLIME DE LAVA", {{""}}},
            {160 ,60 ,30 ,40 ,FALSE ,FOGO ,"DEM�NIO INFERIOR", {{""}}},
            {175 ,60 ,35 ,45 ,FALSE ,GELO ,"COLOSSO DE MAGMA", {{""}}},
            {200 ,70 ,40 ,40 ,FALSE ,GELO ,"DEM�NIO SUPERIOR", {{""}}},
            {275 ,70 ,70 ,60 ,TRUE ,RAIO ,"AZAZEL, O DEM�NIO DA PERDI��O", {{""}}}, // CHEF�O
            {150 ,80 ,40 ,50 ,FALSE ,GELO ,"SLIME", {{""}}},
            {130 ,80 ,35 ,55,FALSE ,RAIO ,"�GUIA", {{""}}},
            {190 ,85 ,45 ,55,FALSE ,RAIO ,"LOBO SUPERIOR", {{""}}},
            {260 ,90 ,45 ,50,FALSE ,FOGO ,"YETI", {{""}}},
            {380, 120, 70, 80, TRUE, FOGO, "DRAGNAR, O DRAG�O DA NEVASCA", {{""}}}, // CHEF�O
            {400, 135, 70, 80, TRUE, NULO, "ZEPHIR, O ARCANO NEFASTO", {{""}}} // CHEF�O
        };

        MAPA mapas[9]= {

            { // Mapa 0
            {" "},
            {39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}, // Posi��es X
            {41,40,40,39,38,37,36,35,35,34,33,32,32,31,30,30,29,28,27,27,26,25,24,24,23,22,22,21,20,19,19,18,17,17,16,15,14,14,13,13,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}, // Posi��es Y
            {26,12},// Monstros X
            {35,25}, // Monstros Y
            80, // Total de Posi��es Limite
            0, // Saida X
            16, // Saida Y
            39, // Inicio X
            43, // Inicio Y
            'B'
            },
            // N�O USAR AINDA KKKK


            { // Mapa 1
            {" "},
            {14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21}, // Posi��es X
            {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59}, // Posi��es Y
            {17,17},// Monstros X
            {20,51}, // Monstros Y
            118, // Total de Posi��es Limite
            17, // Saida X
            55, // Saida Y
            18, // Inicio X
            0, // Inicio Y
            'Y'
            },

            { // Mapa 2
            {" "},
            {33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}, // Posi��es X
            {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}, // Posi��es Y
            {34},// Monstros X
            {24}, // Monstros Y
            50, // Total de Posi��es Limite
            35, // Saida X
            24, // Saida Y
            34, // Inicio X
            0, // Inicio Y
            '|'
            },

            { // Mapa 3
            {" "},
            {17,17,17,17,17,17,17,17,17,17,17/**/,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,/**/17,17,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,/**/14,14,14,14,/*Intervalo*/20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20}, // Posi��es X
            {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,40,41,42,43,43,44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,43,44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59}, // Posi��es Y
            {20,18},// Monstros X
            {26,57}, // Monstros Y
            109, // Total de Posi��es Limite
            16, // Saida X
            59, // Saida Y
            18, // Inicio X
            0, // Inicio Y
            'R'
            },

            { // Mapa 4
            {" "},
            {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20}, // Posi��es X
            {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59}, // Posi��es Y
            {18,18},// Monstros X
            {19,48}, // Monstros Y
            120, // Total de Posi��es Limite
            18, // Saida X
            53, // Saida Y
            18, // Inicio X
            0, // Inicio Y
            'R'
            },

            { // Mapa 5
            {" "},
            {33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36}, // Posi��es X
            {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}, // Posi��es Y
            {34},// Monstros X
            {24}, // Monstros Y
            50, // Total de Posi��es Limite
            34, // Saida X
            24, // Saida Y
            34, // Inicio X
            0, // Inicio Y
            'Z'
            },

            {// Mapa 6
            {" "},
            {39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,14,13,12,12,1,10,10,9,9,8,7,7,6,5,5,4,3,3,2,1,1,0,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,15,14,13,13,12,12,11,10,10,9,8,8,7,6,6,5,4,4,3,3,2,1,1}, // Posi��es X
            {37,37,36,36,35,35,35,34,34,33,33,32,32,31,31,31,30,30,29,29,28,28,28,28,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,41,41,41,40,40,39,39,38,38,38,37,37,36,36,35,35,34,34,34,33,33,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58}, // Posi��es Y
            {17,7},// Monstros X
            {30,44}, // Monstros Y
            96, // Total de Posi��es Limite
            0, // Saida X
            59, // Saida Y
            39, // Inicio X
            39, // Inicio Y
            'R'
            },

            { // Mapa 7
            {" "},
            {39,38,37,36,35,34,33,32,31,30,39,38,37,36,35,34,33,32,31,30}, // Posi��es X
            {28,28,28,28,28,28,28,28,28,28,33,33,33,33,33,33,33,33,33,33}, // Posi��es Y
            {34,34},// Monstros X
            {31,30}, // Monstros Y
            20, // Total de Posi��es Limite
            31, // Saida X
            31, // Saida Y
            39, // Inicio X
            32, // Inicio Y
            'R'
            },

            {
            // Mapa 8
            {" "},
            {34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36}, // Posi��es X
            {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}, // Posi��es Y
            {35,0},// Monstros X
            {24,0}, // Monstros Y
            50, // Total de Posi��es Limite
            35, // Saida X
            24, // Saida Y
            35, // Inicio X
            0, // Inicio Y
            'Z'
            },      
};
        

// FUN��ES
void vapara(int linha, int coluna)
{
  COORD coord;
  coord.X = coluna;
  coord.Y = linha;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// FUN��ES DO MENU
void creditos(){
    int tecla;
    system("cls");
    printf("\t\t\t %sELYRIA%s\n\n",VR,N);
    printf("\t\t\tProduzido por: \n");
    printf("\t\t\tEduardo Marinho\n");
   // printf("\t\t\tN�fi Angelo\n");
    printf("\t\t\tJo�o Victor Amaral\n");
    printf("\t\t\tLuiz Henrique\n");
    // printf("\t\t\tPaulo Henrique\n");
    // printf("\t\t\tRafael Alexander\n");
    printf("\t\t\tLuiz Felipe\n\n\n\n");
    printf("Criado em 2023 como Atividade para Disciplina de Laborat�rio de Programa��o\n");
    printf("No primeiro per�odo de Ci�ncia da Computa��o UERN\n");
    printf("\n\n\nPressione %sENTER%s para Voltar ao MENU\n",V,N);

    while(1){
        if(kbhit() != 0){
            tecla = getch();
            if(tecla == 13){
                system("cls");
                break;
            }   
        }
    }
}




void imp(int lins , int cols, int sprite_a_usar){ // IMPRIMIR MENU / MAPAS / VIT�RIA E DERROTA
    int x, y; 
    char cache;
    for(x=0;x<lins;x++){
        if(sprite_a_usar <= 4){
            printf("\t\t\t\t");
        }

        for(y=0; y<cols ;y++){

            if(sprite_a_usar == 1){
                cache = ELYRIA[x][y];
            }
            else if(sprite_a_usar == 2){
                cache = VITORIA[x][y];
            }
            else if(sprite_a_usar == 3){
                cache = DERROTA[x][y];
            }
            else if(sprite_a_usar == 4){
                cache = mapas[mapa_atual].sprite[x][y];
            }
            else if(sprite_a_usar == 5 ){
                cache = anterior;
            }
            else if(sprite_a_usar == 6 ){
                cache = CLASSES[x][y];
            }
            else if(sprite_a_usar == 7){
                cache = jogador_sprite_tras[x][y];
    
            }

             if(cache == 'A'){
            printf("%s %s",FAC,N);
            }
            else if(cache == 'B'){
                printf("%s %s",FA,N);
            }
            else if(cache == 'C'){
                printf("%s %s",FAE,N);
            }
            else if(cache == 'D'){
                printf("%s %s",FAZC,N);
            }
            else if(cache == 'E'){
                printf("%s %s",FAZ,N);
            }
            else if(cache == 'F'){
                printf("%s %s",FAZE,N);
            }
            else if(cache == 'G'){
                printf("%s %s",FVC,N);
            }
            else if(cache == 'H'){
                printf("%s %s",FV,N);
            }
            else if(cache == 'I'){
                printf("%s %s",FVE,N);
            }
             else if(cache == 'L'){
                printf("%s %s",FVRE,N);
            }
            else if(cache == 'J'){
                printf("%s %s",FVRC,N);
            }
            else if(cache == 'K'){
                printf("%s %s",FVR,N);
            }
            else if(cache == 'K'){
                printf("%s %s",FVRE,N);
            }
            else if(cache == 'M'){
                printf("%s %s",FVIC,N);
            }
            else if(cache == 'N'){
                printf("%s %s",FVI,N);
            }
            else if(cache == 'O'){
                printf("%s %s",FVIE,N);
            }
            else if(cache == 'U'){
                printf("%s %s",FCZE,N);
            }
            else if(cache == 'P'){
                printf("%s %s",FLC,N);
            }
            else if(cache == 'Q'){
                printf("%s %s",FL,N);
            }
            else if(cache == 'R'){
                printf("%s %s",FLE,N);
            }
            else if(cache == 'S'){
                printf("%s %s",FB,N);
            }
            else if(cache == 'T'){
                printf("%s %s",FCZ,N);
            }
            else if(cache == 'V'){
                printf("%s %s",FRC,N);
            }
            else if(cache == 'W'){
                printf("%s %s",FR,N);
            }
            else if(cache == 'X'){
                printf("%s %s",FRE,N);
            }
            else if(cache == 'Y'){
                printf("%s %s",FMC,N);
            }
            else if(cache == 'Z'){
                printf("%s %s",FM,N);
            }
            else if(cache == '*'){
                printf("\033[48;5;234m %s",N);
            }
             else if(cache == '+'){
                printf("\033[48;5;245m %s",N);
            }
            else if(cache == '|'){
                printf("\033[48;5;247m %s",N);
            }
            else if(cache == ' '){
                printf(" ");
            }
            else if(cache == '-'){
                printf("\033[48;5;216m %s",N);
            }
            else if(cache == '1'){
                printf("\033[48;5;52m %s",N);
            }
            // Fim impress�o

            if(sprite_a_usar == 6 && y%15 == 0 && y != 60 && y > 14){
                printf("\t\t\t    ");
            }

        } // Fim FOR COLUNAS
            if(sprite_a_usar != 7){
                printf("\n");
            }
            else{
                printf("                                        ");// 40
                for(y=0; y<cols ;y++){
                        cache = monstros[monstro_atual].sprite[x][y];
                        if(cache == 'A'){
                        printf("%s %s",FAC,N);
                        }
                        else if(cache == 'B'){
                            printf("%s %s",FA,N);
                        }
                        else if(cache == 'C'){
                            printf("%s %s",FAE,N);
                        }
                        else if(cache == 'D'){
                            printf("%s %s",FAZC,N);
                        }
                        else if(cache == 'E'){
                            printf("%s %s",FAZ,N);
                        }
                        else if(cache == 'F'){
                            printf("%s %s",FAZE,N);
                        }
                        else if(cache == 'G'){
                            printf("%s %s",FVC,N);
                        }
                        else if(cache == 'H'){
                            printf("%s %s",FV,N);
                        }
                        else if(cache == 'I'){
                            printf("%s %s",FVE,N);
                        }
                        else if(cache == 'L'){
                            printf("%s %s",FVRE,N);
                        }
                        else if(cache == 'J'){
                            printf("%s %s",FVRC,N);
                        }
                        else if(cache == 'K'){
                            printf("%s %s",FVR,N);
                        }
                        else if(cache == 'K'){
                            printf("%s %s",FVRE,N);
                        }
                        else if(cache == 'M'){
                            printf("%s %s",FVIC,N);
                        }
                        else if(cache == 'N'){
                            printf("%s %s",FVI,N);
                        }
                        else if(cache == 'O'){
                            printf("%s %s",FVIE,N);
                        }
                        else if(cache == 'U'){
                            printf("%s %s",FCZE,N);
                        }
                        else if(cache == 'P'){
                            printf("%s %s",FLC,N);
                        }
                        else if(cache == 'Q'){
                            printf("%s %s",FL,N);
                        }
                        else if(cache == 'R'){
                            printf("%s %s",FLE,N);
                        }
                        else if(cache == 'S'){
                            printf("%s %s",FB,N);
                        }
                        else if(cache == 'T'){
                            printf("%s %s",FCZ,N);
                        }
                        else if(cache == 'V'){
                            printf("%s %s",FRC,N);
                        }
                        else if(cache == 'W'){
                            printf("%s %s",FR,N);
                        }
                        else if(cache == 'X'){
                            printf("%s %s",FRE,N);
                        }
                        else if(cache == 'Y'){
                            printf("%s %s",FMC,N);
                        }
                        else if(cache == 'Z'){
                            printf("%s %s",FM,N);
                        }
                        else if(cache == '*'){
                            printf("\033[48;5;234m %s",N);
                        }
                        else if(cache == '+'){
                            printf("\033[48;5;245m %s",N);
                        }
                        else if(cache == '|'){
                            printf("\033[48;5;247m %s",N);
                        }
                        else if(cache == ' '){
                            printf(" ");
                        }
                        else if(cache == '-'){
                            printf("\033[48;5;216m %s",N);
                        }
                        else if(cache == '1'){
                            printf("\033[48;5;52m %s",N);
                        }
                }
                printf("\n");
            }  
            
    } // Fim FOR LINHAS


    if(sprite_a_usar == menu_elyria){
        vapara(11,60);
        if(jogo_iniciou == TRUE){
            printf("CONTINUAR");
        }
        else{
            printf("NOVO JOGO");
        }
        vapara(12,60);
        printf("%sCOMO JOGAR%s",V,N);
        vapara(13,60);
        printf("CR�DITOS");
        vapara(14,60);
        if(strcmp(jogador.habs[0],"NULO") != 0){
            printf("%sHABILIDADES%s",AZ,N);
            vapara(15,60);
            limite_menu = 15;
        }
        printf("SAIR DO JOGO");

        vapara(30,0);
        printf("%sVers�o 1.1 (Beta)%s",CZE,N);
    }

  
   
}


 void como_jogar(){
    system("cls");
    printf("\t\t\t\t\t%s-------------%sCOMO JOGAR%s-------------%s",VR,V,VR,N);
    printf("\n\n\t1) Para se Mover use as teclas %sA S W D%s, Respectivamente: Esquerda, Baixo, Cima, Direita.\n",V,N);
    printf("\n\t2) Para Acessar o Inventario Pressione %sI%s (Durante o Jogo).\n",V,N);
    printf("\n\t3) Para Acessar o Menu Pressione %sM%s (Durante o Jogo).\n",V,N );
    printf("\n\t4) H� 3 formas de finalizar o jogo: a) Perdendo um combate | b) Chegando ao Final | C) Finalizando manualmente no MENU\n");
    printf("\n\t5) Os %sPONTOS%s s�o mostrados ao final do jogo e levam em conta suas %sVit�rias%s em combate e a %sRapidez%s com que terminou.\n",V,N,VR,N,VR,N);
    printf("\n\t6) O Combate ocorre por turnos, onde o jogador � o primeiro a agir e o advers�rio responde logo em seguida\n");
    printf("\n\t7) Para verificar suas Habilidades Pressione M (Durante o jogo) e depois selecione 'HABILIDADES'\n");
    printf("\n\n\nPara Prosseguir pressione %sENTER%s",V,N);
    int tecla;
    while(1){
        if(kbhit() != 0){
            tecla = getch();
            if(tecla == 13){
                system("cls");
                break;
            }   
        }
    }

}

void escolha_personagem(){
    Sleep(300);
    printf("\t\t\t%s======================================= %s ESCOLHA A SUA CLASSE %s=======================================%s\n\n",L,VC,L,N);
    int opc;
    imp(16,4*16,6);

        printf("\n[ GUERREIRO ] - 1"); printf("\t\t\t[ MAGO ] - 2"); printf("\t\t\t\t[ VIGARISTA ] - 3"); printf("\t\t\t[ MONGE ] - 4\n");
    // Atributos
    printf("Vida: 130 %s(+5)%s",VR,N); printf("\t\t\t\tVida: 100 %s(+2)%s",VR,N); printf("\t\t\t\tVida: 100 %s(+3)%s",VR,N); printf("\t\t\t\tVida: 115 %s(+5)%s\n",VR,N);
    printf("Ataque: 22 %s(+3)%s",A,N); printf("\t\t\t\tAtaque: 25 %s(+6)%s",A,N); printf("\t\t\t\tAtaque: 28 %s(+5)%s",A,N); printf("\t\t\t\tAtaque: 25 %s(+3)%s\n",A,N);
    printf("Defesa: 12 %s(+4)%s",V,N); printf("\t\t\t\tDefesa: 10 %s(+2)%s",V,N); printf("\t\t\t\tDefesa: 10 %s(+2)%s",V,N); printf("\t\t\t\tDefesa: 10 %s(+4)%s\n",V,N);
    printf("Esquiva: 4 %s(+2)%s",AZ,N); printf("\t\t\t\tEsquiva: 5 %s(+2)%s",AZ,N); printf("\t\t\t\tEsquiva: 7 %s(+3)%s",AZ,N); printf("\t\t\t\tEsquiva: 4 %s(+2)%s\n",AZ,N);
    printf("Habilidade 1: Golpe Demolidor"); printf("\t\tHabilidade 1: Bombardeio M�gico"); printf("\t\tHabilidade 1: Eclipse Sombrio"); printf("\t\tHabilidade 1: Punho de L�tus\n");
    printf("Habilidade 2: F�ria Berserker"); printf("\t\tHabilidade 2: L�mina M�gica");     printf("\t\tHabilidade 2: L�mina Umbra");    printf("\t\tHabilidade 2: Golpe do Drag�o\n");
    printf("\n\nSelecione uma Classe: ");
    scanf("%d",&opc);

    switch(opc){
        case 1:
            jogador.classe_id =1; 
            strcpy(jogador.classe, "Guerreiro");
            jogador.atk = 22;
            jogador.def = 12 ;
            jogador.esq = 4;
            jogador.hp= 130;
            jogador.nivel = 1;
            strcpy(jogador.habs[0], "Golpe Demolidor");
            strcpy(jogador.habs[1], "F�ria Berserker");
            strcpy(jogador.desc_habs[0], "1.2 vezes o Dano Base, mas se o seu HP chegar a 30% aumenta para 1.5");
            strcpy(jogador.desc_habs[1], "Receba 20% do Dano Base em Dano Auto-inflingido e desfira um golpe de 200% ");
            memcpy(jogador_sprite_tras, GUERREIRO, sizeof(GUERREIRO));
            memcpy(jogador.sprite, GUERREIRO_FRENTE, sizeof(GUERREIRO_FRENTE));

            hp_referencia = 130;
            aumento_hp = 5;
            aumento_atk = 3;
            aumento_def = 4;
            aumento_esq = 2;
        break;

        case 2: 
            jogador.classe_id = 2; 
            strcpy(jogador.classe, "Mago");
            jogador.atk  = 25;
            jogador.def = 10;
            jogador.esq = 5;
            jogador.hp  = 100;
            jogador.nivel = 1;
            strcpy(jogador.habs[0], "Bombardeio M�gico");
            strcpy(jogador.habs[1], "L�mina M�gica");
            strcpy(jogador.desc_habs[0], "5 m�sseis m�gicos s�o lan�ados, cada um d� entre 10% a 40% do seu Dano Base");
            strcpy(jogador.desc_habs[1], "1.2 vezes o dano base + 10 a (10 + N�vel)");
            memcpy(jogador_sprite_tras, MAGO, sizeof(MAGO));
            memcpy(jogador.sprite, MAGO_FRENTE, sizeof(MAGO_FRENTE));


            hp_referencia = 100;
            aumento_hp = 2;
            aumento_atk = 6;
            aumento_def= 2;
            aumento_esq= 2;

        break;

        case 3: 
            jogador.classe_id = 3; 
            strcpy(jogador.classe, "Vigarista");
            jogador.atk  = 28;
            jogador.def= 10;
            jogador.esq = 7 ;
            jogador.hp = 100 ;
            jogador.nivel = 1;
            strcpy(jogador.habs[0], "Eclipse Sombrio");
            strcpy(jogador.habs[1], "L�mina Umbra");
            strcpy(jogador.desc_habs[0], "1.75 vezes o Dano base, caso passe no teste de Esquiva, do contr�rio � o Dano Base");
            strcpy(jogador.desc_habs[1], "Dano Base + 50% da defesa do Inimigo");
            memcpy(jogador_sprite_tras, VIGARISTA, sizeof(VIGARISTA));
            memcpy(jogador.sprite, VIGARISTA_FRENTE, sizeof(VIGARISTA_FRENTE));

            hp_referencia = 100;
            aumento_hp = 3;
            aumento_atk = 5;
            aumento_def = 2;
            aumento_esq = 3;

        break;

        case 4: 
            jogador.classe_id = 4; 
            strcpy(jogador.classe, "Monge");
            jogador.atk = 25;
            jogador.def = 10;
            jogador.esq =4;
            jogador.hp = 115;
            jogador.nivel = 1;
            strcpy(jogador.habs[0], "Punho de L�tus");
            strcpy(jogador.habs[1], "Golpe do Drag�o");
            strcpy(jogador.desc_habs[0], "Dano Base*1.2 + 3% do Hp Atual do inimigo. Se estiver com 30% do HP, Recebe Bonus de 20%");
            strcpy(jogador.desc_habs[1], "Dano Base*1.1 + (0 a 10)% do HP Atual do Inimigo");
            memcpy(jogador_sprite_tras, MONGE, sizeof(MONGE));
            memcpy(jogador.sprite, MONGE_FRENTE, sizeof(MONGE_FRENTE));


            hp_referencia = 115;
            aumento_hp= 5;
            aumento_atk = 3;
            aumento_def = 4;
            aumento_esq = 2;

        break;
    }

    
    system("cls");
    printf("\n\n\n\n\n\t\t\t\tDigite o seu Nome, Bravo Aventureiro: ");
    scanf("%s",jogador.nome);
    printf("\n\t\t\t\tBem Vindo %s, hora de come�ar a sua Hist�ria",jogador.nome); 
    Sleep(2000);
    system("cls");

    
    
}   
void mostrar_habilidades(){
    int tecla;
    system("cls");
    printf("=============== HABILIDADES DO %s ===============================\n", strupr(jogador.classe));

    printf("\nHabilidade 1: %s%s%s\n",AE,jogador.habs[0],N);
    printf("Calculo do Dano: %s\n\n",jogador.desc_habs[0]);

    printf("Habilidade 2: %s%s%s\n",AE,jogador.habs[1],N);
    printf("Calculo do Dano: %s\n",jogador.desc_habs[1]);
    
    printf("\n\n\n%sPressione %sENTER %spara voltar%s",CZ,VR,CZ,N);
    while(1){
        tecla = getch();
        if(tecla == 13){
            system("cls");
            break;
        }
    }

}

int digitado(int tecla, int *linha_m){
    if((*linha_m == 11 && (tecla == 'w' || tecla == 'W')) || (*linha_m == limite_menu && (tecla == 's' || tecla == 'S'))){
        // Invalido
    }
    else{
        // Valido
        if(tecla == 'w' || tecla == 'W'){
            *linha_m -=1;
            return FALSE;
        }
        else if(tecla == 's' || tecla == 'S'){
            *linha_m +=1;
            return FALSE;
        }
    }

    if(tecla == ENTER){
        return TRUE;
    }
    else{
        return FALSE;
    }

}

void ativar_menu(){

    system("cls");
    int linha_menu= 11; // 7
    int tecla=0,input = FALSE;
    imp(10,68,menu_elyria);
    vapara(linha_menu,58); printf("%s\033[1m%c%s",VR,187,N); // 7 espa�os
    while(1){
        if(kbhit() != 0){

            tecla = getch();

            vapara(linha_menu,58); printf(" "); // 8 espa�os

            input = (digitado(tecla,&linha_menu));

            vapara(linha_menu,58); printf("%s\033[1m%c%s",VR,187,N); // 7 espa�os

            if(input == TRUE){
                if(linha_menu == 11){  // Continuar ou Novo Jogo
                    system("cls");
                    if(jogo_iniciou == FALSE){
                        jogo_iniciou = TRUE;
                        escolha_personagem();
                    }
                    break;
                }

                else if(linha_menu == 12){ // Como Jogar
                    como_jogar();
                    imp(10,68,menu_elyria);
                    linha_menu = 11;
                    vapara(linha_menu,58); printf("%s\033[1m%c%s",VR,187,N);
                    tecla = 0;
                }

                else if(linha_menu == 13){  // CREDITOS
                    creditos();
                    imp(10,68,menu_elyria);
                    linha_menu = 11;
                    vapara(linha_menu,58); printf("%s\033[1m%c%s",VR,187,N);
                    tecla = 0;
                }
                else if(linha_menu == 14 && strcmp(jogador.habs[0],"NULO") != 0 ){
                    mostrar_habilidades();
                    imp(10,68,menu_elyria);
                    linha_menu = 11;
                    vapara(linha_menu,58); printf("%s\033[1m%c%s",VR,187,N);
                    tecla = 0;
                }
                else if(linha_menu == 14 || linha_menu == 15){
                    system("cls");
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n   \t\t\t\t\t\t\tOBRIGADO POR JOGAR E AT� A PR�XIMA\n\n\n\n\n\n\n\n\n\n\n");
                    Sleep(2000);
                    exit(0);
                }
            }

            if(tecla == 27){ //SAIR COM ESC
                system("cls");
                break;
            }
            
        }

    }

}

// FUN��ES DO MAPA
int contar_vetor_num(int *vetor[]){ // N�o pode colocar '0' nos limites de x e y
   int x; 
   for(x=0;vetor[x]!=0;x++){
   }
   return x;
}

int testar_se_pode(int prox_PJL, int prox_PJC ){
    int cont;
   for(cont=0; cont < mapas[mapa_atual].tam_lim; cont++){
            if(PJL+prox_PJL == mapas[mapa_atual].limites_de_x[cont] && (PJC-32)+prox_PJC == mapas[mapa_atual].limites_de_y[cont]){
               return FALSE;
            }
      }

    return TRUE;

}



// FUN��ES DO INVENT�RIO

void mostrar_inventario() {
    int i;
     for(i = 0; i < numItens; i++){
            printf("    %d.  %s\n", i+1, inventario[i].nome); // 4 espa�os
    }
}


void ativar_inventario(){
    int linha_atual = 7;// O cursor ">"
    int index =0; 
    int sair_menu =0;
    int mov=0; // Se movimentou o Cursor
    int selecionado =0; // Se selecionou algo valido
    int tecla=0;

   //TELA DE INVENT�RIO
   do{
    system("cls");
    printf("\n            |=== MENU GERAL DO JOGADOR ===|\n");
    printf("\n === %sSTATUS%s =======================================================================",VR,N);
    printf("\n  => NOME: %s\t\t => HP:  %d\t => ATK: %d", jogador.nome, jogador.hp, jogador.atk);
    printf("\n  => CLASSE: %s\t\t => DEF: %d\t => ESQ: %d", jogador.classe, jogador.def, jogador.esq);

    printf("\n === %sITENS%s ========================================================================\n",V,N);
        mostrar_inventario();
        printf("\n");

    printf(" === %sITEM INFO%s ====================================================================\n",AZ,N);
        if(selecionado == 1){
            index = linha_atual-7;
            printf("\t%s%s%s\n",A,inventario[index].nome,N);
            if(inventario[index].atk != 0){
                printf("\tBonus de Ataque: %d\n",inventario[index].atk);
            }
            if(inventario[index].def != 0){
                printf("\tBonus de Defesa: %d\n",inventario[index].def);
            }
            if(inventario[index].esq != 0){
                printf("\tBonus de Esquiva: %d\n",inventario[index].esq);
            }
            if(inventario[index].hp != 0){
                printf("\tBonus de Vida: %d\n",inventario[index].hp);
            }
            if(inventario[index].equipado == TRUE){
                printf("\tSitu��o: %sEquipado%s\n",V,N);
            }
            else{
                printf("\tSitua��o: %sDesequipado%s\n",A,N);
            }
            if(inventario[index].elemento == 1){
                printf("\tElemento: %sRAIO%s \n",VI,N);
            }
            else if(inventario[index].elemento == 2){
                printf("\tElemento: %sGELO%s \n",AZ,N);
            }
            else if(inventario[index].elemento == 3){
                printf("\tElemento: %sFOGO%s \n",VR,N);
            }
            printf("\tDescri��o: %s\n",inventario[index].desc);
        }

    printf("\n === %sAC�ES%s =========================================================================",L,N);
    if(selecionado == 1){
        if(inventario[index].equipado == NOT_EQUIPED){
            printf("\n\t%sPRESSIONE %sE %sPARA EQUIPAR%s",AZ,VR,AZ,N);
        }
        if(inventario[index].equipado == EQUIPED){
            printf("\n\t%sPRESSIONE %sE %sPARA DESEQUIPAR%s",AZ,VR,AZ,N);
        }
    }
    printf("\n  => PRESSIONE %sENTER%s NO ITEM QUE DESEJA SABER MAIS SOBRE                           ",VR,N);
    printf("\n  => USE %sW%s e %sS%s PARA MOVER ENTRE OS ITENS DO INVENT�RIO.                         ",AZ,N,AZ,N);
    printf("\n  => PARA SAIR PRESSIONE %sESC%s                         \n",A,N);
    vapara(linha_atual,3);
    printf("%s>%s",V,N);
    selecionado =0;
    while(1){
        if(kbhit()!=0){
        tecla = getch();
        
            vapara(linha_atual,3);
            printf(" "); // Inicialmente reseta
            if((tecla == 'W' || tecla == 'w') && linha_atual >7){
                linha_atual--;
                index = linha_atual-7;
                vapara(linha_atual,3);
                mov=1;
            }
            else if( (tecla == 's' || tecla == 'S') && linha_atual < 6+numItens){
                linha_atual++;
                index = linha_atual-7;
                vapara(linha_atual,3);
                mov=1;
            }
            else if(tecla == 27){
                sair_menu = 1;
                system("cls");
                break;
            }
            else if(tecla == 13){
                selecionado =1;
                break;
            }
            else if(tecla == 'e' || tecla =='E'){
                if(inventario[index].equipado == NOT_EQUIPED){
                    inventario[index].equipado = EQUIPED;
                    jogador.hp += inventario[index].hp;
                    jogador.atk += inventario[index].atk;
                    jogador.def += inventario[index].def;
                    jogador.esq += inventario[index].esq;

                    int temp; 
                    for(temp =0; temp < numItens;temp++){
                        if((inventario[temp].equipado == TRUE && inventario[temp].tipo == ARMA) && (strcmp(inventario[temp].nome,inventario[index].nome) != 0) && inventario[index].tipo == ARMA){
                            inventario[temp].equipado = FALSE;
                            jogador.hp -= inventario[temp].hp;
                            jogador.atk -= inventario[temp].atk;
                            jogador.def -= inventario[temp].def;
                            jogador.esq -= inventario[temp].esq;
                        }
                    }

                    break;
                }
                else{
                    inventario[index].equipado = NOT_EQUIPED;
                    jogador.hp -= inventario[index].hp;
                    jogador.atk -= inventario[index].atk;
                    jogador.def -= inventario[index].def;
                    jogador.esq -= inventario[index].esq;
                    break;
                }
            }
            if(sair_menu == 0 && tecla !=13){
                if(mov == 0){
                    vapara(linha_atual,3);
                }
                printf("%s>%s",V,N);
            }
            mov =0;
    }
    }
    
}while(sair_menu == 0);
system("cls");
}

// FUN��ES DE DERROTA E DE VIT�RIA

void Vitoria( int tempo_decorrido, int pontuacao){
        //Sleep(1000);
        system("cls");
        int tecla;
        pontuacao += 3000 + ((300 - tempo_decorrido)*4);
        imp(16,16,sprite_vitoria);
        printf("\t\t\t%sPARAB�NS,VOC� COMPLETOU ELYRIA !!%s\n",A,N);
        printf("\t\t\t%sJogador:%s %s\n",VC,N,jogador.nome);
        printf("\t\t\t%sPontua��o:%s %d\n",VRE,N,pontuacao);
        printf("\t\t\t%sTempo de Jogo:%s %d minutos e %.0f segundos\n",AZC,N,tempo_decorrido/60, 60 * ((tempo_decorrido*1.0 /(60*1.0)) - (tempo_decorrido/60)));
        printf("\t\t\t%sObrigado por Jogar!!%s\n",AC,N);
        printf("\n\n\n%sPressione %sENTER%s para fechar o jogo%s",CZ,VR,CZ,N);

        while(1){
            tecla = getch();
            if(tecla == 13){
                system("cls");
                exit(0);
            }
        }
    }

void Derrota( int tempo_decorrido, int pontuacao){
        //Sleep(1000);
        system("cls");
        int tecla;
        imp(25,31,sprite_derrota);
        printf("\t\t\tInfelizmente voc� morreu em batalha ...\n");
        printf("\t\t\t%sJogador:%s %s\n",VC,N,jogador.nome);
        printf("\t\t\t%sPontua��o:%s %d\n",VRE,N,pontuacao);
        printf("\t\t\t%sTempo de Jogo:%s %d minutos e %.0f segundos\n",AZC,N,tempo_decorrido/60, 60 * ((tempo_decorrido*1.0 /(60*1.0)) - (tempo_decorrido/60)));
        printf("\t\t\t%sObrigado por Jogar e mais sorte na pr�xima !!%s\n",AC,N);
        printf("\n\n\n%sPressione %sENTER %spara fechar o jogo%s",CZ,VR,CZ,N);

        while(1){
            tecla = getch();
            if(tecla == 13){
                system("cls");
                exit(0);
            }
        }
    }
// FUN��ES DO COMBATE 


void combate_vitorioso(){ 
    int mult = 1;
    if(monstro_atual == 14){
        mult = 5;
        level_atual+=4;
    }

    jogador.atk += mult * aumento_atk;
    jogador.hp  += mult * aumento_hp;
    jogador.def += mult * aumento_def;
    jogador.esq += mult * aumento_esq;
    level_atual ++;
    printf("===========================================================================================================");
    printf("\n");
    printf("\t%sVIT�RIA%s: Voc� Derrotou %s\n\n",V,N,strupr(monstros[monstro_atual].nome));
    printf("\tVoc� aumentou de n�vel, N�vel Atual: %d\n",level_atual);
    printf("\tSeus atributos aumentaram !!\n");
    printf("\tVida (%s+%d%s)\n",VR,aumento_hp*mult,N);
    printf("\tAtaque (%s+%d%s)\n",A,aumento_atk*mult,N);
    printf("\tDefesa (%s+%d%s)\n",V,aumento_def*mult,N);
    printf("\tEsquiva (%s+%d%s)\n\n",AZ,aumento_esq*mult,N);
    int item = 0;

    if(monstro_atual != 4 && monstro_atual != 9 && monstro_atual != 14){
        pontuacao += 100 + (10*monstro_atual);
    }else{
        pontuacao += 300 + (20*monstro_atual); 
    }

// Item 1 Arma 1
    if(monstro_atual == 3){
        if(jogador.classe_id == 1){
            inventario[numItens] = itens[0];
            
        }

        if(jogador.classe_id == 2){
            inventario[numItens] = itens[5];
                    }

        if(jogador.classe_id == 3){
            inventario[numItens] = itens[10];
            
        }

        if(jogador.classe_id == 4){
            inventario[numItens] = itens[15];
            
        }
        item = 1;
    }
// Item 2 Armadura 1
    else if(monstro_atual == 5){
        if(jogador.classe_id == 1){
            inventario[numItens] = itens[1];
                    }

        if(jogador.classe_id == 2){
            inventario[numItens] = itens[6];
                    }

        if(jogador.classe_id == 3){
            inventario[numItens] = itens[11];
            
        }

        if(jogador.classe_id == 4){
            inventario[numItens] = itens[16];
            
        }
        item = 1;
    }
// Item 3 Armadura 2
    else if(monstro_atual == 8){
        if(jogador.classe_id == 1){
            inventario[numItens] = itens[2];
                    }

        if(jogador.classe_id == 2){
            inventario[numItens] = itens[7];
                    }

        if(jogador.classe_id == 3){
            inventario[numItens] = itens[12];
            
        }

        if(jogador.classe_id == 4){
            inventario[numItens] = itens[17];
            
        }
        item = 1;
    }
// Item 4 Arma 2
    else if(monstro_atual == 10){
        if(jogador.classe_id == 1){
            inventario[numItens] = itens[3];
                    }

        if(jogador.classe_id == 2){
            inventario[numItens] = itens[8];
                    }

        if(jogador.classe_id == 3){
            inventario[numItens] = itens[13];
            
        }

        if(jogador.classe_id == 4){
            inventario[numItens] = itens[18];
            
        }
        item = 1;
    }
// Item 5 Armadura 3
    if(monstro_atual == 12){
        if(jogador.classe_id == 1){
            inventario[numItens] = itens[4];
            
        }

        if(jogador.classe_id == 2){
            inventario[numItens] = itens[9];
                    }

        if(jogador.classe_id == 3){
            inventario[numItens] = itens[14];
        }

        if(jogador.classe_id == 4){
            inventario[numItens] = itens[19];
        }
        item = 1;
        
    }

    if(item == 1){
        printf("\tVoc� conseguiu saquear um(a) %s%s%s do(a) %s%s%s\n",A,inventario[numItens].nome,N,VRC,monstros[monstro_atual].nome,N);
        numItens++;
    }

    if(monstro_atual != 14){
        while(1) // TESTE PARA ACESS�RIO 30% DE CHANCE
        {
            int chance, index; 
            chance = 1+ (rand() % 10);
            if(chance <= 1){
                while(1){
                    index = rand() % 4;
                    int x, equip = 0, tem=0;
                    // Teste para saber se j� tem o item
                    for (x=0;x<numItens;x++){
                        if(strcmp(inventario[x].nome,acessorios[index].nome) == 0){
                            equip ++;
                            tem=1;
                            break;
                        }
                    }

                    if(equip == 4){ // J� tem todos os itens
                        break;
                    }

                    if(tem == 0){ // N�o tem o item
                            inventario[numItens] = acessorios[index];
                            printf("\tParab�ns voc� ganhou o item %s%s%s, verifique o invent�rio para mais informa��es.\n",V,inventario[numItens].nome,N);
                            numItens++;
                            break;
                    }
                    
                }
            }
            break;
        }
    }
    int tecla;
    printf("\n\n\n%sPara Prosseguir pressione %sENTER%s\n",CZ,VR,N);
    while(1){
        tecla = getch();
        if(tecla == 13){
            break;
        }
        else{
            // Nothing Ma Brother
        }
    }

    system("cls");
}


int calcularDano(int opc,int efeito){
    double dano;
    int fraqueza = monstros[monstro_atual].fraqueza;
//STRCMP | 0 = IGUAIS
    switch(jogador.classe_id){
// GUERREIRO
         case 1:
         if(opc == 1){
            if(jogador.hp <= (hp_referencia * 0.30)){
                dano = jogador.atk * 1.5;
            }else{
                dano = jogador.atk * 1.2;
            }
         }
         else if(opc ==2){
            jogador.hp -= jogador.atk * 0.2;
            dano =  jogador.atk*2;
         }
        break;
// MAGO
        case 2:
            if(opc == 1){
                dano =  ( jogador.atk *  ( ( rand() % 4 ) + 1 ) )/10 ; // 0 a 4
                dano += ( jogador.atk *  ( ( rand() % 4 ) + 1 ) )/10 ;
                dano += ( jogador.atk *  ( ( rand() % 4 ) + 1 ) )/10 ;
                dano += ( jogador.atk *  ( ( rand() % 4 ) + 1 ) )/10 ;
                dano += ( jogador.atk *  ( ( rand() % 4 ) + 1 ) )/10 ;    
            }

            else if(opc ==2){
                dano = jogador.atk * 1.2 + (rand() % (10 + jogador.nivel) + 1 );
            }

            if(monstro_atual == 14){
                dano += jogador.atk / 2;
            }

        break;
// VIGARISTA
        case 3:
              if(opc == 1){
                if(rand () % (jogador.esq) >= monstros[monstro_atual].esq){
                    dano = jogador.atk * 1.75;

                }
                else{
                    dano = jogador.atk;
                }
            }

            else if(opc ==2){
                dano = jogador.atk + (monstros[monstro_atual].def/2);
            }
        break;
// MONGE 
        case 4:
             if(opc == 1){
                dano =  jogador.atk*1.2 + (monstros[monstro_atual].hp * 0.03);  
                if(monstros[monstro_atual].hp <= hp_ref_monstro * 0.3){
                    dano += jogador.atk * 0.2;
                }
            }
            else if(opc ==2){
                dano =  jogador.atk*1.1 + (monstros[monstro_atual].hp * 10 )/ 100 ;
            }
        break;
    }

    if(efeito == fraqueza){
        dano = dano *1.25;
    }

    dano = floor(dano);

    return dano;
}

void ativar_combate(){
    int opc,vez=0;
    double dano=0.0;
    // Batalha = 1 ==> Vit�ria. | Batalha = 2 ==> Derrota | Batalha = 3 ==> Fugiu
    int vez_inimigo = FALSE;
    int c;
    int uso_fuga = FALSE;
    int esquiva = FALSE;
    int hp_base = jogador.hp;
    batalha = 0;

do {
    system("cls");
    //BARRA DE STATUS:
    printf("%s LV %d\t\t\t\t\t\t\t%s #\n\n",jogador.nome,level_atual,monstros[monstro_atual].nome);
    printf("HP: %d \t\t\t\t\t\t\tHP: %d\n\n",jogador.hp,monstros[monstro_atual].hp);
    //SPRITES:
        imp(18,18,7);   
    printf("\n==============================================================================================================================\n");
//PARTE DO JOGADOR
        if(vez%2 == 0){
        //HAB 1 OU HAB 2
            if(dano != 0.0){ 
                printf("Voce acertou o(a) %s e causou %.0lf de DANO no %s\n",jogador.habs[opc-1],dano,monstros[monstro_atual].nome);
                dano =0.0;
                vez++;
            }
        //FUGA
            else if(uso_fuga == TRUE){
                system("cls");
                printf("\nCom receio do pior, voce p�e o rabo entre as pernas e se coloca a fugir. Para a sua sorte o monstro n�o conseguiu lhe alcan�ar.");
                printf("\nQuando o monstro come�a a dormir voc� aproveita e passa pelo local sem que ele perceba.");
                uso_fuga = FALSE;
                printf("\nPressione ENTER para continuar.");
                do{
                    c = getch();
                }while(c!=13);
                batalha = 3;
                break;
                
            }

            else if(uso_fuga == 3){//Tentou fugir e deu errado
                printf("Voc� tenta fugir, mas infelizmente o monstro foi mais r�pido e lhe impediu.");
                uso_fuga = FALSE;
                vez++;
            }
        }
// PARTE DO MONSTRO 
                if(vez_inimigo == TRUE){
                    if(esquiva == TRUE){
                        printf("O(A) %s ia lhe acertar, entretando voce conseguiu ser mais rapido que ele e desviou do ataque",monstros[monstro_atual].nome);
                    }
                    else{ 
                        printf("O(A) %s lhe acerta um golpe e causa %.0lf de DANO",monstros[monstro_atual].nome,dano);
                    }
                    dano =0; //Resetar.
                    vez_inimigo=FALSE; //Resetar
                    vez++; //Passar a vez para o jogador
                }
            
            printf("\n==============================================================================================================================\n");
//VEZ DO JOGADOR:
                if (vez%2 == 0){ 
                    printf("O que voce deseja fazer?\n");
                    printf("\t1- %s\t 2- %s\t",jogador.habs[0],jogador.habs[1]);
                    if(monstro_atual == 4 || monstro_atual == 9 || monstro_atual == 14 || monstro_atual == 15){

                    }
                    else{
                        printf("3- Tentar Fugir");
                    }
                    printf("\nSua Escolha => ");
                    scanf("%d",&opc);
                      
                    dano =0;
                // Preciso do index da arma em uso
        
                    switch(opc){
                        case 1:
                            dano =calcularDano(opc,inventario[arma_atual].elemento); //OBS:Adicionar efeito de arma
                            dano = dano - monstros[monstro_atual].def;
                            if(dano <0){
                                //Nada, o dano foi negativo, se somar aumenta o hp do inimigo
                            }
                            else{
                                monstros[monstro_atual].hp -= dano;
                            }
                            printf("Dano: %0.lf | Opc: %d | vez: %d",dano,opc,vez);
                        break;

                        case 2:
                            dano =calcularDano(opc,inventario[arma_atual].elemento); //OBS:Adicionar efeito de arma
                            dano = dano - monstros[monstro_atual].def;

                            if(dano <0){
                                //Nada, o dano foi negativo, se somar aumenta o hp do inimigo
                            }
                            else{
                                monstros[monstro_atual].hp -= dano;
                            }

                        break;

                        case 3:
                            if(jogador.esq + (rand()% 15)+1 > monstros[monstro_atual].esq){
                                uso_fuga = TRUE;
                            }
                            else{
                                uso_fuga = 3;
                            }
                        break;

                        default:
                        break;
                    }  
                }

//VEZ DO MONSTRO
            else{
                printf("\nAgora eh a vez do inimigo.");
                printf("\nPressione ENTER para prosseguir.");
                vez_inimigo=TRUE;
                do{
                    c = getch();
                }while(c!=13);

            }
                
// PARTE DO INIMIGO
            if(vez_inimigo == TRUE){
                    if(jogador.esq + (rand()%10)+1 > monstros[monstro_atual].esq){//Sucesso na esquiva
                        int chance = rand()%10 + 1;
                        if (chance <=3 ){
                            esquiva = TRUE;
                        }
                        else{
                            esquiva = FALSE;
                        }
                        
                    }
                    else{//Calculo do dano do monstro em você
                        dano = monstros[monstro_atual].atk - jogador.def;
                        if(dano<=0)
                        {
                            //Nada
                        }
                        else{
                            esquiva = FALSE;
                            //Aplicar dano e resetar
                            jogador.hp -= dano;
                        }

                    }
            }
            if(monstros[monstro_atual].hp <= 0){ //Vitoria 
                jogador.hp = hp_base;
                batalha = 1;
                break;
            }

            if(jogador.hp <=0){ // Derrota
                batalha = 2;
                break;
            }
        

    }while(batalha == 0);
    system("cls");
}

// FALAS
void enter(){
    int tecla;
    printf("\n\n\nPressione %sENTER%s para prosseguir\n",VR,N);
            while(1){
                if(kbhit() != 0){
                    tecla = getch();
                    if(tecla == 13){
                        system("cls");
                        break;
                    }else{
                        //NADA
                    } 
                }
            }
}
void falas(int cont){
        system("cls");
    

    int x,y,max = 1;
    char cache,tecla;


    for(x=0;x<30;x++){
        if(max == 0){
            break;
        }
        printf("\n\t");
        if(x == 0){
            printf("\n\t");
        }
        for(y=0;y<120;y++){

            if(x == max){
                max = 0;
                break;
            }

            else if(cont == 2){
                cache = falas_aranha[x][y];
                max = 5;
            }
            
            else if(cont == 3){
                cache = falas_demonio[x][y];
                max = 6;
            }
            
            else if(cont == 4){
                cache = falas_dragao_batalha[x][y];
                max = 5;
            }
            
            else if(cont == 5){
                cache = falas_dragao_derrota[x][y];
                max = 6;
            }
            
            else if(cont == 6){
                cache = falas_dragao_trato[x][y];
                max = 3;
            }


            else if(cont == 10){
                cache = falas_guerreiro[x][y];
                max = 7;
            }

            else if(cont == 11){
                cache = falas_mago[x][y];
                max = 8;
            }

            else if(cont == 12){
                cache = falas_vigarista[x][y];
                max = 9;
            }

            else if(cont == 13){
                cache = falas_monge[x][y];
                max = 11;
            }
            else {
                max = 0;
            }

            if(cache == '&'){
                printf("%s",jogador.nome);
            }
            else if(cache == '1'){
                printf("%s",V);
            }
            else if(cache == '2'){
                printf("%s",N);
            }
            else{
                if(max != 0){
                    printf("%c",cache);
                }
            }

            if(cache == '\n'){
                printf("\t");
            }

        }
    }


if(cont == 5){
    cont++;
}

    if(cont == 'R'){
        printf("\n");
        printf("\n\tAp�s derrotar e pegar o sangue de Lilith, voc� encontra nos pertences dela um orbe de teleporte\n");
        printf("\tEra justamente o que voc� precisava, ir ao submundo ser� f�cil dessa vez\n");
        enter();
        printf("\n");
        printf("\tAp�s usar o telerporte voc� agora se depara com um cen�rio apocal�ptico\n");
        printf("\tPlanicies Aridas de terras avermelhadas e cheio de rios de lava\n");
        printf("\tNormalmente voc� sentiria muito calor e falta de ar em um ambiente desse\n");
        printf("\tMas o Medalh�o parece lhe proteger das adversidades\n");
    }
    else if(cont == 'D'){
        printf("\n");
        printf("\n\tAp�s derrotar e arrancar os chifres de Azazel, voc� encontra nos pertences dele um pergaminho de teleporte\n");
        printf("\tSem muitos arrodeios, voc� usa o pergaminho para ir at� as Montanhas Geladas\n");
        enter();
        printf("\n");
        printf("\tAp�s usar o telerporte voc� agora se depara com uma montanha gigantesca\n");
        printf("\tParece haver um castelo no topo dela. Deve ser l� onde Dragnar vive\n");
        printf("\tNormalmente voc� sentiria muito frio e falta de ar em um ambiente desse\n");
        printf("\tMas mais uma vez o Medalh�o parece lhe proteger das adversidades\n");
    }

    else if(cont == 'G'){// Final Guerreiro
        printf("\n");
        printf("\tCom bastante esfor�o %s derrota Zephir e impede o seu plano maligno...\n",jogador.nome);
        printf("\tDragnar estava certo, voc� estava sendo usado.\n\n");
        printf("\tFelizmente %s foi forte o suficiente para impedir um evento catastr�fico...\n",jogador.nome); 
        enter();
        printf("\n");
        printf("\tIsso o faz perceber que h� muitos mals que assolam a terra sem o conhecimento das pessoas comuns.\n\n");
        printf("\tSeres Malignos se movem na surdina, esperando a menor abertura\n");
        printf("\tpara colocar seus planos nefastos em a��o... algu�m tem que dete-los.\n\n");
        enter();
        printf("\n");
        printf("\tLutar pelos homens n�o trouxe nenhuma satsifa��o a %s, apenas arrependimento\n",jogador.nome); 
        printf("\tmesmo assim, lutar est� em sua ess�ncia, por isso, dessa vez ele n�o lutar� por um rei ou um reino\n");
        printf("\tmas pela humanidade, pelo bem e pela justi�a.\n\n");
        enter();
        printf("\n");
        printf("\t%s come�a agora sua jornada para tornar-se um Paladino.\n",jogador.nome);
        printf("\tE quem sabe, um dia, formar a pr�pria ordem de cavaleiros.\n\n");

    }
    else if(cont == 'M'){ // Final Mago
        printf("\n");
        printf("\tPassado por suas aventuras, o mago se v� perante a um caminho indecifr�vel.\n");
        printf("\tSeu problema n�o fora resolvido e ele continua tendo somente a sua pr�pria vida como aliada, Ou quase isso...\n");
        printf("\tExperi�ncia e confian�a brilharam juntas na ess�ncia do pequeno, que no fim, independentemente do seu destino\n");
        printf("\tsabe em seu cora��o que vai sobreviver, pois o mago...\n\n");

        printf("\n� %sIMPLAC�VEL!%s\n",A,N);

    }
    else if(cont == 'V'){ // Final Vigarista
        printf("\n");
        printf("\tCom bastante esfor�o %s derrota Zephir e impede o seu plano maligno...\n",jogador.nome);
        printf("\tDragnar estava certo, voc� estava sendo usado.\n\n");
        printf("\tFelizmente %s foi forte o suficiente para impedir um evento catastr�fico...\n",jogador.nome); 
        enter();
        printf("\n");
        printf("\tisso o faz pensar, sobre como tudo o que queria era uma vida comum\n"); 
        printf("\tentretanto tudo isso foi retirado de ti pelas circunst�ncias.\n"); 
        printf("\tPor isso mesmo, %s decide n�o deixar que o mesmo ocorra com outras pessoas.\n\n",jogador.nome);
        enter();
        printf("\n");
        printf("\t%s regressa ao submundo e saqueia os tesouros do Dem�nio Azazel\n",jogador.nome);
        printf("\tE usa-os para criar a maior escola-Orfanato do reino\n"); 
        printf("\tOnde as crian�as pobres, os orf�os e os desamparados recebiam sustento\n"); 
        printf("\tAl�m de aprender as mat�rias comuns a todos, bem como a auto defesa\n");
        printf("\te o combate as for�as sombrias.\n");

    }
    else if (cont == 'O'){ // Final Monge
        printf("\n");
        printf("\tCom bastante esfor�o %s derrota Zephir e impede o seu plano maligno...\n",jogador.nome);
        printf("\tDragnar estava certo, voc� estava sendo usado.\n\n");
        printf("\tFelizmente %s foi forte o suficiente para impedir um evento catastr�fico...\n",jogador.nome); 
        enter();
        printf("\n");
        printf("\t%s Decide ent�o tirar um tempo para aprimorar suas habilidades espirituais\n",jogador.nome);
        printf("\tafim de saber quando algu�m mente ou esconde coisas a partir da sua energia espiritual\n");
        printf("\tpara que nunca mais seja enganado novamente.\n\n");
        enter();
        printf("\n");
        printf("\tTendo enfim atinigido este n�vel, dirige-se agora a capital do reino\n");
        printf("\tonde pretende fazer o seu caminho at� os mais altos cargos pol�ticos\n");
        printf("\te impedir as guerras antes mesmo delas acontecerem.\n");
    }

    else if (cont == 1){
        printf("\n");
        printf("\tVoc� se encontra no quarto de uma hospedaria na capital do reino de Elyria\n");
        printf("\tAlgu�m bate a sua porta, voc� se levanta para abrir e descobrir quem �\n");
        printf("\tUm senhor de apar�ncia fr�gil est� do outro lado da porta\n");
        enter();
        printf("\n");
        printf("%s--%s\tOl� %s, perdoe-me pela visita repentina, mas n�o pude deixar de ouvir falar sobre a sua situa��o...\n",V,N,jogador.nome);
        printf("\t� realmente uma pena que tenha de passar pelo que est� passando. Mas n�o se preocupe\n");
        printf("\tcreio ter uma solu��o para os seus problemas. %s--%s \n\n",V,N);
        enter();
        printf("\n");
        printf("%s--%s\tMeu nome � Meruen, sou um alquimista formado a mais de 20 anos.\n",V,N);
        printf("\tNesse meio tempo andei fazendo diversas pesquisas e descobri coisas muito importantes...\n");
        printf("\tDescobri que � poss�vel, com os materias certos, criar a Pedra Filosofal\n");
        printf("\tdessas mesmas que contadores de hist�ria falam nas lendas. %s--%s \n\n",V,N);
        enter();
        printf("\n");
        printf("%s--%s\tPelos ultimos 10 anos pesquisei e descobri o m�todo e os materiais necess�rios para cria-la, mas h� um por�m...\n",V,N);
        printf("\tOs materias que compoem este artefato s�o demasiado raros e dif�ceis de obter.\n\n");
        printf("\tS�o eles: O %sSangue de uma Aranha Rainha%s, %sUm Chifre de Demonio de alto n�vel%s \n\te %sAs Escamas do Drag�o Rei Dragnar%s. %s--%s \n\n",R,N,VR,N,AZ,N,V,N);
        enter();
        printf("\n");
        printf("%s--%s\tSe eu tivesse mais habilidades fisicas e de combate j� haveria ido atr�s destes itens eu mesmo,\n",V,N);
        printf("\tentretanto, n�o � esse o caso... Por�m � ai onde voc� entra.\n");
        printf("\tOuvi falar muito bem das suas habilidades e sei que pode me ajudar %s--%s \n\n",V,N);
        enter();
        printf("\n");
        printf("%s--%s\tFa�o um juramento aqui e agora que em nome da minha Santa M�e (que deus a tenha) e da Guilda dos Alquimistas que\n",V,N);
        printf("\tcom o poder da Pedra Filosofal que me ajudar�s a criar reverterei a sua Lament�vel Situa��o.\n\n");
        printf("\tAl�m disso, � claro que n�o lhe deixarei ir sem antes ajudar com as prepara��es %s--%s \n",V,N);
        enter();
        printf("\n");
        printf("%s--%s\ttome este %sMedalh�o M�gico%s que produzi, � minha Magnus Oppus at� agora.\n",V,N,A,N);
        printf("\tCom ele cada inimigo que derrotares aumentar� sua for�a\n");
        printf("\tpois a alma deles ser� absorvida pelo Medalh�o e convertida em Vitalidade e estamina para Ti.\n\n");
        printf("\tAgora v�! Vamos mudar o seu e o meu Destino %s ! %s--%s \n",jogador.nome,V,N);
}

else if(cont == 6){
    printf("\n\nPara Aceitar a Oferta de Dragnar Pressione %s'S'%s\t Para Negar Pressione %s'N'%s\n\n",V,N,VR,N);
     while(1){
        if(kbhit() != 0){
            tecla = getch();
            if(tecla == 's' || tecla == 'S'){
                final_bom = TRUE;
                system("cls");
                printf("\n\n");
                printf("\tCautelosamente voc� entrega o Medalh�o a Dragnar, que agradece a confian�a\n");
                printf("\te recita palavras em uma lingua que voc� n�o consegue compreender, mas assim que ele\n");
                printf("\tfinaliza as palavras o medalh�o brilha ofuscantemente e uma fuma�a Preta sai de dentro\n");
                printf("\tdele e � soprada em dire��o as janelas abertas.\n\n");
                printf("\tDragnar devolve o medalh�o a voc� e diz que o imbuiu com parte de seu pr�prio poder restante.\n\tEle espera que voc� fa�a bom uso.\n\n");
                printf("\tVoc� parte seguindo caminho para casa... durante o caminho voc� sente como\n\tse um peso tivesse sido retirado de ti... algo certamente mudou.\n");
                break;
            }else if (tecla == 'n' || tecla == 'N'){
                final_bom = FALSE;
                system("cls");
                printf("\n\n");
                printf("\tVoc� age como quem aceitou a Proposta, mas ao chegar proximo o suficiente de Dragnar\n");
                printf("\tvoc� o finaliza em um golpe r�pido.\n\nLogo em seguida pega umas das suas escamas...\n\n");
                printf("\tHora de procurar o caminho de volta.\n");
                jogador.atk-= (jogador.atk*0.3);
                jogador.def-= (jogador.def*0.3);
                jogador.esq-= (jogador.esq*0.3);
                jogador.hp -= (jogador.hp*0.3); 
                break;
            }else{
                // Nada
            }
        }
    }

}

else if(cont == 7 || cont == 8){
    printf("\n");
    printf("\tAo retornar ao local de inicio da sua partida, voc� avista Meruan, que parece muito feliz em ver que voc� retornou.\n");
    printf("\tEntretanto, ao se aproximar ele come�a a agir de maneira estranha\n\n");
    printf("%s--%s\tFinalmente, Eu sabia que algu�m uma hora ou outra conseguiria ! %s--%s \n\n",V,N,V,N);
    printf("\tMeruan Retira sua capa de Alquismista revelando um corpo raqu�tico e p�lido.\n");
    printf("\tLogo em seguida uma n�voa branca adentra a casa e se reune ao delor dele, desmanchando sua carne e revelando seus ossos.\n");
    printf("\tDe onde emana uma luz verde poderosa. A sua apar�ncia atual lembra um Lich.\n\n");
    enter();
    printf("\n");
    printf("%s--%s\tTe enganar foi muito f�cil. Estava t�o afundado nas m�gos se lan�ou na primeira miss�o suicida que apareceu.\n",V,N);
    printf("\tE agora que voc� me ajudou a reunir os itens necess�rios para Invocar meu Mestre Mephisto, O Senhor da Destrui��o\n");
    printf("\tsua utilidade acabou. S� precisava de voc� para passar pela maldita barreira m�gica de Dragnar\n\te pegar a escama daquele lazarento. %s--%s \n\n",V,N);
    enter();
    printf("\n");
    printf("%s--%s\tCom Mephisto aqui toda a terra ser� dominio dos Dem�nios. A era das Sombras come�a agora. %s--%s \n\n",V,N,V,N);
    if(final_bom == TRUE){
        printf("\tCom um mecher de m�os e um cantigo antigo Meruen parece Ordenar que algo venha at� ele, mas nada acontece...\n\n");
        printf("%s--%s\tO que voc� fez com o medalh�o que MEPHISTO ME DEU SEU MALDITO VOC� VAI PAGAR POR ISSO !! %s--%s",V,N,V,N);
    }
    else{
        printf("\tCom um mecher de m�os e um cantigo antigo Meruen parece Ordenar que algo venha at� ele.\n\n");
        printf("\tO medalh�o em seu pesco�o responde ao chamado do seu mestre e levita velozmente at� as m�os de Meruan\n\n");
        printf("%sTodos os seus status foram reduzidos em 30%% %s", VR,N);
    };



}
    if(cont != 5){
        printf("\n\n\nPressione %sENTER%s para prosseguir\n",VR,N);
            while(1){
                if(kbhit() != 0){
                    tecla = getch();
                    if(tecla == 13){
                        system("cls");
                        break;
                    }else{
                        //NADA
                    } 
                }
            }
    }


    if(cont == 10 || cont == 11 || cont == 12 || cont == 13){
        falas(1);
    }
}


int main(){
   /*
   1) JOGADOR E ITENS DEVEM SER ENVIADOS COMO PONTEIROS PARA A FUN��O DE INVENT�RIO
   */
   // TELA CHEIA
    keybd_event(VK_MENU,0x36,0,0);
    keybd_event(VK_RETURN,0x1C,0,0);
    keybd_event(VK_RETURN,0x1C,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
    setlocale(LC_ALL, "Portuguese"); // PORTUGU�S
    Sleep(300);
    srand(time(NULL));
   
    int tecla;
// SETANDO MONSTROS
    memcpy(monstros[0].sprite,ARANHA_VEN,sizeof(ARANHA_VEN));
    memcpy(monstros[1].sprite,GOBLIN,sizeof(GOBLIN));
    memcpy(monstros[2].sprite,LIZARD,sizeof(LIZARD));
    memcpy(monstros[3].sprite,OGRO,sizeof(OGRO));
    memcpy(monstros[4].sprite,RAINHA_ARANHA,sizeof(RAINHA_ARANHA));
    memcpy(monstros[5].sprite,SLIME_LAVA,sizeof(SLIME_LAVA));
    memcpy(monstros[6].sprite,DEM_INFERIOR,sizeof(DEM_INFERIOR));
    memcpy(monstros[7].sprite,GOLEM_LAVA,sizeof(GOLEM_LAVA));
    memcpy(monstros[8].sprite,DEM_SUPERIOR,sizeof(DEM_SUPERIOR));
    memcpy(monstros[9].sprite,AZAZEL,sizeof(AZAZEL));
    memcpy(monstros[10].sprite,SLIME,sizeof(SLIME));
    memcpy(monstros[11].sprite,AGUIA,sizeof(AGUIA));
    memcpy(monstros[12].sprite,LOBO_SUPERIOR,sizeof(LOBO_SUPERIOR));
    memcpy(monstros[13].sprite,YETI,sizeof(YETI));
    memcpy(monstros[14].sprite,DRAGNAR,sizeof(DRAGNAR));
    memcpy(monstros[15].sprite,ZEPHIR,sizeof(ZEPHIR));

// SETANDO MAPAS
    memcpy(mapas[0].sprite, MAPA_1,sizeof(MAPA_1));
    memcpy(mapas[1].sprite, MAPA_2,sizeof(MAPA_2));
    memcpy(mapas[2].sprite, MAPA_3,sizeof(MAPA_3));
    memcpy(mapas[3].sprite, MAPA_4,sizeof(MAPA_4));
    memcpy(mapas[4].sprite, MAPA_5,sizeof(MAPA_5));
    memcpy(mapas[5].sprite, MAPA_6,sizeof(MAPA_6));
    memcpy(mapas[6].sprite, MAPA_7,sizeof(MAPA_7));
    memcpy(mapas[7].sprite, MAPA_8,sizeof(MAPA_8));
    memcpy(mapas[8].sprite, MAPA_9,sizeof(MAPA_9));

    int mont = 0;

    ativar_menu();
    // J� ativa o Escolha de personagem dentro do menu
    if(jogador.classe_id == 1){ // Guerreiro
        falas(10);
    }
    else if(jogador.classe_id == 2){ // Mago
        falas(11);
    }
    else if (jogador.classe_id == 3){ // Vigarista
        falas(12);
    }
    else{ // Monge
        falas(13);
    }
    //Ai j� entra na parte abaixo e pronto

     double tempo_decorrido = 0.0;
    clock_t begin  = clock(); // Posiciona-lo ap�s o inicio do jogo em si
   do{
        system("cls");
        mont = 0;
      anterior = mapas[mapa_atual].bloco_inicial;
      
       if(mapa_atual == 1){
        monstro_atual = 2;
      }
      else if(mapa_atual == 2){ // BOSS
        monstro_atual = 4;
      }
      else if(mapa_atual == 3){
        monstro_atual = 5;
      }
      else if(mapa_atual == 4){
        monstro_atual = 7;
      }
      else if(mapa_atual == 5){ // BOSS
        monstro_atual = 9;
      }
      else if(mapa_atual == 6){
        monstro_atual = 10;
      }
      else if (mapa_atual == 7){
        monstro_atual = 12;
      }
      else if (mapa_atual == 8){ // BOSS
        monstro_atual = 14;
      }
      imp(40,60,sprite_mapas);
      PJL = mapas[mapa_atual].inicio_x;
      PJC = mapas[mapa_atual].inicio_y + 32;
      vapara(PJL,PJC);
      printf("*");

      do{
        
         // TESTAR PARA BORDAS DIRETAMENTE AQUI, O RESTO QUE TESTA FORA. 
         if(kbhit() != 0){
            tecla = getch();

            vapara(PJL,PJC);
            imp(1,1,andar);

            if(tecla == 'm' || tecla == 'M'){
               ativar_menu();
               imp(40,60,sprite_mapas);
               vapara(PJL,PJC);
               printf("*");
            }
            else if(tecla == 'i' || tecla == 'I'){
               ativar_inventario();
               imp(40,60,sprite_mapas);
               vapara(PJL,PJC);
               printf("*");
            }

            else if(tecla == ESC){
               exit(0);
            }

            else if(tecla == 'a' || tecla == 'A'){
               if(PJC-1 < 0+32){
                  // Nada, n�o pode andar
               }else{
                    if(testar_se_pode(0,-1)){
                        PJC--;
                    }
               }
               
               
            }
            else if(tecla == 's' || tecla == 'S'){
               if(PJL+1 >39){
                  // Nada, n�o pode andar
               }else{         
                    if(testar_se_pode(1,0)){
                        PJL++;
                    }                                    
               }
            }
            else if(tecla == 'd' || tecla == 'D'){
               if(PJC+1 > 59+32){
                  // Nada, n�o pode andar
               }else{     
                    if(testar_se_pode(0,1)){
                        PJC++;
                    }
               }
            }
            else if(tecla == 'w' || tecla == 'W'){
               if(PJL-1 < 0){
                  // Nada, n�o pode andar
               }else{
                    if(testar_se_pode(-1,0)){
                        PJL--;
                    }
               }
            }

            anterior = mapas[mapa_atual].sprite[PJL][PJC-32];
            vapara(PJL,PJC);
            printf("*");
            if(PJL == mapas[mapa_atual].monstros_x[mont] && (PJC-32) == mapas[mapa_atual].monstros_y[mont]){
                hp_ref_monstro = monstros[monstro_atual].hp;
                 if(monstro_atual == 4){
                        falas(2); //2
                    }
                    
                     if(monstro_atual == 9){
                        falas(3); //3
                    }

                     if(monstro_atual == 14){
                        falas(4); //4
                    }

                    if(monstro_atual == 15){
                        falas(7);
                    }

                ativar_combate();
                if(batalha == 2){
                    clock_t end = clock();
                    tempo_decorrido += (double)(end-begin)/CLOCKS_PER_SEC;
                    Derrota(tempo_decorrido,pontuacao);
                }
                else if(batalha == 1){
                    mapas[mapa_atual].monstros_x[mont] = 0;
                    mapas[mapa_atual].monstros_y[mont] = 0;
                    if(monstro_atual == 4){
                        falas('R');
                        combate_vitorioso();
                        monstro_atual++;
                        mapa_atual++;
                        break;
                    }
                    else if(monstro_atual == 9){
                        falas('D');
                        combate_vitorioso();
                        monstro_atual++;
                        mapa_atual++;
                        break;
                    }
                    else if(monstro_atual == 14){
                        falas(5); // A escolha final tamb�m ocorre aqui
                        combate_vitorioso();
                        monstro_atual++;
                        falas(7);
                        ativar_combate();
                        clock_t end = clock();
                        tempo_decorrido += (double)(end-begin)/CLOCKS_PER_SEC;

                        if(batalha == 1){
                            pontuacao += 1000;
                            switch(jogador.classe_id){
                                case 1: falas('G'); break;
                                case 2: falas('M'); break;
                                case 3: falas('V'); break;
                                case 4: falas('O'); break;
                            }
                             Vitoria(tempo_decorrido,pontuacao);
                             
                        }
                        else{
                             Derrota(tempo_decorrido,pontuacao);
                        }
                       
                    }
                    else {
                        combate_vitorioso();
                        monstro_atual++;
                    }

                    anterior = 'H'; // Verde de que concluiu o monstro
                    imp(40,60,sprite_mapas);
                    vapara(PJL,PJC);
                    printf("*");
                }
                else if(batalha == 3){
                    mapas[mapa_atual].monstros_x[mont] = 0;
                    mapas[mapa_atual].monstros_y[mont] = 0;
                    imp(40,60,sprite_mapas);
                    anterior = 'H'; 
                }
                mont++;
        }

        if(PJL == mapas[mapa_atual].saida_x && (PJC-32) == mapas[mapa_atual].saida_y){
                mapa_atual ++;
                break;
        }
            
    }
      }while(1);

   }while(1);

}
 