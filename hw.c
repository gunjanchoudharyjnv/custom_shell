#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
  //int i=
  // helloWorld();
  // getprocesstimedetails();
  // for(int i=0;i<2;i++){
    fork();
    // yield();

  // }
  //cprintf("%d",i);
  getprocesstimedetails();
  exit();
}

// int
// main(void)
// {
//     printf(1, "Total Number of Open Files: %d\n", numOpenFiles());
//     int fd;
//     fd = open("backup", O_CREATE | O_RDWR);
    
//     // fd = open("backup", O_CREATE | O_RDWR);
//     printf(1, "Total Number of Open Files: %d\n", numOpenFiles());
//     close(fd);
//     printf(1, "Total Number of Open Files: %d\n", numOpenFiles());
//     exit();
// }

// int main(int argc, char *argv[])
// {
//   printf(1,"Memory allocated till now: %d bytes\n", memAlloc());
//   sleep(10);

//   char* x = sbrk(1024);
//   printf(1,"Memory allocated till now: %d bytes\n", memAlloc());
  
//   //free(x);
//   char* y = sbrk(4096);
//   printf(1,"Memory allocated till now: %d bytes\n", memAlloc());


//   printf(1,"Memory allocated till now: %d bytes\n", memAlloc());
  

//   char* z = sbrk(-10);
//   printf(1,"Memory allocated till now: %d bytes\n", memAlloc());

//   char* a = sbrk(-20000);
//   printf(1,"Memory allocated till now: %d bytes\n", memAlloc());



//   free(x);
//   free(y);
//   free(z);  
//   free(a);
//   exit();
// }


// $ testcase1
// Memory allocated till now: 32768 bytes
// Memory allocated till now: 33792 bytes
// Memory allocated till now: 37888 bytes
// Memory allocated till now: 37888 bytes
// Memory allocated till now: 37878 bytes
// Memory allocated till now: 17878 bytes