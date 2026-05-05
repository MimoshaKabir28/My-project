#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
struct Product
{
    int id;
    char name[50];
    int quantity;
    float price;
    struct Product* next;
};
struct Stack
{
    struct Product* top;
};
struct Product* hashTable[SIZE];
// Hash function
int hashFunction(int id)
{
    return id % SIZE;
}
// Create product
struct Product* createProduct(int id, char name[], int qty, float price)
{
    struct Product* p = (struct Product*)malloc(sizeof(struct Product));
    p->id = id;
    strcpy(p->name, name);
    p->quantity = qty;
    p->price = price;
    p->next = NULL;
    return p;
}
// Add product
void addProduct()
{
    int id, qty;
    float price;
    char name[50];
    printf("Enter ID: ");
    scanf("%d", &id);
    printf("Enter Name: ");
    scanf("%s", name);
    printf("Enter Quantity: ");
    scanf("%d", &qty);
    printf("Enter Price: ");
    scanf("%f", &price);
    int index = hashFunction(id);
    struct Product* p = createProduct(id, name, qty, price);
    p->next = hashTable[index];
    hashTable[index] = p;
    printf("Product Added!\n");
}
// Display products
void displayProducts()
{
    for (int i = 0; i < SIZE; i++)
    {
        struct Product* temp = hashTable[i];
        while (temp != NULL)
        {
            printf("ID:%d Name:%s Qty:%d Price:%.2f\n",
                   temp->id, temp->name, temp->quantity, temp->price);
            temp = temp->next;
        }
    }
}
// Search product
void searchProduct()
{
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    int index = hashFunction(id);
    struct Product* temp = hashTable[index];
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("Found: %s | Qty: %d | Price: %.2f\n",
                   temp->name, temp->quantity, temp->price);
            return;
        }
        temp = temp->next;
    }
    printf("Not Found!\n");
}
// Stack functions
void push(struct Stack* s, struct Product* p)
{
    p->next = s->top;
    s->top = p;
}
struct Product* pop(struct Stack* s)
{
    if (s->top == NULL) return NULL;
    struct Product* temp = s->top;
    s->top = s->top->next;
    return temp;
}
// Delete product
void deleteProduct(struct Stack* s)
{
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    int index = hashFunction(id);
    struct Product* temp = hashTable[index];
    struct Product* prev = NULL;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            if (prev == NULL)
                hashTable[index] = temp->next;
            else
                prev->next = temp->next;
            push(s, temp);
            printf("Deleted! (Stored in Stack)\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Not Found!\n");
}
// Undo delete
void undoDelete(struct Stack* s)
{
    struct Product* p = pop(s);
    if (p == NULL)
    {
        printf("Nothing to Undo!\n");
        return;
    }
    int index = hashFunction(p->id);
    p->next = hashTable[index];
    hashTable[index] = p;
    printf("Undo Successful!\n");
}
// Main
int main()
{
    struct Stack s;
    s.top = NULL;
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = NULL;
    int choice;
    while (1)
    {
        printf("\n===== INVENTORY MENU =====\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product\n");
        printf("4. Delete Product\n");
        printf("5. Undo Delete\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addProduct();
            break;
        case 2:
            displayProducts();
            break;
        case 3:
            searchProduct();
            break;
        case 4:
            deleteProduct(&s);
            break;
        case 5:
            undoDelete(&s);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
}
