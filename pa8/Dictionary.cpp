//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa8
// Dictionary.cpp
// Implementation of Dictionary ADT
//------------------------------------------------------------------------------

#include "Dictionary.h"

// Global Constants ------------------------------------------------------------
#define RED -1
#define BLACK -2

// Helper Functions ------------------------------------------------------------

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R != nil) {
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R != nil) {
        s.append(R->key);
		if (R->color == RED) {
			s.append(" (RED)");
		}
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::BST_insert(Node* M) {
	if (M == nil) {
		return;
	}
	Node* N = new Node(M->key,M->val);
	N->color = M->color;
	N->left = nil;
	N->right = nil;
    Node* Y = nil;
    Node* X = root;
    while (X != nil) {
        Y = X;
        if (N->key < X->key) {
            X = X->left;
        } else {
            X = X->right;
        }
    }
    N->parent = Y;
    if (Y == nil) {
        root = N;
    } else if (N->key < Y->key) {
        Y->left = N;
    } else {
        Y->right = N;
    }
	num_pairs++;
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        BST_insert(R);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        R->parent = nullptr;
        R->left = nullptr;
        R->right = nullptr;
        delete R;
        num_pairs--;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if (R->key == k || R == nil) {
        return(R);
    }
    if (k < R->key) {
        return(search(R->left, k));
    }
    if (k > R->key) {
        return(search(R->right, k));
    }
    return(nil);
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) {
        throw std::logic_error("Dictonary: findMin(): subtree is empty");
    }
    while (R->left != nil) {
        R = R->left;
    }
    return(R);
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nil) {
        throw std::logic_error("Dictonary: findMax(): subtree is empty");
    }
    while (R->right != nil) {
        R = R->right;
    }
    return(R);
}

Dictionary::Node* Dictionary::findNext(Node* N) {
	if (N->right != nil) {
		return(findMin(N->right));
	}
	Node* Y = N->parent;
	while (Y != nil && N == Y->right) {
		N = Y;
		Y = Y->parent;
	}
	return Y;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
	if (N->left != nil) {
		return(findMax(N->left));
	}
	Node* Y = N->parent;
	while (Y != nil && N == Y->left) {
		N = Y;
		Y = Y->parent;
	}
	return Y;
}

// RBT Helper Functions --------------------------------------------------------

void Dictionary::LeftRotate(Node* N) {
    Node* Y = N->right;
    N->right = Y->left;
    if (Y->left != nil) {
        Y->left->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == nil) {
        root = Y;
    } else if (N == N->parent->left) {
        N->parent->left = Y;
    } else {
        N->parent->right = Y;
    }
    Y->left = N;
    N->parent = Y;
}

void Dictionary::RightRotate(Node* N) {
    Node* Y = N->left;
    N->left = Y->right;
    if (Y->right != nil) {
        Y->right->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == nil) {
        root = Y;
    } else if (N == N->parent->right) {
        N->parent->right = Y;
    } else {
        N->parent->left = Y;
    }
    Y->right = N;
    N->parent = Y;
}

void Dictionary::RB_InsertFixUp(Node* N) {
    Node* Y;
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Y = N->parent->parent->right;
            if (Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        } else {
            Y = N->parent->parent->left;
            if (Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
    Node* W;
    while (N != root && N->color == BLACK) {
        if (N == N->parent->left) {
            W = N->parent->right;
            if (W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                W = N->parent->right;
            }
            if (W->left->color == BLACK && W->right->color == BLACK) {
                W->color = RED;
                N = N->parent;
            } else {
                if (W->right->color == BLACK) {
                    W->left->color = BLACK;
                    W->color = RED;
                    RightRotate(W);
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            W = N->parent->left;
            if (W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                W = N->parent->left;
            }
            if (W->right->color == BLACK && W->left->color == BLACK) {
                W->color = RED;
                N = N->parent;
            } else {
                if (W->left->color == BLACK) {
                    W->right->color = BLACK;
                    W->color = RED;
                    LeftRotate(W);
                    W = N->parent->left;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N) {
    Node* Y = N;
    Node* X;
    int Y_og_color = Y->color;
    if (N->left == nil) {
        X = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        X = N->left;
        RB_Transplant(N, N->left);
    } else {
        Y = findMin(N->right);
        Y_og_color = Y->color;
        X = Y->right;
        if (Y->parent == N) {
            X->parent = Y;
        } else {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }
	if (current == N) {
		current = nil;
	}
    if (Y_og_color == BLACK) {
        RB_DeleteFixUp(X);
    }
	delete N;
}


// Class Constructors & Destructors --------------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

Dictionary::Dictionary() {
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

// Access functions ------------------------------------------------------------

int Dictionary::size() const{
    return(num_pairs);
}

bool Dictionary::contains(keyType k) const{
    if (search(root, k) == nil) {
        return(false);
    }
    return(true);
}

valType& Dictionary::getValue(keyType k) const{
    Node* N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return(N->val);
}

bool Dictionary::hasCurrent() const{
    if (current == nil || current == nullptr) {
        return(false);
    }
    return(true);
}

keyType Dictionary::currentKey() const{
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return(current->key);
}

valType& Dictionary::currentVal() const{
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return(current->val);
}


// Manipulation Procedures -----------------------------------------------------

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* Y = nil;
    Node* X = root;
    Node* Z = new Node(k, v);
	Z->left = nil;
	Z->right = nil;
    Z->color = RED;
    while (X != nil) {
        Y = X;
        if (k < X->key) {
            X = X->left;
        } else if (k > X->key) {
            X = X->right;
        } else {
			X->val = v;
			delete Z;
			return;
		}
    }
    Z->parent = Y;
    if (Y == nil) {
        root = Z;
    } else if (k < Y->key) {
        Y->left = Z;
    } else {
        Y->right = Z;
    } 
    RB_InsertFixUp(Z);
	num_pairs++;
}

void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary:: remove(): key \"" + k + "\" does not exist");
    }
    Node* Z = search(root, k);
    if (current == Z) {
        current = nil;
    }
    RB_Delete(Z);
	num_pairs--;
}

void Dictionary::begin() {
    if (num_pairs == 0) {
        return;
    }
    current = findMin(root);
}

void Dictionary::end() {
    if (num_pairs == 0) {
            return;
    }
    current = findMax(root);
}

void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findPrev(current);
}


// Other functions -------------------------------------------------------------

std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return(s);
}

std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return(s);
}

bool Dictionary::equals(const Dictionary& D) const{
    if (num_pairs != D.num_pairs) {
        return(false);
    }
    std::string tS = "";
    std::string dS = "";
    inOrderString(tS, root);
    D.inOrderString(dS, D.root);
    return(tS == dS);
}

// Overloaded Operators --------------------------------------------------------

std::ostream& operator<<( std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D) {
    if (this != &D) {
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}
