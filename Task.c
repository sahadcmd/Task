#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() 
{
    const char* products[] = {"Product A", "Product B", "Product C"};
    int price[] = {20, 40, 50};

    int quantities[sizeof(products) / sizeof(products[0])];
    bool gift_wrapping[sizeof(products) / sizeof(products[0])];

    // Getting datas from the user for quantities and gift wrapping
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) 
    {
        printf("Enter the quantity of %s: ", products[i]);
        scanf("%d", &quantities[i]);

        char wrap[40];
        printf("Wrap %s as a gift? (y/n): ", products[i]);
        scanf("%s", wrap);
        gift_wrapping[i] = (strcmp(wrap, "y") == 0);
    }

    // Calculating Subtotal
    int subtotal = 0;
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) 
    {
        subtotal += quantities[i] * price[i];
    }

    char discount_name[20];
    int discount_amount = 0;
    int max_discount_amount = 0; // for getting most beneficial discount amount
    char max_discount_name[20] = "";


    // checking flat 10 discount
    if (subtotal > 200 && 10 > max_discount_amount) 
    {
        strcpy(max_discount_name, "flat_10_discount");
        max_discount_amount = 10;
    }


    // checking bulk 5 discount
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) 
    {
        if (quantities[i] > 10 && price[i] * quantities[i] * 0.05 > max_discount_amount) 
        {
            strcpy(max_discount_name, "bulk_5_discount");
            max_discount_amount = price[i] * quantities[i] * 0.05;
        }
    }

    // Calculating total quantities
    int total_quantity = 0;

    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) 
    {
        total_quantity += quantities[i];
    }


    // checking bulk 10 discount
    if (total_quantity > 20 && subtotal * 0.1 > max_discount_amount) 
    {
        strcpy(max_discount_name, "bulk_10_discount");
        max_discount_amount = subtotal * 0.1;
    }


    // checking tiered 50 discount
    if (total_quantity > 30) 
    {
        for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) 
        {
            if (quantities[i] > 15 && (quantities[i] - 15) * price[i] * 0.5 > max_discount_amount) 
            {
                strcpy(max_discount_name, "tiered_50_discount");
                max_discount_amount = (quantities[i] - 15) * price[i] * 0.5;
            }
        }
    }

    // applying most beneficial discount
    discount_amount = max_discount_amount;
    strcpy(discount_name, max_discount_name);


    int total_packages = (total_quantity + 9) / 10; // rounding off number
    int shipping_fee = total_packages * 5; // calculating shipping fee

    // calculating gift wraop fee
    int gift_wrap_fee = 0;
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) 
    {
        if (gift_wrapping[i]) 
        {
            gift_wrap_fee += quantities[i];
        }
    }

    // calculating total amount 
    int total = subtotal - discount_amount + shipping_fee + gift_wrap_fee;

    // products detail
    printf("\nOrder Details:\n");
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) 
    {
        printf(" Quantity of %s: %d, Total amount of %s: %d\n", products[i], quantities[i], products[i], quantities[i] * price[i]);
    }

    printf("\nSubtotal: $%d\n", subtotal);
    printf("Discount Applied: %s\n", discount_name);
    printf("Discount Amount: $%d\n", discount_amount);
    printf("Shipping Fee: $%d\n", shipping_fee);
    printf("Gift Wrap Fee: $%d\n", gift_wrap_fee);
    printf("Total: $%d\n", total);

    return 0;
}
