/**
    UNIVERSIDADE FEDERAL DO VALE DO SAO FRANCISCO
    DISCIPLINA: COMPUTACAOO GRAFICA  TURMA: 2020.2
    PROFESSOR: JORGE CAVALCANTE
    ALUNOS: JOSE WESLLES
            MATHEUS ADHONNAY
            RAYANNE CAROLINE
*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>
#include <time.h>

//CORES USADAS NO FUNDO DO LABIRINTO
#define AZUL     0.0, 0.0, 0.5, 1.0
#define VERMELHO 0.5, 0.0, 0.0, 1.0
#define VERDE  0.0, 0.5, 0.0, 1.0
#define CINZA    0.5,0.5, 0.5, 1.0

#define PASSO 1.5

GLfloat ro,go,bo; //RGB do quadrado
GLfloat rl,gl,bl; //RGB das paredes do labirinto

int max_verticais = 14;
int max_horizontais = 18;

int auxcolor;
int vidas = 3;
int cont =0;

//PAREDES DO LABIRINTO

int linhas_verticais[14][3] = { {0,34,138},{0,0,17},{18,17,68},{34,85,119},{34,0,17},
                                {51,102,138},{51,68,85},{68,34,68},{85,17,51},{102,51,119},
                                {119,68,85},{119,34,51},{138,0,102},{138,119,138}
                               };

int linhas_horizontais[18][3] = {   {0,0,138},{17,102,138},{17,51,85},{34,0,17},{34,34,68},{34,85,102},
                                    {51,17,51},{51,102,119},{68,34,85},{68,102,119},{85,17,34},{85,68,102},
                                    {102,0,17},{102,51,85},{102,119,138},{119,0,34},{119,68,138},{138,0,138}
                                };

//DESENHO DA FIGURA
float quad[4][2] = {{2.5,19.5},{12.5,19.5},{12.5,29.5},{2.5, 29.5}};
float quadAux[4][2] = {{2.5,19.5},{12.5,19.5},{12.5,29.5},{2.5, 29.5}};

void Inicializa(void);
void Desenha(void);
bool colisaoVertical(void);
bool colisaoHorizontal(void);
void TecladoEspecial(int , int , int );
void Mouse(int , int ,int , int );

int main(int argc, char *argv[]){

    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutCreateWindow("Atravessando o Labirinto");
    glutDisplayFunc(Desenha);
    glutSpecialFunc(TecladoEspecial);
    glutMouseFunc(Mouse);
    Inicializa();
    glutMainLoop();
}

void Inicializa (void){
    glClearColor(CINZA);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,138,0,138);
    ro=0; go=0; bo=255;
    rl=0; gl=0; bl=0;

}

void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5);
    glColor3f(rl,gl,bl);
    for(int i = 0; i < max_verticais; i++){
             glBegin(GL_LINES);
                glVertex2i(linhas_verticais[i][0], linhas_verticais[i][1]);
                glVertex2i(linhas_verticais[i][0], linhas_verticais[i][2]);
             glEnd();
    }
    for(int i = 0; i < max_horizontais; i++){
             glBegin(GL_LINES);
                glVertex2i(linhas_horizontais[i][1],linhas_horizontais[i][0]);
                glVertex2i(linhas_horizontais[i][2],linhas_horizontais[i][0]);
             glEnd();
    }
    glColor3f(ro, go, bo);
    glBegin(GL_QUADS);
        glVertex2f(quad[0][0],quad[0][1]);
        glVertex2f(quad[1][0],quad[1][1]);
        glVertex2f(quad[2][0],quad[2][1]);
        glVertex2f(quad[3][0],quad[3][1]);
    glEnd();

    glFlush();
}

bool colisaoVertical(void){
        for(int i = 0; i < max_verticais; i++){
            if( (linhas_verticais[i][0] >= quad[0][0] && linhas_verticais[i][0] <= quad[1][0]) &&
                (quad[1][1] >= linhas_verticais[i][1] && quad[2][1] <= linhas_verticais[i][2])
               ) {
                printf("vidas = %d\n", vidas-1);
                return true;
            }
        }
        return false;
}

bool colisaoHorizontal(void){
    for(int i = 0; i < max_horizontais; i++){
            if( (linhas_horizontais[i][0] >= quad[1][1] && linhas_horizontais[i][0] <= quad[2][1]) &&
                (quad[0][0] >= linhas_horizontais[i][1] && quad[1][0] <= linhas_horizontais[i][2])
               ){
                printf("vidas = %d\n", vidas-1);
                return true;
            }
        }
        return false;
}

void TecladoEspecial(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            for(int i= 0; i < 4; i++)
                quad[i][1]+=PASSO;
            if(colisaoHorizontal()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;
        case GLUT_KEY_DOWN:
            for(int i= 0; i < 4; i++)
                quad[i][1]-=PASSO;
            if(colisaoHorizontal()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;
        case GLUT_KEY_LEFT:
            for(int i= 0; i < 4; i++)
                quad[i][0]-=PASSO;
            if(colisaoVertical()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;
        case GLUT_KEY_RIGHT:
            for(int i= 0; i < 4; i++)
                quad[i][0]+=PASSO;
            if(colisaoVertical()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;
    }
    if(vidas <= 0){
        printf("Voce Perdeu!\n!");
        vidas=3;

    } else
        if(quad[1][1] > 102 && quad[2][1] < 119 && quad[1][0] > 138){
            printf("Voce Ganhou!!\n");
            vidas+=1;
            for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
        }else{
            if(quad[1][0] < 0 && quad[2][0] < 0){
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        }
    glutPostRedisplay();

}

void Mouse(int button, int state,int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){

            //MUDAN�A DE COR DO OBJETO
            ro=(GLbyte)rand() % 255;
            go=(GLbyte)rand() % 255;
            bo=(GLbyte)rand() % 255;

            //MUDAN�A DE COR DAS LINHAS DO LABIRINTO
            rl=(GLbyte)rand() % 255;
            gl=(GLbyte)rand() % 255;
            bl=(GLbyte)rand() % 255;

            //MUDAN�A DE COR DO FUNDO DO LABIRINTO
            switch (cont){
                case 0:
                    glClearColor(AZUL);
                    cont++;
                    break;
                case 1:
                    glClearColor(VERMELHO);
                    cont++;
                    break;

                case 2:
                    glClearColor(VERDE);
                    cont++;
                    break;

                case 3:
                    glClearColor(CINZA);
                    cont =0;
                    break;

               }
            glutPostRedisplay();
        }
    }
}
