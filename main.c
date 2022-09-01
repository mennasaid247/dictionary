
 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct

{
    char *data;
   struct node *left, *right;
}node;

node *newnode(char *st)
{
    node *n =  malloc(sizeof(node));
    n->data =  malloc(strlen(st) + 1);
    strcpy(n->data, st);
    n->left = n->right = NULL;
    return n;
}

node *insert(char *st, node *root)
{
    if (root == NULL)
    {
        root = newnode(st);
        return root;
    }
    else if (strcasecmp(st, root->data) < 0)
    {
        root->left = insert(st, root->left);
    }
    else if (strcasecmp(st, root->data) > 0)
    {
        root->right = insert(st, root->right);
    }
    return root;
}



node *load()
{
    char st[100];

    node *root = NULL;
    FILE *p = fopen("EN-US-Dictionary.txt", "r");
    if (p == NULL)
    {
        return NULL;
    }
    else
    {
        while (!feof(p))
        {

            fscanf(p, "%[^\n] ", &st);
            root = insert(st, root);
        }
    }

    fclose(p);
    return root;
}

int size(node *root)
{

    if (root == NULL)
        return 0;
    else
        return (1 + size(root->left) + size(root->right));
}

node *search(char *st, node *root)
{
    if (root == NULL)
        return NULL;

    else if (strcasecmp(root->data, st) == 0)
        return root;

    else if (strcasecmp(root->data, st) < 0)
        return search(st, root->right);

    else if (strcasecmp(root->data, st) > 0)
        return search(st, root->left);
}



int height(node *root)
{
    int x = 0;
    int y = 0;
    if (root == NULL || size(root) == 1)
        return 0;

    else
    {

        if (root->left)
        {
            x = 1 + height(root->left);
        }
        if (root->right)
        {
            y = 1 + height(root->right);
        }
    }

    if (x > y)
        return x;

    return y;
}

node* inOrderSuccessor(node* root, node* n)
{
    if (n->right != NULL)
    {
        n = n->right;
        while (n->left)
        {
            n = n->left;
        }
        return n;
    }

    node *succer = NULL;
    node *temp = root;

    while (temp != n)
    {
        if (strcasecmp(temp->data, n->data) > 0)
        {
            succer = temp;
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }

    return succer;
}

node* inOrderPredecessor (node* root, node* n)
{
    if (n->left != NULL)
    {
        n = n->left;
        while (n->right)
        {
            n = n->right;
        }
        return n;
    }

    node *predecessor  = NULL;
    node *temp = root;

    while (temp != n)
    {
        if (strcasecmp(temp->data, n->data) < 0)
        {
            predecessor = temp;
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }

    return predecessor;
}

node *nerest_node_helper(char *st, node *root,node *prev)
{
    if (root == NULL)
        return prev;

    else if (strcasecmp(root->data, st) < 0)
    {
        prev = root;
        return nerest_node_helper(st, root->right,prev);
    }

    else if (strcasecmp(root->data, st) > 0)
    {
        prev = root;
        return nerest_node_helper(st, root->left,prev);
    }
}

node *nerest_node(char *st, node *root)
{
    node *prev = NULL;
    return nerest_node_helper(st, root, prev);
}

char* find_suggest(char *str, node *root )
{char *suggest=malloc(strlen(str)+1);

    node *nearest_sug = nerest_node(str, root);
    node *succer = inOrderSuccessor(root, nearest_sug);
    node *predecessor = inOrderPredecessor(root, nearest_sug);
    strcpy(suggest, nearest_sug->data);
    strcat(suggest, " ");

    if (succer != NULL)
    {
        strcat(suggest, succer->data);
        strcat(suggest, " ");
    }

    if (predecessor != NULL)
    {
        strcat(suggest, predecessor->data);
        strcat(suggest, " ");
    }

    return suggest;

}
void check_sentence(char *sent,node*root)
{
   char *suggest;
    char *token;
    token = strtok(sent, " ");
    while(token != NULL)
    {
          if (search(token, root) != NULL)
        {
            printf("%s - CORRECT \n", token);
        }
         else
        {
       suggest= find_suggest(token, root);
            printf("%s - Incorrect, Suggestions: %s \n", token, suggest);
        }
        token = strtok(NULL, " ");
    }
    printf("\n");

}


int main()
{
    node *root = NULL;
char sentence[1000];
    root = load();
    printf(".................................\n");
    if (root == NULL) printf("Can't Load The Dictionary\n");
    else printf("Dictionary Loaded Successfully...!\n");
    int x = size(root);
    printf(".................................\n");
    printf("Size = %d\n", x);

    int z = height(root);
    printf(".................................\n");
    printf("Height = %d\n", z);

    printf(".................................\n");
   printf("Enter a sentence: \n");
  gets(sentence);
check_sentence(sentence,root);









    return 0;
}


