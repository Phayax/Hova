# Hova
Just tinkering with some ideas.
Currently there is a rectangle that will follow your mouse. You can slow it down a bit by pressing space.

The target is to have a "spaceship" aka a rectangle that has a booster on the right and left bottom. These can be activated to fly with it.
The interesting part is that these boosters will exert a rotational force on the ship.
I want to try to find a solution on my own on how to animate this behaviour - Oh yeah gravity would be nice too...


----
## Controls

* Arrow Buttons increase the velocity in the respective direction.  
* A and T fire the Left and Right Thrusters (mounted on the bottom.) the cause a rotation as well as an impulse.  
To go left you first need to fire the right thruster to tilt the ship to the left. Then fire both to accelerate the ship to the left.  
(If you wonder about A and T that's what I get when i press F and J with my keyboard layout)
* You can enable three followMouse Methods:
  - `followMouse(Vector2i mpos)`  
very naive method that makes the ship follow the Mouse rather vaguely in circles
  - `followMouseLine(Vector2i mpos)`  
calculates the difference Vector and moves a part of it. Very quick but smooth motion since the ship slows down the closer it gets.
  - `followMouseThrusters(Vector2i mpos)`  
not finished yet. It's supposed to follow the Mouse not by moving the ship directly but by using the Thrusters. Will propably need some way prediction algorithm to already slow down in advance.


----
## Plans for more features
* fancier ship
* some background
* if i have way too much time some genetic machine learning for the `followMouseThrusters` method