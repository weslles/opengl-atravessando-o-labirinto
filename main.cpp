/**
    UNIVERSIDADE FEDERAL DO VALE DO SAO FRANCISCO
    DISCIPLINA: COMPUTACAOO GRAFICA  TURMA: 2020.2
    PROFESSOR:  JORGE CAVALCANTE
    ALUNOS:     JOSE WESLLES
                MATHEUS ADHONNAY
                RAYANNE CAROLINE
*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>
#include <time.h>

//CORES USADAS NO FUNDO DO LABIRINTO
#define AZUL     0.25, 0.25, 0.5, 1.0
#define VERMELHO 1.65, 0.0, 0.0, 1.0
#define VERDE  0.0, 0.5, 0.0, 1.0
#define CINZA    0.5,0.5, 0.5, 1.0

#define PASSO 0.5     //MOSTRA O QUANTO O QUADRADO SE MOVIMENTA NO PLANO CARTESIANO
#define ESPESSURA 3 //ESPESSURA DA PAREDE DO LABIRINTO

GLfloat ro,go,bo; //RGB DO QUADRADRO
GLfloat rl,gl,bl; //RGB DAS PAREDES DO LABIRINTO

int max_verticais = 14;
int max_horizontais = 18;

int vidas = 3;
int cont =0;            //VARIAVEL USADA PARA CONTROLAR A MUDANÇA DE COR DO FUNDO DO LABIRINTO
char winLose[15] = " "; //MENSAGEM DE VITORIA/DERROTA


//POSIÇÕES DAS PAREDES DO LABIRINTO
int linhas_verticais[14][3] = { {0,34,138},{0,0,17},{18,17,68},{34,85,119},{34,0,17},
                                {51,102,138},{51,68,85},{68,34,68},{85,17,51},{102,51,119},
                                {119,68,85},{119,34,51},{138,0,102},{138,119,138}
                               };

int linhas_horizontais[18][3] = {   {0,0,138},{17,102,138},{17,51,85},{34,0,18},{34,34,68},{34,85,102},
                                    {51,18,51},{51,102,119},{68,34,85},{68,102,119},{85,17,34},{85,68,102},
                                    {102,0,17},{102,51,85},{102,119,138},{119,0,34},{119,68,138},{138,0,138}
                                };

//POSIÇÃO INICIAL DO QUADRADO
float quad[4][2] = {{2.5,115.5},{12.5,115.5},{12.5,105.5},{2.5, 105.5}};
float quadAux[4][2] = {{2.5,115.5},{12.5,115.5},{12.5,105.5},{2.5, 105.5}};

void Inicializa(void);
void Desenha(void);
bool colisaoVertical(void);
bool colisaoHorizontal(void);
void teclado(unsigned char , int , int );
void TecladoEspecial(int , int , int );
void Mouse(int , int ,int , int );
void DesenhaTexto(char *);

int main(int argc, char *argv[]){

    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutCreateWindow("Atravessando o Labirinto");
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(TecladoEspecial);
    glutMouseFunc(Mouse);
    Inicializa();
    glutMainLoop();
}

void Inicializa (void){
    printf("\n-----------------------\n");
    printf("BEM VINDO AO LABIRINTO!!");
    printf("\n-----------------------\n");
    printf("Voce comeca com %d vidas.\n", vidas);
    glClearColor(CINZA);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,138,0,138);
    ro=0; go=0; bo=255;
    rl=0; gl=0; bl=0;

}

void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);

    //DESENHA AS PAREDES DO LABIRINTO
    glLineWidth(ESPESSURA);
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
    //DESENHA UM QUADRADO DENTRO DO LABIRINTO
    glColor3f(ro, go, bo);
    glBegin(GL_QUADS);
        glVertex2f(quad[0][0],quad[0][1]); // A(2,19)
        glVertex2f(quad[1][0],quad[1][1]); // B(12,19)
        glVertex2f(quad[2][0],quad[2][1]); // C(12,29)
        glVertex2f(quad[3][0],quad[3][1]); // D(2,29)
    glEnd();

    // INSERE STRING VAZIA NO CANTO SUPERIOR DIREITO DO LABIRINTO
     glColor3f(0.0f,0.0f,0.0f);
     DesenhaTexto(winLose);
     glutSwapBuffers();

    glFlush();
}

bool colisaoVertical(void){
        for(int i = 0; i < max_verticais; i++){

            if( (linhas_verticais[i][0] >= quad[0][0] && linhas_verticais[i][0] <= quad[1][0]) &&
                (quad[1][1] >= linhas_verticais[i][1] && quad[2][1] <= linhas_verticais[i][2])
               ) {
                printf("Vidas restantes: %d\n", vidas-1);
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
                printf("Vidas restantes: %d\n", vidas-1);
                return true;
            }
        }
        return false;
}

void teclado(unsigned char key, int x, int y){
    switch (key) {
            case 27:
                system("cls");
                printf("\n-----------------------\n");
                printf("SENTIREMOS SUA FALTA!!");
                printf("\n-----------------------\n");
                exit(0);
                break;
    }
    glutPostRedisplay();
}

void TecladoEspecial(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            strcpy(winLose, " ");
            for(int i= 0; i < 4; i++)
                quad[i][1]+=PASSO;
            if(colisaoHorizontal()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
            if(colisaoVertical()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;
        case GLUT_KEY_DOWN:
            strcpy(winLose, " ");
            for(int i= 0; i < 4; i++)
                quad[i][1]-=PASSO;
            if(colisaoHorizontal()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
            if(colisaoVertical()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;
        case GLUT_KEY_LEFT:
            strcpy(winLose, " ");
            for(int i= 0; i < 4; i++)
                quad[i][0]-=PASSO;
            if(colisaoVertical()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
            if(colisaoHorizontal()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;
        case GLUT_KEY_RIGHT:
            strcpy(winLose, " ");
            for(int i= 0; i < 4; i++)
                quad[i][0]+=PASSO;
            if(colisaoVertical()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
            if(colisaoHorizontal()){
                vidas--;
                for(int i=0;i < 4;i++)
                    for(int j=0; j < 2; j++)
                    quad[i][j] = quadAux[i][j];
            }
        break;

    }
    if(vidas <= 0){
        //printf("Voce Perdeu!\n!");
        strcpy(winLose, "Voce Perdeu!");
        system("cls");
        printf("\nTENTE NOVAMENTE!\n------------------------------\n");

        vidas=3;
        printf("Vidas restantes: %d\n", vidas);
    } else
        if(quad[1][1] > 102 && quad[2][1] < 119 && quad[1][0] > 138){
            //printf("Voce Ganhou!!\n");
            strcpy(winLose, "Voce Venceu!");
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

void DesenhaTexto(char *string){
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(70,125);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	glPopMatrix();
}
