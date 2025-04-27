#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define PASSWORD "admin123" // Admin password

struct Book {
    int id;
    char title[100];
    char author[100];
    char genre[50];
    int quantity;
    float price;
};

struct Sale {
    int bookId;
    int quantitySold;
    float totalPrice;
};

struct Book inventory[MAX_BOOKS];
struct Sale sales[MAX_BOOKS];
int totalBooks = 0;
int totalSales = 0;
float totalRevenue = 0;

// Function prototypes
void adminLogin();
void displayMenu();
void addBook();
void displayBooks();
void modifyBook();
void deleteBook();
void searchBook();
void buyBook();
void sortBooks();
void showSalesReport();
void lowStockWarning();
void topSellingBook();
void checkBookAvailability();
void updateBookQuantity();

int main() {
    int choice;
    adminLogin();
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: modifyBook(); break;
            case 4: deleteBook(); break;
            case 5: searchBook(); break;
            case 6: buyBook(); break;
            case 7: sortBooks(); break;
            case 8: showSalesReport(); break;
            case 9: topSellingBook(); break;
            case 10: checkBookAvailability(); break;
            case 11: updateBookQuantity(); break;
            case 12: printf("Exiting Bookshop Management System. Goodbye!\n"); break;
            default: printf("Invalid choice. Try again!\n");
        }
    } while (choice != 12);
    return 0;
}

// Function definitions

void adminLogin() {
    char pass[20];
    printf("Enter Admin Password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';
    if (strcmp(pass, PASSWORD) != 0) {
        printf("Incorrect password! Exiting...\n");
        exit(0);
    }
    printf("Access Granted!\n\n");
}

void displayMenu() {
    printf("\n========== Bookshop Management ==========\n");
    printf("1. Add Book\n");
    printf("2. Display All Books\n");
    printf("3. Modify Book Details\n");
    printf("4. Delete Book\n");
    printf("5. Search Book\n");
    printf("6. Buy Book\n");
    printf("7. Sort Books\n");
    printf("8. Show Sales Report\n");
    printf("9. Show Top Selling Book\n");
    printf("10. Check Book Availability\n");
    printf("11. Update Book Quantity\n");
    printf("12. Exit\n");
    printf("==========================================\n");
}

void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        printf("Inventory Full! Cannot add more books.\n");
        return;
    }
    struct Book b;
    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar();
    printf("Enter Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';
    printf("Enter Author: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';
    printf("Enter Genre: ");
    fgets(b.genre, sizeof(b.genre), stdin);
    b.genre[strcspn(b.genre, "\n")] = '\0';
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);
    printf("Enter Price: ");
    scanf("%f", &b.price);

    inventory[totalBooks++] = b;
    printf("Book Added Successfully!\n");
    lowStockWarning();
}

void displayBooks() {
    if (totalBooks == 0) {
        printf("No books available.\n");
        return;
    }
    printf("\nAvailable Books:\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("\nBook ID: %d\nTitle: %s\nAuthor: %s\nGenre: %s\nQuantity: %d\nPrice: ₹%.2f\n", 
            inventory[i].id, inventory[i].title, inventory[i].author, inventory[i].genre, inventory[i].quantity, inventory[i].price);
    }
}

void modifyBook() {
    int id, found = 0;
    printf("Enter Book ID to modify: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < totalBooks; i++) {
        if (inventory[i].id == id) {
            printf("Enter New Title: ");
            fgets(inventory[i].title, sizeof(inventory[i].title), stdin);
            inventory[i].title[strcspn(inventory[i].title, "\n")] = '\0';
            printf("Enter New Author: ");
            fgets(inventory[i].author, sizeof(inventory[i].author), stdin);
            inventory[i].author[strcspn(inventory[i].author, "\n")] = '\0';
            printf("Enter New Genre: ");
            fgets(inventory[i].genre, sizeof(inventory[i].genre), stdin);
            inventory[i].genre[strcspn(inventory[i].genre, "\n")] = '\0';
            printf("Enter New Quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter New Price: ");
            scanf("%f", &inventory[i].price);
            printf("Book Modified Successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Book ID not found.\n");
}

void deleteBook() {
    int id, found = 0;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < totalBooks; i++) {
        if (inventory[i].id == id) {
            for (int j = i; j < totalBooks - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            totalBooks--;
            printf("Book Deleted Successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Book ID not found.\n");
}

void searchBook() {
    int choice;
    printf("Search By:\n1. ID\n2. Title\n3. Author\nEnter choice: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1) {
        int id, found = 0;
        printf("Enter Book ID: ");
        scanf("%d", &id);
        for (int i = 0; i < totalBooks; i++) {
            if (inventory[i].id == id) {
                printf("\nBook Found!\nTitle: %s\nAuthor: %s\nGenre: %s\nQuantity: %d\nPrice: ₹%.2f\n",
                    inventory[i].title, inventory[i].author, inventory[i].genre, inventory[i].quantity, inventory[i].price);
                found = 1;
                break;
            }
        }
        if (!found) printf("Book not found.\n");
    } else if (choice == 2) {
        char title[100];
        int found = 0;
        printf("Enter Title: ");
        fgets(title, sizeof(title), stdin);
        title[strcspn(title, "\n")] = '\0';
        for (int i = 0; i < totalBooks; i++) {
            if (strcmp(inventory[i].title, title) == 0) {
                printf("\nBook Found!\nID: %d\nAuthor: %s\nGenre: %s\nQuantity: %d\nPrice: ₹%.2f\n",
                    inventory[i].id, inventory[i].author, inventory[i].genre, inventory[i].quantity, inventory[i].price);
                found = 1;
                break;
            }
        }
        if (!found) printf("Book not found.\n");
    } else if (choice == 3) {
        char author[100];
        int found = 0;
        printf("Enter Author: ");
        fgets(author, sizeof(author), stdin);
        author[strcspn(author, "\n")] = '\0';
        for (int i = 0; i < totalBooks; i++) {
            if (strcmp(inventory[i].author, author) == 0) {
                printf("\nBook Found!\nID: %d\nTitle: %s\nGenre: %s\nQuantity: %d\nPrice: ₹%.2f\n",
                    inventory[i].id, inventory[i].title, inventory[i].genre, inventory[i].quantity, inventory[i].price);
                found = 1;
                break;
            }
        }
        if (!found) printf("Book not found.\n");
    } else {
        printf("Invalid search choice.\n");
    }
}

void buyBook() {
    int id, qty, found = 0;
    printf("Enter Book ID to buy: ");
    scanf("%d", &id);
    for (int i = 0; i < totalBooks; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Enter quantity to purchase: ");
            scanf("%d", &qty);
            if (qty <= inventory[i].quantity) {
                float price = qty * inventory[i].price;
                inventory[i].quantity -= qty;
                sales[totalSales].bookId = id;
                sales[totalSales].quantitySold = qty;
                sales[totalSales].totalPrice = price;
                totalSales++;
                totalRevenue += price;
                printf("Purchase Successful! Total Price: ₹%.2f\n", price);
                lowStockWarning();
            } else {
                printf("Not enough stock. Available: %d\n", inventory[i].quantity);
            }
            break;
        }
    }
    if (!found)
        printf("Book not found.\n");
}

void sortBooks() {
    int choice;
    printf("Sort By:\n1. ID\n2. Title\n3. Author\nEnter choice: ");
    scanf("%d", &choice);
    getchar();
    struct Book temp;
    for (int i = 0; i < totalBooks-1; i++) {
        for (int j = i+1; j < totalBooks; j++) {
            int swap = 0;
            if (choice == 1 && inventory[i].id > inventory[j].id)
                swap = 1;
            else if (choice == 2 && strcmp(inventory[i].title, inventory[j].title) > 0)
                swap = 1;
            else if (choice == 3 && strcmp(inventory[i].author, inventory[j].author) > 0)
                swap = 1;
            if (swap) {
                temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }
    printf("Books sorted successfully!\n");
}

void showSalesReport() {
    printf("\n====== Sales Report ======\n");
    for (int i = 0; i < totalSales; i++) {
        printf("Book ID: %d | Quantity Sold: %d | Total Price: ₹%.2f\n", 
            sales[i].bookId, sales[i].quantitySold, sales[i].totalPrice);
    }
    printf("\nTotal Revenue: ₹%.2f\n", totalRevenue);
}

void topSellingBook() {
    if (totalSales == 0) {
        printf("No sales recorded yet.\n");
        return;
    }
    int maxIndex = 0;
    for (int i = 1; i < totalSales; i++) {
        if (sales[i].quantitySold > sales[maxIndex].quantitySold)
            maxIndex = i;
    }
    printf("Top Selling Book ID: %d | Quantity Sold: %d | Revenue: ₹%.2f\n",
        sales[maxIndex].bookId, sales[maxIndex].quantitySold, sales[maxIndex].totalPrice);
}

void checkBookAvailability() {
    int id, found = 0;
    printf("Enter Book ID to check availability: ");
    scanf("%d", &id);
    for (int i = 0; i < totalBooks; i++) {
        if (inventory[i].id == id) {
            printf("Available Copies: %d\n", inventory[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Book not found.\n");
}

void updateBookQuantity() {
    int id, qty, found = 0;
    printf("Enter Book ID to update quantity: ");
    scanf("%d", &id);
    for (int i = 0; i < totalBooks; i++) {
        if (inventory[i].id == id) {
            printf("Enter new quantity: ");
            scanf("%d", &qty);
            inventory[i].quantity = qty;
            printf("Quantity Updated Successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Book not found.\n");
}

void lowStockWarning() {
    for (int i = 0; i < totalBooks; i++) {
        if (inventory[i].quantity > 0 && inventory[i].quantity < 3) {
            printf("Warning: Low stock for '%s'! Only %d copies left.\n", inventory[i].title, inventory[i].quantity);
        }
    }
}
