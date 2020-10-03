/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
        char server_message[2000], client_message[2000];                 // Sending values from the server and receive from the server we need this

        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));     // Set all bits of the padding field//
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;               /* Address family = Internet */
        server_addr.sin_port = htons(2001);               // Set port number, using htons function to use proper byte order */
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* Set IP address to localhost */
		
		
		
		// BINDING FUNCTION
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)    // Bind the address struct to the socket.  /
	                            	//bind() passes file descriptor, the address structure,and the length of the address structure
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)                               //This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a "backlog queue" until accept() call accepts the connection.
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        while(1==1){

        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
        
        client_size = sizeof(client_addr);
		
		
		
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);          // heree particular client k liye new socket create kr rhaa ha
        
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
        
        printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		       //inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation
        
        //Receive the message from the client
        
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        

        char* abc;
        abc=strtok(client_message," ");
        printf("%s\n",abc);
        char client_mes2[1000];

        char alpha[100];
        int l5=strlen(abc);
        int j=0;
        for(int i=l5-1;i>=0;i--)
        {
            alpha[j]=abc[i];
            j++;

        }
        strcpy(client_mes2,alpha);
        printf("%s  \n","strcpy client alpha ::");
        printf("%s \n",client_mes2);


        while(abc!=NULL)
        {
            
        
        

        abc=strtok(NULL," ");
        printf("%s \n",abc);

        for(int i=l5-1;i>=0;i--)
        {
            alpha[j]=abc[i];
            j++;

        }
        j=0;
        printf("%s  \n","for loop alpha::");
        printf("%s",alpha);

        

        int len2=strlen(client_mes2);
        int k=0;
        int lengt=strlen(abc)+len2;
        
        for(int i=len2;i<lengt;i++)
        {
            client_mes2[i]=abc[k];
            k++;
            

        }
        k=0;
        //strcat(client_mes2,alpha);

       printf("%s  \n","end of while loop abc ");
       printf("%s",abc);

        }
        printf("%s  \n","client mesage::");
        printf("%s",client_mes2);
        int len1=strlen(client_mes2);
        client_mes2[len1]=NULL;
        printf("Client Message: %s\n",client_mes2);
        
        //Send the message back to client
        
        //strcpy(server_message, client_message);
        strcpy(server_message, "hello this is server your id is :");
        int l=strlen(client_message);
        int l2=strlen(server_message);
        
        //char abc=client_message[l-1];
        //printf("%c",abc);
        //strcat(server_message,client_message[l-1]);
        server_message[l2]=client_message[l-1];
        server_message[l2+1]="\0";
        
        
        
        
        if (send(client_sock, server_message, strlen(server_message),0)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
              
        //Closing the Socket
        }
        close(client_sock);
        close(socket_desc);
        return 0;       
}
