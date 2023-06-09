#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <wait.h>

enum { BATCH_SIZE = 1000, BUFF_SIZE = 1024 };

int create_listener(char* service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
            .ai_flags = AI_PASSIVE,
    };
    if (gai_err = getaddrinfo(NULL, service, &hint, &res)) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(gai_err));
        return -1;
    }
    int sock = -1;
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, 0);
        if (sock < 0) {
            perror("socket");
            continue;
        }
        if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("bind");
            close(sock);
            sock = -1;
            continue;
        }
        if (listen(sock, SOMAXCONN) < 0) {
            perror("listen");
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(res);
    return sock;
}

void create_daemon() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("server: forking failure");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
}

void read_string(int sock, char *str) {
    read(sock, str, BATCH_SIZE);
}

int str_to_int(char *str) {
    int ans = 0;
    for (int i = 0; i < strlen(str); ++i) {
        ans *= 10;
        ans += str[i] - '0';
    }
    return ans;
}

void command_spawn(int connection_read) {
    char buff[BUFF_SIZE];
    read(connection_read, buff, BATCH_SIZE);
    int arg_cnt = str_to_int(buff);
    arg_cnt -= 3;
    char *args[BUFF_SIZE];
    for (int i = 0; i < arg_cnt; ++i) {
        args[i] = calloc(BUFF_SIZE, sizeof(char));
        read(connection_read, args[i], BATCH_SIZE);
    }
    dup2(connection_read, STDIN_FILENO);
    dup2(connection_read, STDOUT_FILENO);
    close(connection_read);
    args[arg_cnt] = NULL;
    printf("HERE\n");
    execvp(args[0], args);
}

void kill_zombies() {
    while(wait(NULL) > 0) {
        ;;;
    }
};

int main(int argc, char *argv[]) {
    create_daemon();
    int sock;
    if (argc < 2) {
        perror("not enough args");
        return 1;
    }
    if ((sock = create_listener(argv[1])) == -1) {
        return 1;
    }
    int connection_read;
    while ((connection_read = accept(sock, NULL, NULL))) {
        int connection_write = dup(connection_read);
        pid_t pid = fork();
        if (pid < 0) {
            perror("server: forking failure");
        } else if (!pid) {
            close(sock);
            char buff[BUFF_SIZE];
            char spawn_command[] = "spawn";
            read(connection_read, buff, BATCH_SIZE);

            if (strcmp(spawn_command, buff) == 0) {
                //printf("HERE1\n");
                command_spawn(connection_read);
            } else {
                perror("server: unknown command");
            }
            _exit(0);
        } else {
            close(connection_read);
            close(connection_write);
            kill_zombies();
        }
    }
}
