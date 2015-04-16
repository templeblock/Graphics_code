#include <stdio.h>
#include <graphics.h>

#define L 0x1
#define R 0x2
#define B 0x4
#define A 0x8

#define accept(a,b) (!(a|b))
#define reject(a,b)	(a & b)
#define inside(a) (!a)
#define round(a) ((int)(a+0.5))

unsigned char encode (int x, int y, int x_min, int x_max, int y_min, int y_max)
{
	unsigned char code=0x00;
	if(x<x_min)
		code=code|L;
	if(x>x_max)
		code=code|R;
	if(y>y_max)
		code=code|A;
	if(y<y_min)
		code=code|B;

	//printf("Code=%c\n",code);
	return code;
}

void swap_code(char *a,char *b)
{
	unsigned char temp;
	temp=*a;
	*a=*b;
	*b=temp;
	//printf("In Swap Code\n");
}

void swap_pt(int *x1,int *y1,int *x2,int *y2)
{
	int temp,temp1;
	temp=*x1;
	*x1=*x2;
	*x2=temp;
//	printf("Before Swap y1=%d & y2=%d\n",*y1,*y2);
	temp1=*y1;
	*y1=*y2;
	*y2=temp1;
	//printf("In Swap Point\n");
//	printf("\nSwap x1=%d y1=%d\n",*x1,*y1);
}

void clipping(int x_min,int y_min,int x_max,int y_max,int x1,int y1,int x2,int y2)
{
	unsigned char code1,code2;
	int done=0,draw=0;

	float m;

	while(!done)
	{
		//printf("In while\n");
		code1=encode(x1,y1,x_min,x_max,y_min,y_max);
		code2=encode(x2,y2,x_min,x_max,y_min,y_max);
		//printf("%d\n",code1 );
		//printf("%d\n",code2 );
		if(accept(code1,code2)) {
			done=1;
			draw=1;
			//printf("In Accept\n");
		}
		else
			if(reject(code1,code2))
			{
				done=1;
				//printf("In Reject\n");
			}
			else
			{
				if(inside(code1)){
					swap_pt(&x1,&y1,&x2,&y2);
					swap_code(&code1,&code2);
				}
				if (x2!=x1)
				{
					m=((float)y2-y1)/(x2-x1);
					printf("m=%f\n",m);
				}
				if(code1 & L){
					y1+=(m*(x_min-x1));
					x1=x_min;
//					printf("code & L x1=%d  y1=%d",x1,y1);
				}
				else
					if(code1 & R) {
//						printf("x1=%d y1=%d\n",x1,y1);
						y1=y1+(m*(x_max-x1));
						x1=x_max;
//						printf("code & R x1=%d  y1=%d",x1,y1);		
					} 
					else
						if(code1 & B) {
							if(x2!=x1) {
								x1=x1+((y_min-y1)/m);
								y1=y_min;
							}
						}
						else
							if (code1 & A)
							{
								if(x2!=x1){
									x1=x1+((y_max-y1)/m);
									y1=y_max;
								}
							}
			}
	}
	if(draw)
	{
		//printf("Draw\n");
//		printf("%d %d %d %d",x1,x2,y1,y2);
		line(round(x1),round(y1),round(x2),round(y2));
	}
}



int main()
{
	/* code */
	int gd,gm;
	int x_min,x_max,y_min,y_max,x1,y1,x2,y2;
	gd=DETECT;
	printf("Enter the Co-ordinates of clipping Window\n");
	scanf("%d%d%d%d",&x_min,&y_min,&x_max,&y_max);

	initgraph(&gd,&gm,"");

	line(x_min,y_min,x_max,y_min);
	line(x_max,y_min,x_max,y_max);
	line(x_min,y_min,x_min,y_max);
	line(x_min,y_max,x_max,y_max);

	line(80,120,220,180);
	line(220,180,180,250);
	line(180,250,150,50);

	delay(3000);

	cleardevice();

	line(x_min,y_min,x_max,y_min);
	line(x_max,y_min,x_max,y_max);
	line(x_min,y_min,x_min,y_max);
	line(x_min,y_max,x_max,y_max);



	clipping(x_min,y_min,x_max,y_max,80,120,220,180);
	delay(1000);
	clipping(x_min,y_min,x_max,y_max,220,180,180,250);
	delay(1000);
	clipping(x_min,y_min,x_max,y_max,180,250,150,50);

	getch();
	return 0;
}
