#include <iostream>
#include <sys/types.h>  // fork, getpid
#include <unistd.h>
#include <sys/wait.h>   // wait
#include <queue>

using namespace std;

queue<int> pids;



int main(int argc, char* argv[])
{
   int child1, child2, child3;
   int int1, int2, int3, int4;
   int fd[2];

   // create shared pipe
   pipe(fd);
   child1 = fork();
   
   // ONLY fork again if it's the parent! 
   if (child1 == 0)   // child process
   {
      int1 = 3;
      close(fd[0]);
      write(fd[1], &int1, sizeof(int));

      int1++;
      write(fd[1], &int1, sizeof(int));

      int1++;
      write(fd[1], &int1, sizeof(int));
   }
   else               // parent process
   {
      close(fd[1]);
      read(fd[0], &int2, sizeof(int));
      read(fd[0], &int3, sizeof(int));
      // read(fd[0], &int4, sizeof(int));
      
      // cout << "number passed is: " << int2 << endl;
      pipe(fd);
      child2 = fork();

      if (child2 == 0)  // second child
      {
         int1 = 103;
         close(fd[0]);
         write(fd[1], &int1, sizeof(int));
      }
      else              // still the parent
      {
         close(fd[1]);
         read(fd[0], &int4, sizeof(int));
      }

   }
   
   // cout << "child1 value: " << child1 << endl;
   // cout << "parent ID : " << getppid() << endl;
   // cout << "process ID running: " << getpid() << endl;

   // int child2 = fork();
   // cout << "child2: " << child2 << endl;
   
   // there are now 3 processes running this code
   // int proc = getpid();
   // if (child1 == 0)
   // {
   //    cout << "child is running!" << endl;
   // }
   // else if (child1 > 0)
   // {
   //    cout << "parent is running!" << endl;
   // }
   // else
   // {
   //    cout << "else clause fired: why?????" << endl;
   // }   
   
   // cout << getpid() << " still running before exit..." << endl;
   // waitpid(child1, NULL, 0);
   // waitpid(child2, NULL, 0);
   wait(&child1);
   wait(&child2);

   // can i pull both messages out now?
   cout << "number passed is: " << int2 << endl;
   cout << "number passed is: " << int3 << endl;
   cout << "number passed is: " << int4 << endl;
   cout << getpid() << " exiting..." << endl;
   exit(0);

   return 0;
}