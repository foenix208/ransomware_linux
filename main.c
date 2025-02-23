#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//ajouter des verification de permision de utilisation de stat pour plus de portabiliter
// changer fond ecrant linux commande


void fichier_liste(char *path){
    DIR *rep = opendir(path);
    if (rep == NULL)
        return ;
    struct dirent *file;
    while ((file = readdir(rep)) != NULL)
    {
        if (file->d_type == 8)
            printf("%s%s \n",path,file->d_name);
        if (file->d_type == 4)
        {
            char new_path[2064];
            if (strcmp("..",file->d_name) != 0 && strcmp(".",file->d_name) != 0 && strcmp("proc",file->d_name) != 0)
            {
                strcpy(new_path,path);
                strcat(strcat(new_path,file->d_name),"/");
                printf("%s \n",new_path);
                
                fichier_liste(new_path);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    fichier_liste("/");
    return 0;
}