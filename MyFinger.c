#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <utmp.h>
#include "Myfingerfunc.c"





int main(int argc, char *argv[])
{
    int controllo=0;
    if (argc==1)
    {
        basic();
        basicprint();
    }  
    else
    {
        
        int l=0;
        int s=0;
        int m=0;
        int p=0;
        

        for (int i=1;i<argc;i++)
        {
            if(strcmp(argv[i],"-l")==0) {l=1;}
            
            else if(strcmp(argv[i],"-s")==0) {s=1;}
            
            else if(strcmp(argv[i],"-m")==0) {m=1;}
            
            else if(strcmp(argv[i],"-p")==0) {p=1;}
            
            else if(strncmp(argv[i],"-",1)==0) {printf(" %s Opzione non valida ",argv[i]);}
            
            else
            {
                char utente[100];
                strcpy(utente,argv[i]);
               aggiunginome(utente);
               controllo=1;
            }
            
        }

        if(controllo==0)
        {
            basic();
            //controllo quale stampa effettuare
            if(l!=0) {printlversion(p);}
            
            else if(s!=0) {basicprint();}
        }
        else
        {
            advanced(m);
            if(l!=0 | (l==0 && s==0)) {printlversion(p);}
            
            else if(s!=0) {basicprint();}  
        }
        
    }  
}