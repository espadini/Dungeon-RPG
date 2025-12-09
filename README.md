# ECE 312 - Lab 6 Write-Up

**Name:** Elijah Spadini
**EID:** ems5746  
**Date:** 12/8/2025

---

## 1. Design Decisions (3-4 sentences)

Briefly describe your key design choices and rationale:

- **Overall implementations:** How did you make use of object-oriented concepts in your decision?  Specifically, how did you use inheritance and polymorphism (if you did) and how did it help or complicate the design over using a language like C?  Draw a diagram showing the classes you used and their relationships to each other (subclass to superclass relationships specifically.) 

I leaned pretty heavily on Object-Oriented Programming (OOP) to avoid writing duplicate code. By using inheritance, I created base classes like Character and Item so that Player and Monster could share logic (like health and names), while Weapon and Potion could share basic item traits. The real MVP here was polymorphism; using virtual functions like calculateDamage() meant I could treat a Dragon exactly like a Goblin in the combat loop, but the Dragon would still automatically use its special fire damage math without me needing a bunch of messy if-else statements. If I had done this in C, I would have needed complex structs or unions and manual type checking for everything, which would have been a nightmare to debug.

        [Character]                       [Item]
             ^                               ^
             |                               | 
      +------+------+             +----------+----------+
      |             |             |          |          |
   [Player]     [Monster]      [Weapon]   [Armor]  [Consumable]
                    ^
                    |
           [Goblin/Dragon/etc]

    [Game]
       |
       +---> [Player]
       |
       +---> [Room]
               +---> [Monster]
               +---> [Item]

- **Memory management:** What strategy did you use to avoid leaks? Any particular challenges?

I used destructors to automate the cleanup—for example, when the Game ends, it deletes the Rooms, and when a Room is deleted, it deletes any Monster or Item inside it. The trickiest part was moving items around; when a player picks up a sword, I had to make sure to remove it from the room's vector without deleting the memory, effectively handing ownership over to the player so I didn't end up with a dangling pointer or a double-free crash.

---


## 2. Testing & Debugging (2-3 sentences)

Describe your testing process and any major bugs you encountered:

- **Testing approach:** What was your strategy beyond running `make test`?
My testing strategy beyond make test was implementing the testing functions in TODO.md and using the debugger in vscode.

- **Most difficult bug:** What was the hardest bug to find/fix and how did you solve it?
The hardest bug was inactivity/invalid white space when attacking. I was not sure what to do in that case.


---

## 3. Implementation Challenges (2-3 sentences)

Which TODOs were most challenging and why?

1. **Hardest TODO:** 
Combat was the hardest due to the extensive TODOs.

2. **Most time-consuming:** 
Combat again, for the same exact reason. The TODOs had many edge cases as well.

3. **Most interesting:** 
Player/Monster.cpp building the class hierarchy from the bottom up was super interesting and cool to see come together.

---


## 4. Reflection (1-2 sentences)

What was the most valuable lesson from this lab?
Starting early and utilizing little bits of time throughout the week goes a really long way.


---

## Submission Checklist

- [y] All functionality completed
- [y] `make test` passes with no failures
- [y] `make valgrind` shows no memory leaks
- [y] Game fully functional 
- [y] Code compiles without warnings (`-Wall -Wextra`)
- [y] This write-up completed
- [y] Optional Bonus attempted? (Yes/No): Yes (2 extensions for 10%)

