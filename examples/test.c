#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>

#include <edu.h>

int main(int argc, char *argv[])
{
    int fd, rc;
    struct edu_xor_cmd cmd_xor;
    struct edu_intr_cmd cmd_intr;
    struct edu_factorial_cmd cmd_fact;
    
    fd = open("/dev/edu0", O_RDWR);
    if (fd == -1) {
        printf("failed to open /dev/edu0 (rc = %d)\n", errno);
        return 1;
    }

    cmd_xor.val_in = 0x0;
    rc = ioctl(fd, EDU_IOCTL_XOR, &cmd_xor);
    if (rc) {
        printf("EDU_IOCTL_XOR failed (rc = %d)\n", rc);
        return 1;
    }

    printf("cmd_xor.val_out = 0x%08"PRIx32"\n", cmd_xor.val_out);

    // cmd_intr.val_in = 0xdeadf00d;
    // rc = ioctl(fd, EDU_IOCTL_INTR, &cmd_intr);
    // if (rc) {
    //     printf("EDU_IOCTL_INTR failed (rc = %d)\n", rc);
    //     return 1;
    // }

    // printf("check dmesg fot 'got interrupted' message...\n");

    cmd_fact.val_in = 5;
    cmd_fact.val_out = 0;
    rc = ioctl(fd, EDU_IOCTL_FACTORIAL, &cmd_fact);
    if (rc)
    {
        printf("EDU_IOCTL_FACTORAIL failed (rc = %d)\n", cmd_fact.val_out);
        return 1;
    }

    printf("cmd_fact.val_out = %d\n", cmd_fact.val_out);

    return 0;
}
