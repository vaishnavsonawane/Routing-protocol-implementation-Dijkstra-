#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h> 

#include<netinet/in.h>
#define INFINITY 9999
#define MAX 60

int main() {

    
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket <0){
        printf("Cannot creat the socket\n");
    } else {
        printf("Socket created\n");
    }

    //Creating sever Address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(9003);
    

    //Connection to the Server
    int connection_staus = connect(client_socket,(struct sockaddr *) &server_address, sizeof(server_address));
    if(connection_staus <0){
        printf("Can't connect to sever\n");
    } else {
        printf("connection established\n");
    }

    int G[MAX][MAX],i,j,n,u;
    int distance[MAX], pred[MAX];
    printf("\npls give Number of Vertices : ");
    scanf("%d", &n);

    printf("\npls give the distance between nodes in matrix form :\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);
	
    printf("\npls give the starting node :");
	scanf("%d",&u);

    while(u>=n || u<0){
	    printf("Please Enter valid starting node.");
        printf("\npls give the starting node : ");
	    scanf("%d",&u);
    }


    if(send(client_socket, &n ,sizeof(n),0) < 0){
        printf("Couldn't send vertices");
        exit(0);
        // break;
    }
    if(send(client_socket, &G ,sizeof(G),0) < 0){
        printf("Couldn't send matrix");
        exit(0);
        // break;
    }
    if(send(client_socket, &u ,sizeof(u),0) < 0){
        printf("Couldn't send starting vertex");
        exit(0);
        // break;
    }

    printf("\nAll nodes are send successfully to the server for finding Shortest Path.\n\n ---------------------------------\n\n");

    printf("Recieving shortest path from server................\n");
    if(recv(client_socket, &distance ,sizeof(distance),0) < 0){
        printf("Couldn't recieve distance");
        exit(0);
    } 

    if(recv(client_socket, &pred ,sizeof(pred),0) < 0){
        printf("Couldn't recieve pred");
        exit(0);
    } 

    for(i=0;i<n;i++)
		if(i!=u)
		{
			printf("\n\nDistance between node %d to %d : %d",u,i,distance[i]);
			printf("\nPath : %d ",i);
			
			j=i;
			do
			{
				j=pred[j];
				printf("<- %d ",j);
			}while(j!=u);
	}

    printf("\n\nShortest path for all nodes are received successfully.\n\n");
    
    close(client_socket);
    return 0;
}



