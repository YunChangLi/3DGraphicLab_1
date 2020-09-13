#include <gl/GLUT.H>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

struct point {
	int x;
	int y;
};

void init();
void setpixel(int, int);
void storePoint(int, int);
void lineAlgorithm(point, int, int);
void circleAlgorithm(int, int, int);
void MyMouse(int, int, int, int);
void recover();
void keyboardFunc(unsigned char, int, int);



vector <point> list;
string caseCode = "00";
int lineCounter = 0;
int polygonCounter = 0;
point polygonBegin;
point circleCenter;

int main(int argc, char * argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(520, 520);
	glutCreateWindow("hello");
	init();
	glutKeyboardFunc(keyboardFunc);
	glutMainLoop();

	return 0;
}

void init() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluOrtho2D(0.0, 520, 0.0, 520);
	glPointSize(3.0);

	glColor3f(100.0, 150.0, 0.0);
	glFlush();
}

void setpixel(int x, int y)
{

	glBegin(GL_POINTS);/**start**/
	glVertex2i(x, y);
	glEnd();/**End**/
	glFlush();
	return;

}

void storePoint(int xx, int yy)
{
	point temp;
	temp.x = xx; temp.y = yy;
	list.push_back(temp);
	return;
}

void lineAlgorithm(point first, int xt, int yt)
{
	//cout << "x1 , y1 :" << first.x << " , " << first.y << endl;
	//cout << "x2 , y2 :" << xt << " , " << yt << endl;

	/**initial judge**/
	bool inverse = abs(yt - first.y) > abs(xt - first.x);


	if (inverse) {   //swap(x1 , y1) swap(x2 , y2)  //scope > 1 || scope < -1
		//cout << "123" << endl;
		int temp1 = 0;
		temp1 = first.x;
		first.x = first.y;
		first.y = temp1;

		temp1 = xt;
		xt = yt;
		yt = temp1;

	}
	if (first.x > xt) //swap(x1 , x2) swap(y1 , y2)
	{
		int temp2 = 0;
		temp2 = first.x;
		first.x = xt;
		xt = temp2;

		temp2 = first.y;
		first.y = yt;
		yt = temp2;
	}
	//cout << "x1 , y1 :" << first.x << " , " << first.y << endl;
	//cout << "x2 , y2 :" << xt << " , " << yt << endl;

	/**initial**/
	bool Yminus = first.y > yt;     //y1 < y2
	//cout << Yminus << endl;
	int x = first.x, y = first.y;
	int a = yt - y, b = x - xt;
	int d = 0;
	if (Yminus) { d = a - b / 2; }
	else { d = a + b / 2; }


	while (x <= xt) {   //x <= x2

		if (Yminus) {
			if (d >= 0) //choose E
			{

				x++;
				d += a;
			}
			else {      //SE(Yminus : 그쾤쨛⒀0)

				x++; y--;
				d += (a - b);  //SE(Yminus : 그쾤쨛⒀0)

			}
		}
		else {
			if (d <= 0) //choose E
			{

				x++;

				d += a;
			}
			else {      //choose NE 

				x++;  y++;
				d += (a + b);

			}
		}

		if (inverse) {
			setpixel(y, x);
			storePoint(y, x);
		}
		else {
			setpixel(x, y);
			storePoint(x, y);
		}
		
		//cout << "** " << x << " " << y << endl;

	}
	

	return;
}

void circleAlgorithm(int r, int centerX, int centerY) {

	int x = 0, y = r;  /**initial point -> (0 , r)**/
	int d = 1 - r;
	int incE = 2 * x + 3;   //equal to 3
	int incSE = 2 * (x - y) + 5;  //equal to (-2 * r + 5)

	while (x < y)
	{
		if (d < 0) {       //chooseE
			d += incE;
			incE += 2;
			incSE += 2;
			x++;
		}
		else {             //choose SE
			d += incSE;
			incE += 2;
			incSE += 4;
			x++;
			y--;
		}

		setpixel(x + centerX, y + centerY);
		setpixel(centerX - x, y + centerY);
		setpixel(x + centerX, centerY - y);
		setpixel(centerX - x, centerY - y);

		setpixel(y + centerX, x + centerY);
		setpixel(centerX - y, x + centerY);
		setpixel(y + centerX, centerY - x);
		setpixel(centerX - y, centerY - x);

		/**store**/
		storePoint(x + centerX, y + centerY);
		storePoint(centerX - x, y + centerY);
		storePoint(x + centerX, centerY - y);
		storePoint(centerX - x, centerY - y);

		storePoint(y + centerX, x + centerY);
		storePoint(centerX - y, x + centerY);
		storePoint(y + centerX, centerY - x);
		storePoint(centerX - y, centerY - x);

	}

	return;
}

void MyMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && caseCode != "00")
	{
		if (caseCode == "01") {
			setpixel(x, 520 - y);

			/**store the point**/
			storePoint(x, 520 - y);

			//cout << x << " " << 520 - y << endl;
		}
		else if (caseCode == "10") {
			setpixel(x, 520 - y);
			lineCounter++;
			//cout << "C" << lineCounter << endl;
			if (lineCounter == 2) {
				lineCounter = 0;
				//cout << "2. " << x << " " << 520 - y << endl;
				lineAlgorithm(list.back(), x, 520 - y);
			}
			else {
				storePoint(x, 520 - y);
				//cout << "1. " << x << " " << 520 - y << endl;

			}
		}
		else if (caseCode == "11") {
			setpixel(x, 520 - y);
			polygonCounter++;
			if (polygonCounter == 1) {
				polygonBegin.x = x;
				polygonBegin.y = 520 - y;
			}
			else {
				lineAlgorithm(list.back(), x, 520 - y);
			}
			storePoint(x, 520 - y);
		}
		else if (caseCode == "22") {
			//setpixel(x, 520 - y);
			//cout << "F . " << x << " " << 520 - y << endl;
			circleCenter.x = x; circleCenter.y = 520 - y;
		}

	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && caseCode != "00") {
		if (caseCode == "11") {
			polygonCounter = 0;
			lineAlgorithm(list.back(), polygonBegin.x, polygonBegin.y);
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && caseCode != "00") {
		if (caseCode == "22") {
			//cout << "S . " << x << " " << 520 - y << endl;
			/**calculate the radius**/
			int radius = sqrt(pow(x - circleCenter.x, 2) + pow(520 - y - circleCenter.y, 2));
			//cout << "R . " << radius << endl;
			circleAlgorithm(radius, circleCenter.x, circleCenter.y);
		}
	}
}
void recover()
{
	for (int i = 0; i < list.size(); i++) {
		setpixel(list[i].x, list[i].y);
	}

	return;
}


void keyboardFunc(unsigned char c, int x, int y)
{
	caseCode = "00";
	//cout << caseCode << endl;
	if (c == 'c') {  /**clear**/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // (or whatever buffer you want to clear)
		glFinish();

	}
	else if (c == 'd') {  /**point**/
		caseCode = "01";
		glutMouseFunc(MyMouse);

	}
	else if (c == 'l') {  /**line**/
		caseCode = "10";
		glutMouseFunc(MyMouse);
	}
	else if (c == 'p') {  /**polygon**/
		caseCode = "11";
		glutMouseFunc(MyMouse);
	}
	else if (c == 'o') {  /**circle**/
		caseCode = "22";
		glutMouseFunc(MyMouse);
	}
	else if (c == 'r') {  /**recovery**/
		recover();

	}
	else if (c == 'q') {  /**finish**/
		PostQuitMessage(0);
	}

}