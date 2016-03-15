<<<<<<< HEAD
Caltech CS2 Assignment 9: Othello

See [assignment9_part1.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part1.html) and [assignment9_part2.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part2.html)
=======
# othello
AI-based Othello player for CS2. Made by Cody Lim and Marc Muhleisen.
>>>>>>> 26fd049adbe1799b6119df6b451b5edb129346f0

Marc worked on initially setting up the Othello AI and minimax,
and Cody optimized the AI via the use of principal variation
search, an algorithm originally made for chess AIs that 
can outperform alpha-beta pruning.

Our group initially implemented alpha-beta pruning to improve on 
minimax. However, because our AI was slow and could not reach
depths to consistently beat some of the later AIs 
(i.e. BetterPlayer), we researched negamax algorithms on
Wikipedia, and eventually came across principal variation
search, whose pseudocode seemed applicable enough to an Othello
AI. We spent some time implementing principal variation search,
improving our heuristic, and playing around with depths, and
settled on our current heuristic with a principal variation
search to a depth of 3. We think principal variation search
will work because it will allow for our AI to accurately predict
moves to make to a fairly deep depth, while still being fairly
quick in its evaluations (depths >= 4 seemed to be much slower
without much of an increase in win rate, with depths >= 5
actually having a lower winrate while still being sluggish).
In our testing (n = 20), we were able to beat ConstantTimePlayer
70% of the time, and we were able to beat BetterPlayer 100% of
the time, with 44-20 being the final score each time.
