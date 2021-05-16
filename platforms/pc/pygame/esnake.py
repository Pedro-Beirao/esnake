import os
import pygame
import threading
import sys
import random
import json
from playsound import playsound

grid_height=25
grid_width=25
gridsize=20

up = 0,-1
down = 0,1
left = -1,0
right = 1,0


positions = []
direction = right
length = 2
foodPos = ()
queue = [(1,0)]

highscore = 2

def reset():
        global length, positions,direction,score,highscore

        positions = [(5*gridsize, 5*gridsize)]
        direction = right
        score = 0
        scriptPath = os.path.dirname(os.path.abspath(__file__))
        if highscore < length:
            highscore=length
        with open(scriptPath+"/esnake.json","w") as writeTxt:
            json.dump(highscore, writeTxt)

        length = 2

def drawGrid(surface):
    for y in range(0, int(grid_height)):
        for x in range(0, int(grid_width)):
            if (x+y)%2 == 0:
                r = pygame.Rect((x*gridsize, y*gridsize), (gridsize,gridsize))
                pygame.draw.rect(surface,(50,50,50), r)
            else:
                rr = pygame.Rect((x*gridsize, y*gridsize), (gridsize,gridsize))
                pygame.draw.rect(surface, (70,70,70), rr)


def keys():
        global queue,direction
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN and len(queue)<3:
                try:
                    if event.key == pygame.K_w and direction!=down:
                        direction=up
                        queue+=[up]
                    elif event.key == pygame.K_s and direction!=up:
                        direction=down
                        queue+=[down]
                    elif event.key == pygame.K_a and direction!=right:
                        direction=left
                        queue+=[left]
                    elif event.key == pygame.K_d and direction!=left:
                        direction=right
                        queue+=[right]
                    elif event.key == pygame.K_ESCAPE :
                        pygame.quit()
                        sys.exit()
                except:
                    pass



def drawSnake(surface):
    firstPos=True
    for p in positions:
        if((p[0]==positions[0][0]) and (p[1]==positions[0][1]) and not firstPos):
                reset()
        sDraw = pygame.Rect((p[0], p[1]), (gridsize,gridsize))
        pygame.draw.rect(surface, (200,200,200), sDraw)
        firstPos=False




def move():
    global positions,direction,queue
    try:
            direction=queue[0]
            queue.pop(0)
    except:pass
    newPos = (positions[0][0]+direction[0]*gridsize,positions[0][1]+direction[1]*gridsize)
    positions.insert(0,newPos)
    if len(positions) > length:
                positions.pop()

    if positions[0][0]<0 or positions[0][0]>(grid_width-1)*gridsize or positions[0][1]<0 or positions[0][1]>(grid_height-1)*gridsize:
        reset()


def drawFood():
    fDraw = pygame.Rect((foodPos[0], foodPos[1]), (gridsize,gridsize))
    pygame.draw.rect(surface, (200,0,0), fDraw)

def randomFood():
    global foodPos
    foodPos = (random.randint(0, grid_width-1)*gridsize, random.randint(0, grid_height-1)*gridsize)


pygame.init()
  
scriptPath = os.path.dirname(os.path.abspath(__file__))

def playMusic():
    global isPlaying
    isPlaying=True
    try:
        playsound(scriptPath+'/midi.mp3')
        isPlaying=False
    except:
        try:
            playsound(scriptPath+'/midi.wav')
            isPlaying=False
        except:
            isPlaying=True

t = threading.Thread(target=playMusic)
t.daemon = True
t.start()

try:
    with open(scriptPath+"/esnake.json","r") as readTxt:
        highscore=json.load(readTxt)

except:
    pass
reset()
randomFood()
clock = pygame.time.Clock()
screen = pygame.display.set_mode((grid_width*gridsize, grid_height*gridsize), 0, 32)

surface = pygame.Surface(screen.get_size())
surface = surface.convert()
drawGrid(surface)

font = pygame.font.SysFont("monospace",30)



while (True):
        clock.tick(10)
        if isPlaying==False:
            t1 = threading.Thread(target=playMusic)
            t1.daemon = True
            t1.start()
        keys()
        move()
        for p in positions:
            if p == foodPos:
                length += 1
                randomFood()
        drawGrid(surface)
        drawFood()
        drawSnake(surface)
        screen.blit(surface, (0,0))
        text = font.render(str(length), 5, (200,200,200))
        screen.blit(text, (10,10))
        textHi = font.render(str(highscore), 5, (200,200,200))
        screen.blit(textHi, (10,35))
        pygame.display.update()
