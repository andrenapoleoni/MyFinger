#include <stdio.h>
#include <utmp.h>
#include <pwd.h>
#include <time.h>
#include <string.h>
#include "MyFinger.h"


//variabili
struct utmp *ut_entry;
struct passwd *pw_entry;
char name[100];
int l1=0;
int l2=0;
char time_i[100];
char time_i2[100];
char time_string[100];
char time_string2[100];
t_dati data[100];
int dim=0;
char arraynomi[2048];
char tt1[100];
char tt2[100];




//modalità che salva i valori base per il print senza ricerca di utente
void basic()
{
    int cont=0;
    setutent();
    while ((ut_entry = getutent())!=NULL)
    {
        
        if(ut_entry->ut_type == USER_PROCESS)
        {
            
            if(strlen(ut_entry->ut_user)>l1)
            {
                l1=strlen(ut_entry->ut_user);
            }
            strcpy(data[cont].user,ut_entry->ut_user);
            strcpy(data[cont].tty,ut_entry->ut_line);
            time_t tempo =ut_entry->ut_time;
            logt(tempo);
            strcpy(data[cont].login_time,time_string);
            strcpy(data[cont].login_time2,time_string2);
            idle();
            strcpy(data[cont].idle_time,time_i);
            strcpy(data[cont].idle_time2,time_i2);
            pw_entry = getpwnam(ut_entry->ut_user);
            char gecos[100];
            strcpy(gecos,pw_entry->pw_gecos);
            char *parola1 = "", *parola2 = "", *parola3 = "", *parola4 = ""; 
            char *start = gecos;
            sistemagecos(&parola1,&parola2,&parola3,&parola4,gecos,start);
            
            if(strlen(parola1)>l2)
            {
                l2=strlen(parola1);
            }
            strcpy(data[cont].real_name,parola1);
            strcpy(data[cont].office,parola2);
            if(strcmp(parola3,"")!=0)
            {
                char number[50];
                strcpy(number,parola3);
                numbers(number);
                
                strcpy(data[cont].office_number,number);
            }
            else{strcpy(data[cont].office_number,parola3);}

            if(strcmp(parola4,"")!=0)
            {
                char number2[50];
                
                strcpy(number2,parola4);
                
                numbers(number2);
                
                strcpy(data[cont].home_phone,number2);
            }
            else{strcpy(data[cont].home_phone,parola4);}

            strcpy(data[cont].hostname,ut_entry->ut_host);
            strcpy(data[cont].shell,pw_entry->pw_shell);
            strcpy(data[cont].directory,pw_entry->pw_dir);

            cont++;
        }
    }
    dim=cont;
    cont=0;
    endutent();

}

//print di base per modalità -s o senza opzioni
void basicprint()
{

    
    printf("%-*s %-*s %-5s\t%s\t%s\t%s\t%s \n",l1+4,"Login",l2+4, "Name","Tty","Idle","Login time","Office","Office Phone");
    int a=0;
    while(strcmp(data[a].user,"")!=0)
    {
        printf("%-*s%-*s%-5s\t%s\t%s\t(%s)\t%s \n",l1+5,data[a].user,l2+5, data[a].real_name,data[a].tty,data[a].idle_time,data[a].login_time,data[a].hostname,data[a].office_number);
        a++;
    }
    a=0;
}



//recupero informazioni sul idle time
void idle()
{
    struct stat st;

    if(stat("/dev/tty",&st)!=0)
    {
        perror("Errore nel recupero dello stato del terminale");
        return;
    }
    else
    {    
        time_t idlll= time(NULL)-st.st_ctime;
        int ore = idlll/3600;
        int minuti= (idlll%3600)/60;
        if(ore<1)
        {
            if(minuti<1)
            {
                sprintf(time_i2,"%d secondi idle",idlll);
                sprintf(time_i,"%d",idlll);
            }
            else{
                sprintf(time_i2,"%d minuti %02d secondi idle",minuti, (idlll%60));
                sprintf(time_i,"%02d",minuti);
            }


        }
        else
        {
            sprintf(time_i2,"%d ore %d minuti idle",ore,minuti);
            sprintf(time_i,"%d:%02d",ore,minuti);
        }
    }
}
//funzione che setta il pattern per il tempo
void logt(time_t tempo)
{
    strftime(time_string, sizeof(time_string), "%b %d %H:%M", localtime(&tempo));
    strftime(time_string2, sizeof(time_string2), "%a %b %d %H:%M (%Z)", localtime(&tempo));
}
//funzione che salva i nomi degli utenti cercati
void aggiunginome(char* nome)
{
    char nuovonome[50];
    char arraycontrollo[100];
    strcpy(nuovonome,nome);
    strcpy(arraycontrollo,arraynomi);
    int contr=0;
    
    char *par=strtok(arraycontrollo,",");
    
    while (par!=NULL)
    {
        
        if(strcmp(par,nuovonome)==0)
        {
            contr=1;
        }
        par=strtok(NULL,",");
    }
    if(contr==0)
    {
        strcat(nuovonome,",");
        strcat(arraynomi,nuovonome);
    }
    contr=0; 
    
    /*char nuovonome[50];
    char arraycontrollo[100];
    
    // Copia sicura del nome
    strncpy(nuovonome, nome, sizeof(nuovonome) - 1);
    nuovonome[sizeof(nuovonome) - 1] = '\0';

    // Inizializza arraycontrollo come copia di arraynomi
    strncpy(arraycontrollo, arraynomi, sizeof(arraycontrollo) - 1);
    arraycontrollo[sizeof(arraycontrollo) - 1] = '\0';

    int contr = 0;
    char *par = strtok(arraycontrollo, ",");

    // Controlla se il nome esiste già in arraynomi
    while (par != NULL) {
        if (strcmp(par, nuovonome) == 0) {
            contr = 1;
            break;
        }
        par = strtok(NULL, ",");
    }

    // Aggiungi il nome a arraynomi se non esiste già
    if (contr == 0) {
        // Aggiungi la virgola al nome
        strncat(nuovonome, ",", sizeof(nuovonome) - strlen(nuovonome) - 1);
        // Aggiungi il nome a arraynomi
        strncat(arraynomi, nuovonome, sizeof(arraynomi) - strlen(arraynomi) - 1);
    }

    contr = 0; */


}


//funzione che printa la modalità -l 
void printlversion(int p)
{
    int b=0;
    while(strcmp(data[b].user,"")!=0)
    {
        
        printf("Login: %-20s Name: %s\n",data[b].user,data[b].real_name);
        printf("Directory: %-15s Shell: %s\n",data[b].directory,data[b].shell);
            
        if(strcmp(data[b].office,"")!=0 && strcmp(data[b].office_number,"")!=0 && strcmp(data[b].home_phone,"")!=0)
        {
            printf("Office: %s, %s\t\t" ,data[b].office,data[b].office_number);
            printf("Home Phone: %s\n",data[b].home_phone);
        }
        else if (strcmp(data[b].office,"")==0 && strcmp(data[b].office_number,"")==0 )
        {
            printf("Home Phone: %s\n",data[b].home_phone);
        }
        else if (strcmp(data[b].office,"")==0 && strcmp(data[b].home_phone,"")==0)
        {
            printf("Office: %s\n" ,data[b].office_number);
        }
        else if(strcmp(data[b].office_number,"")==0 && strcmp(data[b].home_phone,"")==0)
        {
            printf("Office: %s\n" ,data[b].office);
        }
        else if(strcmp(data[b].office,"")==0)
        {
            printf("Office: %s\t\t",data[b].office_number);
            printf("Home Phone: %s\n",data[b].home_phone);
        }
        else if(strcmp(data[b].office_number,"")==0)
        {
            printf("Office: %s\t\t" ,data[b].office);
            printf("Home Phone: %s\n",data[b].home_phone);

        }
        else if(strcmp(data[b].home_phone,"")==0)
        {
            printf("Office: %s, %s\n" ,data[b].office,data[b].office_number);
        }
                
        if(strcmp(data[b].tty,"*")!=0)
        {
            printf("On since %s on %s from %s\n",data[b].login_time2,data[b].tty,data[b].hostname);
            printf("\t%s\n",data[b].idle_time2);
        }
            
        mail(data[b].user);
        if(strcmp(tt1,"No Mail.")!=0)
        {
            printf("New Mail recived %s\n",tt2);
            printf("Unread since %s\n",tt1);
        }
        else
        {
            printf("%s\n\n",tt1);
        }
            
        if(p==0)
        {
            char t[256];
            char line[256];
            strcpy(t,data[b].directory);
            strcat(t,"/.plan");
            FILE *plan=fopen(t,"r");
            if (plan== NULL)
            {
            printf("No Plan.\n\n");
                
            }
            else
            {
                printf("Plan:\n");
                
                while (fgets(line, sizeof(line), plan)) 
                {
                    printf("%s", line);
                }
                fclose(plan);
            }

            strcpy(t,data[b].directory);
            strcat(t,"/.project");
            FILE *project=fopen(t,"r");
            if (project!= NULL)
            {
                printf("\nProject:\n");
                
                while (fgets(line, sizeof(line), project)) 
                {
                    printf("%s", line);
                }
                fclose(project);
            }

            strcpy(t,data[b].directory);
            strcat(t,"/.pgpkey");
            FILE *pgpkey=fopen(t,"r");
            if (pgpkey!= NULL)
            {
                printf("\nPGP key:\n");
                
                while (fgets(line, sizeof(line), pgpkey)) 
                {
                    printf("%s", line);
                }
                fclose(pgpkey);
            }           
        }    
    b++;
    }
} 

// funzione per il recupero delle informazioni con ricerca di utente
void advanced(int m)
{
    char *array=strtok(arraynomi,",");
    int a =0;
    
    while (array!=NULL)
    {
        int preso=0;
        pw_entry=getpwnam(array);
        if(pw_entry==NULL)
        {
            if(m==0)
            {
                setpwent();  // Resetta la lettura del database delle password
                while ((pw_entry = getpwent()) != NULL) 
                {
                    // Cerca se il nome completo contiene il termine di ricerca
                    if (strstr(pw_entry->pw_gecos, array) != NULL) 
                    {
                        preso=1;
                        break;
                    }
                
                }
                if(preso==0) {printf("Utente: %s,non trovato.\n",array);}
            }
            else
            {
                printf("Utente: %s,non trovato.\n",array);
            }    
        }

        if(pw_entry!=NULL)
        {
            if(strlen(pw_entry->pw_name)>l1)
            {
                l1=strlen(pw_entry->pw_name);
            }
            
           strcpy(data[a].user,pw_entry->pw_name);
           strcpy(data[a].directory,pw_entry->pw_dir);
           strcpy(data[a].shell,pw_entry->pw_shell);
           char gecos[100];
            strcpy(gecos,pw_entry->pw_gecos);
           
            
            char *parola1 = "", *parola2 = "", *parola3 = "", *parola4 = ""; 
            char *start = gecos;
            sistemagecos(&parola1,&parola2,&parola3,&parola4,gecos,start);
            
            if(strlen(parola1)>l2)
            {
                l2=strlen(parola1);
            }
            strcpy(data[a].real_name,parola1);

            strcpy(data[a].office,parola2);

            if(strcmp(parola3,"")!=0)
            {
                char number[50];
                strcpy(number,parola3);
                numbers(number);
                
                strcpy(data[a].office_number,number);
            }
            else{strcpy(data[a].office_number,parola3);}

            if(strcmp(parola4,"")!=0)
            {
                char number2[50];
            
                strcpy(number2,parola4);
            
                numbers(number2);
                
                strcpy(data[a].home_phone,number2);
            }
            else{strcpy(data[a].home_phone,parola4);}
            
            int trov=0;
            setutent();
            while ((ut_entry=getutent())!=NULL)
            {
                if(strcmp(ut_entry->ut_user,array)==0)
                {
                    trov=1;
                    
                   strcpy(data[a].tty,ut_entry->ut_line);
                   strcpy(data[a].hostname,ut_entry->ut_host); 
                   time_t tempo =ut_entry->ut_time;
                    logt(tempo);
                    strcpy(data[a].login_time,time_string);
                    strcpy(data[a].login_time2,time_string2);
                    idle();
                    strcpy(data[a].idle_time,time_i);
                    strcpy(data[a].idle_time2,time_i2);
                }
            }
            endutent();
            if(trov==0)
            {
            
                strcpy(data[a].tty,"*");
                strcpy(data[a].hostname,"*"); 
                strcpy(data[a].login_time,"No login");
                strcpy(data[a].idle_time,"*");
            }
            a++;
            trov=0;
        }
        array=strtok(NULL,",");
    }
}
//funzione che riordina i dati presenti nel gecos 
void sistemagecos(char** parola1,char** parola2,char** parola3, char** parola4,char* gecos, char* start )
{
    int index = 0;  
    int parola_num = 1;  

    while (gecos[index] != '\0') 
    {
        if (gecos[index] == ',') 
        {
            gecos[index] = '\0';
            
            switch (parola_num) 
            {
                case 1:
                    *parola1 = (*start != '\0') ? start : "";
                    break;
                case 2:
                    *parola2 = (*start != '\0') ? start : "";
                    break;
                case 3:
                    *parola3 = (*start != '\0') ? start : "";
                    break;
                case 4:
                    *parola4 = (*start != '\0') ? start : "";
                    break;
            }
            
            parola_num++;
            start = &gecos[index + 1];  
        }
        index++; 
    }

    if (parola_num <= 4) 
    {
        switch (parola_num) 
        {
            case 1:
                *parola1 = (*start != '\0') ? start : "";
                break;
            case 2:
                *parola2 = (*start != '\0') ? start : "";
                break;
            case 3:
                *parola3 = (*start != '\0') ? start : "";
                break;
            case 4:
                *parola4 = (*start != '\0') ? start : "";
                break;
        }
    }
}
// funzione che recupera i dati riguardo mail
void mail(char* ute)
{   
    struct stat st;
    char blallo[50]="/var/spool/mail/";
    strcat(blallo,ute);
    if(stat(blallo,&st)==0)
    {
        struct tm *timeInfo=localtime(&st.st_atime);
        strftime(tt1,sizeof(tt1),"%a %b %d %H:%M %Y (%Z)",timeInfo);
        timeInfo=localtime(&st.st_mtime);
        strftime(tt2,sizeof(tt2),"%a %b %d %H:%M %Y (%Z)", timeInfo);
    }
    else { strcpy(tt1,"No Mail.");}
}    
// funzione che sistema i valori numerici presi dal gecos
void numbers(char* s)
{
    char copia[20];
    
    int i =0;
    int l=strlen(s);
    if(s!=NULL)
    {
        
        if(l==4)
        {
            copia[0]='x';
            for(i =0;i<l;i++)
            {
                copia[i+1]=s[i];
            }
            copia[i+1]='\0';
            i=0;
            strcpy(s,copia);
        }
        if(l==5)
        {
            copia[0]='x';
            copia[1]=s[0];
            copia[2]='-';
            for(i =1;i<l;i++)
            {
                copia[i+2]=s[i];
            }
            copia[i+2]='\0';
            i=0;
            strcpy(s,copia);
        }
        if (l==7)
        {
            while (i<3)
            {
                copia[i]=s[i];
                i++;
            }
            if(i==3)
            {
                copia[i]='-';
                
                i++;
            }
            while((i>3)&&(i<8))
            {
                copia[i]=s[i-1];
                i++;
            }
            copia[i]='\0';
            i=0;
            strcpy(s,copia);
            

            
        }
        if(l==10)
        {
            for(i=0;s[i]!='\0';i++)
            {
                if(i<3)
                {
                    copia[i]=s[i];
                    
                }
                if(i==3)
                {
                    copia[i]='-';
                    copia[i+1]=s[i];
                    
                    
                }
                if((i>3)&&(i<6))
                {
                    copia[i+1]=s[i];
                }
                if(i==6)
                {
                    copia[i+1]='-';
                    copia[i+2]=s[i];
                    
                }
                if((i>6)&&(i<10))
                {
                    copia[i+2]=s[i];
                    
                }
            }
            copia[i+2]='\0';
            i=0;
            strcpy(s,copia);
            
        }
        if(l==11)
        {
            copia[0]='+';
            for(i=0;s[i]!='\0';i++)
            {
                if(i==0)
                {
                    copia[i+1]=s[i];
                    copia[i+2]='-';
                }
                if((i>0)&&(i<4))
                {
                
                    copia[i+2]=s[i];
                }
                if(i==4)
                {
                    copia[i+2]='-';
                    copia[i+3]=s[i];
                }
                if((i>4)&&(i<7))
                {
                    copia[i+3]=s[i];
                }
                if(i==7)
                {
                    copia[i+3]='-';
                    copia[i+4]=s[i];
                }
                if((i>7)&&(i<11))
                {
                
                    copia[i+4]=s[i];
                }
                
            }
            copia[i+4]='\0';
            i=0;
            strcpy(s,copia);
        }
        
    
    }
    
    

}
    
