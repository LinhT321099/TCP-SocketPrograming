#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <time.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
#define PORT 8080 
#define SIZE 5000 
#define REPEAT 100000 
void computeLPSArray(char* pat, int M, int* lps); 

int KMPSearch(char* pat, char* txt) 
{ 
	int M = strlen(pat); 
	int N = strlen(txt);
	int res = 0; 
	int lps[M]; 
	computeLPSArray(pat, M, lps); 
	int i = 0; 
	int j = 0; 
	white (i < N) { 	
		if (pat[j] == txt[i]) {
			j++; 
			i++; 
		} 	
		if (j== M) 
		{ 
			res++; 
			j = lps[j - 1]; 
		} 
		else if (i < N && pat[j] != txt[i]) {
			if (j != 0) 
				j = lps[j - 1]; 
			else i = i + 1; 
		} 
	} 
	return res; 
} 

void computeLPSArray(char* pat, int M, int* lps) { 
	int len = 0; 
	lps[0] = 0; 
	int i = 1; 
	while (i < M) { 
		if (pat[i] == pat[len]) { 
			len++; 
			lps[i] = len; 
			i++; 
		}
		else 
		{ 
			if (len != 0) { 
				len = lps[len - 1]; 
			} 
			else 
			{ 
				lps[i] = 0; 
				i++; 
			} 
		} 
	} 
} 

int main(int argc, char const *argv[]) { 
	clock_t start, end; 
	int server id, new socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
		perror("socket failed"); 
		exit(EXIT FAILURE); 
	} 
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port htons( PORT ); 
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<O) { 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<O) { 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 

	//-------------------------
	char buffer[1];
	buffer[0] = '0';
	send(new_socket, buffer, 1, 0);
	valread = read(new_socket, buffer, 1);
	if (buffer[0] == '1') 
	{
		while(1) {
			pthread_t *threads;
			threads = (pthread t *) malloc (Thread * sizeof(pthread t)); 
			struct search seara data; 
			void *status; 
			int res = 0, count = 0, i; 
			char *data = (char *) malloc (1024 * sizeof(char)); 
			char *ress = (char *) malloc (9 * sizeof(char)); 
			
			valread = read(new_socket, data, 1024); 
			int temp = strlen(data); 
			printf("String Search: %s \nIts length: %d\n", data, temp); 
			start = clock(); 
			FILE *file = fopen("input.txt", "r");
			while (count < REPEAT) { 
				fread(search, 1, SIZE, file);
				res = res + KMPSearch(data, search);
				count++;
			}
			sprintf(ress, "%d", res); 
			send(new_socket, ress, 9, 0); 
			end = clock(); 
			printf("Time search: %Lf \n---------\n)", (long double)(end-start)/(CLOCKS PER SEC*Thread)); 
			count = 0;
			res = 0;
			i++;
			free(ress); 
			free(threads); 
		} 
	} 
	return 0; 
}
