#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#define PORT 8080 
#define SIZE 5000
   
int main(int argc, char const *argv[]) 
{
    clock_t start, end;
    int sock = 0, valread; 
    struct sockaddr_in serv_addr;
 //-------------------
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

//-------------
   	int i = 1; 
	char buffer[1]; 
	char c[1]; 
	valread = read(sock, buffer, 1); 
	if (buffer[0] == '0') { 
		buffer[0] = '1'; 
		send(sock, buffer, 1, 0); 
		while(1){ 
			char *data = (char*) malloc(1024 *sizeof(char)); 
			char *res = (char*) malloc(9 *sizeof(char)); 

			printf("Enter your string: "); 
			scanf("%s", data); 
			int temp = strlen(data); 
			printf(nLength: %d\n", temp); 
			send(sock, data, 1024, 0); 
			free(data); 
			valread = read(sock, res, 9); 
			temp = strlen(res); 
			printf("Result: %s\n--------------------\n", res);
			free(res); 
			i++; 
		} 
	} 
	return 0; 	 
}