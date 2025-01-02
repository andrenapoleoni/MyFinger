



typedef struct dati_utente
{
    /* data */
    char user[100];
    char real_name[100];
    char directory[100];
    char shell[100];
    char tty[20];
    char login_time[100];
    char login_time2[100];
    char office[100];
    char office_number[100];
    char home_phone[100];
    char idle_time[100];
    char idle_time2[100];
    char mail[100];
    char plan[100];
    char hostname[100];
}t_dati;


void basic();

void basicprint();

void idle();

void logt(time_t tempo);

void aggiunginome(char* nome);

void printlversion(int p);

void advanced(int m);

void mail();

void sistemanumeri(char** parola1,char** parola2,char** parola3, char** parola4,char* gecos, char* start );

void numbers(char* n);

