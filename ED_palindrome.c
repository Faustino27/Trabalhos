#include<stdio.h>
#include<string.h>

int main(){
	char linha[255], palindrome[5], palindrome2[5];

	int i = 0, npalindrome = 0, j = 0;

	while(scanf("%s", linha) > 0){
		i = 0;
		j = 0;
		npalindrome = 0;
		while(linha[i] != '\0'){
			if(npalindrome == 0 && linha[i+2] == linha[i]){
				palindrome[0] = linha[i];
				palindrome[1] = linha[i+1];
				palindrome[2] = linha[i+2];
				palindrome[3] = '\0';
				npalindrome++; 
			}
			else if(npalindrome == 1 && linha[i+2] == linha[i]){
				palindrome2[0] = linha[i];
				palindrome2[1] = linha[i+1];
				palindrome2[2] = linha[i+2];
				palindrome2[3] = '\0';
				npalindrome++;
			}
			else if(npalindrome == 0 && linha[i+3] == linha[i] && linha[i+1] == linha[i+2]){
				palindrome[0] = linha[i];
				palindrome[1] = linha[i+1];
				palindrome[2] = linha[i+2];
				palindrome[3] = linha[i+3];
				palindrome[4] = '\0';
				npalindrome++;
			}
			else if(npalindrome == 1 && linha[i+3] == linha[i] && linha[i+1] == linha[i+2]){
				palindrome2[0] = linha[i];
				palindrome2[1] = linha[i+1];
				palindrome2[2] = linha[i+2];
				palindrome2[3] = linha[i+3];
				palindrome2[4] = '\0';
				npalindrome++; 
			}
			i++;
			if(npalindrome == 2){
				if(strcmp(palindrome, palindrome2) != 0 && strstr(palindrome, palindrome2) == NULL ){
					while(linha[j] != ' ' && linha[j] != '\0'){
						printf("%c", linha[j]);
						j++;
					}
					printf("\n");
					while(linha[i] != ' ' && linha[i] != '\0')
						i++;
				}
				else
					npalindrome--;
			}
		}
	}
}