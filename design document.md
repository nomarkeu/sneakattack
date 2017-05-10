Map generation
	draw walls first
		render
	put in doors

if you want to connect to a line, press c
	then start point will be the closest point on a nearby line. and will stay attached to that line, until pulled away.

Draw a rectangle first.

1. Implememnt stopping auto connection and starting new line

2. Implement attaching to closeby line
	1. attache when scroll wheel is clicked any way


if (!draw && mousewheel is clicked)
	search for line closeby within 100 distance;
	if 


slope = x2>x1? y2-y1/x2-x1 : y1-y2/x1-x2;

assert(slope!=0.f)
	slope2 = -1.f/slope;
y1=mx1+c

c= y1-mx1

y = mx + y1-mx1
y-y1= m(x-x1)
Or
mx-y+(y1-mx1)=0


|(mx-y+(y1-mx1)|/(m*m+1)

x=c;
x-c=0;

-----------------------
after finding attach point, move the attach point along the lines as mouse pointer moves.

x1,y1	x2, y2
	mx, my

x0 = mx
y0 = y
x0 =x
y0 = my

a---------------- d----------------b

                 .p



ap.ab/ab

ap = mx-x1, my-y1
ab = x2-x1, y2-y1 

|ab| = sqrt( (y2-y1)^2 + (x2-x1)^2)


d/|ab| = ap.ab/|ab|^2 = ((mx-x1)*(x2-x1) + (my-y1)*(y2-y1))/ ( (y2-y1)^2 + (x2-x1)^2)

x0 = (d/|ab|)*(x2-x1) + x1

y0 = d/|ab|*(y2-y1) + y1

-----------------------------------------------------------
Collision
-Shouldn't move across lines.

two height levels for visibility.

Visibility, three coincident points - fix - incorrect sorting of segments
--
finish all types of floor tiles
--------------------------------
finish player
-----------------------------
check visibility displaying only visible floor
-----------------------------
do wall collision
--------------------


------------------------
wall tiles - 1-14



-- enemy visibility obstacles

----------------------------------
Effective C++
- always use explicit constructors unless explicitly necessary
- generally bad idea to pass user defined types by value - use pass by reference to const
- make class specific contants static
- in-class initialisation is only allowed for integral types and only for constants
- conceptual constness?



Implement sound visually

