#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

enum { BATCH_SIZE = 1000, BUFF_SIZE = 1024 };

int create_connection(char* node, char* service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
    };
    if (gai_err = getaddrinfo(node, service, &hint, &res)) {
        fprintf(stderr, "client: gai error: %s\n", gai_strerror(gai_err));
        return -1;
    }
    int sock = -1;
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, 0);
        if (sock < 0) {
            perror("client: socket");
            continue;
        }
        if (connect(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("client: connect");
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(res);
    return sock;
}

void write_string(int sock, char *str) {
    ssize_t i = 0;
    while (i < strlen(str)) {
        ssize_t write_bytes = write(sock, str + i, BATCH_SIZE);
        if (write_bytes < 0) {
            perror("error when writing");
            exit(EXIT_FAILURE);
        }
        i += write_bytes;
    }
}

void int_to_str(int num, char *buf) {
    ssize_t i = 0;
    while (num > 0) {
        buf[i] = (char)('0' + (num % 10));
        i++;
        num /= 10;
    }
    buf[i] = '\0';
    for (int j = 0; j < i; ++j) {
        char t = buf[j];
        buf[j] = buf[i - j - 1];
        buf[i - j - 1] = t;
    }
}

int sock_read, sock_write;

void *thread_reader(void *ptr) {
    char buff[BUFF_SIZE];
    ssize_t bytes_read;
    while ((bytes_read =  read(sock_read, buff, BATCH_SIZE)) > 0) {
        buff[bytes_read] = '\0';
        printf("%s", buff);
        fflush(stdout);
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        perror("client: not enough arguments");
        return 1;
    }

    int offset = 0;

    for (int i = 0; i < strlen(argv[1]); ++i) {
        if (argv[1][i] == ':') {
            argv[1][i] = '\0';
            offset = i;
        }
    }

    char spawn_command[] = "spawn";

    if (strcmp(argv[2], spawn_command) != 0) {
        perror("client: unknown command");
        return 1;
    }
    sock_read = create_connection(argv[1], argv[1] + offset + 1);
    sock_write = dup(sock_read);

    if (sock_read < 0) {
        perror("client: connection failed");
        return 1;
    }

    char buf[BUFF_SIZE];
    write_string(sock_write, argv[2]);
    int_to_str(argc, buf);
    write_string(sock_write, buf);
    for (int i = 3; i < argc; ++i) {
        write_string(sock_write, argv[i]);
    }

    pthread_t reader_from_server;
    pthread_create(&reader_from_server, NULL, *thread_reader, NULL);


    while (read(STDIN_FILENO, buf, BATCH_SIZE) > 0) {
        write_string(sock_write, buf);
    }
}