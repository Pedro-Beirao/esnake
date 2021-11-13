grid_height=17
grid_width=30
gridsize=15

up = 0,-1
down = 0,1
left = -1,0
right = 1,0


positions = {}
direction = {}
lenght = 1
queue = {{}}

highscore = 1

gridImage1 = Image.load("grid.png")

snakeImage = Image.createEmpty(480, 272)
snakeImage:fillRect((0), (0), (gridsize),(gridsize), Color.new(250,250,250))

foodImage = Image.createEmpty(480, 272)
foodImage:fillRect((0), (0), (gridsize),(gridsize), Color.new(250,0,0))

function drawGrid()
  screen:blit((0), (0), gridImage1)
end


function drawSnake()
  for p=1,table.maxn(positions),1
  do
      if((positions[p][1]==positions[1][1]) and (positions[p][2]==positions[1][2]) and p~=1 and p~=2 and p~=3)
      then
                  print("lol")
                  resetGame()

      elseif(positions[p][1]==foodPos[1] and positions[p][2]==foodPos[2])
      then
                    lenght =lenght +1
                    randomizeFood()
      end
      screen:blit(positions[p][1], positions[p][2], snakeImage)
      
  end
end

function resetGame()
  positions = {{60,60},{45,60}}
  direction = {1,0}
  lenght = 2
  queue = {{1,0}}
end

function thereIsTwo()
  if(queue[2]~=nill)
  then
      table.remove(queue,1)
  end
end

function move()
  pcall(thereIsTwo)
  current = positions[1]
  x=queue[1][1]
  y=queue[1][2]
  new = {((current[1]+(x*gridsize))), (current[2]+(y*gridsize))}
  if(new[1]~=positions[2][1] or new[2]~=positions[2][2])
  then
      table.insert(positions,1,new)
      if(new[1]>grid_width*gridsize or new[1]<0 or new[2]>grid_height*gridsize or new[2]<0)
      then
          resetGame()
      elseif(table.maxn(positions)>lenght)
      then
          table.remove(positions, table.maxn(positions))
      end
      if(table.maxn(queue)>1)
      then
          table.remove(queue,1)
      end
  end
end

function controls()
  if(table.maxn(queue)<5)
  then
      if((Controls.read():up() or Controls.read():analogY()<-100) and direction[2]== 0)
      then
              direction={0,-1}
              table.insert(queue,table.maxn(queue)+1,{0,-1})
              table.remove( queue,1)
      end
      if((Controls.read():down() or Controls.read():analogY()>100) and direction[2]== 0)
      then
              direction={0,1}
              table.insert(queue,table.maxn(queue)+1,{0,1})
              
      end
      if((Controls.read():left() or Controls.read():analogX()<-100) and direction[1]== 0)
      then
              direction={-1,0}
              table.insert(queue,table.maxn(queue)+1,{-1,0})
      end
      if((Controls.read():right() or Controls.read():analogX()>100) and direction[1]== 0)
      then
              direction={1,0}
              table.insert(queue,table.maxn(queue)+1,{1,0})
      end
  end
end

function randomizeFood()
  foodX = math.random(0,18)
  foodY = math.random(0,13)
  foodPos = {foodX*15,foodY*15}
end

function drawFood()
      screen:blit(foodPos[1], foodPos[2], foodImage)
end

timer = Timer.new()
timer:start()
resetGame()
randomizeFood()
System.setCpuSpeed(333)

while true do
  controls()
  System.showFPS() 
  if timer:time() >=100
  then
    move()
    System.draw()
    screen:clear()
    drawGrid()
    drawFood()
    drawSnake()
    System.endDraw()
    screen.waitVblankStart()
    screen.flip()
    timer:reset()
    timer:start()
  end 
end