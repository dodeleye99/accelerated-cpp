#ifndef GUARD_Lst_h
#define GUARD_Lst_h

#include <iterator>


/**
 * A custom "category" of classes used to represent a simplified List (implementing a doubly-linked list) 
 * of elements of a particular type.
 * ===============
 * CLASS INVARIANT
 * ===============
 * While constructed:
 * 1) head always points to the first element of the Lst.
 * 1) the left of the head node is always a fixed NULL element representing the reverse end of the Lst.
 * 2) tail always points to a fixed NULL element represnting the forward end of the Lst
 * 3) Non-null elements have been constructed in the range [head, tail)
 * 4) head points to the same position or an earlier position than tail in the Lst
 **/
template <class T> class Lst {

// --- First declare the types to be defined in the Lst ---
private:
    class Node;
    class Iterator;
    class ConstIterator;

// ---- Public (free access) members, representing the interface ---- 
public:
    // ---------- Type definitions ----------

    // type used to represent the type of the elements stored
    typedef T value_type;

    // type used for defining references to an object of value_type
    typedef T& reference;
    // constant reference type used for read-only access
    typedef const T& const_reference;

    // type used for iterating over elements of the contanier.
    typedef typename Lst::Iterator iterator;
    // iterator type used for read-only access to elements
    typedef typename Lst::ConstIterator const_iterator;

    // type used for iterating over elements of the contanier in reverse order
    typedef std::reverse_iterator<iterator> reverse_iterator;

    // reverse iterator type used for read-only access to elements
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // type used to represent size of the container
    typedef std::size_t size_type;

    // type used to represent distance between iterators
    typedef std::ptrdiff_t difference_type;
    
    // --------------- Constructors ---------------

    // default constructor
    Lst() { create(); }

    // copy constructor
    Lst(const Lst& l) { create(l.begin(), l.end()); }

    // fill constructor
    explicit Lst(size_type n, const T& val = T()){ create(n, val); }

    // range constructor
    template <class InputIterator>
    Lst(InputIterator first, InputIterator last) { create(first, last); }
    // --------------- Destructor ---------------
    ~Lst(){ uncreate(); }

    // --------------- Operators ----------------

    // the assignment operator
    Lst& operator=(const Lst& rhs) {

        // check for self-assignment, in which case do nothing.
        if(&rhs != this) {

            // free the Lst nodes in the left hand side
            uncreate();

            // copy elements from the right-hand side to the left-hand side (this object)
            create(rhs.begin(), rhs.end());
        }
        // ensure to return the modified object.
        return *this;
    }

    // --------------- Member functions ---------------

    // ---- Iterators ----

    // outputs an iterator to the first element of the Lst
    iterator begin() { return Iterator(head); }
    // (read-only iterator)
    const_iterator begin() const { return ConstIterator(head); }

    // outputs a reverse iterator to the (actual) last element of the Lst
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    // (read-only reverse iterator)
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    // outputs an iterator to the end of the Lst (one-past the last element)
    iterator end() { return Iterator(tail); }
    // (read-only iterator)
    const_iterator end() const { return ConstIterator(tail); }

    // outputs a reverse iterator to the (actual) first element of the Lst
    reverse_iterator rend()  { return reverse_iterator(begin()); }
    // (read-only reverse iterator)
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    // ---- Capacity functions ----

    // a predicate for whether the Lst is empty (no elements).
    bool empty() const { return head == tail;}

    // outputs the number of elements in the Lst
    size_type size() const {
        // iterate over each element, counting each one read
        size_type i = 0;
        for(const_iterator iter = begin(); iter != end(); ++iter) {
            ++i;
        }
        return i;
    }

    // ---- Modifiers ----

    /**
     * Inserts a given value into the Lst BEFORE the element at the given position,
     * returning an iterator to this inserted element.
     **/
    iterator insert(iterator position, const T& v){ return insert_node(position, v); }

    // adds an element to the end of the Lst.
    void push_back(const T& val)
    {   
        // simply insert the element to the end of the Lst.
        insert(Iterator(tail), val);
    }

    // adds an element to the front of the Lst.
    void push_front(const T&  val)
    {   
        // simply insert the element to the front of the Lst.
        insert(Iterator(head), val);
    }
    
    /**
     * Removes (and destroys) the element at the given position from the Lst, 
     * returning an iterator to the element after it.
     **/
    iterator erase(iterator position){ return erase_node(position); }

    // removes the element at the end of the Lst.
    void pop_back() {
        // simple erase the last element (first in reverse order) of the Lst
        erase(rbegin());
    }

    // removes the element at the front of the Lst.
    void pop_front() {
        // simple erase the first element of the Lst
        erase(begin());
    }
    
    // removes all the elements from the Lst.
    void clear() { erase_all(); }

// ---- Private (class-access only) members, representing the implementation ---- 
private:

    // -------- The main member variables, iterators to different positions of the Vec --------

    // front of the Lst (HEAD POINTER)
    typename Lst::Node* head;
    // back of the Lst  (TAIL POINTER)
    typename Lst::Node* tail;

    // gives the "front" position of the Lst when traversed in reverse order (b, f]
    typename Lst::Node* rhead(){return tail->left;}

    // gives the "back" position of the Lst when traversed in reverse order (b, f]
    typename Lst::Node* rtail(){return head->left;}
    
    // -------- Facilites for constructing and destroying the Lst --------

    /**
     * Does the initial setup of the Lst, initialising null nodes for the 
     * end and reverse-end positions.
     **/
    void create();

    // Creates a Lst of a given capacity, filling it up with a given value      
    void create(size_type, const T&);

    // Creates a Lst out of a sequence values from the range of input iterators [first, last)
    template <class InputIterator> 
    void create(InputIterator, InputIterator);

    // Destroys the elements in the Lst, freeing the memory
    void uncreate();

    /**
     * Implementation of the insert member function, adding a new node containing the given value, 
     * at the position in the Lst just BEFORE the one given.
     **/
    iterator insert_node(iterator, const T&);

    /**
     * Implementation of the erase member function, removing a single element from the Lst, 
     * returning an iterator to the element after it.
     **/
    iterator erase_node(iterator);

    /**
     * Implementation of the clear member function, removing every element from the Lst.
     **/
    void erase_all();

    // -------- Types used to represent the elements in the Lst and how they connect with eachother -------

    /**
     * Represents the values of the Lst, along with the mechanism for how the elements are ordered, 
     * or "linked"/"chained", forming the foundations for how iteration through the Lst is carried out.
     **/
    struct Node {
    
        // represents a pointer to the value of the node;
        T* val;
        // represents the previous adjacent node in the list
        Node* left;
        // represents the next adjacent node in the list
        Node* right;

        // default constructor
        Node() {
            // set all pointers to 0, representing a "null-node"
            val=0; left=0; right=0;
        }

        // construtor which sets its value
        Node(const T& v) {
            // create a copy of the given value, setting the val pointer to its address
            val = new T(v); left=0; right=0;
        }
        // destructor
        ~Node()
        {   
            // only destroy the value if it was dynamically allocated in the first place.
            if(val != 0) {
                delete val;
            }      
        }

        // chain another node to the left of this node
        void left_chain(Node* n) {
            // be sure to first check if this node actually has a left node
            if (left != 0) {
                // retrieve this node's left node, setting its right pointer to the given node,
                left->right = n;
                // then set the given node's left pointer to this left node.
                n->left = left;
            }
            
            // set the given node's right pointer to this node.
            n->right = this;
            // then set this node's left pointer to the given node.
            this->left = n;

            /**
             * --- ILLUSTRATION OF LEFT_CHAIN() ---
             * 
             *    ======       ======       ======       ======
             *      LN   <--->  THIS  <--->   RN         NODE n  (before chain)
             *    ======       ======       ======       ======
             * 
             *    ======       ======       ======       ====== 
             *      LN   <---> NODE n <--->  THIS  <--->   RN    (after chain)
             *    ======       ======       ======       ======
             **/
        }

        // chain another node to the right of this node
        void right_chain(Node* n) {

            // be sure to first check if this node actually has a right node
            if(right != 0) {
                // retrieve this node's right node, setting its left pointer to the given node,
                right->left = n;
                // then set the given node's right pointer to this right node.
                n->right = right;
            }
            
            // set the given node's left pointer to this node.
            n->left = this;
            // then set this node's right pointer to the given node.
            this->right = n;

            /**
             * --- ILLUSTRATION OF RIGHT_CHAIN() ---
             * 
             *    ======       ======       ======       ======
             *      LN   <--->  THIS  <--->   RN         NODE n  (before chain)
             *    ======       ======       ======       ======
             * 
             *    ======       ======       ======       ====== 
             *      LN   <--->  THIS  <---> NODE n <--->   RN    (after chain)
             *    ======       ======       ======       ======
             **/         
        }

        // unchains the left node from this node, replacing it with its left node.
        Node* left_unchain() {

            // Get a pointer to the left node to unchain
            Node* l = left;
            
            // retrieve its left node, setting its right pointer to this node
            l->left->right = this;
            // then set this node's left pointer to this retrieved node
            left = l->left;

            // return the pointer the unchained node rather than destroying it, in case it is still needed
            return l;

            /**
             * --- ILLUSTRATION OF LEFT_UNCHAIN() ---
             * 
             *    ======       ======       ======       ====== 
             *     LLN   <--->   LN   <--->  THIS  <--->   RN    (before chain)
             *    ======       ======       ======       ======
             *                 ^to remove
             *                                          (RETURN)
             *    ======       ======       ======       ======
             *     LLN   <--->  THIS  <--->   RN           LN    (after chain)
             *    ======       ======       ======       ======
             **/
        }

        // unchains the right node from this node, replacing it with its right node.
        Node* right_unchain() {

            // Get a pointer to the right node to unchain
            Node* r = right;
            
            // retrieve its right node, setting its left pointer to this node
            r->right->left = this;
            // then set this node's right pointer to this retrieved node
            right = r->right;

            // return the pointer to the unchained node rather than destroying it, in case it is still needed
            return r;
    
            /**
             * --- ILLUSTRATION OF RIGHT_UNCHAIN() ---
             * 
             *    ======       ======       ======       ====== 
             *      LN   <--->  THIS  <--->   RN   <--->  RRN    (before chain)
             *    ======       ======       ======       ======
             *                              ^to remove
             *                                          (RETURN)
             *    ======       ======       ======       ======
             *      LN   <--->  THIS  <--->  RRN           RN    (after chain)
             *    ======       ======       ======       ======
             **/
        }

        /**
         * Unchains this very node from its adjecent nodes, which become directly joined together,
         * returning a pointer to its right node that takes its position in the Lst.
         **/
        Node* unchain() {
            
            // Get pointers to the left and rights nodes
            Node* l = left;
            Node* r = right;

            // Chain these nodes directly.
            l->right = r;
            r->left  = l;

            // Effectively unchain this node by zeroing the left and right pointers.
            left=right=0;

            // Return the right node pointer, since it will takes this node's position.
            return r;
    
            /**
             * --- ILLUSTRATION OF UNCHAIN() ---
             * 
             *    ======       ======       ======
             *      LN   <--->  THIS  <--->   RN  
             *    ======       ======       ======
             *                 ^to remove
             *                                     (RETURN)
             *          ======       ======         ======
             *            LN   <--->   RN            THIS    (after chain)
             *          ======       ======         ======
             **/
        }

    };

    /**
     * Represents bi-directional iterators that enable one to traverse through the entire Lst. 
     * In reality, it packages or encapsulates Node objects from the user's point of view, 
     * providing an interface for them to access node values and move to adjacent values without
     * having any knowlege of the underlying nodes."
     **/
    class Iterator {
    
    // allow the Lst class to acccess iterator's private members (particularly, its node pointer)
    friend class Lst;
    
    private:
        // a pointer to the node the iterator is currently refering to
        Node* np;
    
    public:
        // ---------- Type definitions ----------
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;


        // ---------- Constructors ----------

        // default constructor
        Iterator() {
            // set node pointer to 0, representing a "null-pointer"
            np=0;
        }

        // copy constructor
        Iterator(const Iterator& it) {
            // simply make node pointer match
            np=it.np;
        }

        // constructor which sets its node pointer. 
        Iterator(Node* p) {
            np=p;
        }

        // ---------- Operators ----------

        // assignment operator
        Iterator& operator=(const Iterator& rhs) {
            // check for self-assignment, in which case do nothing.
            if(&rhs != this) {
                // simply make the node pointer match
                np = rhs.np;
            }
            // ensure to return the modified object.
            return *this;
        }

        // dereference operator, returning a reference to the iterator's (node's) value
        T& operator*() {return *(np->val);}
        // for read-only access
        const T& operator*() const {return *(np->val);}

        // member access operator
        T* operator->() {return *(np->val);}
        // for read-only access
        const T* operator->() const {return *(np->val);}

        // increment operator, advancing to the next iterator
        // (prefix) (++it) 
        Iterator& operator++() {
            // set the node of this iterator to be its right (next) node.
            np = np->right;
            return *this;
        }

        // (postfix) (it++)
        Iterator operator++(int) {   
            // copy this iterator's state
            Iterator old_it = *this; 
            // do prefix increment of this iterator
            operator++();
            // return the iterator with the original state
            return old_it; 
        }

        // decrement operator, moving back to the previous iterator
        // (prefix) (--it) 
        Iterator& operator--() {
            // set the node of this iterator to be its left (previous) node.
            np = np->left;
            return *this;
        }

        // (postfix) (it--)
        Iterator operator--(int) {   
            // copy this iterator's state
            Iterator old_it = *this; 
            // do prefix decrement of this iterator
            operator--();
            // return the iterator with the original state
            return old_it; 
        }

        // equality operator, comparing the equivilence of two iterators by their node pointers
        bool operator==(const Iterator& rhs) const {return np == rhs.np;}
        // negation of the equality operators
        bool operator!=(const Iterator& rhs) const {return !operator==(rhs);}

        // comparing with constant iterators
        bool operator==(const ConstIterator& rhs) const {return rhs.operator==(*this);}
        bool operator!=(const ConstIterator& rhs) const {return rhs.operator!=(*this);}
    };

    /**
     * Represents read-only iterators - they do not allow elements they traverse over to be modified,
     * but only read. 
     * 
     * In reality, it is a wrapper class of Iterator, with all the same operators, 
     * except that operations that involve accessing an element return only a 
     * constant (read-only) reference.
     **/
    class ConstIterator {
        
        // represents the iterator to the element currently being traversed over.
        Iterator iter;
    
    public:
        // ---------- Type definitions ----------
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef const T value_type;
        typedef const T* pointer;
        typedef const T& reference;

        // ---------- Constructors ----------

        // default constructor
        ConstIterator() {
            iter = Iterator();
        }

        // copy constructor
        ConstIterator(const ConstIterator& it) {
            iter=it.iter;
        }

        // constructor which sets its node pointer. 
        ConstIterator(Node* p) {
            iter= Iterator(p);
        }

        ConstIterator(const Iterator& it) {
            iter=it;
        }

        // ---------- Operators ----------

        // assignment operator
        ConstIterator& operator=(const ConstIterator& rhs) {
            // check for self-assignment, in which case do nothing.
            if(&rhs != this) {
                // simply make the inner iterator match
                iter = rhs.iter;
            }
            // ensure to return the modified object.
            return *this;
        }

        // assigning to an Iterator type
        ConstIterator& operator=(const Iterator& rhs) {
            iter = rhs;
            // ensure to return the modified object.
            return *this;
        }

        // dereference operator (read-only), returning a reference to the iterator's (node's) value
        const T& operator*() const {return *iter;}

        // member access operator (read-only access - not allowed to modify the objects)
        const T* operator->() const {return iter.operator->();}

        // increment operator, advancing to the next iterator
        // (prefix) (++it) 
        ConstIterator& operator++() {
            // set the node of this iterator to be its right (next) node.
            ++iter;
            return *this;
        }
        // (postfix) (it++)
        ConstIterator operator++(int) {   
            // copy this iterator's state
            ConstIterator old_it = *this; 
            // do prefix increment of this iterator
            operator++();
            // return the iterator with the original state
            return old_it; 
        }

        // decrement operator, moving back to the previous iterator
        // (prefix) (--it) 
        ConstIterator& operator--() {
            --iter;
            return *this;
        }
        // (postfix) (it--)
        ConstIterator operator--(int) {   
            // copy this iterator's state
            ConstIterator old_it = *this; 
            // do prefix decrement of this iterator
            operator--();
            // return the iterator with the original state
            return old_it; 
        }

        // equality operator, comparing the equivilence of two iterators by their node pointers
        bool operator==(const ConstIterator& rhs) const {return iter == rhs.iter;}
        // negation of the equality operators
        bool operator!=(const ConstIterator& rhs) const {return !operator==(rhs);}

        // comparing with non-constant iterators
        bool operator==(const Iterator& rhs) const {return iter == rhs;}
        bool operator!=(const Iterator& rhs) const {return !operator==(rhs);}


    };

};

template <class T> void Lst<T>::create()
{
    /**
     * Allocate memory and initialise a new "null node" or "dummy node", having
     * the front and back pointers point to its memory location
     **/
    head = tail = new Node();
    
    /**
     * Allocate memory for another "null node", used as the end node
     * for reverse iteration. Link it to the right of the front node
     **/
    head->left = new Node();
    head->left->right = head;
}

template <class T> void Lst<T>::create(size_type n, const T& val)
{   
    // set up initial state of the Lst 
    create();
    
    // add each element to the end of the Lst, one by one.
    for(size_type i=0; i!=n; ++i) {
        push_back(val);
    }
}

template <class T> 
template <class InputIterator> void Lst<T>::create(InputIterator first, InputIterator last)
{   
    // set up initial state of the Lst 
    create();

    // add each element to the end of the Lst, one by one.
    for (InputIterator iter = first; iter != last; ++iter) {
        /**
         * Before adding, be sure (assuming it is possible) to first construct 
         * values of type T out of the ones the iterator points to, to ensure 
         * it is the right type.
         **/
        push_back(T(*iter));
    }
}

template <class T> void Lst<T>::uncreate()
{
    /**
     * (In reverse order) destroy nodes starting from the tail NULL node,
     * stopping once the reverse-tail NULL node is reached
     **/
    while(tail != rtail()) {
        // move the tail pointer to its left node
        tail = tail->left;
        // destroy the node we were just at
        delete tail->right;
    }
    // finally destroy the reverse-tail NULL node.
    delete tail;

    // zero the pointers.
    head = tail = 0;
}

template <class T> 
typename Lst<T>::iterator Lst<T>::insert_node(typename Lst<T>::iterator position, const T& v)
{
    // Create a new node that holds a reference of the given value.
    Node* np= new Node(v);

    // Get the node that the iterator points to.
    Node* node_it = position.np;

    // Add ("chain") the new node to the left of the node at the given position.
    node_it->left_chain(np);

    // Ensure that the head is set to point to the new node if added to the front.
    if(node_it == head){
        head = np;
    }

    // return an iterator to the position of the added node.
    return --position;
}

template <class T> 
typename Lst<T>::iterator Lst<T>::erase_node(typename Lst<T>::iterator position)
{   
    // Get the node that the iterator points to.
    Node* node_it = position.np;
    
    /**
     * Unchain this node from the connections of nodes, returning a pointer to the
     * node taking its place.
     **/
    Node* next = node_it->unchain();

    /**
     * If the element to be deleted is at the front of the Lst, ensure the head is updated
     * to point to the new front element.
     **/
    if(node_it == head){
        head = next;
    }

    // Finally destroy the node to free memory.
    delete node_it;

    // return an iterator to the position of the next node.
    return Iterator(next);
}

template <class T> void Lst<T>::erase_all()
{
    // Get a node pointer to the last element of the Lst
    Node* np = rhead();
    
    // Destroy each element, in reverse order - from the last element to the first element.
    while(np != rtail()) {
        // move the pointer to its left node
        np = np->left;
        // destroy the node we were just at
        delete np->right;      
    }

    // join the end pointers (null nodes)
    rtail()->right = tail;
    tail->left = rtail();

    // set the head pointer to the tail pointer, since the Lst is now empty.
    head = tail;
}

#endif
/**
 * ======================================
 * Illustration of the Lst container type
 * ======================================
 * 
 * ===== EMPTY (DEFAULT STATE) =====
 *                 ======                              Two null/dummy nodes, F_NULL and R_NULL,
 * (START) ------> F_NULL <----- (END)                 marking the end of the Lst when traversed 
 *                 ======                              in forward order (START to END) and in 
 *                 /                                   reverse order respectively.
 *    ======      / 
 *    R_NULL <-->/
 *    ====== 
 * 
 * ===== NON-EMPTY =====
 * 
 *                 ======      ======               ======      ======
 * (START) ------> Node 1 <--> Node 2 <--> ... <--> Node n <--> F_NULL <----- (END)
 *                 ======      ======               ======      ======
 *                 / 
 *    ======      /   
 *    R_NULL <-->/
 *    ======   
 * -----------------------------------------------------
 * ADDING A NODE FROM AN EMPTY LST
 * 
 * The LST initially has start and end pointers pointing
 * to the F_NULL node.
 *                 ======            
 * (START) ------> F_NULL  <----- (END)
 *                 ======
 *                 /
 *    ======      / 
 *    R_NULL <-->/
 *    ======
 *                 ======                ======
 * (START) ------> F_NULL  <----- (END)   Node 1  (to add)
 *                 ======                ======
 *                 /
 *    ======      / 
 *    R_NULL <-->/
 *    ======
 *                 ======        ======
 * (START) ------> Node 1 <====> F_NULL  <----- (END)
 *                 ======        ======
 *                 /
 *    ======      / 
 *    R_NULL <-->/
 *    ======
 * 
 * 1) Set left node of Node 1 to F_NULL's left node (R_NULL)
 * 2) Set right node of Node 1 to F_NULL
 * 3) Set the left node of F_NULL to Node 1
 * 4) Since it was initially empty (F_NULL's left is R_NULL), have the start pointer
 *    point to Node 1.
 * -----------------------------------------------------
 * ADDING A NODE FROM THE END OF A NON-EMPTY LST
 *                 ======        ======                 ======
 * (START) ------> Node 1 <====> F_NULL  <----- (END)   Node 2  (to add)
 *                 ======        ======                 ======
 *                  /
 *    ======       / 
 *    R_NULL <--> /
 *    ======
 *                 ======        ======        ======
 * (START) ------> Node 1 <====> Node 2 <====> F_NULL <----- (END)
 *                 ======        ======        ======
 *                 /
 *   ======       / 
 *   R_NULL <--> /
 *   ======
 * 1) Set the left node of Node 2 to be F_NULL's left node (Node 1)
 * 2) Set the right node of F_NULL's left node (Node 1) to Node 2
 * 3) Set right node of Node 2 to F_NULL
 * 4) Set the left node of F_NULL to Node 2
 * -----------------------------------------------------
 **/
