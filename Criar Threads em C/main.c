#include <stdio.h>
#include <pthread.h>

/*

- Criar 3 threads utilizando a biblioteca pthread.h
- Sincronizar as threads para que executem ordenamente utilizando o busy wait loop e flag
- As threads devem preencher o vetor nesta ordem: 
   TA ->'A' no primeiro elemento
   TB -> 'B' no segundo elemento
   TC -> 'C' no terceiro elemento
- O vetor tem 30 elementos
*/



char arr[30];
int letterIndex = 0;

void escreverNoArr(char letra){
	arr[letterIndex] = letra;
	letterIndex += 1;
}

/* Sincronizando threads utilizando  busy wait loop*/

pthread_t TA,TB,TC;
int flag1 = 1;
int flag2 = 0;
int flag3 = 0;

void *thread_A(void *threadno){
	while(letterIndex <= 27){
		while (flag1 == 0);
		escreverNoArr('A');
		flag2 = 1;
		flag1 = 0;
	}
	return NULL;
}

void *thread_B(void *threadno){
	while(letterIndex <= 28) {
		while (flag2 == 0);
		escreverNoArr('B');
		flag3 = 1;
		flag2 = 0;
	}

	return NULL;
}

void *thread_C(void *threadno){
	while(letterIndex <= 29) {
		while (flag3 == 0);
		escreverNoArr('C');
		flag1 = 1;
		flag3 = 0;		
	}

	return NULL;
}

void exibirVetor() {
	for(int i = 0; i < 30; i++){
		printf("%c", arr[i]);
	}
}

int main(void) {

  /* Criar 3 threads utilizando a biblioteca pthread.h*/
  
	pthread_create(&TA, NULL, thread_A, NULL);
	pthread_create(&TB, NULL, thread_B, NULL);
	pthread_create(&TC, NULL, thread_C, NULL);
	
	pthread_join(TA, NULL);
	pthread_join(TB, NULL);
	pthread_join(TC, NULL);
	
	exibirVetor();
	return 0;
	
}