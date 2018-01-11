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
    //char ip[30] = "192.168.1.102";//INADDR_ANY;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int fd = socket(PF_INET, SOCK_STREAM, 0); // --SOCKET()
    int on = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    bind(fd, (struct sockaddr*)&addr, sizeof(addr)); // --BIND()
    listen(fd, 5);         //fd zawsze ten z funkcji socket, liczba oczekujacych polaczen // --LISTEN()
    int new_fd;
    printf("Works\n");
    while(1)
    {
        new_fd = accept(fd, (struct sockaddr*)&addr, &rozmiar); // blokujaca, przekazuje IP i adres portu klienta, zwraca deskryptor nowego gniazda - sluzy tylko do komunikacji z tym klientem, gniazdo glowne jest stosowane tylko do akceptacji // --ACCEPT()
        //int i = read(new_fd, &tab, sizeof(tab));
        printf("Zgloszenie\n");
        int last = 0;
        int suma = 0;
        char * ptr;
        int eho = 0;
        do {
            last = read(new_fd, &(tab[suma]), sizeof(tab)-suma);
            suma += last;
            printf("--%s--last:%d,suma:%d\n",tab, last, suma);
            ptr = strchr(tab, 'X');
            eho++;
            if (eho > 15) break;
        }
        while (ptr == NULL);
        *ptr = '\0';
        printf("%s\n",tab);
        if (!strcmp(tab, "shutdown"))
        {
            strcpy(odp, "shutdown confirm");
            write(new_fd, odp, strlen(odp));
            printf("odpowiedzialem\n");
            close(new_fd);
            close(fd);
            sleep(5);
            execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/shutdown", "now", NULL); 
        }
	else
        {
            printf("error\n");
            strcpy(odp, "shutdown error");
            write(new_fd, odp, strlen(odp));
        }
        //printf("Klient %s message: %s\n", addr.sin_addr.s_addr, tab);
	//strcpy(odp, "shutdown now");
       // write(new_fd, odp, strlen(odp));
	//write(1,"das", 3);
        
          
    };
    
    close(fd);
    
}
