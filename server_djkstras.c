#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>  //write
#include<netinet/in.h>
#define INFINITY 9999
#define MAX 60

int main() {
  
    char msg[256] = "server talking to you";


    int s_socket = socket(AF_INET,SOCK_STREAM,0);
    if(s_socket<0){
        printf("Socket creation failed!\n");
    } else {
        printf("Socket created successfully\n");
    }

    struct sockaddr_in s_address;
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(9003);
    s_address.sin_addr.s_addr = INADDR_ANY;

    //Binding Address to Socket
    int status = bind(s_socket,(struct sockaddr *)&s_address,sizeof(s_address));
    if(status < 0){
        printf("Binging not successful\n");
    } else {
        printf("Successful Binding\n");
    }

    //Listening 
    int listen_status;
    listen_status = listen(s_socket,5);
    if(listen_status <0){
        printf("Listening problems\n");
    } else {
        printf("Waiting...\n");
    }

    //Accepting client sockets
    int client_socket, size = sizeof(struct sockaddr_in);
    struct sockaddr_in client_address;
    client_socket = accept(s_socket,(struct sockaddr *)&client_socket,&size);
    if(client_socket < 0){
        printf("Accept failed\n");
    } else {
        printf("Client accepted\n");
    }  printf("Listening problems\n");

    int G[MAX][MAX],n,startnode;
    int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
   
    if(recv(client_socket, &n ,sizeof(n),0) < 0){
        printf("Couldn't recieve vertex..............");
        exit(0);
    } 
    if(recv(client_socket, &G ,sizeof(G),0) < 0){
        printf("Couldn't recieve vertex..............");
        exit(0);
    }
    if(recv(client_socket, &startnode ,sizeof(startnode),0) < 0){
        printf("Couldn't recieve vertex...........");
        exit(0);
    }

    printf("\nCalculating Shortest Path for all nodes -----------------------------------------------\n");

    for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
	

	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
	
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
				
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
    printf("Shortest path calculated using Dijikt's Algorithm.\n---------------------------------\n\nSending to client...\n");

    if(send(client_socket, &distance ,sizeof(distance),0) < 0){
        printf("Couldn't send arrived time");
        exit(0);
    }

    if(send(client_socket, &pred ,sizeof(pred),0) < 0){
        printf("Couldn't send arrived time");
        exit(0);
    }

    printf("---------------------------------\n\nAll shortest path are send successfully.\n\n");
    
    close(s_socket);
    return 0;
}


