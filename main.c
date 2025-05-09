#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep function

#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_NAME_LEN 50
#define MAX_REQUESTS 100

// Structures
typedef struct {
    char title[MAX_NAME_LEN];
    char author[MAX_NAME_LEN];
    char subject[MAX_NAME_LEN];
    int id;
    int available; // Number of copies available
} Book;

typedef struct {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    char role[MAX_NAME_LEN]; // "librarian" or "student"
    char field[MAX_NAME_LEN]; // For students only
} User;

typedef struct {
    int id;
    char username[MAX_NAME_LEN];
    int book_id;
} Request;

// Global variables
Book books[MAX_BOOKS];
User users[MAX_USERS];
Request requests[MAX_REQUESTS];
int book_count = 0;
int user_count = 0;
int request_count = 0;

// Function prototypes
void load_data();
void save_data();
void librarian_menu();
void student_menu(User user);
void add_book();
void delete_book();
void view_books();
void edit_book();
void request_book(User user);
void return_book(User user);
void create_student_account();
void create_librarian_account();
void view_requests();
void approve_request();
void reject_request();
void login_menu();
void load_requests();
void save_requests();

// Main function
int main() {
    load_data();
    load_requests();
    printf("Welcome to Library Management System!\n");
    for (int i = 0; i < user_count; i++){
        printf("%d -> %s\n",i ,users[i].username);
    }
    login_menu();
    /*
    char username[MAX_NAME_LEN], password[MAX_NAME_LEN];
    int authenticated = 0;


    while (!authenticated) {
        printf("\nEnter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);
        
        strcpy(users[0].username,"admin");
        strcpy(users[0].password,"admin123");
        strcpy(users[0].role,"librarian");
        
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
                authenticated = 1;
                if (strcmp(users[i].role, "librarian") == 0) {
                    librarian_menu();
                } else {
                    student_menu(users[i]);
                }
                break;
            }
        }

        if (!authenticated) {
            printf("Invalid username or password. Try again.\n");
            sleep(2); // Add delay before re-prompting
        }
    }
    */
    save_data();
    save_requests();
    return 0;
}

char username[MAX_NAME_LEN], password[MAX_NAME_LEN];
//login menu 
void login_menu() {
    int authenticated = 0;
    int attempts = 0; // شمارنده تعداد تلاش‌ها

    while (!authenticated) {
        printf("\nEnter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
                authenticated = 1;
                if (strcmp(users[i].role, "librarian") == 0) {
                    librarian_menu();
                } else {
                    student_menu(users[i]);
                }
                break;
            }
        }

        if (!authenticated) {
            attempts++;
            printf("Invalid username or password. Try again.\n");
            if (attempts >= 3) { // حداکثر تلاش‌ها
                printf("Too many failed attempts. Exiting...\n");
                exit(1);
            }
            sleep(2); // تأخیر قبل از ورود دوباره
        }
    }
}

// Librarian menu
void librarian_menu() {
    int choice;

    do {
        printf("\nLibrarian Menu:\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Edit Book\n");
        printf("4. View All Books\n");
        printf("5. Create Student Account\n");
        printf("6. Create Librarian Account\n");
        printf("7. View Requests\n");
        printf("8. Approve Request\n");
        printf("9. Reject Request\n");
        printf("10. Logout\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                delete_book();
                break;
            case 3:
                edit_book();
                break;
            case 4:
                view_books();
                break;
            case 5:
                create_student_account();
                break;
            case 6:
                create_librarian_account();
                break;
            case 7:
                view_requests();
                break;
            case 8:
                approve_request();
                break;
            case 9:
                reject_request();
                break;
            case 10:
                printf("Logging out...\n");
                login_menu();
                return;
            case 11:
                printf("Exiting program...\n");
                save_data();
                save_requests();
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (1);
}

// Student menu
void student_menu(User user) {
    int choice;

    do {
        printf("\nStudent Menu:\n");
        printf("1. View Books\n");
        printf("2. Request Book\n");
        printf("3. Return Book\n");
        printf("4. Logout\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_books();
                break;
            case 2:
                request_book(user);
                break;
            case 3:
                return_book(user);
                break;
            case 4:
                printf("Logging out...\n");
                login_menu();
                return;
            case 5:
                printf("Exiting program...\n");
                save_data();
                save_requests();
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (1);
}

// Add a new book
void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book new_book;
    printf("Enter book title: ");
    getchar(); // To consume the newline character left by previous input
    fgets(new_book.title, sizeof(new_book.title), stdin);
    new_book.title[strcspn(new_book.title, "\n")] = 0; // Remove the newline character

    printf("Enter author name: ");
    fgets(new_book.author, sizeof(new_book.author), stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0; // Remove the newline character

    printf("Enter subject: ");
    fgets(new_book.subject, sizeof(new_book.subject), stdin);
    new_book.subject[strcspn(new_book.subject, "\n")] = 0; // Remove the newline character

    printf("Enter number of copies available: ");
    scanf("%d", &new_book.available);

    new_book.id = book_count + 1;
    books[book_count++] = new_book;

    printf("Book added successfully!\n");
}

// Delete a book
void delete_book() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < book_count - 1; j++) {
                books[j] = books[j + 1];
            }
            book_count--;
            printf("Book deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

// Edit a book
void edit_book() {
    int id;
    printf("Enter book ID to edit: ");
    scanf("%d", &id);
    getchar(); // To consume the newline character left by previous input

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            printf("Editing book: %s\n", books[i].title);
            printf("Enter new title: ");
            fgets(books[i].title, sizeof(books[i].title), stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0; // Remove newline character

            printf("Enter new author: ");
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0; // Remove newline character

            printf("Enter new subject: ");
            fgets(books[i].subject, sizeof(books[i].subject), stdin);
            books[i].subject[strcspn(books[i].subject, "\n")] = 0; // Remove newline character

            printf("Enter new number of copies: ");
            scanf("%d", &books[i].available);

            printf("Book updated successfully!\n");
            return;
        }
    }

    printf("Book not found.\n");
}

// View all books
void view_books() {
    printf("\nList of Books:\n");
    for (int i = 0; i < book_count; i++) {
        printf("ID: %d, Title: %s, Author: %s, Subject: %s, Available: %d\n",
               books[i].id, books[i].title, books[i].author, books[i].subject, books[i].available);
    }
    
}

// Request a book
void request_book(User user) {
    int id;
    printf("Enter book ID to request: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            if (books[i].available > 0) {
                Request new_request = {request_count + 1, "", id};
                strcpy(new_request.username, user.username);
                requests[request_count++] = new_request;
                save_requests();
                printf("Book request submitted successfully!\n");
            } else {
                printf("Book is currently unavailable.\n");
            }
            return;
        }
    }

    printf("Book not found.\n");
}

// Return a book
void return_book(User user) {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            books[i].available++;
            printf("Book returned successfully!\n");
            return;
        }
    }

    printf("Book not found.\n");
}

// Load data from files
void load_data() {
    FILE *file = fopen("books.txt", "r");
    if (file) {
        while (fscanf(file, "%d %[^ ]\t%[^ ]\t%[^ ]\t%d\n", &books[book_count].id, books[book_count].title, books[book_count].author, books[book_count].subject, &books[book_count].available) != EOF) {
            book_count++;
        }
        fclose(file);
    } else {
        printf("Warning: books.txt not found. Creating a new file...\n");
        file = fopen("books.txt", "w"); // فایل را ایجاد کنید
        if (file) fclose(file);
    }

    file = fopen("users.txt", "r");
    if (file) {
        while (fscanf(file, "%49s %49s %49s %49[^\n]", users[user_count].username, users[user_count].password, users[user_count].role, users[user_count].field) != EOF) {
            user_count++;
        }
        fclose(file);
    } else {
        printf("Warning: users.txt not found. Creating a new file...\n");
        file = fopen("users.txt", "w"); // فایل را ایجاد کنید
        if (file) fclose(file);
    }

    // اضافه کردن اکانت پیش‌فرض اگر کاربران وجود ندارند
    if (user_count == 0) {
        User default_librarian = {"admin", "admin123", "librarian", ""};
        users[user_count++] = default_librarian;
        save_data(); // ذخیره به‌روزرسانی‌ها
    }
}

void load_requests() {
    FILE *file = fopen("requests.txt", "r");
    if (file) {
        while (fscanf(file, "%d %49s %d", &requests[request_count].id, requests[request_count].username, &requests[request_count].book_id) != EOF) {
            request_count++;
        }
        fclose(file);
    } else {
        printf("Warning: requests.txt not found. Creating a new file...\n");
        file = fopen("requests.txt", "w");
        if (file) fclose(file);
    }
}

// Save data to files
void save_data() {
    FILE *file = fopen("books.txt", "w");
    if (file) {
        for (int i = 0; i < book_count; i++) {
            fprintf(file, "%d %s %s %s %d\n", books[i].id, books[i].title, books[i].author, books[i].subject, books[i].available);
        }
        fclose(file);
    } else {
        printf("Error opening books.txt for writing\n");
    }

    file = fopen("users.txt", "w");
    if (file) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%s %s %s %s\n", users[i].username, users[i].password, users[i].role, users[i].field);
        }
        fclose(file);
    } else {
        printf("Error opening users.txt for writing\n");
    }
}

void save_requests() {
    FILE *file = fopen("requests.txt", "w");
    if (file) {
        for (int i = 0; i < request_count; i++) {
            fprintf(file, "%d %s %d\n", requests[i].id, requests[i].username, requests[i].book_id);
        }
        fclose(file);
    } else {
        printf("Error opening requests.txt for writing\n");
    }
}

// Create student account
void create_student_account() {
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    User new_user;
    printf("Enter username: ");
    scanf("%49s", new_user.username);

    // بررسی یکتا بودن نام کاربری
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, new_user.username) == 0) {
            printf("Username already exists. Try a different one.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%49s", new_user.password);
    strcpy(new_user.role, "student");
    printf("Enter field of study: ");
    scanf("%49s", new_user.field);

    users[user_count++] = new_user;
    save_data();
    printf("Student account created successfully.\n");
}


// Create librarian account
void create_librarian_account() {
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    User new_user;
    printf("Enter username: ");
    scanf("%49s", new_user.username);

    // بررسی یکتا بودن نام کاربری
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, new_user.username) == 0) {
            printf("Username already exists. Try a different one.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%49s", new_user.password);
    strcpy(new_user.role, "librarian");
    strcpy(new_user.field, "");

    users[user_count++] = new_user;
    save_data();
    printf("Librarian account created successfully.\n");
}


// View requests
void view_requests() {
    printf("\nList of Pending Requests:\n");
    for (int i = 0; i < request_count; i++) {
        printf("Request ID: %d, User: %s, Book ID: %d\n", requests[i].id, requests[i].username, requests[i].book_id);
    }
}

// Approve request
void approve_request() {
    int request_id;
    printf("Enter Request ID to approve: ");
    scanf("%d", &request_id);

    for (int i = 0; i < request_count; i++) {
        if (requests[i].id == request_id) {
            for (int j = 0; j < book_count; j++) {
                if (books[j].id == requests[i].book_id && books[j].available > 0) {
                    books[j].available--;
                    printf("Request approved, book allocated.\n");
                    for (int k = i; k < request_count - 1; k++) {
                        requests[k] = requests[k + 1];
                    }
                    request_count--;
                    save_requests();
                    return;
                }
            }
            printf("Book is currently unavailable.\n");
            return;
        }
    }
    printf("Request not found.\n");
}

// Reject request
void reject_request() {
    int request_id;
    printf("Enter Request ID to reject: ");
    scanf("%d", &request_id);

    for (int i = 0; i < request_count; i++) {
        if (requests[i].id == request_id) {
            for (int k = i; k < request_count - 1; k++) {
                requests[k] = requests[k + 1];
            }
            request_count--;
            save_requests();
            printf("Request rejected.\n");
            return;
        }
    }
    printf("Request not found.\n");
}

