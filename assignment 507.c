#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int main()
{
    float fc,fs;
    
    float input_x[3];/*This is an Array which Stores latest 3 input samples*/
    float output_y[3];/*This is an Array which Stores latest 3 filtered values*/
    int input_samplescount=0;/*Sample Count*/
    printf("enter the cut off freq");
    scanf("%f",&fc);
    printf("enter the sampling freq"); 
    scanf("%f",&fs);
    float rad =(fc*3.14)/fs;/*Calculating the Angle part of tan*/
    float angle=tan(rad);/*Tan of rad*/
    float square=pow(angle,2);
    float divisor=1+angle*1.414+square;/*Common Divisor of Values in Filter Equation*/
    char element[10];/*THis is the value which is read from Sample.csv file*/
    FILE* ipf = fopen("Samples.csv", "r");
    FILE * temp1 = fopen("in.txt", "w");
    FILE * temp2 = fopen("filteredout.txt", "w");
    while(fgetc(ipf)!=EOF){
    fscanf(ipf,  "%s", element);
    fprintf(temp1, "%d %f \n", input_samplescount, atof(element));  
    input_samplescount++;
    }
    /*Reading the Sample.csv and filtering the corresponding values*/
    rewind(ipf);
    input_samplescount=0;   
    while(fgetc(ipf)!=EOF){
    fscanf(ipf,  "%s", element);

       if(input_samplescount<2){
       fprintf(temp2, "%d %f \n", input_samplescount, atof(element));
       input_x[2-input_samplescount]=atof(element);
       output_y[2-input_samplescount]=atof(element);
       input_samplescount++;
       }else{
       input_x[0]=atof(element);
       output_y[0]=(square*input_x[0]+2*square*input_x[1]+square*input_x[2]-(2*square-2)*output_y[1]-(1-1.414*angle+square)*output_y[2])/(1+angle*1.414+square);
       fprintf(temp2, "%d %f \n", input_samplescount, output_y[0]);
       output_y[2]=output_y[1];
       output_y[1]=output_y[0];
       input_x[2]=input_x[1];
       input_x[1]=input_x[0];
       input_samplescount++;
       }    
    }
     /*comands for GNU plot*/
    
         char * commandsForGnuplot1[] = {"set title \"Raw Ecg\"","set xlabel \"time\"",
"set ylabel \"Amplitude\"", "plot [100:600][400:580] 'raw.temp' with l"};
    char * commandsForGnuplot2[] = {"set title \"Filtered Ecg\"","set xlabel \"time\"",
"set ylabel \"Amplitude\"", "plot [100:600][400:580] 'filtered.temp' with l"};
    FILE * gnuplotPipe1 = popen ("gnuplot -persistent", "w");
    FILE * gnuplotPipe2 = popen ("gnuplot -persistent", "w");    
    /*opening shell and passing the arguments to the gnu plot*/
    for (int iCounter=0; iCounter < 4; iCounter++)
    {
    fprintf(gnuplotPipe1, "%s \n", commandsForGnuplot1[iCounter]); //Send commands to gnuplot one by one.
    }
    for (int iCounter=0; iCounter < 4; iCounter++)
    {
    fprintf(gnuplotPipe2, "%s \n", commandsForGnuplot2[iCounter]); //Send commands to gnuplot one by one.
    }
    fclose(ipf);
    fclose(temp1);
    fclose(temp2);
    fclose(gnuplotPipe1);
    return 0;
}
