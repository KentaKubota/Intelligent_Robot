/* Define.h */
#define ON  1
#define OFF 0

#define NO_BALL 0                         
#define BLUE 1
#define YELLO 2
#define RED 3                                                                  

#define FREE_BALL   1
#define BALL_SEARCH 2
#define BALL_CATCH  3 
#define BALL_SHOOT  4
#define GO_HOME     5
#define TIMER       6

const float PI = 3.14159;
extern int cup;
extern float targetSpeed_r, targetSpeed_l;
extern float get_angle0, get_angle1;
extern float x0,y0,tht0;
extern float x1,y1,tht1;
extern float speed_r[100],speed_l[100]; /////
extern float timer;
