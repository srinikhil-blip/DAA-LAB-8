
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    int freq;
    int order;
    struct Node *left, *right;
} Node;

Node *createNode(char ch, int freq, int order,
                 Node *left, Node *right) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->ch = ch;
    n->freq = freq;
    n->order = order;
    n->left = left;
    n->right = right;
    return n;
}


int smaller(Node *a, Node *b) {
    if (a->freq != b->freq)
        return a->freq < b->freq;
    return a->order < b->order;
}

Node *extractMin(Node *nodes[], int *size) {
    int min = 0;

    for (int i = 1; i < *size; i++) {
        if (smaller(nodes[i], nodes[min]))
            min = i;
    }

    Node *result = nodes[min];

    for (int i = min; i < *size - 1; i++)
        nodes[i] = nodes[i + 1];

    (*size)--;
    return result;
}

void printCodes(Node *root, int code[], int depth,
                long long *totalBits) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        printf("%c\t%d\t", root->ch, root->freq);

        for (int i = 0; i < depth; i++)
            printf("%d", code[i]);

        printf("\t%d\n", depth);
        *totalBits += (long long)root->freq * depth;
        return;
    }

    code[depth] = 0;
    printCodes(root->left, code, depth + 1, totalBits);

    code[depth] = 1;
    printCodes(root->right, code, depth + 1, totalBits);
}

int main(void) {
    char chars[] = {'a', 'c', 'd', 'e', 'o',
                    'm', 's', 't', 'u'};
    int freq[] = {20, 11, 2, 10, 15,
                  8, 10, 22, 2};

    int n = 9;
    int size = n;
    int nextOrder = n;
    int step = 1;

    Node *nodes[2 * 9 - 1];

    for (int i = 0; i < n; i++)
        nodes[i] = createNode(chars[i], freq[i],
                              i, NULL, NULL);

    printf("Huffman tree construction:\n");

    while (size > 1) {
        Node *x = extractMin(nodes, &size);
        Node *y = extractMin(nodes, &size);

        Node *parent = createNode(
            '\0', x->freq + y->freq, nextOrder++,
            x, y
        );

        printf("Step %d: %d + %d = %d\n",
               step++, x->freq, y->freq, parent->freq);

        nodes[size++] = parent;
    }

    Node *root = nodes[0];
    int code[20];
    long long totalBits = 0;

    printf("\nCharacter\tFrequency\tCode\tLength\n");
    printCodes(root, code, 0, &totalBits);

    
    totalBits *= 100;

    printf("\nTotal characters = 10000\n");
    printf("Total bits = %lld\n", totalBits);
    printf("Memory in bytes = %lld\n", totalBits / 8);

    return 0;
}
