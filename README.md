# the_little_snake_game

This is a small project I implemented to have some C++ code to show to interested employers.
I picked something simple that would be doable within a day and after that is usable. So I went for 
implementing snake. The project is easily extensible by creating a more sophisticated UI, improving the graphics or
add more walls, obstacles, etc.

I picked a game because I have never implemented something like that and I wanted to learn something
from this tiny project too. For the same reason I chose to use [nana](http://nanapro.org/en-us/) as the graphics library.
I have never worked with it before and I wanted to give it a try. 

I did not look up any online ressources on snake implementations. 
In a professional context, I would have done that first and probably I would have found a superior implementation of snake that can 
be taken as a basis. However, this code should show a very brief overview of what the code I write looks like.
Nevertheless, I was able to write this code within the time of a normal working day (although split over two days) 
and you can play a very rudimentary version of snake with it.

If you want to run the code, simply clone the nana repository into the nana folder at root level of the repo and 
then build the `snake` executable with CMake. I tested it on Ubuntu 18.04.

I added comments both for a docuemtation purpose as well to highlight certain shortcomings mostly in the OOP design.