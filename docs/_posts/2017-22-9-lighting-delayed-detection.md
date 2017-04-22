---
layout: post
title:  "Enemy AI: delayed detection and lighting"
subtitle: "Did I see something?"
date:   2017-04-22 08:11:45
categories: [tool]
---

It takes a lot to make an interesting and challenging enemy AI. As of now, enemy detection is based on whether the player is
* in the enemy's view cone,
* in his line of sight, and
* if there's enough light falling on the player

Once the player is detected, enemy's state changes to ```AlertState::ALERT``` and if the player stays in view for a certain amount of time (I set it as 2s for now) player gets spotted.

I want to add sound based detection as well.

Also, the way the enemy viewcone is displayed is not intuitive now. I want it to be visible only when the enemy is in sight of the player. And ofcourse it should be limited to what's actually in sight. Now as you can see, the viewcone doesn't care about walls.

![Gameplay](http://i.imgur.com/XDpTGja.gif)

