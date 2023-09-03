OBJECTS_SERVER=Stdtcp.c 003Stdserver.c StdThread.c DoubleLinkList.c ThreadPool.c LQueue.c
server:${OBJECTS_SERVER}
	gcc ${OBJECTS_SERVER} -o server

OBJECTS_CLIENT=Stdtcp.c 003Stdclient.c StdThread.c DoubleLinkList.c ThreadPool.c LQueue.c
client:${OBJECTS_CLIENT}
	gcc ${OBJECTS_CLIENT} -o client

.PHONY:clean

clean:
	rm -f server client

