#include "Dictionary.h"

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
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
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
	if (R == nil) {
		return(nil);
	}
    if (R->key == k) {
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

void Dictionary::transplant(Node* U, Node* V) {
    if (U->parent == nil) {
        root = V;
    } else if (U == U->parent->left) {
        U->parent->left = V;
    } else {
        U->parent->right = V;
    }
    if (V != nil) {
        V->parent = U->parent;
    }
}

// Private Constructor ---------------------------------------------------------

// Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Class Constructors & Deconstructors -----------------------------------------

Dictionary::Dictionary() {
    nil = new Node("nil", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("nil", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary(){
    clear();
    delete nil;
}


// Access functions -------------------------------------------------------------

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


// Manipulation procedures -----------------------------------------------------

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
        num_pairs++;
    } else if (k < Y->key) {
        Y->left = Z;
        num_pairs++;
    } else if (k > Y->key) {
        Y->right = Z;
        num_pairs++;
    } else {
        Y->val = v;
        delete Z;
    }
}

void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary:: remove(): key \"" + k + "\" does not exist");
    }
    Node* Z = search(root, k);
    if (current == Z) {
        current = nil;
    }
    if (Z->left == nil) {
        transplant(Z, Z->right);
		delete Z;
    } else if (Z->right == nil) {
        transplant(Z, Z->left);
		delete Z;
    } else {
        Node* Y = findMin(Z->right);
        if (Y->parent != Z) {
            transplant(Y, Y->right);
            Y->right = Z->right;
            Y->right->parent = Y;
        }
        transplant(Z, Y);
        Y->left = Z->left;
        Y->left->parent = Y;
		delete Z;
    }
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
