#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define struct to hold patient information: ID, name, appointment date, and time
struct PatientEntry {
    char patientID[7];
    char name[50];
    char appointmentDate[15];
    char appointmentTime[10];
};

// Function to validate that the patient ID contains only digits and is 6 digits long
int validPatientID(char *id) {
    if (strlen(id) != 6) return 0;
    for (int i = 0; i < 6; i++) {
        if (!isdigit(id[i])) return 0;
    }
    return 1;
}

// Function to display all patient records
void displayAll(struct PatientEntry patients[], int size) {
    printf("\nCurrent Appointment Records:\n");
    for (int i = 0; i < size; i++) {
        printf("ID: %s, Name: %s, Date: %s, Time: %s\n",
               patients[i].patientID, patients[i].name, patients[i].appointmentDate, patients[i].appointmentTime);
    }
    printf("\n");
}

// Function to add a new entry
int addEntry(struct PatientEntry patients[], int *size) {
    if (*size >= 100) { // limit to 100 entries for simplicity
        printf("Error: Cannot add more entries, database is full.\n");
        return *size;
    }
    struct PatientEntry newPatient;
    
    // Input Patient ID
    printf("Enter 6-digit Patient ID: ");
    scanf("%s", newPatient.patientID);
    getchar();  // Clear newline character left in the input buffer
    if (!validPatientID(newPatient.patientID)) {
        printf("Error: Invalid Patient ID. Please enter a 6-digit numeric ID.\n");
        return *size;
    }
    
    // Input Patient Name
    printf("Enter Patient Name: ");
    fgets(newPatient.name, sizeof(newPatient.name), stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = '\0'; // Remove trailing newline

    // Input Appointment Date in DD-MM-YYYY format
    printf("Enter Appointment Date (DD-MM-YYYY): ");
    scanf("%s", newPatient.appointmentDate);
    getchar();  // Clear newline character left in the input buffer
    
    // Input Appointment Time using fgets
    printf("Enter Appointment Time (HH:MM AM/PM): ");
    fgets(newPatient.appointmentTime, sizeof(newPatient.appointmentTime), stdin);
    newPatient.appointmentTime[strcspn(newPatient.appointmentTime, "\n")] = '\0'; // Remove trailing newline

    patients[*size] = newPatient;
    (*size)++;
    printf("Entry added successfully.\n");
    return *size;
}

// Function to remove an entry
int removeEntry(struct PatientEntry patients[], int *size) {
    char id[7];
    printf("Enter Patient ID to remove: ");
    scanf("%s", id);
    getchar(); // Clear newline character left in the input buffer

    for (int i = 0; i < *size; i++) {
        if (strcmp(patients[i].patientID, id) == 0) {
            for (int j = i; j < *size - 1; j++) {
                patients[j] = patients[j + 1];
            }
            (*size)--;
            printf("Entry removed successfully.\n");
            return *size;
        }
    }
    printf("Patient ID not found.\n");
    return *size;
}

// Function to update an entry
void updateEntry(struct PatientEntry patients[], int size) {
    char id[7];
    printf("Enter Patient ID to update: ");
    scanf("%s", id);
    getchar(); // Clear newline character left in the input buffer

    for (int i = 0; i < size; i++) {
        if (strcmp(patients[i].patientID, id) == 0) {
            printf("Updating record for %s (ID: %s)\n", patients[i].name, id);
            printf("Enter new Appointment Date (DD-MM-YYYY): ");
            scanf("%s", patients[i].appointmentDate);
            getchar(); // Clear newline character left in the input buffer
            printf("Enter new Appointment Time (HH:MM AM/PM): ");
            fgets(patients[i].appointmentTime, sizeof(patients[i].appointmentTime), stdin);
            patients[i].appointmentTime[strcspn(patients[i].appointmentTime, "\n")] = '\0'; // Remove trailing newline
            printf("Entry updated successfully.\n");
            return;
        }
    }
    printf("Patient ID not found.\n");
}

int main() {
    struct PatientEntry patients[100] = {
        {"100001", "Ankita Joshi", "05-11-2024", "10:30 AM"},
        {"100002", "Nikita Kolambe", "05-11-2024", "11:00 AM"},
        {"100003", "Sachin Karche", "06-11-2024", "09:00 AM"},
        {"100004", "Amisha Parmar", "06-11-2024", "11:30 AM"},
        {"100005", "Donald Trump", "07-11-2024", "02:00 PM"}
    };
    int size = 5;
    char userPatientID[7];
    int found = 0;
    int choice;

    // Main menu loop
    while (1) {
        printf("\nMenu:\n1. Search Patient\n2. Add Entry\n3. Remove Entry\n4. Update Entry\n5. Display All Records\n6. Exit\nChoose an option: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character left in the input buffer

        switch (choice) {
            case 1:
                // Search for a patient
                printf("Enter the Patient ID to search: ");
                scanf("%s", userPatientID);
                getchar(); // Clear newline character left in the input buffer

                // Validate Patient ID
                if (!validPatientID(userPatientID)) {
                    printf("Error: Invalid Patient ID. Please enter a 6-digit number.\n");
                    break;
                }

                found = 0;
                for (int i = 0; i < size; i++) {
                    if (strcmp(patients[i].patientID, userPatientID) == 0) {
                        printf("Appointment found:\nName: %s\nDate: %s\nTime: %s\n",
                               patients[i].name, patients[i].appointmentDate, patients[i].appointmentTime);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("The Patient ID is not in the records.\n");
                }
                break;

            case 2:
                // Add a new entry
                addEntry(patients, &size);
                break;

            case 3:
                // Remove an entry
                removeEntry(patients, &size);
                break;

            case 4:
                // Update an entry
                updateEntry(patients, size);
                break;

            case 5:
                // Display all entries
                displayAll(patients, size);
                break;

            case 6:
                // Exit the program
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }
}