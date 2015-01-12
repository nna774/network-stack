#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tun", O_RDWR)) < 0 )
        return puts("err");//tun_alloc_old(dev);

    memset(&ifr, 0, sizeof(ifr));

    /* フラグ: IFF_TUN   - TUN デバイス (イーサネットのヘッダなし) 
     *         IFF_TAP   - TAP デバイス
     *
     *         IFF_NO_PI - パケットの情報を提供しない
     */

    ifr.ifr_flags = IFF_TUN; 
    if( *dev )
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        close(fd);
        return err;
    }
    strcpy(dev, ifr.ifr_name);
    return fd;
}

int main(){
    char str[]="tun%d";
    tun_alloc(str);
    int i;
    scanf("%d",&i);
    return 0;
}
