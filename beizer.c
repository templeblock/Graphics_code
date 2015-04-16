#include <stdio.h>
#include <graphics.h>
#include <math.h>


void beizer(int x[],int y[])
{
	int gd,gm;

	double i,x1,y1;

	gd=DETECT;
	initgraph(&gd,&gm,"");

	for(i=0.0;i<1.0;i+=0.00005)
	{
		x1=(x[0]*1*pow(1-i,4))+(x[1]*4*pow(i,1)*pow(1-i,3))+(x[2]*6*pow(i,2)*pow(1-i,2))+(x[3]*4*pow(i,3)*i)+(x[4]*1*pow(i,4));
		y1=(y[0]*1*pow(1-i,4))+(y[1]*4*pow(i,1)*pow(1-i,3))+(y[2]*6*pow(i,2)*pow(1-i,2))+(y[3]*4*pow(i,3)*i)+(y[4]*1*pow(i,4));
		putpixel(x1,y1,1);
	}

	//delay(50000);
}


int main()
{
	int x[5],y[5],i;
	for(i=0;i<5;i++)
		scanf("%d%d",&x[i],&y[i]);

	beizer(x,y);
	getchar();
	return 0;
}
