#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int quarter = 25; 
    int dime = 10; 
    int nickel = 5; 
    int penny = 1; 
    int coins = 0; 
    int rest = 0;
    
    //prompt user for $ until valid input
    do
    {
        printf("How much change do I owe you?\n");
        change = GetFloat();
        
        //if under 0 re-prompt user for a correct input
        if (change <= 0)
        printf("$%.2f, are you sure? I don't owe you anything then? So tell me,  \n", change);
    }
    while (change <= 0); 
    
    //convert dollar to cents
    int cents;
    cents = (int) round (change * 100);
    
    //count 
    coins = cents / quarter;
    rest = cents % quarter;
  
    coins += rest / dime;                                          
    rest %= dime;                               
    
    coins += rest / nickel;
    rest %= nickel;
    
    coins += rest / penny;
    rest %= penny;
    
    printf("%d\n", coins);
}
    
