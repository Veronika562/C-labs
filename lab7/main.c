#include "person.h"

int main(int argc, char* argv[]) {
    char filename[FILE_NAME_SIZE];
    if (argc == 2) {
        strcpy(filename, argv[1]);
    }
    else {
        strcpy(filename, "data.txt");
    }
    list_t* main_list = read_from_file(filename);
    int function_num = 0;
    do {
        puts("Enter a number:");
        puts("1. Add person.");
        puts("2. Create a connection.");
        puts("3. Destroy a connection.");
        puts("4. Find people.");
        puts("5. Show circle of contacts.");
        puts("6. Exit.");
        do {
            function_num = getchar();
            char c;
            while ((c = getchar()) != '\n') {}
        } while (function_num < '1' || function_num > '6');
        switch (function_num) {
        case '1':
        {
            person_t* new_person = (person_t*)malloc(sizeof(person_t));
            new_person->contacts.head = new_person->contacts.tail = NULL;
            new_person->contacts.size = 0;
            assert(new_person != NULL);
            puts("Enter person's name:");
            fgets(new_person->name, NAME_SIZE, stdin);
            puts("Enter person's city:");
            fgets(new_person->city, CITY_SIZE, stdin);
            puts("Enter person's education:");
            fgets(new_person->education, EDUCATION_SIZE, stdin);
            puts("Enter person's job:");
            fgets(new_person->job, JOB_SIZE, stdin);   
            puts("Enter person's interests:");            
            fgets(new_person->interests, INTERESTS_SIZE, stdin);
            add_to_list(main_list, new_person);
            puts("Enter \"6\" to exit the program.");
            puts("Enter any other character to return to the menu.");
            if (getchar() == '6') { function_num = '6'; }
            char c;
            while ((c = getchar()) != '\n') {}
            break;
        }
        case '2':
        { 
            puts("Enter first person's name:");
            char first_name[NAME_SIZE];
            fgets(first_name, NAME_SIZE, stdin);
            person_t* person1 = find_person(main_list, first_name);
            while (person1 == NULL) {
                puts("Person with this name does not exists. Try again:");
                fgets(first_name, NAME_SIZE, stdin);
                person1 = find_person(main_list, first_name);
            }
            puts("Enter second person's name:");
            char second_name[NAME_SIZE];
            fgets(second_name, NAME_SIZE, stdin);
            person_t* person2 = find_person(main_list, second_name);
            while (person2 == NULL) {
                puts("Person with this name does not exists. Try again:");
                fgets(second_name, NAME_SIZE, stdin);
                person2 = find_person(main_list, second_name);
            }
            add_contact(person1, person2);
            puts("Enter \"6\" to exit the program.");
            puts("Enter any other character to return to the menu.");
            if (getchar() == '6') { function_num = '6'; }
            char c;
            while ((c = getchar()) != '\n') {}
            break;
        }
        case '3':
        { 
            puts("Enter first person's name:");
            char first_name[NAME_SIZE];
            fgets(first_name, NAME_SIZE, stdin);
            person_t* person1 = find_person(main_list, first_name);
            while (person1 == NULL) {
                puts("Person with this name does not exists. Try again:");
                fgets(first_name, NAME_SIZE, stdin);
                person1 = find_person(main_list, first_name);
            }
            puts("Enter second person's name:");
            char second_name[NAME_SIZE];
            fgets(second_name, NAME_SIZE, stdin);
            person_t* person2 = find_person(main_list, second_name);
            while (person2 == NULL) {
                puts("Person with this name does not exists. Try again:");
                fgets(second_name, NAME_SIZE, stdin);
                person2 = find_person(main_list, second_name);
            }
            remove_contact(person1, person2);
            puts("Enter \"6\" to exit the program.");
            puts("Enter any other character to return to the menu.");
            if (getchar() == '6') { function_num = '6'; }
            char c;
            while ((c = getchar()) != '\n') {}
            break;
        }
        case '4':
        { 
            puts("Choose searching criteria:");
            puts("1. Interests.");
            puts("2. Location.");
            puts("3. Education.");
            puts("4. Job.");
            int criteria_num = '0';
            while (criteria_num < '1' || criteria_num > '4') {
                criteria_num = getchar();
                char c;
                while ((c = getchar()) != '\n') {}
            }
            switch (criteria_num) {
            case '1':
            {
                puts("Enter an interest:");
                char interest[INTERESTS_SIZE];
                fgets(interest, INTERESTS_SIZE, stdin);
                list_t* result_list = find_by_interest(main_list, interest);
                node_t* node = result_list->head;
                while (node != NULL) {
                    printf("%s", node->person->name);
                    node = node->next;
                }
                destroy_list(result_list);
                break;
            }
            case '2':
            {
                puts("Enter a city:");
                char city[CITY_SIZE];
                fgets(city, CITY_SIZE, stdin);
                list_t* result_list = find_by_location(main_list, city);
                node_t* node = result_list->head;
                while (node != NULL) {
                    printf("%s", node->person->name);
                    node = node->next;
                }
                destroy_list(result_list);
                break;
            }
            case '3':
            {
                puts("Enter an education:");
                char education[EDUCATION_SIZE];
                fgets(education, EDUCATION_SIZE, stdin);
                list_t* result_list = find_by_education(main_list, education);
                node_t* node = result_list->head;
                while (node != NULL) {
                    printf("%s", node->person->name);
                    node = node->next;
                }
                destroy_list(result_list);
                break;
            }
            case '4':
            {
                puts("Enter a job:");
                char job[JOB_SIZE];
                fgets(job, JOB_SIZE, stdin);
                list_t* result_list = find_by_job(main_list, job);
                node_t* node = result_list->head;
                while (node != NULL) {
                    printf("%s", node->person->name);
                    node = node->next;
                }
                destroy_list(result_list);
                break;
            }
            }
            puts("Enter \"6\" to exit the program.");
            puts("Enter any other character to return to the menu.");
            if (getchar() == '6') { function_num = '6'; }
            char c;
            while ((c = getchar()) != '\n') {}
            break;
        }
        case '5':
        {
            puts("Enter the name of the person whose contacts you want to see:");
            char name[NAME_SIZE];
            fgets(name, NAME_SIZE, stdin);
            person_t* person = find_person(main_list, name);
            if (person != NULL) {
                node_t* node = person->contacts.head;
                while (node != NULL) {
                    printf("%s", node->person->name);
                    node = node->next;
                }
            }
            else {
                puts("No person with such name.");
            }
            puts("Enter \"6\" to exit the program.");
            puts("Enter any other character to return to the menu.");
            if (getchar() == '6') { function_num = '6'; }
            char c;
            while ((c = getchar()) != '\n') {}
            break;
        }
        }
    } while(function_num != '6');
    FILE* output_file = fopen(filename, "w");
    assert(output_file != NULL);
    print_list(main_list, output_file);
    close(output_file);
    destroy_list(main_list);
    return 0;
}