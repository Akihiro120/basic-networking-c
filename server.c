#include <stdio.h>
#include <WinSock2.h>
#include <winsock.h>

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
  SOCKET serverSocket;
  serverSocket = INVALID_SOCKET;
  serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(serverSocket == INVALID_SOCKET) {
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
  printf("INFO: Binding Socket\n");
  struct sockaddr_in service;
  service.sin_family = AF_INET;
  service.sin_addr.s_addr = inet_addr(ip_address);
  service.sin_port = htons(port);
  if(bind(serverSocket, (struct sockaddr*)&service, sizeof(service)) == SOCKET_ERROR) {
    printf("ERROR: Failed to bind socket, %d\n", WSAGetLastError());
    closesocket(serverSocket);
    WSACleanup();
    return 1;
  }

  // listen for connections
  printf("INFO: Listening\n");
  if(listen(serverSocket, 1) == SOCKET_ERROR) {
    printf("ERROR: Failed to Listen on Socket");
  }

  // accept incoming connections
  SOCKET acceptSocket;
  acceptSocket = accept(serverSocket, NULL, NULL);
  if(acceptSocket == INVALID_SOCKET) {
    printf("ERROR: Failed to accept connection");
    WSACleanup();
    return 1;
  }
  
  char buffer[1024];
  char response[] = "This is a very awesome message from the server, 1234 you are poor!";

  // receiving data
  printf("INFO: Receiving Data\n");
  int rbyteCount = recv(acceptSocket, buffer, 1024, 0);
  if(rbyteCount < 0) {
    printf("INFO: No Message Received\n");
  }
  printf("Received: %s", buffer);

  // sending a response
  if (send(acceptSocket, response, strlen(response), 0) == SOCKET_ERROR) {
    printf("ERROR: Failed to Send Response to Client Socket");
  }

  return 0;
}
