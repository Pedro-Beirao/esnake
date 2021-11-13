--Loading colors
blue = Color.new(0,0,255)
shadow = Color.new(255,255,0,250)

--loading images
wall= Image.load("menu.png")

--Selector
selector = 1

--load fonts
font = Font.load("font.ttf")
font:setPixelSizes(25,25)

oldpad = Controls.read()

while true do
  screen:clear()
  pad = Controls.read()

  screen:blit(0,0,wall)

  if pad:down() and not oldpad:down() then selector = selector +1
  elseif pad:up() and not oldpad:up() then selector = selector -1
  end
   
  if selector < 1 then selector = 2 
  elseif selector > 2 then selector = 1 
  end 

  if selector == 1 then screen:fillRect(50,79,65,20,shadow) end
  if selector == 2 then screen:fillRect(50,99,73,20,shadow) end

  screen:fontPrint(font,55,100,"START",blue)
  screen:fontPrint(font,55,120,"EXIT",blue)

  if pad:cross() and not oldpad:cross() and selector == 1 then
    dofile("game.lua")
	file:close()
  end

  if pad:cross() and not oldpad:cross() and selector == 2 then
    System.Quit()
  end

  oldpad=pad
  screen.waitVblankStart()
  screen.flip()
  pad=nil
  
  end