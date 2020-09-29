# LICENSE for this project #
Copyright 2020 Alex Darby / Gamer Camp (BCU) Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# overview #
This branch represents the result of an afternoon's messing about with the MODULE 1 branch sample game to try to push it firmly in the direction of space invaders.

There are a bunch of changes vs. the other framework branches:

- it registers collision handlers with IGCGameLayer::CollisionManager for all the game significant collisions 
- it also shows how to derive a class from CGCObjSpritePhysics which has no sprite and manages its own physics behaviour (CGCScreenBound) which replaces the by-hand static physcis bodies which form the screen bounds in the template games.
