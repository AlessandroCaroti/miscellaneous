#CC=gcc
CFLAGS=  -Ilib
#CFLAGS= -Wall -pedantic -Ilib
BIN_DIR = bin
LIB_DIR = lib

LDFLAGS = -L$(BIN_DIR) -lclientserver -lrt
CLIENTSERVER_LIB=$(BIN_DIR)/libclientserver.a
CLIENT=$(BIN_DIR)/client
SERVER=$(BIN_DIR)/server
CLIENT_OBJS=$(BIN_DIR)/client.o
SERVER_OBJS=$(BIN_DIR)/server.o

EXECS = $(CLIENT) $(SERVER)

all: $(EXECS)

$(EXECS): | $(DATA_DIR)

#common library
$(CLIENTSERVER_LIB): $(BIN_DIR)/utils.o $(BIN_DIR)/fail.o $(BIN_DIR)/addr_utlis.o | $(BIN_DIR)
	ar rcs $@ $(BIN_DIR)/*.o
$(BIN_DIR)/utils.o: $(LIB_DIR)/associationFinder_lib.h $(LIB_DIR)/utils.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(LIB_DIR)/utils.c
$(BIN_DIR)/fail.o: $(LIB_DIR)/associationFinder_lib.h $(LIB_DIR)/fail.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(LIB_DIR)/fail.c
$(BIN_DIR)/addr_utlis.o: $(LIB_DIR)/associationFinder_lib.h $(LIB_DIR)/addr_utlis.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(LIB_DIR)/addr_utlis.c

#client
$(CLIENT): $(CLIENT_OBJS) $(CLIENTSERVER_LIB) | $(BIN_DIR)
	$(CC) -o $@ $(CLIENT_OBJS) $(LDFLAGS)
$(BIN_DIR)/client.o: client/client.c client/client_function.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ client/client.c

#Server
$(SERVER): $(SERVER_OBJS) $(CLIENTSERVER_LIB) | $(BIN_DIR)
	$(CC) -o $@ $(SERVER_OBJS) $(LDFLAGS)
$(BIN_DIR)/server.o: server/server.c server/server_function.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ server/server.c

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)