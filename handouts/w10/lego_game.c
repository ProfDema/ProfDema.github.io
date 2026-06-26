#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>    /* Internet domain header */
#include <arpa/inet.h>     /* only needed on mac */

/*
 * TODO: Step 2
 * Change this value to customize the port per student
 */
#define PORT 54321
#define LEGO_PIECES 10
#define MAX_BUF 128
#define MAX_QUEUE 2

/*
 * TODO: Step 4
 * Complete this function, which accepts a new connection
 * and returns the file descriptor of the new socket.
 * The input parameters are the file descriptor
 * of a listener socket and the name of the player
 * (which should be "one" or "two") that is about to
 * connect.
 *
 */
int accept_player(int listen_soc, char *name) {

    // you must complete this function
    
    char msg[MAX_BUF];
    sprintf(msg, "Hello player %s! Please wait for your turn to begin.\r\n", name);

    // you must complete this function
    
    return 0;
}


/*
 * TODO: Step 5
 * Complete this function, which sends a string msg to
 * players with socket descriptors player1 and player2.
 */
void write_to_players(char *msg, int player1, int player2) {
    // you must complete this function
}

/* 
 * TODO: Step 6
 *
 * Read message from a player's socket and return a valid move
 * a valid move is a text integer between 1 and 3 followed by a \r\n
 * 
 * Hint: read from the socket into a buffer, loop over the buffer
 *   until you find \r\n and then replace the \r with \0 to make a 
 *   string. Then use strtol to convert to an integer. If the result
 *   isn't in range, write a message to the socket and repeat. 
 */
int read_a_move(int socket) {
    int move = -1;

    // you must complete this function
    
    return -1;
}

int main() {
    // create socket
    int listen_soc = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_soc == -1) {
        perror("server: socket");
        exit(1);
    }

    // initialize server address    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);  
    memset(&server.sin_zero, 0, 8);
    server.sin_addr.s_addr = INADDR_ANY;

    // This sets an option on the socket so that its port can be reused right
    // away. Since you are likely to run, stop, edit, compile and rerun your
    // server fairly quickly, this will mean you can reuse the same port.
    int on = 1;
    int status = setsockopt(listen_soc, SOL_SOCKET, SO_REUSEADDR, 
                            (const char *) &on, sizeof(on));
    if (status == -1) {
        perror("setsockopt -- REUSEADDR");
    }


    // bind socket to an address
    if (bind(listen_soc, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) {
      perror("server: bind");
      close(listen_soc);
      exit(1);
    } 


    // Set up a queue in the kernel to hold pending connections.
    if (listen(listen_soc, MAX_QUEUE) < 0) {
        perror("listen");
        exit(1);
    }
  
    /*
     * TODO: Step 4
     * You should be calling your new helper function accept_player() around here.
     */
    struct sockaddr_in client_addr;
    unsigned int client_len = sizeof(struct sockaddr_in);
    client_addr.sin_family = AF_INET;

    int client_socket = accept(listen_soc, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1) {
        perror("accept");
        return -1;
    } 


    /*
     * TODO: Step 8
     * Fix up the game logic below
     */

    int item = LEGO_PIECES;
    int round = 0;
    while (item > 0) {
        // Announce the current status to all players
        char status_update[MAX_BUF];
        sprintf(status_update, "There are %d lego pieces left.\r\n", item);
        write(client_socket, status_update, strlen(status_update)); // REMOVE ME
        //write_to_players(status_update, FIXME, FIXME);

        // Read a move from one player. Alternating between two players.
        int curr_player = client_socket; // FIXME
        char *msg = "Please enter a move between 1-3.\r\n";
        write(curr_player, msg, strlen(msg));
        int move = read_a_move(curr_player);
        item -= move;
        round += 1;

        // Prompt the player to wait
        if (item != 0) {
            msg = "Thanks! Please wait for the other player to move.\r\n";
            write(curr_player, msg, strlen(msg));
        }
    }

    // Announce the winner
    char winner_announcement[MAX_BUF];
    sprintf(winner_announcement, "Winner is player %d!\r\n", (round - 1) % 2 + 1);

    //write_to_players(winner_announcement, FIXME, FIXME);

    return 0;
}


