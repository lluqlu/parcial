#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#define MAX_VUELOS 5
#define TODAS_LAS_VARIABLES "%d %d %d %d %d %v", &dp1, &dp2, &ap1, &ap2, &desperfectos, &maxVuelos
void inicializarVariables(const char *formato, ...);
int validarOpc(char opc){
    char str[2];
    str[0]=opc;
    str[1]='\0';
    int opcion=atoi(str);
    return (opc>='0'&&opc<='9') ? opcion:-1;
    
}
void takeoff(int *p1, int *p2, int *inci, int *maxVuelos){
    int pista;
    char opc;

    printf("Ingrese número de pista \n");
    scanf("%d", &pista);
    if(pista==1){
        (*p1)++;
        (*maxVuelos)--;
    }else if(pista==2){
        (*p2)++;
        (*maxVuelos)--;
    }else{
        printf("Número de pista incorrecto \n");
        return;
    }
    printf("Se registró algún incidente? s/n\n");
    scanf(" %c", &opc);
    if(opc=='s'||opc=='S'){
        (*inci)++;
        printf("Hubo un incidente durante el despegue en pista %d\n", pista);
    }else{
        printf("Despegue existoso en pista %d\n", pista);
        
    }
}
void landing(int *p1, int *p2, int *inci, int *maxVuelos){
    int pista;
    char opc;
    printf("Ingrese el número de pista \n");
    scanf("%d", &pista);
    if(pista==1){
        (*p1)++;
        (*maxVuelos)--;
        
    }else if(pista==2){
        (*p2)++;
        (*maxVuelos)--;
    }else{
        printf("Número de pista incorrecto\n");
        return;
    }
    printf("Hubo algún incidente? s/n\n");
        scanf(" %c", &opc);
        if(opc=='s'||opc=='S'){
            (*inci)++;
            printf("Hubo un incidente durante el aterrizaje en pista %d\n", pista);
        }else{
            
            printf("aterrizaje exitoso en pista %d\n", pista);
        } 
}
float porcentaje(int inci){
    float sinInci;
    int maxVuelos=MAX_VUELOS;
    return (((sinInci=maxVuelos-inci)/(float)maxVuelos)*100);
    
    
}
int masDespegues(int dp1, int dp2){
    return(dp1>dp2) ? 1:(dp1<dp2) ? 2:0;
}
int sumarVuelos(int ap1, int ap2, int dp1, int dp2){
    return (ap1+ap2+dp1+dp2);
}
int sumarDespegues(int dp1, int dp2){
    return (dp1+dp2);
}
int sumarAterrizajes(int ap1, int ap2){
    return (ap1+ap2);
}
void imprimirMasDespegues(int dp1,int dp2){
    int pista=masDespegues(dp1,dp2);
    int totalDespegues=sumarDespegues(dp1,dp2);
    if(totalDespegues){
        if(pista){
            printf("La pista con más despegues en el día es pista %d\n",pista);
        }else{
            printf("Ambas pistas tuvieron la misma cantidad de despegues\n");
        }
    }else{
        printf("No se registró nigún despegue en el día\n");
    }
}
void imprimirInforme(int ap1, int ap2, int dp1, int dp2, int inci){
    int totalDespegues=sumarDespegues(dp1, dp2);
    int totalAterrizajes=sumarAterrizajes(ap1,ap2);
    int totalVuelos=sumarVuelos(ap1,ap2,dp1,dp2);
    int pistaMasDespegues=masDespegues(dp1,dp2);
    float vuelosSinIncidentes=porcentaje(inci);
    printf("\n\n*********INFORME DEL DÍA**********\n\n");
    printf("Cantidad total de vuelos en el día: %d\n", totalVuelos);
    printf("Cantidad total de despegues en el día: %d\n", totalDespegues);
    printf("Cantidad total de aterrizajes en el día: %d\n", totalAterrizajes);
    printf("El porcentaje de vuelos sin desperfectos es del %.2f%%\n", vuelosSinIncidentes);
    imprimirMasDespegues(dp1,dp2);
    printf("\n**********FIN DEL INFORME**********\n\n");
    
}

int main()
{
    int dp1, dp2, ap1, ap2, desperfectos, maxVuelos;
    int opc;
    inicializarVariables(TODAS_LAS_VARIABLES);
    while(true){
        while(maxVuelos){
        printf("***************%d**********************\n", maxVuelos);
        printf("1 - Despegue\n");
        printf("2 - Aterrizaje\n");
        printf("*************************************\n");
        scanf(" %d", &opc);
        switch(opc){
            case 1:
                takeoff(&dp1, &dp2,&desperfectos, &maxVuelos);
                
                break;
            case 2:
                landing(&ap1, &ap2, &desperfectos,&maxVuelos);
                
                break;
           
            default: 
                printf("opción incorrecta\n");
                
                break;
            
        }
        
        
    }
    opc=0;
    printf("\n*************************************\n");
    printf("1 - Ver informe del dia\n");
    printf("2 - Comenzar nuevo día \n");
    printf("3 - Salir\n");
    printf("*************************************\n");
    scanf(" %d", &opc);
    switch(opc){
        case 1:
            imprimirInforme(ap1,ap2,dp1,dp2,desperfectos);
            break;
        case 2:
            printf("Comenzando nuevo día \n");
            inicializarVariables(TODAS_LAS_VARIABLES);
            break;
        case 3: 
            exit(0);
    }
    
        
        
    }
    

    return 0;
}

void inicializarVariables(const char *formato, ...) {
    va_list args;
    va_start(args, formato);

    while (*formato) {
        if (*formato == '%') {
            formato++;
            switch (*formato++) {
                case 'v': {
                    int *var = va_arg(args, int *);
                    *var = MAX_VUELOS;
                    break;
                }
                case 'd': {
                    int *var = va_arg(args, int *);
                    *var = 0;
                    break;
                }
                case 'f': {
                    float *var = va_arg(args, float *);
                    *var = 0.0f;
                    break;
                }
                case 'b': {
                    bool *var = va_arg(args, bool *);
                    *var = false;
                    break;
                }
                default: {
                    fprintf(stderr, "Formato no reconocido: %c\n", *(formato - 1));
                    va_end(args);
                    return;
                }
            }
        } else if (*formato == ' ') {
            // Ignora espacios en blanco
            formato++;
        } else {
            fprintf(stderr, "Carácter inesperado en la cadena de formato: %c\n", *formato);
            va_end(args);
            return;
        }
    }

    va_end(args);
}
