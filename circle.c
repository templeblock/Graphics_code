#include <stdio.h>
#include <graphics.h>

int main()
{
	int i,gd,gm,Xc,Yc,r,pk,x,y;
	gd=DETECT;


	printf("Enter The Center Xc,Yc and Raduis of Circle \n");
	scanf("%d%d%d",&Xc,&Yc,&r);
	initgraph(&gd,&gm,"");
	x=0;
	y=r;

	putpixel(Xc+x,Yc-y,1);

	pk=3-(2*r);

	for(x=0;x<=y;x++)
	{
		if(pk<0)
		{
			y=y;
			pk=pk+(4*x)+6;
		}
		else
		{
			y=y-1;
			pk=pk+4*(x-y)+10;
		}

		putpixel(Xc+x,Yc-y,1);
		putpixel(Xc-x,Yc-y,1);
		putpixel(Xc+x,Yc+y,1);
		putpixel(Xc-x,Yc+y,1);
		putpixel(Xc+y,Yc-x,1);
		putpixel(Xc-y,Yc-x,1);
		putpixel(Xc+y,Yc+x,1);
		putpixel(Xc-y,Yc+x,1);
		
		//delay();

	}
	delay(7000);


	return 0;
}
