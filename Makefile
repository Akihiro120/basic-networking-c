build:
	gcc server.c -o server.exe -lws2_32
	gcc client.c -o client.exe -lws2_32

run_server:
	server.exe

run_client:
	client.exe
