#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[]) {
  // networking data
  char ip_address[32];
  int port = 0;
  
  // initialize winsock
  WSADATA wsaData;
  printf("INFO: Initializing WinSock\n");
  if(WSAStartup(MAKEWORD(2, 2), &wsaData)) {
    printf("ERROR: WinSock failed to load");
    return 1;
  }

  // create a socket
  printf("INFO: Creating Socket\n");
  SOCKET clientSocket;
  clientSocket = INVALID_SOCKET;
  clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(clientSocket == INVALID_SOCKET) {
    printf("ERROR: Socket failed to create\n");
    WSACleanup();
    return 1;
  }

  // get the address and port
  printf("Enter the IP Address: ");
  scanf("%s", ip_address);
  printf("Enter the PORT: ");
  scanf("%d", &port);

  // bind the socket
  printf("INFO: Connecting Socket to Server\n");
  struct sockaddr_in service;
  service.sin_family = AF_INET;
  service.sin_addr.s_addr = inet_addr(ip_address);
  service.sin_port = htons(port);
  if(connect(clientSocket, (struct sockaddr*)&service, sizeof(service)) == SOCKET_ERROR) {
    printf("ERROR: Failed to connect to server\n");
    WSACleanup();
    return 1;
  }
  printf("INFO: Successfully Connected to Server\n"); 

  char receiveBuffer[1024];
  char sendBuffer[] = "This is very cool message from the client, hi mum!";

  // send
  if (send(clientSocket, sendBuffer, strlen(sendBuffer), 0) == SOCKET_ERROR) {
    printf("ERROR: Failed to Send Response to Client Socket");
  }
 
  // receive
  printf("INFO: Receiving\n");
  int rbyteCount = recv(clientSocket, receiveBuffer, 1024, 0);  
  if (rbyteCount < 0) {
    printf("INFO: No Message Received");
  }
  printf("INFO: Received: %s", receiveBuffer);

  return 0;
}
