#include <stdio.h>
#include <stdlib.h>

typedef struct sll_node sll_node;
struct sll_node {
        int value;
        sll_node *next;
};

typedef struct sll sll;
struct sll {
        sll_node *first;
        sll_node *last;
        int length;
};

sll *sll_create(void);
void sll_delete(sll *list);
sll_node *sll_node_create(int value);
sll_node *sll_node_by_index(int index, sll *list);
sll_node *sll_node_prev_by_pointer(sll_node *node, sll *list);
sll_node *sll_node_prev_by_index(int index, sll *list);
void sll_node_delete_by_pointer(sll_node *node, sll *list);
void sll_node_delete_by_index(int index, sll *list);
sll_node *sll_node_add_at_start(sll_node *node, sll *list);
sll_node *sll_node_add_at_end(sll_node *node, sll *list);
sll_node *sll_node_add_at_index(sll_node *node, sll *list, int index);
sll_node *sll_node_add_at_middle(sll_node *node, sll *list);
sll_node *sll_node_add_before_pointer(sll_node *cur, sll_node *new, sll *list);

sll *sll_create(void)
{
        return calloc(1, sizeof(sll));
}

void sll_delete(sll *list)
{
        if (!list)
                return;
        while (list->first)
                sll_node_delete_by_pointer(list->first, list);
        free(list);
}

sll_node *sll_node_create(int value)
{
        sll_node *node = calloc(1, sizeof(sll_node));

        if (!node)
                return NULL;
        node->value = value;

        return node;
}

sll_node *sll_node_prev_by_pointer(sll_node *node, sll *list)
{
        sll_node *cur, *prev;

        if (!node || !list || !list->length)
                return NULL;

        if (node == list->first)
                return NULL;

        cur = list->first;
        while (cur && cur != node) {
                prev = cur;
                cur = cur->next;
        }
        if (!cur)
                return NULL;

        return prev;
}

sll_node *sll_node_prev_by_index(int index, sll *list)
{
        int cur = 0;
        sll_node *node;

        if (!list || !list->length || index <= 0)
                return NULL;

        --index;
        node = list->first;
        while (node && cur < index) {
                node = node->next;
                ++cur;
        }

        return node;
}

sll_node *sll_node_by_index(int index, sll *list)
{
        return sll_node_prev_by_index(index + 1, list);
}

void sll_node_delete_by_pointer(sll_node *node, sll *list)
{
        sll_node *prev;

        if (!node || !list || !list->length)
                return;

        if (node == list->first) {
                list->first = list->first->next;
        } else {
                if (!(prev = sll_node_prev_by_pointer(node, list)))
                        return;
                prev->next = prev->next->next;
                if (node == list->last)
                        list->last = prev;
        }
        free(node);
        printf("Node %p deleted\n", node);

        if (--list->length == 0)
                list->last = NULL;
}

void sll_node_delete_by_index(int index, sll *list)
{
        sll_node *node;

        node = sll_node_by_index(index, list);
        sll_node_delete_by_pointer(node, list);
}

sll_node *sll_node_add_before_pointer(sll_node *cur, sll_node *new, sll *list)
{
        sll_node *prev;

        if (!cur || !new || !list)
                return NULL;

        if (cur == list->first) {
                return sll_node_add_at_start(new, list);
        } else {
                prev = sll_node_prev_by_pointer(cur, list);
                if (!prev)
                        return NULL;
                new->next = cur;
                prev->next = new;
        }

        ++list->length;

        return new;
}

sll_node *sll_node_add_at_index(sll_node *node, sll *list, int index)
{
        sll_node *cur = sll_node_by_index(index, list);

        if (!cur && list && !list->length)
                return sll_node_add_at_start(node, list);
	else if (index >= list->length)
		return sll_node_add_at_end(node, list);

        return sll_node_add_before_pointer(cur, node, list);
}

sll_node *sll_node_add_at_middle(sll_node *node, sll *list)
{
        int index;

        if (!list)
                return NULL;

        index = (list->length) ? list->length / 2 : 0;
        return sll_node_add_at_index(node, list, index);
}

sll_node *sll_node_add_at_start(sll_node *node, sll *list)
{
        if (!node || !list)
                return NULL;

        if (!list->length) {
                list->first = node;
                list->last = node;
        } else {
                node->next = list->first;
                list->first = node;
        }

        ++list->length;

        return node;
}

sll_node *sll_node_add_at_end(sll_node *node, sll *list)
{
        if (!node || !list)
                return NULL;

        if (!list->length) {
                list->first = node;
                list->last = node;
        } else {
                list->last->next = node;
                list->last = node;
        }

        ++list->length;

        return node;
}

void sll_print_list(sll *list)
{
	if (!list)
		return;

	printf("%p: first -> %p | last -> %p | length -> %d\n", list, list->first, list->last, list->length);
	for (sll_node *node = list->first; node; node = node->next) {
                printf("%p: node value -> %d\n", node, node->value);
	}
	printf("---\n");
}

int main(void)
{
        sll *list1;
        sll_node *node1, *node2, *node3;

        list1 = sll_create();
        node1 = sll_node_create(1);
	node2 = sll_node_create(2);
	node3 = sll_node_create(3);

        sll_node_add_at_start(node1, list1);
        sll_node_add_at_start(node2, list1);
        sll_node_add_at_start(node3, list1);
        sll_node_add_at_end(sll_node_create(4), list1);
        sll_node_add_at_end(sll_node_create(5), list1);
        sll_node_add_at_end(sll_node_create(6), list1);
        sll_node_add_at_end(sll_node_create(7), list1);

	sll_node_add_at_index(sll_node_create(100), list1, 3);
	sll_node_add_at_index(sll_node_create(0), list1, 0);
	sll_node_add_at_index(sll_node_create(999), list1, list1->length - 1);
	sll_node_add_at_index(sll_node_create(777), list1, list1->length);

	sll_node_add_at_middle(sll_node_create(500), list1);
	sll_node_add_at_middle(sll_node_create(50), list1);

	sll_print_list(list1);

        sll_delete(list1);

        return 0;
}
