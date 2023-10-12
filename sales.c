#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fptr;

/*
    Print basic monthly report information, with an array of
    months and an array of sales numbers as the parameters
*/
void printReport(char* months[], float sales[]) {
    printf("Monthly sales report for 2023:\n");
    printf("Month\t\tSales\n");

    /*
        Iterate from index 0 to 12 and print each month and its
        corresponding sales number, formatted appropriately
    */
    for (int i = 0; i < 12; i++) {
        /*
            formatting depends on the strlen of the month, otherwise months
            with longer names will have different spacing than those with shorter names
        */
        if (strlen(months[i]) < 8) {
            printf("%s\t\t$%0.2f\n", months[i], sales[i]);
        }
        else {
            printf("%s\t$%0.2f\n", months[i], sales[i]);
        }
    }
    printf("\n");   // print an empty line after the section for better readability
}

/*
    Print the summary info of the report, including the minimum, maximum, and average
    sales values
*/
void printSummary(char* months[], float sales[]) {
    /*
        keeping track of the index of the values makes it easier to grab the corresponding month

        initial index is 0 so that the for loop is able to compare its first iteration with a default index
    */
    int minIndex = 0;
    int maxIndex = 0;
    float average = sales[0];   // the for loop iterates from february onward, so the average starts with the value of january
    for (int i = 1; i < 12; i++) {
        // change the min or max index depending on if the current index is a better fit 
        if (sales[i] < sales[minIndex]) {
            minIndex = i;
        }
        else if (sales[i] > sales[maxIndex]) {
            maxIndex = i;
        }
        average += sales[i];
    }
    average /= 12;

    // print the min, max, and avg sales and their corresponding months, formatted appropriately
    printf("Sales summary:\n");
    printf("Minimum sales:\t$%0.2f\t(%s)\n", sales[minIndex], months[minIndex]);
    printf("Maximum sales:\t$%0.2f\t(%s)\n", sales[maxIndex], months[maxIndex]);
    printf("Average sales:\t$%0.2f\n\n", average);
}

/*
    Print the Six-Month Moving Average Report, with spans from Jan-Jun to Jul-Dec
*/
void printSixMonthReport(char* months[], float sales[]) {
    printf("Six-Month Moving Average Report:\n");
    float average = 0;
    /*
        the outer for loop iterates through the different six-month spans (Jan-Jun, to Feb-Jul, etc.)
        the inner loop iterates through each month within a span
    */
    for (int i = 0; i <= 6; i++) {  // i is the index of the first month of the span, and only iterates through Jul (Jul-Dec and can't end past Dec)
        for (int j = i; j < i + 6; j++) {   // j iterates through each month after month i
            average += sales[j];
        }
        average /= 6;
        
        // print each span and its sales average, formatted depending on the strlen of the months of the span
        if (strlen(months[i]) < 8) {    // shorter month names need two tab spaces (\t)
            if (strlen(months[i+5]) < 8) {
                printf("%s\t\t-\t%s\t\t$%0.2f\n", months[i], months[i+5], average);
            }
            else {  // if its a longer month name it only needs one \t
                printf("%s\t\t-\t%s\t$%0.2f\n", months[i], months[i+5], average);
            }
        }
        else {
            if (strlen(months[i+5]) < 8) {
                printf("%s\t-\t%s\t\t$%0.2f\n", months[i], months[i+5], average);
            }
            else {
                printf("%s\t-\t%s\t$%0.2f\n", months[i], months[i+5], average);
            }
        }

        // reset the average after each iteration so the one span doesn't affect another
        average = 0;
    }

    printf("\n");   // print a new line after the section
}

/*
    Print the sales report from the month with the highest value first
    to the month with the lowest value last
*/
void printHighToLow(char* months[], float sales[]) {
    printf("Sales Report (Highest to Lowest):\n");
    printf("Month\t\tSales\n");

    // temporary variables for holding data while sorting
    float tempSales;
    char* tempMonth;

    /*
        bubble sort
        not the best sort but the most straightforward to implement
        swaps a value with the next value if the current value is lower than the next
        this sort swaps the values of the months and also swaps the order of the months themselves so that everything stays with its corresponding value
    */
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 11-i; j++) {
            if (sales[j] < sales[j + 1]) {
                tempSales = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = tempSales;

                tempMonth = months[j];
                months[j] = months[j + 1];
                months[j + 1] = tempMonth;
            }
        }
    }

    // iterate through all the months and print the month and its sales value
    for (int i = 0; i < 12; i++) {
        if (strlen(months[i]) < 8) {
            printf("%s\t\t$%0.2f\n", months[i], sales[i]);
        }
        else {
            printf("%s\t$%0.2f\n", months[i], sales[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    // exit the process if there is an incorrect amount of command-line arguments
    if (argc != 2) {
        printf("Usage: ./sales INPUT_FILE\n");
        exit(0);
    }

    /*
        variables for reading the data from the file
        fileString stores the next line in the file for reading
        salesValues is an array to store all the different sales numbers, ordered by month
        currentMonth keeps track of the index of the salesValues for writing to the array from the file
    */
    char fileString[100];
    float salesValues[12];
    int currentMonth = 0;

    // open the file, and if the file doesn't open correctly, exit the process
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Not able to open the file.");
        fclose(fptr);
        exit(0);
    }

    /*
        read each line from the input file to fileString
        convert the string to a float and store it at the appropriate index of salesValues
        clear the fileString
        incremenet to the next index
    */
    while(fgets(fileString, 100, fptr)) {
        salesValues[currentMonth] = (float) atof(fileString);
        memset(fileString, 0, 100);
        currentMonth++;
    }
    fclose(fptr);   // always close the file :)

    // array for all the months
    char* salesMonths[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    // call all functions to print all necessary sales data
    printReport(salesMonths, salesValues);
    printSummary(salesMonths, salesValues);
    printSixMonthReport(salesMonths, salesValues);
    printHighToLow(salesMonths, salesValues);
    return 0;
}