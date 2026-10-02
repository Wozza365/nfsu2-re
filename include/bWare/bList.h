// bNode / bTNode / bList / bTList
// From dbalatoni13/nfsmw src/Speed/Indep/bWare/Inc/bList.hpp (CC0). Adapted for MSVC 7.1.
// Checked against NFSU2 code: the list-iteration code in 0x43B380 matches with these definitions.
#ifndef BWARE_BLIST_H
#define BWARE_BLIST_H

class bNode {
  public:
    bNode *Next; // offset 0x0, size 0x4
    bNode *Prev; // offset 0x4, size 0x4

    bNode() {}

    ~bNode() {}

    bNode *GetNext() {
        return Next;
    }

    bNode *GetPrev() {
        return Prev;
    }

    bNode *AddBefore(bNode *insert_point) {
        bNode *new_prev = insert_point->Prev;
        bNode *new_next = insert_point->Next; // unused
        new_prev->Next = this;
        insert_point->Prev = this;
        this->Prev = new_prev;
        this->Next = insert_point;
        return this;
    }

    bNode *AddAfter(bNode *insert_point) {
        bNode *new_prev = this->Prev; // unused
        bNode *new_next = insert_point->Next;
        insert_point->Next = this;
        new_next->Prev = this;
        this->Prev = insert_point;
        this->Next = new_next;
        return this;
    }

    bNode *Remove() {
        bNode *next_node = this->Next;
        bNode *prev_node = this->Prev;
        prev_node->Next = next_node;
        next_node->Prev = prev_node;
        return this;
    }
};

template <typename T> class bTNode : public bNode {
  public:
    bTNode() {}

    ~bTNode() {}

    T *GetNext() {
        return (T *)bNode::GetNext();
    }

    T *GetPrev() {
        return (T *)bNode::GetPrev();
    }

    T *AddBefore(T *insert_point) {
        return (T *)bNode::AddBefore(insert_point);
    }

    T *AddAfter(T *insert_point) {
        return (T *)bNode::AddAfter(insert_point);
    }

    T *Remove() {
        return (T *)bNode::Remove();
    }
};

class bList {
    bNode HeadNode; // offset 0x0, size 0x8

  public:
    typedef int (*SortFunc)(bNode *, bNode *);

    bList() {
        this->HeadNode.Next = &this->HeadNode;
        this->HeadNode.Prev = &this->HeadNode;
    }
    ~bList() {}

    bNode *GetNode(int ordinal_number);

    void InitList() {
        this->HeadNode.Next = &this->HeadNode;
        this->HeadNode.Prev = &this->HeadNode;
    }

    int IsEmpty() {
        return static_cast<int>(this->HeadNode.GetNext() == &this->HeadNode);
    }

    bNode *EndOfList() {
        return &this->HeadNode;
    }

    bNode *GetHead() {
        return this->HeadNode.GetNext();
    }

    bNode *GetTail() {
        return this->HeadNode.GetPrev();
    }

    bNode *GetNextCircular(bNode *node) {
        if (node->GetNext() == EndOfList()) {
            return GetHead();
        }
        return node->Next;
    }
    bNode *GetPrevCircular(bNode *node) {
        if (node->GetPrev() == EndOfList()) {
            return GetTail();
        }
        return node->Prev;
    }

    bNode *AddHead(bNode *node) {
        return node->AddAfter(&this->HeadNode);
    }

    bNode *AddTail(bNode *node) {
        return node->AddBefore(&this->HeadNode);
    }

    bNode *AddBefore(bNode *insert_point, bNode *node) {
        return node->AddBefore(insert_point);
    }

    bNode *AddAfter(bNode *insert_point, bNode *node) {
        return node->AddAfter(insert_point);
    }

    bNode *Remove(bNode *node) {
        return node->Remove();
    }

    bNode *RemoveHead() {
        return this->GetHead()->Remove();
    }
    bNode *RemoveTail() {
        return this->GetTail()->Remove();
    }

    int GetNodeNumber(bNode *node) {
        return this->TraversebList(node);
    }

    int IsInList(bNode *node) {
        return this->TraversebList(node);
    }

    int CountElements() {
        return this->TraversebList(0);
    }

    void Sort(long (*check_flip)(bNode *, bNode *)) {} // TODO

    void Sort(SortFunc check_flip);

    void AddTail(bList *list);

    void AddHead(bList *list);

    bNode *AddSorted(SortFunc check_flip) {}; // TODO

    bNode *AddSorted(SortFunc check_flip, bNode *node);

  private:
    void MergeSort(SortFunc cmp);
    int TraversebList(bNode *match_node);
};
template <typename T> class bTList : public bList {
  public:
    typedef T *pointer;
    pointer EndOfList() { return (pointer)bList::EndOfList(); }
    pointer GetHead() { return (pointer)bList::GetHead(); }
};

#endif
