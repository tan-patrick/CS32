#include "Multiset.h"

        #define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

        void thisFunctionWillNeverBeCalled()
        {
            Multiset();
            (Multiset(Multiset()));
            CHECKTYPE(&Multiset::operator=,  Multiset& (Multiset::*)(const ItemType&));
            CHECKTYPE(&Multiset::empty,      bool (Multiset::*)() const);
            CHECKTYPE(&Multiset::size,       int  (Multiset::*)() const);
            CHECKTYPE(&Multiset::uniqueSize, int  (Multiset::*)() const);
            CHECKTYPE(&Multiset::insert,     bool (Multiset::*)(const ItemType&));
            CHECKTYPE(&Multiset::erase,      int  (Multiset::*)(const ItemType&));
            CHECKTYPE(&Multiset::eraseAll,   int  (Multiset::*)(const ItemType&));
            CHECKTYPE(&Multiset::contains,   bool (Multiset::*)(const ItemType&) const);
            CHECKTYPE(&Multiset::count,      int  (Multiset::*)(const ItemType&) const);
            CHECKTYPE(&Multiset::get,        int  (Multiset::*)(int, ItemType&) const);
            CHECKTYPE(&Multiset::swap,       void (Multiset::*)(Multiset&));
            CHECKTYPE(combine,  void (*)(const Multiset&, const Multiset&, Multiset&));
            CHECKTYPE(subtract, void (*)(const Multiset&, const Multiset&, Multiset&));
        }

        int main()
        {
        }