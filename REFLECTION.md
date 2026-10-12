1. Why does concat only need to work between two lists of the same representation? What would you have to do
differently, or what would go wrong, if you tried to make it work between a LinkedList and an ArrayList?

concat reads the other list's private internals. ArrayList copies from its data_ array, and LinkedList splices 
on head_ and next, so neither can use the other type's layout. dynamic_cast check prints "Representation mismatch." 
if the types differ. To mix types, you would have to move elements one at a time through the public interface, which is 
slow because LinkedList::addBack walks the whole list. Or you would convert one list to the other's representation first,
which costs extra allocation.
   
2. Walk through reverse() on your linked list: name the three pointers you need alive at once, and explain why losing 
track of any one of them mid-loop corrupts the list.

The 3 pointers are prev, current, and next. next saves the rest of the list before current->next = prev flips the link.
Without it, the nodes after current become unreachable and leak. Without prev, current has nothing to point back to.
Without current, you lose your place in the loop. Afterward head_ = prev makes the old last node the new front. 
If you forgot that line, the list would look like it has one element.

3. addAnywhere and deleteAnywhere both need a bounds check. What’s the valid range for position in each, and what does 
your implementation do if a caller passes a position outside it? 

addAnywhere: valid positions are 0 to size_ inclusive, since size_ means append.
deleteAnywhere: valid positions are 0 to size_ - 1, because there must be an element to delete.

Outside those ranges, both print "Invalid position." and return without changing the list. That prevents dereferencing 
nullptr in LinkedList and out-of-range access in ArrayList.

4. In LinkedList::concat, why did you need to walk to the end of the list first, when addFront and deleteFront never 
needed to? What would change about concat’s performance if LinkedList still tracked a tail pointer, and what would you 
have to keep updated elsewhere if you added one back?

addFront and deleteFront only touch head_, which the list always has. concat has to attach to the last node, and 
without a tail pointer the only way to find it is to walk from head_, which is O(n). With a tail_ pointer, concat 
becomes O(1). You would then have to keep tail_ correct in:

addFront (when the list is empty)
addBack
addAnywhere (when adding at the end)
deleteFront (when the list becomes empty)
deleteAnywhere (when deleting the last node)
reverse (the old head becomes the tail)
concat

5. Pick either addAnywhere or deleteAnywhere in ArrayList and explain, in your own words, what has to shift and in 
which direction, and why shifting in the wrong direction would overwrite data you still need.

In addAnywhere, elements from position onward shift one slot right, and the loop runs from the back toward position.
Going front to back would overwrite data_[position + 1] before it was copied, and every later slot would end up 
holding the same pointer. The originals would leak, and the destructor would delete the same pointer repeatedly.

6. Point to the exact line in your main.cpp where a Reverse card actually changes the direction of play, and explain 
what would visibly break in the game if that call were missing.

It's table->reverse(); at line 79, in Step 3 of the Uno scene. It flips the list of players, so the turn order becomes 
Dave, Carol, Eve, Bob, Alice. Without it, the "Before" and "After" prints would be identical, so the Reverse card would 
visibly do nothing. Step 4 would also break: deleteAnywhere(3) assumes the reversed order, so it would remove Carol 
instead of Bob making the wrong person win the Uno game.
