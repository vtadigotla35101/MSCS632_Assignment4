# MSCS632_Assignment4

Hello Professor,
I have chosen both Python & C++ as my 2 languages for developing a application that manages employee schedules at a company.

Explanation:
1.PYTHON: The Python code uses an Employee class to track individual work limits and shift preferences. It executes a two-pass scheduling algorithm:
a.Preference Pass: It iterates through each day and attempts to assign employees to their preferred shifts using conditionals to ensure no one works twice in a day or exceeds their weekly limit.
b.Gap-Filling Pass: It uses a while loop and randomization to identify shifts with fewer than two people and assigns available employees to fill those gaps.

The entire schedule is managed within nested dictionaries for easy lookup and formatted output, effectively demonstrating the use of complex data structures and branching logic to resolve scheduling conflicts.

2.C++:
The C++ implementation utilizes an Employee class and nested std::map containers to manage data with strict type safety. It follows a two-phase control flow: 
q.an initial for loop attempts to assign preferred shifts, followed by a while loop that uses randomized selection to meet the minimum staffing requirement of number of employees per shift. Conflict resolution is handled through branching logic that reassigns employees to alternative slots if their preferred shift has reached maximum capacity.


GITHUB Link: https://github.com/vtadigotla35101/MSCS632_Assignment4