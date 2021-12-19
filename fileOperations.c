/* 

  Warning : This is not implemented - It is simply proof of concept for dealing with a file of employees 
  
*/

/*

  File Operations
  
*/

int fileReader (empType *emps, char *s) {

    int i = 0;
    FILE *fp;
    fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        perror(FILE_NAME);
        printf ("Error : fOpen failed\n");
        return 1;
    }

    //printf ("File open at : %p.\n\n", fp);

    while (fgets(s, MAX_INPUT, fp) != EOF) {
        if (parseEmp(s, &emps[i], 0)) i++;    // we got a valid employee!
        else
            INVALID_FILE
    }

    fclose(fp);

    return 0;

}
