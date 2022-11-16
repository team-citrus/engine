# Transformation information

Did you like that unintentional rhyme?
Anyways, lets get to business.

Our transform coordinates use right handed X coordinates.
Unfortunately, Bullet uses left handed X coordinates, and box2d uses right handed X coordinates, fortunately, coordinate handedness only matters with rendering stuff, so that won't cause any issues.
Our transformation coordinates use pitch, yaw, roll formating.
Scale works like lens magnification, where negative values invert that axis.
