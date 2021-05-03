#include "list.h"

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& list) : count_(0), min_(nullptr)
{
    if (list.count_ == 0)
    {
        return;
    }
    Node* curr = list.min_;
    do
    {
        this->insertItem(curr->item_);
        curr = curr->next_;
    } while (curr != nullptr);
}

SinglyLinkedList::~SinglyLinkedList()
{
}

int SinglyLinkedList::operator[] (const int index) const
{
    Node* curr = this->min_;
    for (int i = 0; i < index; i++)
    {
        if (curr == nullptr)
        {
            throw "Index error";
        }
        curr = curr->next_;
    }
    return curr->item_;
}

SinglyLinkedList operator+(SinglyLinkedList& list1, SinglyLinkedList& list2)
{
    SinglyLinkedList newList = list1;
    SinglyLinkedList::Node* curr = list2.min_;
    do
    {
        newList.insertItem(curr->item_);
        curr = curr->next_;
    } while (curr != nullptr);
    return newList;
}

SinglyLinkedList operator-(SinglyLinkedList& list1, SinglyLinkedList& list2)
{
    SinglyLinkedList newList = list1;
    SinglyLinkedList::Node* curr = list2.min_;
    do
    {
        newList.deleteItem(curr->item_);
        curr = curr->next_;
    } while (curr != nullptr);
    return newList;
}

SinglyLinkedList operator*(SinglyLinkedList& list1, SinglyLinkedList& list2)
{
    SinglyLinkedList newList;
    SinglyLinkedList::Node* curr = list1.min_;
    do
    {
        if (list2.searchItem(curr->item_))
        {
            newList.insertItem(curr->item_);
        }
        curr = curr->next_;
    } while (curr != nullptr);
    return newList;
}

void SinglyLinkedList::insertMin(SinglyLinkedList::Node* x)
{
    x->next_ = this->min_;
    this->min_ = x;
    this->count_++;
}

void SinglyLinkedList::insertMax(SinglyLinkedList::Node* x)
{
    this->max_->next_ = x;
    this->max_ = x;
    this->count_++;
}

bool SinglyLinkedList::insertNode(SinglyLinkedList::Node* x)
{
    if (this->count_ == 0)
    {
        this->min_ = x;
        this->max_ = x;
        this->count_++;
        return true;
    }

    if (x->item_ == this->min_->item_ || x->item_ == this->max_->item_)
    {
        return false;
    }

    if (this->count_ == 1)
    {
        if (x->item_ > this->min_->item_)
        {
            insertMax(x);
        }
        else
        {
            insertMin(x);
        }
        return true;
    }

    if (x->item_ < this->min_->item_)
    {
        insertMin(x);
        return true;
    }

    if (this->count_ == 2)
    {

        if (x->item_ > this->min_->item_ && x->item_ < this->max_->item_)
        {
            this->min_->next_ = x;
            x->next_ = this->max_;
            this->count_++;
        }
        else
        {
            insertMax(x);
        }
        return true;
    }
    else
    {
        Node* prev = min_;
        Node* curr = min_->next_;
        if (x->item_ < prev->item_)
        {
            insertMin(x);
            return true;
        }
        do
        {
            if (x->item_ == curr->item_)
            {
                return false;
            }
            if (x->item_ > prev->item_ && x->item_ < curr->item_)
            {
                prev->next_ = x;
                x->next_ = curr;
                this->count_++;
                return true;
            }
            curr = curr->next_;
            prev = prev->next_;
        } while (curr != nullptr);
        insertMax(x);
        return true;
    }
}

void SinglyLinkedList::deleteNode(SinglyLinkedList::Node* x)
{
    if (this->count_ == 0)
    {
        throw - 1;
    }
    else if (this->count_ == 1)
    {
        delete this->min_;
        this->min_ = nullptr;
        this->max_ = nullptr;
    }
    else if (this->count_ == 2)
    {
        if (x == this->min_)
        {
            delete this->min_;
            this->min_ = this->max_;
        }
        else
        {
            delete this->max_;
            this->max_ = this->min_;
        }
    }
    else
    {
        Node* prev = min_;
        Node* curr = min_->next_;
        if (x == prev)
        {
            delete prev;
            this->min_ = curr;
            this->count_--;
            return;
        }
        do
        {
            if (x == curr)
            {
                prev->next_ = x->next_;
                if (x->next_ == nullptr)
                {
                    this->max_ = prev;
                }
                delete x;
                this->count_--;
                return;
            }
            prev = prev->next_;
            curr = curr->next_;
        } while (curr != nullptr);
    }
    this->count_--;
}

SinglyLinkedList::Node* SinglyLinkedList::searchNode(int item) const
{
    SinglyLinkedList::Node* curr = this->min_;
    do
    {
        if (curr->item_ == item)
        {
            return curr;
        }
        curr = curr->next_;
    } while (curr != nullptr);
    return nullptr;
}

SinglyLinkedList::Node* SinglyLinkedList::searchSuccessor(int item) const
{
    if (this->count_ == 0)
    {
        return nullptr;
    }
    Node* curr = this->min_;
    do
    {
        if (curr->item_ > item)
        {
            return curr;
        }
        curr = curr->next_;
    } while (curr != nullptr);
    return nullptr;
}

SinglyLinkedList::Node* SinglyLinkedList::searchPredecessor(int item) const
{
    if (this->count_ == 0)
    {
        return nullptr;
    }
    else if (this->count_ == 1 && this->min_->item_ < item)
    {
        return this->min_;
    }
    else if (this->count_ == 2)
    {
        if (this->min_->item_ > item)
        {
            return nullptr;
        }
        else if (this->min_->item_ < item && this->max_->item_ > item)
        {
            return this->min_;
        }
        else
        {
            return this->max_;
        }
    }
    else
    {
        Node* prev = this->min_;
        Node* curr = this->min_->next_;
        do
        {
            if (curr->item_ == item)
            {
                return prev;
            }
            curr = curr->next_;
            prev = prev->next_;
        } while (curr != nullptr);
        return this->max_;
    }
}

bool SinglyLinkedList::insertItem(int item)
{
    return insertNode(new Node(item));
}

bool SinglyLinkedList::searchItem(int item) const
{
    Node* node = searchNode(item);
    if (node == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool SinglyLinkedList::deleteItem(int item)
{
    if (this->count_ == 0)
    {
        return false;
    }
    Node* curr = this->min_;
    do
    {
        if (curr->item_ == item)
        {
            deleteNode(curr);
            return true;
        }
        curr = curr->next_;
    } while (curr != nullptr);
    return false;
}

int SinglyLinkedList::min() const
{
    return this->min_->item_;
}

int SinglyLinkedList::max() const
{
    return this->max_->item_;
}

int SinglyLinkedList::getCount() const
{
    return this->count_;
}

int SinglyLinkedList::successor(int item) const
{
    return searchSuccessor(item)->item_;
}

int SinglyLinkedList::predecessor(int item) const
{
    return searchPredecessor(item)->item_;
}

void SinglyLinkedList::outAll()
{
    if (this->count_ == 0)
    {
        std::cout << std::endl;
        return;
    }
    Node* curr = this->min_;
    do
    {
        std::cout << curr->item_ << ' ';
        curr = curr->next_;
    } while (curr != nullptr);
    std::cout << std::endl;
}

void SinglyLinkedList::toArray(int* arr)
{
    int count = this->count_;
    for (int i = 0; i < count; i++)
    {
        arr[i] = this->operator[](i);
    }
}

void SinglyLinkedList::include(SinglyLinkedList& list)
{
    Node* curr = list.min_;
    do
    {
        this->insertItem(curr->item_);
        curr = curr->next_;
    } while (curr != nullptr);
}

void SinglyLinkedList::exclude(SinglyLinkedList& list)
{
    Node* curr = list.min_;
    do
    {
        this->deleteItem(curr->item_);
        curr = curr->next_;
    } while (curr != nullptr);
}

void SinglyLinkedList::intersect(SinglyLinkedList& list)
{
    if (this->count_ == 0)
    {
        return;
    }
    Node* prev = this->min_;
    if (this->count_ == 1)
    {
        if (!list.searchItem(prev->item_))
        {
            this->deleteNode(prev);
        }
        return;
    }
    Node* curr = prev->next_;
    if (this->count_ == 2)
    {
        if (!list.searchItem(prev->item_))
        {
            this->deleteNode(prev);
        }
        if (!list.searchItem(curr->item_))
        {
            this->deleteNode(curr);
        }
        return;
    }
    do
    {
        if (!list.searchItem(prev->item_))
        {
            deleteNode(prev);
            prev = curr;
            curr = curr->next_;
            if (this->count_ <= 2)
            {
                this->intersect(list);
                return;
            }
        }
        else
        {
            break;
        }
    } while (curr != nullptr);
    do
    {
        if (!list.searchItem(curr->item_)) // HERE
        {
            prev->next_ = curr->next_;
            this->deleteNode(curr);
            if (prev == nullptr)
            {
                return;
            }
            curr = prev->next_;
        }
        else
        {
            prev = prev->next_;
            curr = curr->next_;
        }
    } while (curr != nullptr);
}
