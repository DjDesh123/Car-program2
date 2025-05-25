# Car-program2

---

## Introduction
This is a refactoring of my first big C program that I have done in my first year of university. After evaluating this project I realsied I used fairly simple concepts and less effective solutions to my code like not using dynamic memeory allocation and decidng to only handle situations in stack memory. While my original attempt of this project can function i realsiedf that it can be done more effectively and efficently which is a main part of programming that I want to learn and create.

---
## difficulties and solutions
Early in development, I focused on file handling before establishing core logic, which made testing and struct integration difficult. I revised my approach to first build and validate the main system, then reintroduced file operations. I also replaced platform-specific batch/bash scripts with C-based file initialization using #ifdef for cross-platform support. My current focus is implementing a rotating .dat backup system with recovery fallback, and exploring JSON export/import of struct arrays for future compatibility and readability improvements.


## changes of plans
instead of using shell scripts just kepeing it all in c and creating a bootstrap 


## how to run
-to write up later



copy inventory file and put the info in the backup file thrn a backup is created.

then the backup system is incorpersted just beed to add it.


need a way of only being updated by the most recent backup stste if the main file fails whcih wilk be workimg on.

added a new edge case conceot that i recentlyh learned about 

needs to commit all the changes to file handling section of the program



