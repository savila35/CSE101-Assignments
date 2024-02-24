//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa5
// List.cpp
// Implementation of a List ADT
//------------------------------------------------------------------------------

#include "List.h"

// Private Constructor ---------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
};

// Class Constructors & Destructors --------------------------------------------

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node* N = L.frontDummy->next;
	while (N != L.backDummy) {
		this->insertBefore(N->data);
		N = N->next;
	}
	moveFront();
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions ------------------------------------------------------------

int List::length() const{
    return(num_elements);
}

ListElement List::front() const{
    if (num_elements == 0) {
        throw std::length_error("List: front(): empty List");
    }
    return(frontDummy->next->data);
}

ListElement List::back() const{
    if (num_elements == 0) {
        throw std::length_error("List: back(): empty List");
    }
    return(backDummy->prev->data);
}

int List::position() const{
    return(pos_cursor);
}

ListElement List::peekNext() const{
    if (num_elements < pos_cursor) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return(afterCursor->data);
}

ListElement List::peekPrev() const{
    if (pos_cursor == 0) {
        throw std::range_error("List: peekPrev(): cursor at front");
    } 
    return(beforeCursor->data);
}


// Manipulation procedures -----------------------------------------------------

void List::clear() {
	moveFront();
    while (num_elements > 0) {
        eraseAfter();
    }
}

void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack() {
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return(beforeCursor->data);
}

ListElement List::movePrev() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: movePrev(): cursor at front");
    } 
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return(afterCursor->data);
}

void List::insertAfter(ListElement x) {
    Node* N = new Node(x);
    afterCursor->prev = N;
    N->next = afterCursor;
    beforeCursor->next = N;
    N->prev = beforeCursor;
    afterCursor = N;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node* N = new Node(x);
    beforeCursor->next = N;
    N->prev = beforeCursor;
    N->next = afterCursor;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (pos_cursor <= 0) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    delete afterCursor;
    afterCursor = beforeCursor->next;
	num_elements--;
}

void List::eraseBefore() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    delete beforeCursor;
    beforeCursor = afterCursor->prev;
    pos_cursor--;
	num_elements--;
}


// Other functions -------------------------------------------------------------

int List::findNext(ListElement x) {
    while (pos_cursor < num_elements) {
        int current = moveNext();
        if (current == x) {
            return(pos_cursor);
        }
    }
    return(-1);
}

int List::findPrev(ListElement x) {
    while (pos_cursor > 0) {
        int current = movePrev();
        if (current == x) {
            return(pos_cursor);
        }
    }
    return(-1); 
}

void List::cleanup() {
    Node* N = frontDummy->next;
    int outIndex = 0;
    while (N != backDummy)
    {
        Node* inner = N->next;
		int inIndex = outIndex + 1;
        while (inner != backDummy)
        {
            if (N->data == inner->data) {
                Node* D = inner;
                if (inner == beforeCursor) {
                    beforeCursor = inner->prev;
                } else if (inner == afterCursor) {
                    afterCursor = inner->next;
                }
                inner->prev->next = inner->next;
                inner->next->prev = inner->prev;
                inner = inner->next;
                delete D;
                num_elements--;
                if (inIndex < pos_cursor) {
                    pos_cursor--;
                }
            } else {
                inner = inner->next;
				inIndex++;
            }
        }
		N = N->next;
		outIndex++;
    }
}

List List::concat(const List &L) const{
    List N;
    Node* node = this->frontDummy->next;
    while (node != backDummy) {
        N.insertBefore(node->data);
        node = node->next;
    }
    Node* M = L.frontDummy->next;
    while (M != L.backDummy) {
        N.insertBefore(M->data);
        M = M->next;
    }
	N.pos_cursor = 0;
	N.beforeCursor = N.frontDummy->next;
	N.afterCursor = N.beforeCursor->next;
    return(N);
}

std::string List::to_string() const{
	if (num_elements == 0) {
		return("()");
	}
    Node* N = frontDummy->next;
    std::string s = "(";
    while(1) {
        s += std::to_string(N->data);
        N = N->next;
        if (N == backDummy) {
            s += ")";
            break;
        }
        s += ",";
    }
    return(s);
}

bool List::equals(const List& R) const{
    Node* t = this->frontDummy->next;
    Node* r = R.frontDummy->next;
    if (this->num_elements != R.num_elements) {
        return(0);
    }
    while(t != this->backDummy && r != R.backDummy) {
        if (t->data != r->data) {
            return(0);
        }
        t = t->next;
        r = r->next;
    }
    return(1);
}

std::ostream& operator<<( std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

bool operator==( const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=( const List& L) {
    if ( this != &L ) {
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}
