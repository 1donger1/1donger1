#include "client.h"

int main()
{
    int client_socket = Connect_Server();
	Ask_server(client_socket);
	close(client_socket);
}
