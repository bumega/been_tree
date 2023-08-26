#include <iostream>
#include <cmath>
struct Node {
    int data;
    Node* left;
    Node* right;
};


int sum(int a) {
    int ans = 0;
    a = abs(a);
    while (a != 0) {
        ans+=a % 10;
        a /=10;
    }
    return ans;
}

void AddElement(int data_p, Node** node_p) {
    if (*node_p == NULL) {
        (*node_p) = new Node;
        (*node_p)->data = data_p;
        (*node_p)->left = NULL;
        (*node_p)->right = NULL;
    } else {
        if (sum((*node_p)->data) >= sum(data_p)) {
            AddElement(data_p, &(*node_p)->left);
        } else {
            AddElement(data_p, &(*node_p)->right);
        }
    }
}

void preOrder(Node* rootPtr) {
    if (rootPtr != NULL) {
        std::cout << rootPtr->data << "(" << sum(rootPtr->data) << ")" << ' ';
        preOrder(rootPtr->left);
        preOrder(rootPtr->right);
    }
}
void widthOrder(Node* rootPtr){
    if (rootPtr != NULL) {
        widthOrder(rootPtr->left);
        std::cout << rootPtr->data << "(" << sum(rootPtr->data) << ")" << ' ';
        widthOrder(rootPtr->right);
    }
}
void postOrder(Node* rootPtr) {
    if (rootPtr != NULL) {
        postOrder(rootPtr->left);
        postOrder(rootPtr->right);
        std::cout << rootPtr->data << "(" << sum(rootPtr->data) << ")" << ' ';
    }
}
void printTree(Node* rootPtr, int depth = 0) {
    if (rootPtr != NULL) {
        for (int i = 0; i < depth; i++) {
            std::cout << ' ';
        }
        std::cout << rootPtr->data << "(" << sum(rootPtr->data) << ")" << '\n';

        printTree(rootPtr->left, depth - 2);
        printTree(rootPtr->right, depth + 5);
    }
}


int amount (Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1+amount(root->left)+amount(root->right);
    }
}

int depth (Node* root) {
    if (root != NULL) {
        int l = depth(root->left);
        int r = depth(root->right);
        if (l > r){
            return l+1;
        } else {
            return r+1;
        }
    } else {
        return 0;
    }
}

int search_el2(Node* rootPtr) {
    if (rootPtr == NULL) {
        return 0;
    }
    else if (rootPtr->data % 2 == 0) {
        printf("element %d is even\n", rootPtr->data);
        return 1+search_el2(rootPtr->left)+ search_el2(rootPtr->right);
    } else {
        return search_el2(rootPtr->left)+ search_el2(rootPtr->right);
    }
}

Node** min_el(Node** el) {
    if ((*el)->left != NULL) {
        return  min_el(&(*el)->left);
    } else {
        return el;
    }
}

void del2 (Node** node_p) {
    while ((*node_p) != NULL and (*node_p)->data % 2 == 0) {
        if ((*node_p)->left == NULL and (*node_p)->right == NULL) {
            //std::cout << "yep1\n";
            delete *node_p;
            *node_p = NULL;
            //std::cout << "yep1\n";
            break;
        } else if ((*node_p)->left == NULL) {
            //std::cout << "yep2\n";
            //delete *node_p;
            Node* tmp = *node_p;
            *node_p = (*node_p)->right;
            delete tmp;
        } else if ((*node_p)->right == NULL) {
            //std::cout << "yep3\n";
            Node* tmp = *node_p;
            //delete *node_p;
            *node_p = (*node_p)->left;
            delete tmp;
        } else {
            //std::cout << "yep4\n";
            Node **tmp = min_el(&(*node_p)->right);
            std::cout << (*tmp)->data << "\n";
            (*node_p)->data = (*tmp)->data;
            //std::cout << "yep4\n";
            delete *tmp;
            *tmp = NULL;
        }
    }
    if (*node_p != NULL) {
        del2(&(*node_p)->left);
        del2(&(*node_p)->right);
    }
}

void destruct(Node** root) {
    if (*root != NULL) {
        if ((*root)->left != NULL) {
            destruct(&(*root)->left);
        }
        if ((*root)->right != NULL) {
            destruct(&(*root)->right);
        }
        delete *root;
    }
}

void displayTree(Node* rootPtr, int level){
    std::cout << "Direct order:\n"; // прямой порядок
    preOrder(rootPtr);
    std::cout << "\nSymetry:\n"; // симметричный порядок
    widthOrder(rootPtr);
    std::cout << "\nReverse order:\n"; // обратный порядок
    postOrder(rootPtr);
    std::cout << "\nTree Depth: " << depth(rootPtr); // глубина дерева
    printf("\namoount of elements = %d\n", amount(rootPtr));
    printf("\n---------------\n");
    printf("\namoount of even numbers = %d\n", search_el2(rootPtr));
    //std::cout << " / Node count: " << level;
    std::cout << "\nBinary tree:\n";
    printTree(rootPtr, level); // печать дерева
    std::cout << "\n\n";
}


int main() {
    Node* root = NULL;
    char* tmp = new char[10];
    puts("enter number");
    gets(tmp);
    while(tmp[0] != '\0') {
        AddElement(atoi(tmp), &root);
        printf("%s was added\n", tmp);
        puts("enter number");
        gets(tmp);
    }
    puts("binary tree was built");
    displayTree(root, 20);
    del2(&root);
    printf("-------------------\n");
    printf("tree adter deleting elements\n");
    displayTree(root, 20);
    printf("enter element which you want to add\n");
    printf("----------------------------\n");
    int num;
    scanf("%d", &num);
    AddElement(num, &root);
    printf("%s was added\n", tmp);
    displayTree(root, 20);
    printf("enter element which you want to add\n");
    printf("--------------------------------\n");
    destruct(&root);
    printf("tree successfully deleted\n");
    return 0;
}
