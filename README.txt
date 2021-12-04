Hi! and welcome to my WaTor world;

I suppose you would like to get right into it.
My program includes:

-fish
	behave as described in specifications
	
-sharks
	behave as described in specifications
	
-rocks
	have an increasing,random chance to erode when age is past erodeMin
	
-volcanos
	moves like a rook in chess. has an increasing chance to move each turn until it moves
	has an increasing chance to spawn rocks each turn until it does.
	can spawn rocks in different amounts, ranges, and frequencies around it
	approaches doomsday, which fills most of the map with rocks
	
-Bottom Feeders
	feed off of nutrients from rocks
	when they find a rock, they stay there, and send out babies from their position
	
-whales
	swallow animals whole
	when a whale dies it spills its contents in the locations around it
	(it can die by beaching itself on a rock, or being hit with a rock/volcano)
	
	
SO here is what the template for a "wator.init" file should look like
a series of integers, representing:
*****
worldWidth worldHeight
fishNum fishBreed
sharkNum sharkStarve sharkBreed
bottomFeederNum bottomFeederStarve bottomFeederBreed
whaleNum whaleBreed whaleCannibal
rockNum rockErodeMin rockErodeMax
volcanoNum volcanoMoveFreq volcanoSpewFreq
volcanoSpewmagnitude volcanoSpewRange
volcanoDoomsdayDelay
********
heres what it looks like with actual numbers (also my recommendation):
*******
20 20
4 10
20 5 6
10 12 3
2 40 1
10 10 20
1  4 1  8 2  150
*********
now for an explanation of each variable:

worldWidth: sets the world width. (if num is less than 1, sets worldWidth to 1)
worldHeight: same as world width, but height

fishNum: sets the number of fish to spawn at the beginning
fishBreed: sets the fish breed cooldown

sharkNum: sets the number of sharks to spawn at the beginning
sharkStarve: sets the number of turns without food until a shark dies
sharkBreed: sets the shark breed cooldown

bottomFeederNum: sets the number of bottom feeders to spawn at the beginning
bottomFeederStarve: sets the number of turns without food until a bottom feeder dies
bottomFeederBreed: sets the bottom feeder breed cooldown

whaleNum: sets the number of whales to spawn at the beginning
whaleBreed: sets the whale breed cooldown
whaleCannibal: if is 1 lets whales swallow each other 
				(if you set this to 1 I can't guarantee this won't eventually run your program out of memory)
				if it is anything else but 1,whales are disabled from swallowing each other

rockNum: sets the number of rocks to spawn at the beginning
rockErodeMin: sets the minimum required age to erode
rockErodeMax: sets the maximum age to erode (the chance increases as it ages)
				i.e: % chance of erode = 1/(erodeMax - (erodeMin + age))
				
volcanoNum: sets the number of volcanos to spawn at the beginning
			(if doomsday is less than a very large number, multiple volcanos won't be too exciting)
volcanoMoveFreq: sets how frequently a volcano will move (higher is less frequent)

volcanoSpewFreq: sets how frequently a volcano will spew rocks (higher is less frequent)
volcanoSpewmagnitude: sets how many rocks a volcano can spawn
volcanoSpewRange: sets the taxicab range a volcano will spew rocks

volcanoDoomsdayDelay: sets the delay on doomsday (filling most of the map with rocks)


I strongly encourage you to just do bottom feeders and a volcano
bottom feeders are my favorite fish
I think whales would be cooler if this used an actual display and not CMD window
I hope you have fun!
-JS