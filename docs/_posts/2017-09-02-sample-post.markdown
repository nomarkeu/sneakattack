---
layout: post
title:  "Making a stealth game engine!"
subtitle: "Who goes there?!"
date:   2017-02-09 23:56:45
categories: [tool]
---

I love stealth games. Hitman: Silent Assassin would be my favourite in that genre. This engine is inspired by Mark of the Ninja, Hitman SA and the Thief series. I really like the inclusion of both auditory and visual cues in the Thief series, and also how something similar is done in MOTN. I'm imagining a game based on this engine to look like a Hitman game in topdown view and play like a hybrid of thief and mark of the ninja.

Oh and I'm writing this in C++. I decided to use Visual Studio after trying out Code::Blocks and CodeLite for and IDE. 
And after some looking around I decided to use SFML as a media library. SFML is a nice object oriented C++ wrapper for OpenGL. 


The first major hurdle was implementing a way to restrict visibility to what can be seen from the player's position. Here's the result.

![Realitime visibility](http://i.imgur.com/KD28NNo.gif)

It took some time to fix the bugs. But it works nicely as long as all lines are connected as polygons. Dangling line segments don't work. But that is OK because in the end the map can me constructed using strictly polygons.