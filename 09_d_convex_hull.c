#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { int x, y; } Point;
Point p0;

int compare(const void* a, const void* b) {
    Point *p1=(Point*)a, *p2=(Point*)b;
    int o=(p1->y-p0.y)*(p2->x-p0.x)-(p2->y-p0.y)*(p1->x-p0.x);
    if(o==0) return (hypot(p1->x-p0.x,p1->y-p0.y) >= hypot(p2->x-p0.x,p2->y-p0.y))?-1:1;
    return (o>0)?-1:1;
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y);
    if(val==0) return 0;
    return (val>0)?1:2;
}

void convexHull(Point pts[], int n) {
    int ymin=pts[0].y, min=0;
    for(int i=1;i<n;i++)
        if(pts[i].y<ymin||(pts[i].y==ymin&&pts[i].x<pts[min].x))
            ymin=pts[i].y, min=i;
    Point temp=pts[0]; pts[0]=pts[min]; pts[min]=temp;
    p0=pts[0];
    qsort(&pts[1], n-1, sizeof(Point), compare);
    Point stack[100]; int top=2;
    stack[0]=pts[0]; stack[1]=pts[1]; stack[2]=pts[2];
    for(int i=3;i<n;i++){
        while(orientation(stack[top-1],stack[top],pts[i])!=2) top--;
        stack[++top]=pts[i];
    }
    printf("Points in Convex Hull:\n");
    for(int i=0;i<=top;i++) printf("(%d, %d)\n",stack[i].x,stack[i].y);
}

int main(){
    int n;
    printf("Enter number of points: ");
    scanf("%d",&n);
    Point pts[n];
    printf("Enter coordinates (x y):\n");
    for(int i=0;i<n;i++) scanf("%d %d",&pts[i].x,&pts[i].y);
    convexHull(pts,n);
    return 0;
}