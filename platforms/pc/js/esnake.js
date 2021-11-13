grid_height=23
grid_width=33
gridsize=30

up = [0,-1]
down = [0,1]
left = [-1,0]
right = [1,0]

var positions = [[5*gridsize, 5*gridsize]];
var direction = right;
var lenght = 2;
var queue = [right];

var c = document.getElementById("Canvas");
var ctx = c.getContext("2d");

var firstTime = 1

var foodPos = [10*gridsize,10*gridsize]

function main()
{
    setTimeout(function onTick(){
        move();
        drawGrid();
        drawSnake();
        drawFood();
        if(firstTime==1)
        {
            firstTime=0;
            reset();
        }
        main();
    }, 100)
    
}


function drawGrid()
{
    for(y=0; y<grid_height; y++)
    {
        for(x=0; x<grid_width; x++)
        {
            if((x+y)%2 == 0)
            {
                ctx.beginPath();
                ctx.fillStyle = "#303030";
                ctx.fillRect(x*gridsize, y*gridsize, gridsize,gridsize);
                ctx.stroke();
            }
            else
            {
                ctx.beginPath();
                ctx.fillStyle = "#1f1f1f";
                ctx.fillRect(x*gridsize, y*gridsize, gridsize,gridsize);
                ctx.stroke();
            }
        }
    }
}

function sleep(milliseconds) {
    const date = Date.now();
    let currentDate = null;
    do {
      currentDate = Date.now();
    } while (currentDate - date < milliseconds);
  }

function drawSnake()
{
    for(i=0;i<positions.length;i++)
    {
        ctx.beginPath();
        ctx.fillStyle = "#cfcfcf";
        ctx.fillRect(positions[i][0],positions[i][1], gridsize,gridsize);
        ctx.stroke();

        if(positions[i][0]==positions[0][0] && positions[i][1]==positions[0][1] && i!=0)
        {
            reset();
        }
    }
}

function reset()
{
    direction = right;
    positions = [[5*gridsize, 5*gridsize]];
    lenght = 2;
    queue = [right];
}

function move()
{   
    if(queue.length>1)
    {
        queue.shift()
    }
    if(queue.length>3)
    {
        return
    }
    newPos = [positions[0][0]+queue[0][0]*gridsize, positions[0][1]+queue[0][1]*gridsize];
    positions.unshift(newPos)
    if(positions.length>lenght)
    {
        positions.pop()
    }
    if(positions[0][0]<0 || positions[0][0]>(grid_width-1)*gridsize || positions[0][1]<0 || positions[0][1]>(grid_height-1)*gridsize)
    {
        reset();
    }
    if(positions[0][0]==foodPos[0] && positions[0][1]==foodPos[1])
    {
        lenght+=1
        randomFood()
    }
}

var foodPos;

function drawFood()
{
    ctx.beginPath();
    ctx.fillStyle = "#f20707";
    ctx.fillRect(foodPos[0],foodPos[1], gridsize,gridsize);
    ctx.stroke();
}

function randomFood()
{
    ranint1 = Math.floor(Math.random() * grid_width)*gridsize;
    ranint2 = Math.floor(Math.random() * grid_height)*gridsize;
    foodPos = [ranint1, ranint2];
}

window.addEventListener("keydown", function (event) {
    if ((event.key == "ArrowUp" || event.key == "w" )&& direction!=down)
    {
        direction=up
        queue.push(up)
    }
    else if ((event.key == "ArrowDown" || event.key == "s")&& direction!=up)
    {
        direction=down
        queue.push(down)
    }
    else if ((event.key == "ArrowRight" || event.key == "d")&& direction!=left)
    {
        direction=right
        queue.push(right)
    }
    else if ((event.key == "ArrowLeft" || event.key == "a")&& direction!=right)
    {
        direction=left
        queue.push(left)
    }
  }, true);