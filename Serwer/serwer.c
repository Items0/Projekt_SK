#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct sockaddr_in addr;

int main()
{
    char tab[120];
    uint16_t port = 1235;
    const char ip[30] = "192.168.1.101";
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    int i = read(0, &tab, 50);
    if(tab[i-1]=='\n'){
        i-=1;
    }
    write(fd,tab,i);
    i=read(fd,&tab, 50);
    write(1,tab,i);
    close(fd);
    execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/shutdown", "now", NULL);   
}
