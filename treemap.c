#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2))
{
    TreeMap *nuevoArbol = (TreeMap *)malloc(sizeof(TreeMap));
    if (nuevoArbol == NULL) return NULL;

    nuevoArbol->root = NULL;
    nuevoArbol->current = NULL;
    nuevoArbol->lower_than = lower_than;

    return nuevoArbol;
}


void insertTreeMap(TreeMap * tree, void* key, void * value)
{
    if (tree == NULL) return;

    // Si el arbol esta vacio
    if (tree->root == NULL)
        tree->root = createTreeNode(key, value);
    else
    {
        // Se ubica al inicio del arbol
        TreeNode *aux = tree->root;
        while (aux != NULL)
        {
            // Si ya se encuentra la clave
            if (is_equal(tree, aux->pair->key, key)) return;
            else // En caso de no encontrarse la clave
            {
                if (tree->lower_than(aux->pair->key, key) == 1)
                {
                    // Si el nodo a insertar es menor que el actual
                    // Si el lado izquierdo es nulo
                    if (aux->left == NULL)
                    {
                        TreeNode *nuevoNodo = createTreeNode(key, value);
                        nuevoNodo->parent = aux;
                        aux->left = nuevoNodo;
                        tree->current = nuevoNodo;
                        return;
                    }
                    else // Si el lado izquierdo no es nulo
                        aux = aux->left;
                }
                else
                {
                    // Si el nodo a insertar es mayor que el actual
                    // Si el lado derecho es nulo
                    if (aux->right == NULL)
                    {
                        TreeNode *nuevoNodo = createTreeNode(key, value);
                        nuevoNodo->parent = aux;
                        aux->right = nuevoNodo;
                        tree->current = nuevoNodo;
                        return;
                    }
                    else // Si el lado derecho no es nulo
                        aux = aux->right;
                }
            }
        }
    }
}

TreeNode * minimum(TreeNode *x)
{
    while (x->left != NULL)
        x = x->left;

    return x;
}


void removeNode(TreeMap *tree, TreeNode *node)
{
    if (tree == NULL || tree->root == NULL) return;

    // Si no tiene hijos
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent->left == node) node->parent->left = NULL;
        else node->parent->right = NULL;
    }
    else
    {
        // Si tiene 2 hijos
        if (node->left != NULL && node->right != NULL)
        {
            return;
        }
        else
        {
            // Si tiene un hijo
            TreeNode *hijo = NULL;
            if (node->left != NULL) hijo = node->left;
            else hijo = node->right;
            hijo->parent = node->parent;
            
            if (node->parent->left == node) node->parent->left = hijo;
            else node->parent->right = hijo;
        }
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key)
{
    if (tree == NULL || tree->root == NULL) return NULL;

    TreeNode *aux = tree->root;
    while (aux != NULL)
    {
        if (is_equal(tree, key, aux->pair->key) == 1)
        {
            tree->current = aux;
            return aux->pair;
        }
        else
        {
            if (tree->lower_than(key, aux->pair->key) == 1)
                aux = aux->left;
            else
                aux = aux->right;
        }
    }
    
    return NULL;
}


Pair *upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair *firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair *nextTreeMap(TreeMap * tree) {
    return NULL;
}
