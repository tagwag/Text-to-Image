/******************************************
 *  This program was created by Tag Wagley
 *  for educational purposes and should be
 *  used only for its intented purpose.
 *  The creator is not liable for any
 *  result of misuse of this program.
 *  Open source, but please give me credit.
 *  Feel free to donate to my venmo @tagwag
 *  Proceeds will aid my education.
 *****************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argC, char** argV){
    char *h;
    char ch;
    char in[100], out[100];
    
    //introduction
    for (int x = 0; x < 64; x++)
        printf("\n");
    printf("********* Welcome to the Text to Image experience! **********\n");
    printf("** This was created by Tag Wagley for educational purposes **\n");
    printf("*********** Type x at anytime to exit the program ***********\n");
    for (int x = 0; x < 5; x++)
        printf("\n");
    
jump1:
    printf("%3sEnter the name of file you would like to translate: ", " ");
    fgets(in,100,stdin);
    strtok(in, "\n");    // a weird way to remove the newline character quickly, don't judge me.
    if (strncmp (in,"x",1) == 0)
    {
        printf("\n");
        printf("%3sThank you for using Text to Image!\n", " ");
        printf("\n");
        return 0;
    }
    
    //make sure we can open the input file...
    FILE* inputFile = fopen(in, "r");
    if(inputFile == NULL ){
        printf("\n");
        printf("%3sCould not open %s!!\n", " ", in);
        printf("%3sBe sure that the file you are trying to translate is\nfound within the same folder as the executable!\n", " ");
        printf("\n");
        fclose(inputFile);
        goto jump1;
    }
    
jump2:
    printf("%3sEnter name of the image file to Create or Overwrite: ", " ");
    fgets(out,100,stdin);
    strtok(out, "\n");   //stop judging me lol
    if (strncmp (out,"x",1) == 0)
    {
        printf("\n");
        printf("%3sThank you for using Text to Image!\n", " ");
        printf("\n");
        return 0;
    }
    
    h = strstr(out, ".pbm"); //check if the file extension is included. If not, yell at the user.
    FILE* outputFile = fopen(out, "a");
    if((strlen(out) > 5) && (h != NULL)){
        //this error chech is for my sanity. If the file doesn't exist, it creates a new file.
        if(outputFile == NULL){
            printf("\n");
            printf("%3sCould not open %s!!\n", " ", out);
            printf("\n");
            fclose(outputFile);
            goto jump2;
        }
    }
    else {
        printf("\n");
        printf("%3sERROR: PLEASE ENTER THE NEW IMAGE NAME FOLLOWED BY \".pbm\"\n", " ");
        printf("%3sExample: newImage.pbm\n", " ");
        printf("\n");
        fclose(outputFile);
        goto jump2;
    }
    
    //find out how many bytes are in the file
    //Move file pointer to the end of file.
    fseek(inputFile,0,SEEK_END);
    
    //Get the current position of the file pointer.
    int fileSize=ftell(inputFile);
    
    //calulate here the size of the new .pbm
    int bounds = sqrt(((float)fileSize/3))+1;
    
    //now rewind the file
    fseek(inputFile,0,SEEK_SET);
    
    //fprintf(outputFile,"PF\n344\n344\n-1.0000\n"); // for a 32bit color file
    fprintf(outputFile,"P6\n%d\n%d\n65535\n",bounds,bounds);
    
    //simply copying the file source to output file. This will also include the input file headers.
    while( ( ch = fgetc(inputFile) ) != EOF ) {
        fputc(ch, outputFile);
        fprintf(outputFile, " ");
    }
    printf("%3sImage translation created.\n\n", " ");
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}



