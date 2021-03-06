/**
 * \file ast.c
 * \author Afnan Enayet
 *
 * Function implementations to build and construct an abstract syntax tree.
 * These functions can be invoked via bison.
 */

#include <stdbool.h>
#include <stdlib.h>

#include "ast.h"
#include "vector.h"

// Define the global root (NULL at default to indicate it hasn't been
// initialized)
ast_node_t *ast_root = NULL;

/**
 * \brief Retrieve the root node of the AST
 *
 * If it does not already exist then it will be initialized and allocated.
 * This function returns a pointer to the existing global variable, which
 * can be ignored, as you can just reference `ast_root`.
 */
ast_node_t *get_root() {
    // If root exists, just return a pointer to the root
    if (ast_root != NULL)
        return ast_root;

    ast_root = create_node();
    return ast_root;
}

/**
 * \brief Create/allocate an AST node
 *
 * This initializes a node with no type.
 */
ast_node_t *create_node() {
    ast_node_t *node = malloc(sizeof(ast_node_t));
    return node;
}

/**
 * \brief Create/allocate an AST node with the supplied type.
 *
 * This initializes a node with the provided type
 */
ast_node_t *create_node_type(const type_t type) {
    ast_node_t *node = create_node();
    node->n_type = type;
    return node;
}

/**
 * \brief Create/allocate an AST node with the supplied type and data struct
 *
 * This is a convenience function to initialize a node with a type and some
 * supplied data.
 */
ast_node_t *create_node_type_data(const type_t type, const node_data_u data) {
    ast_node_t *node = create_node_type(type);
    node->data = data;
    return node;
}

/**
 * \brief Delete a provided AST node
 *
 * Deletes an AST node, given a pointer. This will free the node and its
 * internal structs.
 */
void delete_node(ast_node_t *node) {
    switch (node->n_type) {
    case T_SEQ:
        vector_delete(node->data.sequence.children);
        break;
    case T_FUNC:
        free(node->data.func.name);
        break;
    case T_VAR:
        free(node->data.var.id);
        break;
    case T_CONST:
        free(node->data.constant.id);
        break;
    default:
        break;
    }
    free(node);
}

/**
 * \brief Convenience function to create a sequence AST node
 *
 * \return A new node of type `T_SEQ` and an allocated vector
 *     for the node's children
 */
ast_node_t *create_node_seq() {
    node_data_u data;
    data.sequence = (seq_n){vector_new()};
    ast_node_t *node = create_node_type_data(T_SEQ, data);
    return node;
}
