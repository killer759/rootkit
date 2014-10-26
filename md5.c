#include <openssl/md5.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    MD5_CTX lctx;
    unsigned char digest[16];
    char md5msg[40];
    int i;
    int fd;
    struct stat status;
    char *file_name = argv[1];
    char *data;

    MD5_Init(&lctx);

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        perror("error : ");
        exit(0);
    }
    fstat(fd, &status);

    data = (char *)malloc(status.st_size);
    read (fd, data, status.st_size);

    MD5_Update(&lctx, data, status.st_size);
    MD5_Final(digest, &lctx);

    for (i = 0; i < sizeof(digest); ++i)
    {
        sprintf(md5msg+(i*2), "%02x", digest[i]);
    }
    printf ("%s\n", md5msg);
    free(data);
}
