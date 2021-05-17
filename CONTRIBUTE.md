# Contribute

If you wanna contribute to this project, there are a few guidelines you should follow, in order to make all the platforms at least similar

Some ports should have a little *plot twist*, nothing major just to spice it up a bit

## Guidelines

See the pygame and the ti-nspire ports for reference (These were the originals)
___
1. Draw the grid on the background: tile by tile (If system limitations prevent that, use a .png for example)

      Example from pygame:
      ```python3
      def drawGrid(surface):
          for y in range(0, int(grid_height)):
              for x in range(0, int(grid_width)):
                  if (x+y)%2 == 0:
                      r = pygame.Rect((x*gridsize, y*gridsize), (gridsize,gridsize))
                      pygame.draw.rect(surface,(50,50,50), r)
                  else:
                      rr = pygame.Rect((x*gridsize, y*gridsize), (gridsize,gridsize))
                      pygame.draw.rect(surface, (70,70,70), rr)
      ```
___
2. There must be a *queue* system that queues each input.
  
      If you press **up**, the snake goes up, but if you press **up** and **right** quickly, the snake will only go **right**
      
      A *queue* system will prevent this problem
     
___
3. The snake dies at the border.

      I know that the original wasnt like this, and that it is easy to implement, but this need to be consistent between ports
  ___    
  
4. It must show the current score and the highscore of the current session

      Storing the highscore in a .txt/.json file is reccomended but not a must
      
      ```python3
      if highscore < length:
            highscore=length
        with open(scriptPath+"/esnake.json","w") as writeTxt:
            json.dump(highscore, writeTxt)
      ```
5. Implementation of music/audio is recommended

      You you choose to implement audio, you can either include your own, or make it clear how to use our own.
      
      Using a *try* block is the obvious choice. 
      ```python3
      try:
        playsound('/midi.mp3')
      ```
      Try to include support for both .mp3 and .wav
      
      The name of the music should be midi.mp3 / midi.wav for consistency
