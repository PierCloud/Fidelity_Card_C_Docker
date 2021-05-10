/*
 * File:   main.c
 * Author: piergu94
 *
 * Created on 26 agosto 2015, 21.59
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

/*
 * (centro commerciale e fidelity card)
 */
typedef struct{
    int importo;
    int punti[MAX];
    int contatore_punti;
    int data;
}acquisto;

typedef struct{
    char nome[MAX];
    char cognome[MAX];
    int codice;
    int data_nascita;
    float contatore_saldo_punti_fidelity_total;
    float contatore_punti_totale;
    acquisto array_acquisti[MAX];
}fidelity_card;

typedef struct{
    fidelity_card array_card[MAX];
    int numero_carte;
    int numero_acqu;
}centro_commerciale;


void inserimento_nuova_carta_cliente(centro_commerciale*p_centro);
int cerca_fidelity_card(centro_commerciale*p_centro);
void visualizza_fidelity_card(centro_commerciale*p_centro,int posix);
void nuovo_acquisto(centro_commerciale*p_centro);
void utilizzo_punti(centro_commerciale*p_centro);
void visualizza_estratto_punti(centro_commerciale*p_centro);
void stampa_lista_card(centro_commerciale*p_centro);
void elimina_card(centro_commerciale*p_centro);
void elimina_card_bis(centro_commerciale*p_centro);
int cerca_per_codice(centro_commerciale*p_centro,int codice);

int main(int argc, char** argv) {

    centro_commerciale mio_centro_comm;
    centro_commerciale*p_mio_centro_commerciale=NULL;
    p_mio_centro_commerciale=&mio_centro_comm;
    p_mio_centro_commerciale->numero_carte=0;
    p_mio_centro_commerciale->numero_acqu=0;
    p_mio_centro_commerciale->array_card[p_mio_centro_commerciale->numero_carte].contatore_saldo_punti_fidelity_total=0;
    p_mio_centro_commerciale->array_card[p_mio_centro_commerciale->numero_carte].contatore_punti_totale=0;
    int scelta;

    do{
        printf("\n-BENVENUTI IN COMMERCIAL CENTER-");
        printf("\n****(FIDELITY-CARD) MENU ****");
        printf("\nEFFETTUA UNA SCELTA");
        printf("\n[1]_crea una nuova fidelity card a cliente");
        printf("\n[2]_aggiorna fidelity card acquista");
        printf("\n[3]_utilizzo punti");
        printf("\n[4]_visualizza fidelity card");
        printf("\n[5]_stampa lista card");
        printf("\n[6]_seleziona per ricerca");
        printf("\n[7]_elimina card");
        printf("\n[8]_elimina card per struttura");
        printf("\n[0]_esci");
        printf("\nScelta: ");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                printf("\n-FZ.INSERIMENTO CARTA A CLIENTE");
                inserimento_nuova_carta_cliente(p_mio_centro_commerciale);
                printf("\n______________________________________");
                break;

            case 2:
                printf("\nFZ.NUOVO ACQUISTO AUMENTO SALDI FIDELITY");
                nuovo_acquisto(p_mio_centro_commerciale);
                printf("\n______________________________________");
                break;

            case 3:
                printf("\nFZ.UTILIZZO PUNTI");
                utilizzo_punti(p_mio_centro_commerciale);
                printf("\n______________________________________");
                break;

            case 4:
                printf("\nFZ.VISUALIZZA FIDELITY CARD CON ESTRATTO PUNTI");
                visualizza_estratto_punti(p_mio_centro_commerciale);
                printf("\n______________________________________");
                break;

            case 5:
                printf("\nFZ.STAMPA LISTA CARD");
                stampa_lista_card(p_mio_centro_commerciale);
                printf("\n______________________________________");
                break;

            case 6:
                printf("\n-FZ.CERCA CARTA CLIENTE");
                cerca_fidelity_card(p_mio_centro_commerciale);
                printf("\n______________________________________");
                break;

            case 7:
                printf("\nFZ.ELIMINA CARD");
                elimina_card(p_mio_centro_commerciale);
                printf("\n_______________________________________");
                break;
            case 0:
                printf("\nUSCITA IN CORSO");
                system("PAUSE");
                break;

            case 8:
                elimina_card_bis(p_mio_centro_commerciale);
                break;

            default:
                printf("\nOPERAZIONE NON PRESENTE");
                break;
        }
    }while(scelta!=0);


    return (EXIT_SUCCESS);
}

void inserimento_nuova_carta_cliente(centro_commerciale*p_centro){
    int scelta;
    int result;
    int codice;
    do{

        if(p_centro->numero_carte==MAX){
            printf("\nLISTA FIDELITY CARD PIENA");
            printf("\nVUOI ELIMINARE CARD PER INSERIRNE UN'ALTRA?");
            printf("\nSI=1...NO ed ESCI=0");
            printf("\nScelta: ");
            scanf("%d",&scelta);
            if(scelta==1){
                elimina_card(p_centro);
                return;
            }
            if(scelta==0){
                return;
            }

        }
        printf("\nINSERISCI CARD CLIENTE");
        printf("\nInserire nome carta cliente: ");
        scanf("%s",p_centro->array_card[p_centro->numero_carte].nome);
        printf("\nInserire cognome carte cliente: ");
        scanf("%s",p_centro->array_card[p_centro->numero_carte].cognome);
        printf("\nInserire data di nascita cliente: ");
        scanf("%d",&p_centro->array_card[p_centro->numero_carte].data_nascita);
        do{
            printf("\nInserire codice carta cliente: ");
            scanf("%d",&codice);
            result=cerca_per_codice(p_centro,codice);
            if(codice==result){
                printf("\nCodice card gia esistente e' pregato di inserire nuovo codice card");
            }
            else{
                p_centro->array_card[p_centro->numero_carte].codice=codice;
            }
        }while(codice==result);
        p_centro->numero_carte++;

        system("cls");
        printf("\nVUOI CONTINUARE AD INSERIRE FEDELITY CARD A NUOVO UTENTE?");
        printf("\nSI=1...NO=0");
        printf("\nScelta: ");
        scanf("%d",&scelta);
        system("cls");
    }while(scelta!=0);
}
int cerca_fidelity_card(centro_commerciale*p_centro){
    int scelta;
    int i;
    int codice;
    do{
        if(p_centro->numero_carte==0){
            printf("\nLISTA CARD VUOTA");
            return-2;
        }
        printf("\n***FUNZIONE RICERCA***");
        printf("\nSCEGLI DATO IDENTIFICATIVO PER RICERCARE FIDELITY CARD CLIENTE");
        printf("\n***MENU RICERCA***");
        printf("\n[1]_cerca per nome");
        printf("\n[2]_cerca per cognome");
        printf("\n[3]_cerca per codice");
        printf("\n[0]_esci");
        printf("\nScelta: ");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                printf("\n-FZ.CERCA PER NOME");
                char nome[MAX];
                printf("\nINSERISCI NOME DA RICERCARE: ");
                scanf("%s",nome);
                for(i=0;i<p_centro->numero_carte;i++){
                    if(strcmp(nome,p_centro->array_card[i].nome)==0){
                        printf("\nCliente trovato in posizione: %d",i);
                        printf("\nVUOI CONTINARE A CERCARE?");
                        printf("\nSI=1...NO=0");
                        printf("\nScelta: ");
                        scanf("%d",&scelta);
                        if(scelta==1){
                            cerca_fidelity_card(p_centro);
                        }
                        if(scelta==0){
                            return i;
                        }
                    }
                }
                return-1;
                break;

            case 2:
                printf("\n-FZ.CERCA PER COGNOME");
                char cognome[MAX];
                printf("\nINSERISCI COGNOME DA RICERCARE: ");
                scanf("%s",cognome);
                for(i=0;i<p_centro->numero_carte;i++){
                    if(strcmp(nome,p_centro->array_card[i].cognome)==0){
                        printf("\nCliente trovato in posizione: %d",i);
                        printf("\nVUOI CONTINARE A CERCARE?");
                        printf("\nSI=1...NO=0");
                        printf("\nScelta: ");
                        scanf("%d",&scelta);
                        if(scelta==1){
                            cerca_fidelity_card(p_centro);
                        }
                        if(scelta==0){
                            return i;
                        }
                    }
                }
                return-1;
                break;

            case 3:
                printf("\n-FZ.CERCA PER CODICE");
                printf("\nINSERISCI CODICE DA RICERCARE: ");
                scanf("%d",&codice);
                for(i=0;i<p_centro->numero_carte;i++){
                    if(codice==p_centro->array_card[i].codice){
                        printf("\nCliente trovato in posizione: %d",i);
                        printf("\nVUOI CONTINARE A CERCARE?");
                        printf("\nSI=1...NO=0");
                        printf("\nScelta: ");
                        scanf("%d",&scelta);
                        if(scelta==1){
                            cerca_fidelity_card(p_centro);
                        }
                        if(scelta==0){
                            return i;
                        }
                    }
                }
                return-1;
                break;

            case 0:
                printf("\nUSCITA IN CORSO");
                system("PAUSE");
                break;

            default:
                printf("\nOperazione non presente");
                break;
        }
    }while(scelta!=0);
}
void visualizza_fidelity_card(centro_commerciale*p_centro,int posix){
    printf("\n***SCHEMA VISUALIZZAZIONE DATI FIDELITY CARD***");
    printf("\n_______________________________");
    printf("\n -NOME_CARD_CLIENT:%s\n -COGNOME_CARD_CLIENT:%s\n -CODICE_CARD_CLIENT:%d\n -DATA_NASCITA_CLIENT:%d",p_centro->array_card[posix].nome,p_centro->array_card[posix].cognome,p_centro->array_card[posix].codice,p_centro->array_card[posix].data_nascita);
    printf("\n_______________________________");
}
void nuovo_acquisto(centro_commerciale*p_centro){
    int result;
    int scelta;
    float risultato;
    float total;
    do{
        result=cerca_fidelity_card(p_centro);
        if(result==-1){
            printf("\nCLIENTE NON TROVATO");
            printf("\nVUOI AGGIUNGERLO IN MEMORIA O USCIRE?");
            printf("\nAGGIUNNGI=1...ESCI=0");
            printf("\nSCELTA: ");
            scanf("%d",&scelta);
            if(scelta==1){
                system("cls");
                printf("\nFZ:INSRIMENTO A MEMORIA CLIENTE NON TROVATO");
                printf("\n-Dopo aver aggiunto in memoria il cliente si torna al menu-");
                inserimento_nuova_carta_cliente(p_centro);
                return;
            }
            else{
                system("cls");
                return;
            }
        }

        visualizza_fidelity_card(p_centro,result);
        printf("\nI DATI FIDELITY CORRISPONDO AL CLIENTE CARD RICERCATO?");
        printf("\nSI=1...NO=0");
        printf("\nScelta: ");
        scanf("%d",&scelta);
        if(scelta==0){
            system("cls");
            printf("\nI DATI NON CORRISPONDO VERRA RIPORTATO AL MENU INZIALE");
            return;
        }
        printf("\nPunti fidelity attuali del cliente cercato:%2f",p_centro->array_card[result].contatore_saldo_punti_fidelity_total);
        printf("\n---Inserimento nuovi aquisti---");
        printf("\nInserire importo acquisto: ");
        scanf("%d",&p_centro->array_card[result].array_acquisti[p_centro->numero_acqu].importo);
        printf("\nInserire data di acquisto: ");
        scanf("%d",&p_centro->array_card[result].array_acquisti[p_centro->numero_acqu].data);
        risultato=(p_centro->array_card[result].array_acquisti[p_centro->numero_acqu].importo*5/100);
        printf("\n numero punti saldo fidelity sull'acquisto avvenuto in  data:%d \nsono esattamente:%2f",p_centro->array_card[result].array_acquisti[p_centro->numero_acqu].data,risultato);
        total=p_centro->array_card[result].contatore_saldo_punti_fidelity_total+risultato;
        p_centro->numero_acqu++;

        do{
            printf("\nE' PREGATO DI INSERIRE IL VALORE SALDI TOTALE IN MEMORIA\n(inserisca valore saldi): ");
            scanf("%f",&p_centro->array_card[result].contatore_punti_totale);
            printf("\nINSERIRE NUMERO ESATTO DI SALDI ALTRIMENTI IL PROGRAMMA NON FARE INSERIRE IL DATO IN MEMORIA");
        }while(p_centro->array_card[result].contatore_punti_totale!=total);


        printf("\nPUNTI FEDELITY CARD CLIENT AGGIORNATI");
        printf("\nVisualizzare punti aggiornati cliente?");
        printf("\nSI=1...NO=0");
        printf("\nScelta:");
        scanf("%d",&scelta);
        if(scelta==1){
            printf("\nPUNTI AGGIORNATI=%2f",p_centro->array_card[result].contatore_punti_totale);
            return;
        }
    }while(scelta!=0);

}
void utilizzo_punti(centro_commerciale*p_centro){
    int result;
    float importo;
    float contatore_medio_saldi;
    int scelta;
    result=cerca_fidelity_card(p_centro);
    if(result==-1){
        printf("\nCLIENTE NON TROVATO");
        printf("\nVUOI AGGIUNGERLO IN MEMORIA O USCIRE?");
        printf("\nAGGIUNNGI=1...ESCI=0");
        printf("\nSCELTA: ");
        scanf("%d",&scelta);
        if(scelta==1){
            system("cls");
            printf("\nFZ:INSRIMENTO A MEMORIA CLIENTE NON TROVATO");
            printf("\n-Dopo aver aggiunto in memoria il cliente si torna al menu-");
            inserimento_nuova_carta_cliente(p_centro);
            return;
        }
        else{
            system("cls");
            return;
        }
    }
    contatore_medio_saldi=p_centro->array_card[result].contatore_punti_totale;
    printf("\nPUNTI ATTUALI:%2f",p_centro->array_card[result].contatore_punti_totale);
    printf("\nQUANTI PUNTI VUOLE UTILIZZARE? DIGITARE IMPORTO DA USARE: ");
    scanf("%f",&importo);
    if(importo>p_centro->array_card[result].contatore_punti_totale){
        printf("\nATTENZIONE IMPORTO NON VALIDO NON RISPECCHIA LE CARATTERISTICHE MEDIE");
    }

    p_centro->array_card[result].contatore_punti_totale=contatore_medio_saldi-importo;
    printf("\nVISALIZZAZIONE PUNTI AGGIORNATI RIMANENTI DOPO LO SCARICO DATI:%2f",p_centro->array_card[result].contatore_punti_totale);
    return;

}
void visualizza_estratto_punti(centro_commerciale*p_centro){
    int result;
    int scelta;
    result=cerca_fidelity_card(p_centro);
    if(result==-1){
        printf("\nCLIENTE NON TROVATO");
        printf("\nVUOI AGGIUNGERLO IN MEMORIA O USCIRE?");
        printf("\nAGGIUNNGI=1...ESCI=0");
        printf("\nSCELTA: ");
        scanf("%d",&scelta);
        if(scelta==1){
            system("cls");
            printf("\nFZ:INSRIMENTO A MEMORIA CLIENTE NON TROVATO");
            printf("\n-Dopo aver aggiunto in memoria il cliente si torna al menu-");
            inserimento_nuova_carta_cliente(p_centro);
            return;
        }
        else{
            system("cls");
            return;
        }
    }
    printf("\n-NOME:%s\n -COGNOME:%s\n -ESTRATTO_PUNTI:%2f",p_centro->array_card[result].nome,p_centro->array_card[result].cognome,p_centro->array_card[result].contatore_punti_totale);
}
void stampa_lista_card(centro_commerciale*p_centro){
    int i=0;
    if(p_centro->numero_carte==0){
        printf("\nLISTA CARD VUOTA");
        return;
    }
    system("cls");
    do{
        visualizza_fidelity_card(p_centro,i);
        i++;
    }while(i<p_centro->numero_carte);
}
int cerca_per_codice(centro_commerciale*p_centro,int codice){
    int i=0;
    for(i=0;i<p_centro->numero_carte;i++){
        if(codice==p_centro->array_card[i].codice){
            return codice;
        }
    }
    return-1;
}
void elimina_card(centro_commerciale*p_centro){
    int result;
    int scelta;
    int i;
    result=cerca_fidelity_card(p_centro);
    if(result==-1){
        printf("\nATTEZIONE CLIENTE NON TROVATO");
        return;
    }
    visualizza_fidelity_card(p_centro,result);
    printf("\nVUOI ELIMINARE IL CLIENTE FIDLITY CARD?");
    printf("\nSI=1...NO=0");
    printf("\nScelta: ");
    scanf("%d",&scelta);
    if(scelta==1){
        if(result==p_centro->numero_carte-1){
            p_centro->numero_carte--;
            return;
        }
        for(i=result;i<p_centro->numero_carte;i++){
            p_centro->array_card[i].codice=p_centro->array_card[i+1].codice;
            strcmp(p_centro->array_card[i].cognome,p_centro->array_card[i+1].cognome);
            strcmp(p_centro->array_card[i].nome,p_centro->array_card[i+1].nome);
            p_centro->array_card[i].contatore_punti_totale=p_centro->array_card[i+1].contatore_punti_totale;
            p_centro->array_card[i].data_nascita=p_centro->array_card[i+1].data_nascita;
        }
        p_centro->numero_carte--;
        printf("\nCLIENTE ELIMINATO CON SUCCESSO");
    }
    if(scelta==0){
        printf("\nUSCITA IN CORSO");
        system("PAUSE");
        return;
    }

}
void elimina_card_bis(centro_commerciale*p_centro){
    int result;
    int scelta;
    int i;
    result=cerca_fidelity_card(p_centro);
    if(result==-1){
        printf("\nAttenzione cliente fidelyiti non trovato");
        return;
    }
    visualizza_fidelity_card(p_centro,result);

    printf("\nVUOI ELIMINARE IL CLIENTE FIDLITY CARD?");
    printf("\nSI=1...NO=0");
    printf("\nScelta: ");
    scanf("%d",&scelta);
    if(scelta==0){
        return;
    }
    if(scelta==1){
        if(result==p_centro->numero_carte-1){
            p_centro->numero_carte--;
            return;
        }
        for(i=result;i<p_centro->numero_carte;i++){
            p_centro->array_card[i]=p_centro->array_card[i+1];

        }
        p_centro->numero_carte--;
        printf("\nCARD ELIMINATA");
    }
}