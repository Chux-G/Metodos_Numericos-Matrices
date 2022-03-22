#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10 //Constante de dimension para los arreglos

/*Declaracion de los Metodos*/
void IngresarDatosCholesky();
void MostrarMatrizIngresada(double M[MAX][MAX], int fila, int columna);
void MostrarVectorIngresado();
void VerificacionMatriz();
void ConvertirMatrizA();
void MetodoCholesky(double A_C[MAX][MAX], double B_C[MAX]);
void ResultadoMetodoCholesky();
void IngresarDatosQR();
void ResultadoMetodoQR();

/*Declaracion de Variables*/
int i, j, k, n, d=0, f, c, op;
double A[MAX][MAX], B[MAX], X[MAX], L[MAX][MAX], Y[MAX], LT[MAX][MAX], AT[MAX][MAX], Ai[MAX][MAX], Bi[MAX], sum;
double r[MAX][MAX], q[MAX][MAX], qt[MAX][MAX];

int main(){ //Programa Principal
    
    /*Menu del Programa*/
    do{
        
    printf ("\n\n========METODOS PARA DESCOMPOSICION DE MATRICES========");
    printf ("\n\n     1. METODO DE CHOLESKY");
    printf ("\n     2. METODO QR");
    printf("\n     3. SALIR");
    printf("\n\nSELECCIONE UNA OPCION: ");
    scanf("%d",&op);
    
        if (op==1){ //Metodo de Cholesky
            IngresarDatosCholesky();
            MostrarMatrizIngresada(A,n,n);
            MostrarVectorIngresado();
            VerificacionMatriz();
            ResultadoMetodoCholesky();
        }else if(op==2){ //Metodo QR
            IngresarDatosQR();
            MostrarMatrizIngresada(A,f,c);
            ResultadoMetodoQR();
        }else if(op==3){ //Salir del Menu
            break;
        }else{ //Opcion invalida
            printf("\nOPCION INVALIDA");
        }
    
    }while(op!=3);
    
    return 0;
}

/*Metodo para Ingresar la Matriz A Cuadrada y 
el Vector B para aplicar el Metodo de Cholesky*/
void IngresarDatosCholesky(){
    //Ingreso de los elementos de la Matriz A
    printf ("\n\n================METODO DE CHOLESKY================");
    printf ("\n\nINGRESE LA DIMENSION DE LA MATRIZ CUADRADA: ");
    scanf("%d",&n);
    printf("\n\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
                printf("INGRESE EL ELEMENTO DE LA POSICION A[%d][%d] DE LA MATRIZ -> ",i + 1,j + 1);
                scanf("%lf",&A[i][j]);
        }
    }
    
    //Ingreso de los elementos del Vector B
    printf("\n\nELEMENTOS DEL VECTOR: ");
    printf("\n\n");
    for(i = 0; i < n; i++){
        printf("INGRESE EL ELEMENTO DE LA POSICION B[%d] DEL VECTOR -> ",i + 1);
        scanf("%lf",&B[i]);
    }
    printf("\n\n");
}


/*Metodo para mostrar la Matriz que ha introducido el usuario*/
void MostrarMatrizIngresada(double M[MAX][MAX], int fila, int columna){
    //Mostrar la Matriz que ha introducido el usuario
    printf("MATRIZ INTRODUCIDA:");
    printf("\n");
    for(i = 0; i < fila; i++){
        printf("\n\t\t");
        for(j = 0; j < columna; j++){
            printf("    %lf    ",M[i][j]);
        }
    }
    printf("\n\n");
}

/*Metodo para mostrar el vector que ha introducido el usuario*/
void MostrarVectorIngresado(){
    //Mostrar el Vector que ha introducido el usuario
    printf("\nVECTOR INTRODUCIDO:");
    printf("\n");
    for(i = 0; i < n; i++){
        printf("\n\t\t");
        printf("    %lf    ",B[i]);
    }
    printf("\n\n");
}

/*Metodo para determinar la condicion 
para aplicar el Metodo Cholesky*/
void VerificacionMatriz(){
    //Matriz Transpuesta (Matriz AT) de la Matriz Introducida (Matriz A)
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            AT[j][i] = A[j][i];
        }
    }

    /*Detector que determina si la Matriz A 
    es distinta a su Matriz Transpuesta AT*/
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(A[i][j] != AT[j][i]){
                d = d + 1;
            }
        }
    }
}



/*Metodo para convertir la Matriz A para el 
caso que sea diferente a su Transpuesta*/
void ConvertirMatrizA(){
     /*Se calcula una nueva Matriz A haciendo el producto de las dos matrices*/
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            double suma = 0.0; 
            for(k = 0; k < n; k++){
                suma += A[k][j] * AT[k][i];
            }
            Ai[j][i] = suma;
        }
    }

/*Calcular los valores del vector B, multiplicandolo con la Matriz A*/
    for(i = 0; i < n; i++){
        Bi[i] = 0.0;
        for (j = 0; j < n; j++){
            Bi[i] += B[j] * AT[j][i];
        }
    }
    
}


/*Metodo para hacer el calculo de la descomposicion de Cholesky*/
void MetodoCholesky(double A_C[MAX][MAX], double B_C[MAX]){
    
     /*Determinar el valor de la Matriz L*/
    for(i = 0; i < n; i++){
        for (j = 0; j <= i; j++){
            sum = 0.0;

            if (j == i){
                for (k = 0; k < j; k++)
                    /*Algoritmo de Cholesky para elementos en diagonal principal*/
                    sum += pow(L[j][k], 2);
                    L[j][j] = sqrt(A_C[j][j] - sum);
                
            } else {
                for (k = 0; k <= j; k++)
                     /*Algoritmo de Cholesky para elementos debajo de la diagonal principal*/
                    sum += L[i][k] * L[j][k];
                    L[i][j] = (A_C[i][j] - sum) / L[j][j];
            }
        }
    }

    /*Valor calculado de la Matriz L*/
    printf("\nLA MATRIZ L ES:");
    printf("\n");
    for(i = 0; i < n; i++){
        printf("\n\t\t");
        for(j = 0; j < n; j++){
            printf("    %lf     ", L[i][j]);
        }
    }

/*Valor calculado de la Matriz U*/
    printf("\n\nLA MATRIZ U ES:");
    printf("\n");
    for(i = 0; i < n; i++){
        printf("\n\t\t");
        for(j = 0; j < n; j++){
            LT[j][i] = L[j][i];
            printf("    %lf      ", LT[j][i]);
        }
    }

/*Valor calculado del vector Y*/
    Y[0] = B_C[0] / L[0][0];
    for(i = 1; i < n; i++){
        sum = 0.0;
        for(j = 0; j < i; j++){
            sum = sum + Y[j] * L[i][j];
        }

        Y[i] = (B_C[i]-sum) / L[i][j];
    }

    printf("\n\nVALORES DE Y:");
    printf("\n");
    for(i = 0; i < n; i++){
        printf("\n  Y%d = %lf",i + 1,Y[i]);
        printf("\n\n");
    }

/*Valor calculado del vector X*/
    X[n-1] = Y[n-1] / LT[n-1][n-1];
    for(i = n - 2; i >= 0; i--){
        sum = 0;
        for(j = n - 1; j > i; j--){
            sum = sum + (X[j] * LT[j][i]);
        }

        X[i] = (Y[i]-sum) / LT[j][i];
    }

    printf("\nVALORES DE X:");
    printf("\n");
    for(i = 0; i < n; i++){
        printf("\n  X%d = %lf ",i + 1,X[i]);
        printf("\n\n");
    }
}

/*Metodo para aplicar el Metodo de Cholesky,
en funcion a la condicion que presente la
Matriz A en el metodo VerificacionMatriz()*/
void ResultadoMetodoCholesky(){
    /*Si el detector d no vale cero entonces 
    invoca el metodo ConvertirMatriz()*/
    if(d != 0){
        ConvertirMatrizA();
        MetodoCholesky(Ai,Bi);
    } else{
        MetodoCholesky(A,B);
    }
}

/*Metodo para Ingresar la Matriz A Cuadrada 
para aplicar el Metodo QR*/
void IngresarDatosQR(){
    printf ("\n\n=================METODO QR=================");
    printf ("\n\nINGRESE EL NUMERO DE FILAS DE LA MATRIZ: ");
    scanf("%d",&f);
    printf ("\nINGRESE EL NUMERO DE COLUMNAS DE LA MATRIZ: ");
    scanf("%d",&c);
    printf("\n\n");
    for(i = 0; i < f; i++){
        for(j = 0; j < c; j++){
                printf("INGRESE EL ELEMENTO DE LA POSICION A[%d][%d] DE LA MATRIZ -> ",i + 1,j + 1);
                scanf("%lf",&A[i][j]);
            }    
        }
        
    printf("\n");

}

/*Metodo para calcular la Descomposicion QR de la Matriz A*/
void ResultadoMetodoQR(){
    for (k=0; k<f; k++){
      r[k][k]=0;
      for (i=0; i<f; i++)
        /*Norma del Vector*/
        r[k][k] = r[k][k] + A[i][k] * A[i][k]; 
        r[k][k] = sqrt(r[k][k]);  
      
      for (i=0; i<f; i++) {
          /*Calculo del Vector Normalizado*/
          q[i][k] = A[i][k]/r[k][k];
      }
     
      for(j=k+1; j<c; j++) {
        r[k][j]=0;
        for(i=0; i<f; i++) 
            /*Calculo de la Matriz R*/
            r[k][j] += q[i][k] * A[i][j]; 
        
        for (i=0; i<f; i++) 
            /*Calculo de Vectores Ortogonales*/
            A[i][j] = A[i][j] - r[k][j]*q[i][k];
        
      }
    }

    /*Mostrar la Matriz Q*/
    printf("MATRIZ Q:");
    printf("\n");
    for(i = 0; i < f; i++){
        printf("\n\t\t");
        for(j = 0; j < c; j++){
            printf("    %lf    ",q[i][j]);
        }
    }
    printf("\n");
    
    /*Mostrar la Matriz R*/
    printf("MATRIZ R:");
    printf("\n");
    for(i = 0; i < c; i++){
        printf("\n\t\t");
        for(j = 0; j < c; j++){
            printf("    %lf    ",r[i][j]);
        }
    }
    printf("\n");
    
}
