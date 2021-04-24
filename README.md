
Unix Shell
This unix shell has 2 main function;

1-Interactive Mode
Interactive mode takes commands to call the system like shells that we use normally in order to used symbols("|" and ";").
2-Batch Mode
In the batch mode, system takes file (.bat) and reads file with a given order. When it takes the "quit" command , it quits.

There are helper functions as;

1-scan() : Takes the command line and scans it, returns the number of characters.
2-systemcall() : Useful function to direct commands to main shell.
3-receive() : Sends the procceses to thread by using pthread() functions.
4-split_process() : Splits command line to process with a given order.

We used pthread library and properties of pthread library like pthread_create, pthread_join, pthread_exit, pthread_t and we used them to distribute processes to threads.
 
Alperen ASLAN
Yiğithan ÖCAL
