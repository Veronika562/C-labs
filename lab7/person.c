#include "person.h"

void add_contact(person_t* person1, person_t* person2) {
    add_to_list(&person1->contacts, person2);
    add_to_list(&person2->contacts, person1);
}

void remove_contact(person_t* person1, person_t* person2) {
    remove_from_list(&person1->contacts, person2);
    remove_from_list(&person2->contacts, person1);
}

list_t* find_by_interest(list_t* list, char interest[]) {
    list_t* result_list = (list_t*)malloc(sizeof(list_t));
    assert(result_list != NULL);
    result_list->head = result_list->tail = NULL;
    result_list->size = 0;
    node_t* node = list->head;
    while (node != NULL) {
        if (strcmp(node->person->interests, interest) == 0) {
            add_to_list(result_list, node->person);
        }
        node = node->next;
    }
    return result_list;
}

list_t* find_by_location(list_t* list, char city[]) {
    list_t* result_list = (list_t*)malloc(sizeof(list_t));
    assert(result_list != NULL);
    result_list->head = result_list->tail = NULL;
    result_list->size = 0;
    node_t* node = list->head;
    while (node != NULL) {
        if (strcmp(node->person->city, city) == 0) {
            add_to_list(result_list, node->person);
        }
        node = node->next;
    }
    return result_list;
}

list_t* find_by_education(list_t* list, char education[]) {
    list_t* result_list = (list_t*)malloc(sizeof(list_t));
    assert(result_list != NULL);
    result_list->head = result_list->tail = NULL;
    result_list->size = 0;
    node_t* node = list->head;
    while (node != NULL) {
        if (strcmp(node->person->education, education) == 0) {
            add_to_list(result_list, node->person);
        }
        node = node->next;
    }
    return result_list;
}

list_t* find_by_job(list_t* list, char job[]) {
    list_t* result_list = (list_t*)malloc(sizeof(list_t));
    assert(result_list != NULL);
    result_list->head = result_list->tail = NULL;
    result_list->size = 0;
    node_t* node = list->head;
    while (node != NULL) {
        if (strcmp(node->person->job, job) == 0) {
            add_to_list(result_list, node->person);
        }
        node = node->next;
    }
    return result_list;
}

person_t* find_person(list_t* list, char name[]) {
    node_t* node = list->head;
    while (node != NULL) {
        if (strcmp(node->person->name, name) == 0) {
            return node->person;
        }
        node = node->next;
    }
    return NULL;
}

void add_to_list(list_t* list, person_t* new_person) {
    node_t* node = list->head;
    while (node != NULL) {
        if (strcmp(node->person->name, new_person->name) == 0) { 
            node->person = new_person;
            return; 
        }
        node = node->next;
    }
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    assert(new_node != NULL);
    new_node->prev = list->tail;
    new_node->next = NULL;
    new_node->person = new_person;
    if (list->size == 0) {
        list->head = list->tail = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    ++list->size;
}

void remove_from_list(list_t* list, person_t* person) {
    node_t* node = list->head;
    while (node != NULL) {
        if (node->person == person) {
            if (node == list->head) {
                list->head = list->head->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                }     
            }
            else if (node == list->tail) {
                list->tail = list->tail->prev;
                list->tail->next = NULL;
            }
            else {
                node->next->prev = node->prev;
                node->prev->next = node->next;
            }
            free(node);
            --list->size;
            return;
        }
        node = node->next;
    }
}

list_t* read_from_file(char file_name[]) {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    assert(list != NULL);
    list->head = list->tail = NULL;
    list->size = 0;
    FILE* input_file = fopen(file_name, "r");
    assert(input_file != NULL);
    while (!feof(input_file)) {
        person_t* new_person = (person_t*)malloc(sizeof(person_t));
        assert(new_person != NULL);
        new_person->contacts.head = new_person->contacts.tail = NULL;
        new_person->contacts.size = 0;
        fgets(new_person->name, NAME_SIZE, input_file);
        fgets(new_person->city, CITY_SIZE, input_file);
        fgets(new_person->education, EDUCATION_SIZE, input_file);
        fgets(new_person->job, JOB_SIZE, input_file);
        fgets(new_person->interests, INTERESTS_SIZE, input_file);
        char ignored[11];
        fgets(ignored, 11, input_file);
        while (getc(input_file) != '\n' && !feof(input_file)) {
            char contact_name[NAME_SIZE];
            fgets(contact_name, NAME_SIZE, input_file);
            person_t* contact = find_person(list, contact_name);
            if (contact == NULL) {
                contact = (person_t*)malloc(sizeof(person_t));
                assert(contact != NULL);
                contact->contacts.head = contact->contacts.tail = NULL;
                contact->contacts.size = 0;
                strcpy(contact->name, contact_name);
                add_to_list(list, contact);
            }
            add_contact(new_person, contact);
        }
        add_to_list(list, new_person);
    }
    close(input_file);
    return list;
}

void print_list(list_t* list, FILE* file) {
    node_t* node = list->head;
    int count;
    for (count = 0; count < list->size; ++count) {
        print_person(node->person, file);
        if (count < list->size - 1) {
            fprintf(file, "\n");
        }
        node = node->next;
    }
}

void print_person(person_t* person, FILE* file) {
    fprintf(file, "%s", person->name);
    fprintf(file, "%s", person->city);
    fprintf(file, "%s", person->education);
    fprintf(file, "%s", person->job);
    fprintf(file, "%s", person->interests);
    fprintf(file, "Contacts:\n");
    node_t* node = person->contacts.head;
    while (node != NULL) {
        fprintf(file, " %s", node->person->name);
        node = node->next;
    }
}

void destroy_list(list_t* list) {
    node_t* node = list->head;
    while (node != NULL) {
        node_t* next = node->next;
        free(node);
        node = next; 
    }
}
