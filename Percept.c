#include <stdio.h>
#include <stdlib.h>


int main()
{
    int x,y,trainingData[10][10],c, desired[4];
    double weights[3] = {0.0,0.0,0.0};
    double net = 0.0;
    double rate = 0.1, iterError;
    int i,j, iter = 0, out, error, totalError = 0;
    FILE* fp = fopen("test.csv","r");

    //Graceful exit if file not found
    if(fp == NULL)
    {
        printf("Cannot open file");
        exit(-1);
    }


    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 5; x++)
        {
            c = fgetc(fp);
            if((char)c != '\n' && (char)c != '\r')
            {
                trainingData[y][x] = c - '0';
            }
        }
    }
    fclose(fp);

    for(x = 0; x < 4; x++)
    {
        desired[x] = trainingData[x][3];
    }

      do{
       printf("Iteration:  %d   ************************************************\n", iter);
       for(i = 0; i < 4; i++)
        {
            for (j = 0; j < 3; j++)
            {
                net += trainingData[i][j]*weights[j];
            }

        if(net <= 0.5)
            out = 0;
        else
            out = 1;

        error = desired[i] - out;

        if(error != 0)
        {
            totalError++;
        }

        iterError = ((double)totalError/4);
        for (j = 0; j < 3; j++)
        {
            weights[j] += (rate * error) * trainingData[i][j];
        }

        net = 0;

        printf("%4.1f  %4.1f   %4.1f         iterationError = %02.5f\n",weights[0],weights[1],weights[2],iterError);
        }
        iter++;
        totalError = 0;
    }while(iterError != 0 || iter < 9);

    return(0);
}
