#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
        struct list *next;

        long int id;
};

struct list *list_init(long int id)
{
        struct list *head;

        head = malloc(sizeof(struct list));

        head->id = id;
        head->next = NULL;
}

void list_add(struct list *head, long int id)
{
        struct list *node;
        struct list *curr = head;

        node = malloc(sizeof(struct list));

        node->id = id;
        node->next = NULL;

        if (curr == NULL)
                head = node;

        while (curr->next) {
                curr = curr->next;
        }

        curr->next = node;
}

//冒泡排序
struct list *list_sort(struct list *head)
{
        struct list *prev = NULL;
        struct list *next = NULL;
        struct list *tail = NULL;
        struct list *curr = head;

        if (head == NULL)
                return NULL;

        while (curr != tail) {
                while (curr) {
                        next = curr->next;
                        if (next == NULL || next == tail) {
                                tail = curr;
                                prev = NULL;
                                curr = curr->next;
                                break;
                        }

                        if (curr->id > next->id) {
                                if (prev != NULL)
                                        prev->next = next;
                                else
                                        head = next;
                                curr->next = next->next;
                                next->next = curr;
                                prev = next;
                        } else {
                                prev = curr;
                                curr = curr->next;
                        }
                }

                curr = head;
        }

        return head;
}

void list_travel(struct list *head)
{
        int line = 0;
        struct list *curr = head;

        printf("list travel: \n");
        while(curr) {
                if (line % 10) {
                        printf("%5d ", curr->id);
                        if (line % 10 == 9)
                                printf("\n");
                } else {
                        printf("\t%5d ", curr->id);
                        line = 0;
                }
                curr = curr->next;
                line++;
        }
        printf("\n");
}

void list_reverse(struct list **head)
{
        struct list *prev = NULL;
        struct list *next = NULL;
        struct list *curr = *head;

        if (curr == NULL)
                return ;

        while(curr) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
        }

        *head = prev;
}

void list_destroy(struct list **head)
{
        struct list *curr = *head;
        struct list *next;

        while (curr) {
                next = curr->next;
                free(curr);
                curr = next;
        }

        *head = NULL;
}

#define RANDOM_SIZE     (100)

int main(int argc, char *argv[])
{
        long int i, count;
        struct list *head = list_init(1);

        count = random() % RANDOM_SIZE;
        for (i = 0; i < count; i++) {
                list_add(head, random() % RANDOM_SIZE);
        }

        list_travel(head);
        //list_reverse(&head);

        head = list_sort(head);

        list_travel(head);

        list_destroy(&head);

        printf("head: %p\n", head);

        return 0;
}
