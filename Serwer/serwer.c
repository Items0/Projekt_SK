#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in addr;
socklen_t rozmiar;
int main()
{
    char tab[100];
    char odp[100];
    uint16_t port = 1235;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int fd = socket(PF_INET, SOCK_STREAM, 0); // --SOCKET()
    int on = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    bind(fd, (struct sockaddr*)&addr, sizeof(addr)); // --BIND()
    listen(fd, 5); // --LISTEN()
    int new_fd;
    printf("Works\n");
    while(1)
    {
        new_fd = accept(fd, (struct sockaddr*)&addr, &rozmiar); // --ACCEPT()
        printf("Accept connection\n");
        int last = 0;
        int sum = 0;
        char * ptr;
        do {
            last = read(new_fd, &(tab[sum]), sizeof(tab)-sum);
            sum += last;
            printf("--%s-- last: %d, sum: %d\n",tab, last, sum);
            ptr = strchr(tab, 'X');
        }
        while (ptr == NULL); //wczytuje wiadomosc, dopoki napotka na 'X'
        *ptr = '\0';
        printf("%s\n",tab);
        if (!strcmp(tab, "shutdown")) //komunikat prawidlowy
        {
            strcpy(odp, "shutdown confirmX");
            write(new_fd, odp, strlen(odp));
            printf("Confirmation was sent\n");
            close(new_fd);
            close(fd);
            sleep(5); //tylko po to, aby zdazyc przeczytac konsole
            execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/shutdown", "now", NULL); 
        }
	else //komunikat nieprawidlowy
        {
            printf("Error\n");
            strcpy(odp, "shutdown errorX");
            write(new_fd, odp, strlen(odp));
            close(new_fd);
        }
    };
    close(fd);
}
