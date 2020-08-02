---
driveId: 1Q5Mek8IZv9vCZ0b_FnVbA-8NURUwOTYe/preview
---

## Code Review

{% include googleDrivePlayer.html id=page.driveId %}

## [Enhancement One: Software Design and Engineering](EnhancementOne/BidDatabase)


This artifact is a C++ project from my Data Structures class back in my third term of 2019. It is a part of a collection of programs I created for my final project, all of which had similar functionality, but used different data types and algorithms. This specific code reads a .csv file full of data on different bids and adds them to a binary search tree. Once the tree is populated, the user can display all the bids, search for a bid, or remove a bid based on the bid ID. 

I selected this item for several reasons: it had clear room for improvement, it is written in my favorite/most familiar language, and I could find a way to add on to it that would showcase critical skills. Even at first glance the code is very disorganized, so I knew immediately that organizing it into separate class files would be a great way to showcase my ability to create a clean and organized project. Since I have worked with C++ the most, I have more insight into proper procedures such as naming conventions and class structure, making it easier to ensure I follow general coding standards. Lastly, its existing functionality is very limited, so there is plenty of space for improvement. A program that only performs four basic functions and tests their efficiency is not particularly useful outside of a classroom, but it can easily be transformed into a data storage system with a real practical use. 

So far, I have accomplished what I planned to with this enhancement in terms of CS-499-04 in following industry-standard organization and techniques. I have also realized how much security is compromised even with a simple program like this – whenever user input is being read, the program is at risk. Because of this, I have attempted to sanitize any user inputs I read in order to accomplish course outcome CS-499-05.

While I worked on this artifact, I learned how much work it is to refactor code, even a small and simple program like this. I did not expect it to take very long, but I ended up spending several hours testing and modifying it. One of the first challenges I faced was new errors when moving IDEs. This original code was done in Eclipse, but I decided to use Visual Studio since I am more comfortable with it. After creating a new project and pasting the code in, I had to explicitly include new libraries (vector and string) as well as modify my project settings to ensure VS could find the csv parser. Splitting the code into classes was fairly straightforward, but I ran into issues again when working in main(). 

As I said before, I had not realized all the security implications that had to be considered in terms of user input. I often found myself pausing to think through all the potential inputs I had to check for and considering how I would restrict each field. For example, what should the maximum amount of characters for a bid’s title be? How do I ensure a number is entered for the amount? Since I created a new “Add Bid” option, I would have to sanitize every input made when creating a new bid. My biggest struggle was validating that the amount was entered as a number. I could check for non-numeric inputs, but if the user entered a mix of numbers and letters, it could leave characters stuck in the stream. Eventually I decided to read the input as a string, validate it, then convert it to a double. I tried to remain very security-conscious, something I have never really done with a small command-line program like this, and I am very proud of the results so far.
