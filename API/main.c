#include <stdio.h>
#include "api.h"
#include "unistd.h"
#include <stdbool.h>


int main(){
   
   // Declaração de variáveis.
   char path_file[256];
   bool flag_stay = true;
   int opcao;
   int mem_sel;
   int address;
  
   if (api_init() == -1){
      printf("Erro ao inicializar a API.\n");
      return 0;
   }

   printf("API Inicializada!\n\n");

   // Loop só encerra quando flag_stay for falso.
   while (flag_stay) {
       printf("Escolha uma opção:\n\n");
       printf("1. Vizinho mais próximo (Zoom In)\n");
       printf("2. Replicação de pixel\n");
       printf("3. Vizinho mais próximo (Zoom Out)\n");
       printf("4. Média de blocos\n");
       printf("5. Carregar imagem\n");
       printf("6. Reset\n");
       printf("7. Carregar pixel\n");
       printf("0. Sair\n\n");
       printf("Opção: ");
       scanf("%d", &opcao);
       printf("\n");

       // Chama de funções de acordo com o caso escolhido.
       switch (opcao) {
           case 1:
               api_vmp_in();
               system("clear");
               break;
           case 2:
               api_repixel();
               system("clear");
               break;
           case 3:
               api_vmp_out();
               system("clear");
               break;
           case 4:
               api_mblocos();
               system("clear");
               break;
           case 5:
               printf("Diretório da imagem: ");
               scanf("%s", path_file);

               if (api_store(path_file) < 0)
                    printf("Erro ao acessar o arquivo: %s.\n", path_file);
               
               api_refresh_cpa();
               
               break;
           case 6:
               api_reset_cpa();
               break;
           case 7:
               // Pedido de memória (A - original, C - de trabalho) e endereço pretendidos para leitura.
               printf("Selecione a memória (0: A; 1: C): ");
               scanf("%d", &mem_sel);

               printf("Selecione o endereço: ");
               scanf("%d", &address);

               printf("\nPixel do Endereço %d na Memória %d: %d\n", address, mem_sel, api_load(mem_sel, address));       
               
               break;
           case 0:
               // Ao escolher sair (0), a API é finalizada e flag_stay se torna falsa, terminando o loop.
               api_finalize();
               flag_stay = false;
               system("clear");
               break;
           default:
               printf("\nOpção inválida");
               break;       
       }
   }


   printf("API Finalizada!\n");


   return 0;
}







