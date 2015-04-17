#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
 
struct Node
{
    int x;
    int y;
    struct Node* next;
};
 
void fill (int pt[][2], int clr);
void floodfill4 (int x, int y, int oldclr, int newclr);
void insert (int x, int y, struct Node** last);
 
void main()
{
    int i, j;
    int pt[3][2];
    int clr;
 
    printf ("This program demonstrates filling a polygon.\n");
    printf ("Enter the x- and y-coordinates for three points:\n");
    for (i=0; i<3; i++)
	for (j=0; j<2; j++)
	    scanf ("%d", &pt[i][j]);
 
    printf ("Enter the fill-colour: (Any number from 1 to 14) ");
    scanf ("%d", &clr);
    fill (pt, clr);
}
 
void fill (int pt[][2], int clr)
{
    int gd = DETECT, gm;
    int seedx, seedy;
 
    initgraph (&gd, &gm, "..\\bgi");
 
    setcolor (WHITE);
    line (pt[0][0], pt[0][1], pt[1][0], pt[1][1]);
    line (pt[1][0], pt[1][1], pt[2][0], pt[2][1]);
    line (pt[2][0], pt[2][1], pt[0][0], pt[0][1]);
    getch();
 
    seedx = (pt[0][0] + pt[1][0] + pt[2][0]) / 3;
    seedy = (pt[0][1] + pt[1][1] + pt[2][1]) / 3;
 
    floodfill4 (seedx, seedy, BLACK, clr);
    getchar();
 
    closegraph();
    return;
}
 
void floodfill4 (int x, int y, int oldclr, int newclr)
{
    struct Node* first, *last, *tmp;
 
    first = (struct Node*) malloc (sizeof (struct Node));
    if (first == NULL)
    {
	closegraph();
	fprintf (stderr, "floodfill4: Out of memory.\n");
	exit (2);
    }
    if (oldclr == newclr)
    {
	free (first);
	return;
    }
 
    first->x = x;
    first->y = y;
    first->next = NULL;
    last = first;
 
    while (first != NULL)
    {
	putpixel (x, y, newclr);
 
	if (getpixel (x, y-1) == oldclr)
	{
	    putpixel (x, y-1, newclr);
	    insert (x, y-1, &last);
	}
 
 
	if (getpixel (x, y+1) == oldclr)
	{
	    putpixel (x, y+1, newclr);
	    insert (x, y+1, &last);
	}
 
	if (getpixel (x-1, y) == oldclr)
	{
	    putpixel (x-1, y, newclr);
	    insert (x-1, y, &last);
	}
 
	if (getpixel (x+1, y) == oldclr)
	{
	    putpixel (x+1, y, newclr);
	    insert (x+1, y, &last);
	}
 
	tmp = first;
	first = first->next;
	x = first->x;
	y = first->y;
	free (tmp);
    }
}
 
void insert (int x, int y, struct Node** last)
{
    struct Node* p;
    p = (struct Node*) malloc (sizeof (struct Node));
    if (p == NULL)
    {
	closegraph();
	fprintf (stderr, "\n insert: Out of memory.\n");
	exit (2);
    }
 
    p->x = x;
    p->y = y;
    p->next = NULL;
    (*last)->next = p;
    *last = (*last)->next;
}
