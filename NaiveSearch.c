#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <time.h>
#include <stdlib.h>

#define PORT 8080
#define SIZE 5000 
#define REPEAT 100000

int funct(char *a, char *b) 
{
	int i, j, res = 0, temp = 0;
	int len1 = strlen(a), len2 = strlen(b);
	for (i = 0; i < len2; i++)
	{
		for (j = 0; j < len1; j++)
		{
			if (a[j] != b[j+i]) 
			{
				temp = 1;
				break;
			}
		}
		if (temp != 1) res++;
		temp = 0;
	}
	return res;
}
int main(int argc, char const *argv[]) 
{ 
    clock_t start, end;
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address);  

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }
//---------------
    char buffer[1]; 

    int count = 0, i = 1;; 
    int res = 0;
    

    buffer[0] = '0';
    send(new_socket , buffer , 1, 0 );  
    valread = read(new_socket , buffer, 1); 
    if (buffer[0] == '1')
    {

      while(1){
	char *search = (char *) malloc (SIZE *sizeof(char));	
	char *data = (char *) malloc (1024 * sizeof(char));
	char *ress = (char *) malloc (9 * sizeof(char));
	
	valread = read(new_socket, data, 1024);
	int temp = strlen(data);
	start = clock();
       	FILE *file = fopen("input.txt", "r");
	printf("String Search: %s \nIts length: %d\n", data, temp);
	while (count < REPEAT)
	{
		fseek(file, SIZE*count, 0);
		fread(search, 1, SIZE, file);
 		res = res + funct(data, search); 
		count++;
	}
	sprintf(ress, "%d", res);
	//printf("%s", ress);
	send(new_socket, ress, 9, 0);	
	end = clock();
	printf("Time search: %Lf \n-------------\n", (long double)(end-start)/CLOCKS_PER_SEC);
	count = 0;
        res = 0;
	i++;
	free(ress);
	free(data);
      }
    }  
    return 0; 
} 
