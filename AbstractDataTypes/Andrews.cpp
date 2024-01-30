//
// Created by safor on 30.1.24.
//

#ifndef __PROGTEST__
#include <cassert>
#include <cstdarg>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <array>
#include <random>
#include <type_traits>

// We use std::set as a reference to check our implementation.
// It is not available in progtest :)
#include <set>

template < typename T >
struct Ref {
    size_t size() const { return _data.size(); }
    const T* find(const T& value) const {
        auto it = _data.find(value);
        if (it == _data.end()) return nullptr;
        return &*it;
    }
    bool insert(const T& value) { return _data.insert(value).second; }
    bool erase(const T& value) { return _data.erase(value); }

    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

private:
    std::set<T> _data;
};

#endif


namespace config {
    // Enable to check that the tree is AVL balanced.
    inline constexpr bool CHECK_DEPTH = true;

    // Disable if your implementation does not have parent pointers
    inline constexpr bool PARENT_POINTERS = true;
}

// TODO implement
template < typename T >
struct Tree {

    ~Tree ()
    {
        delete root;
    }
    size_t size() const
    {
        return TreeSize;
    }
    const T* find(const T& value) const
    {
        return find_rec ( value, root );
    }

    bool insert(T value)
    {

        // no root
        if ( is_empty() )
        {
            root = new Node ( value );
            TreeSize++;
            return true;
        }

        bool success;
        insert_rec ( value, root, success );
        if ( success )
            TreeSize++;
        return success;
    }
    bool erase (const T& value)
    {

        if ( is_empty() )
            return false;

        bool success;
        erase_rec ( value, root, success );
        if ( success )
            TreeSize--;
        return success;
    }

    bool is_empty () const
    {
        return size() == 0;
    }

    struct Node
    {
        Node ( Node * parent, Node * right, Node * left, const T & value )
                : parent ( parent ) , right ( right ), left ( left ), value ( value )
        {};

        Node ( Node * parent, Node * right, Node * left, T && value )
                : parent ( parent ) , right ( right ), left ( left ), value ( std::move ( value ) )
        {};

        Node ( const T & value, Node * parent )
                : parent ( parent ), right ( nullptr ), left ( nullptr ), value ( value )
        {};

        Node (  T && value, Node * parent )
                : parent ( parent ), right ( nullptr ), left ( nullptr ), value ( std :: move ( value ) )
        {};

        Node ( const T & value )
                : parent ( nullptr ), right ( nullptr ), left ( nullptr ), value ( value )
        {};

        Node ( T && value )
                : parent ( nullptr ), right ( nullptr ), left ( nullptr ), value ( std::move ( value ) )
        {};


        Node ( const Node & ) = delete;
        Node ( Node && ) = delete;
        Node operator = ( const Node & ) = delete;
        Node operator = ( Node && ) = delete;

        size_t number_of_children () const
        {
            if ( left && right )
                return 2;
            if ( left || right )
                return 1;
            return 0;
        }
        int sign () const
        {
            return ( right ? right -> height : 0 ) - ( left ? left -> height : 0 );
        }

        void update_height ()
        {
            height = 1 + std::max ( left ? left -> height : 0, right ? right -> height : 0 );
        }

        ~Node ()
        {
            delete right;
            delete left;
        }

        Node * parent = nullptr;
        Node * right = nullptr;
        Node * left = nullptr;
        int height = 1;
        T value;
    };

    // Needed to test the structure of the tree.
    // Replace Node with the real type of your nodes
    // and implementations with the ones matching
    // your attributes.
    struct TesterInterface {
        // using Node = ...
        static const Node *root(const Tree *t) { return t->root; }
        // Parent of root must be nullptr, ignore if config::PARENT_POINTERS == false
        static const Node *parent(const Node *n) { return n->parent; }
        static const Node *right(const Node *n) { return n->right; }
        static const Node *left(const Node *n) { return n->left; }
        static const T& value(const Node *n) { return n->value; }
    };


private:


    const T * find_rec ( const T & value, Node * node ) const
    {
        if ( ! node )
            return nullptr;
        if ( value == node -> value )
            return & node -> value;
        else if ( value < node -> value )
            return find_rec ( value, node -> left );
        else
            return find_rec ( value, node -> right );
    }

    Node * erase_rec ( const T & value, Node * node, bool & success)
    {
        if ( !node )
        {
            success = false;
            return nullptr;
        }
        if ( value < node -> value )
        {
            node -> left = erase_rec ( value, node -> left, success);
        }

        else if ( value > node -> value )
        {
            node -> right = erase_rec ( value, node -> right, success);
        }

        else
        {
            success = true;
            // erase node and find its replacement to return
            node = erase_node ( node );
        }
        if ( ! node )
            return nullptr;
        node -> update_height();
        return rebalance ( node );
    }

    Node * erase_node ( Node * node )
    {
        Node * replacement;
        if ( node -> number_of_children() == 0 )
            replacement = erase_node_no_children ( node );
        else if ( node -> number_of_children() == 1 )
            replacement = erase_node_one_children ( node );
        else
        {
            replacement = erase_node_two_children ( node );
        }
        return replacement;
    }

    Node * insert_rec ( T value, Node * node, bool & success, Node * parent = nullptr )
    {
        if ( !node )
        {
            success = true;
            return new Node ( value, parent );
        }

        if ( value < node -> value )
            node -> left = insert_rec ( value, node -> left, success,node );
        else if ( value > node -> value )
            node -> right = insert_rec ( value, node -> right, success, node );
        else
        {
            success = false;
            return node;
        }
        node = rebalance ( node );
        return node;
    }

    Node * rebalance ( Node * node )
    {
        if ( !node )
            return nullptr;

        node -> update_height();
        const int sign = node -> sign();

        // left unbalance
        if ( sign < -1 )
        {
            // left child has left child. Right rotation
            if ( node -> left -> sign() <= 0 )
            {
                rotate_right ( node );
                return node -> parent;
            }
                // left child has right child. Double rotation
            else if ( node -> left -> sign() >= 1 )
            {
                rotate_left_right ( node );
                return node -> parent;
            }
        }

            // right unbalance
        else if ( sign > 1 )
        {
            // right child has right child. Left rotation
            if ( node -> right -> sign() >= 0 )
            {
                rotate_left ( node );
                return node -> parent;
            }
                // right child has left child. Right left rotation.
            else if ( node -> right -> sign() <= -1 )
            {
                rotate_right_left ( node );
                return node -> parent;
            }
        }
        return node;
    }

    void rotate_left ( Node * x ){
        Node * y = x -> right;
        if ( root == x )
            root = y;
        x -> right = y -> left;
        y -> left = x;
        if ( x -> right )
            x -> right -> parent = x;
        y -> parent = x -> parent;
        if ( y -> parent )
            y -> parent -> left == x ? y -> parent -> left = y : y -> parent -> right = y;
        x -> parent = y;
        x -> update_height();
        y -> update_height();
    }
    void rotate_right ( Node * x )
    {
        Node * y = x -> left;
        if ( root == x )
            root = y;
        x -> left = y -> right;
        y -> right = x;
        if ( x -> left )
            x -> left -> parent = x;
        y -> parent = x -> parent;
        if ( y -> parent )
            y -> parent -> left == x ? y -> parent -> left = y : y -> parent -> right = y;
        x -> parent = y;
        x -> update_height();
        y -> update_height();
    }
    void rotate_left_right ( Node * node )
    {
        rotate_left ( node -> left );
        rotate_right ( node );
    }
    void rotate_right_left ( Node * node )
    {
        rotate_right ( node -> right );
        rotate_left ( node );
    }

    Node * erase_node_no_children ( Node * node )
    {
        Node * parent = node -> parent;
        if ( parent )
        {
            if ( parent -> left == node )
                parent -> left = nullptr;
            else
                parent -> right = nullptr;
        }
        else
        {
            root = nullptr;
        }
        node -> left = nullptr;
        node -> right = nullptr;
        delete node;
        return nullptr;
    }

    Node * erase_node_one_children ( Node * node )
    {
        Node * child = node -> left ? node -> left : node -> right;
        Node * parent = node -> parent;
        if ( !parent )
        {
            root = child;
            child -> parent = nullptr;
            node -> left = nullptr;
            node -> right = nullptr;
            delete node;
            return child;
        }

        if ( parent -> left == node )
            parent -> left = child;
        else
            parent -> right = child;

        child -> parent = parent;
        node -> left = nullptr;
        node -> right = nullptr;
        delete node;
        return child;
    }

    Node * erase_node_two_children ( Node * node )
    {
        // node has both childs
        Node * succ = successor ( node );
        node -> value = succ -> value;
        bool success;
        erase_rec ( node -> value, node -> right, success );
        return node;
    }

    Node * successor ( Node * node ) const
    {
        if ( node -> right )
        {
            return min ( node -> right );
        }
        Node * parent = node -> parent;
        while ( parent && parent -> right == node )
        {
            node = parent;
            parent = parent -> parent;
        }
        return parent;
    }
    Node * predecessor ( Node * node ) const
    {
        if ( node -> left )
        {
            return max ( node -> left );
        }
        Node * parent = node -> parent;
        while ( parent && parent -> left == node )
        {
            node = parent;
            parent = parent -> parent;
        }
        return parent;
    }
    Node * max ( Node * node ) const
    {
        if ( !node )
            return nullptr;
        while ( node -> right )
        {
            node = node -> right;
        }
        return node;
    }
    Node * min ( Node * node ) const
    {
        if ( !node )
            return nullptr;
        while ( node -> left )
        {
            node = node -> left;
        }
        return node;
    }

    Node * find ( const T & value )
    {
        if ( size() == 0 )
            return nullptr;

        Node * current = root;
        while ( current )
        {
            if ( value == current -> value )
                return current;

            if ( value < current -> value )
            {
                current = current -> left;
                continue;
            }
            current = current -> right;
        }
        return nullptr;
    }
    size_t TreeSize = 0;
    Node * root = nullptr;
};


#ifndef __PROGTEST__

struct TestFailed : std::runtime_error {
    using std::runtime_error::runtime_error;
};

std::string fmt(const char *f, ...) {
    va_list args1;
    va_list args2;
    va_start(args1, f);
    va_copy(args2, args1);

    std::string buf(vsnprintf(nullptr, 0, f, args1), '\0');
    va_end(args1);

    vsnprintf(buf.data(), buf.size() + 1, f, args2);
    va_end(args2);

    return buf;
}

template < typename T >
struct Tester {
    Tester() = default;

    void size() const {
        size_t r = ref.size();
        size_t t = tested.size();
        if (r != t) throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
    }

    void find(const T& x) const {
        auto r = ref.find(x);
        auto t = tested.find(x);
        bool found_r = r != nullptr;
        bool found_t = t != nullptr;

        if (found_r != found_t) _throw("Find mismatch", found_r);
        if (found_r && *t != x) throw TestFailed("Find: found different value");
    }

    void insert(const T& x, bool check_tree_ = false) {
        auto succ_r = ref.insert(x);
        auto succ_t = tested.insert(x);
        if (succ_r != succ_t) _throw("Insert mismatch", succ_r);
        size();
        if (check_tree_) check_tree();
    }

    void erase(const T& x, bool check_tree_ = false) {
        bool succ_r = ref.erase(x);
        auto succ_t = tested.erase(x);
        if (succ_r != succ_t) _throw("Erase mismatch", succ_r);
        size();
        if (check_tree_) check_tree();
    }

    struct NodeCheckResult {
        const T* min = nullptr;
        const T* max = nullptr;
        int depth = -1;
        size_t size = 0;
    };

    void check_tree() const {
        using TI = typename Tree<T>::TesterInterface;
        auto ref_it = ref.begin();
        bool check_value_failed = false;
        auto check_value = [&](const T& v) {
            if (check_value_failed) return;
            check_value_failed = (ref_it == ref.end() || *ref_it != v);
            if (!check_value_failed) ++ref_it;
        };

        auto r = check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);
        size_t t_size = tested.size();

        if (t_size != r.size) throw TestFailed(
                    fmt("Check tree: size() reports %zu but expected %zu.", t_size, r.size));

        if (check_value_failed) throw TestFailed(
                    "Check tree: element mismatch");

        size();
    }

    template < typename Node, typename F >
    NodeCheckResult check_node(const Node* n, const Node* p, F& check_value) const {
        if (!n) return {};

        using TI = typename Tree<T>::TesterInterface;
        if constexpr(config::PARENT_POINTERS) {
            if (TI::parent(n) != p)
            {
                throw TestFailed("Parent mismatch.");
            }
        }

        auto l = check_node(TI::left(n), n, check_value);
        check_value(TI::value(n));
        auto r = check_node(TI::right(n), n, check_value);

        if (l.max && !(*l.max < TI::value(n)))
            throw TestFailed("Max of left subtree is too big.");
        if (r.min && !(TI::value(n) < *r.min))
            throw TestFailed("Min of right subtree is too small.");

        if (config::CHECK_DEPTH && abs(l.depth - r.depth) > 1) throw TestFailed(fmt(
                    "Tree is not avl balanced: left depth %i and right depth %i.",
                    l.depth, r.depth
            ));

        return {
                l.min ? l.min : &TI::value(n),
                r.max ? r.max : &TI::value(n),
                std::max(l.depth, r.depth) + 1, 1 + l.size + r.size
        };
    }

    static void _throw(const char *msg, bool s) {
        throw TestFailed(fmt("%s: ref %s.", msg, s ? "succeeded" : "failed"));
    }

    Tree<T> tested;
    Ref<T> ref;
};


void test_insert() {
    Tester<int> t;

    for (int i = 0; i < 10; i++)
    {
        t.insert(i, true);
    }
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
    for (int i = -10; i < 20; i++) t.find(i);
}

void test_erase() {
    Tester<int> t;

    for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = 3; i < 22; i += 2) {
        t.erase(i, true);
    }
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = 0; i < 10; i++)
    {
        t.insert((1 + i * 13) % 17 - 8, true);
    }
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = -4; i < 10; i++)
    {
        if ( i == 6 )
        {
            int b = 2;
        }
        t.erase(i, true);
    }
    for (int i = -10; i < 20; i++) t.find(i);
}

enum RandomTestFlags : unsigned {
    SEQ = 1, NO_ERASE = 2, CHECK_TREE = 4
};

void test_random(size_t size, unsigned flags = 0) {
    Tester<size_t> t;
    std::mt19937 my_rand(24707 + size);

    bool seq = flags & SEQ;
    bool erase = !(flags & NO_ERASE);
    bool check_tree = flags & CHECK_TREE;

    for (size_t i = 0; i < size; i++)
        t.insert(seq ? 2*i : my_rand() % (3*size), check_tree);

    t.check_tree();

    for (size_t i = 0; i < 3*size + 1; i++) t.find(i);

    for (size_t i = 0; i < 30*size; i++) switch (my_rand() % 5) {
            case 1: t.insert(my_rand() % (3*size), check_tree);
                break;
            case 2: if (erase) t.erase(my_rand() % (3*size), check_tree);
                break;
            default:
                t.find(my_rand() % (3*size));
        }

    t.check_tree();
}

int mainAndr() {
    try {
        std::cout << "Insert test..." << std::endl;
        test_insert();

        std::cout << "Erase test..." << std::endl;
        test_erase();

        std::cout << "Tiny random test..." << std::endl;
        test_random(20, CHECK_TREE);

        std::cout << "Small random test..." << std::endl;
        test_random(200, CHECK_TREE);

        std::cout << "Big random test..." << std::endl;
        test_random(50000);

        std::cout << "Big sequential test..." << std::endl;
        test_random(50000, SEQ);

        std::cout << "All tests passed." << std::endl;
    } catch (const TestFailed& e) {
        std::cout << "Test failed: " << e.what() << std::endl;
    }
}

#endif


