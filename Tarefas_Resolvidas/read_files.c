#include <stdio.h>
#include <dirent.h>

int main(){

    //Estrutura que percorre os arquivos do diretório
    struct dirent **namelist;
    int file_num; // número de arquivos no diretório
    file_num = scandir(".", &namelist, 0, alphasort);
    
    if (file_num < 0)
      perror("Não existem arquivos no diretório");
    else {
      while(file_num--) {
        printf("%s\n", namelist[file_num]->d_name);
        free(namelist[file_num]);
      }
    }

}

