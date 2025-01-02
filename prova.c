#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "casa,,frutto,";  // Stringa di input
    char *parola1, *parola2, *parola3, *parola4;  // Variabili per salvare le parole

    // Inizializziamo tutte le parole a stringhe vuote
    parola1 = "";
    parola2 = "";
    parola3 = "";
    parola4 = "";

    int index = 0;  // Indice per scorrere la stringa
    int parola_num = 1;  // Contatore delle parole

    // Buffer per salvare temporaneamente le parole
    char *start = str;

    // Cicliamo su tutta la stringa fino alla fine
    while (str[index] != '\0') {
        if (str[index] == ',') {
            // Impostiamo la fine della parola attuale
            str[index] = '\0';
            
            // Salviamo la parola nella variabile corretta
            switch (parola_num) {
                case 1:
                    parola1 = (*start != '\0') ? start : "";
                    break;
                case 2:
                    parola2 = (*start != '\0') ? start : "";
                    break;
                case 3:
                    parola3 = (*start != '\0') ? start : "";
                    break;
                case 4:
                    parola4 = (*start != '\0') ? start : "";
                    break;
            }

            // Avanziamo alla parola successiva
            parola_num++;
            start = &str[index + 1];  // Punto di partenza della prossima parola
        }
        index++;  // Passiamo al prossimo carattere
    }

    // Caso particolare: se la stringa termina con una virgola
    if (parola_num <= 4) {
        switch (parola_num) {
            case 1:
                parola1 = (*start != '\0') ? start : "";
                break;
            case 2:
                parola2 = (*start != '\0') ? start : "";
                break;
            case 3:
                parola3 = (*start != '\0') ? start : "";
                break;
            case 4:
                parola4 = (*start != '\0') ? start : "";
                break;
        }
    }

    // Output per verificare il risultato
    printf("Parola 1: %s\n", parola1 );
    printf("Parola 2: %s\n", parola2);
    printf("Parola 3: %s\n", parola3);
    printf("Parola 4: %s\n", parola4);

    return 0;
}

